import re
import pathlib
import sys
import argparse
from collections import defaultdict

# Convert PascalCase to snake_case
import re

def to_snake_case(name):
    # Skip if ALL CAPS (macros)
    if name.isupper():
        return name.lower()  # or just return name if you want to keep macros fully uppercase
    
    # Step 1: Split acronyms followed by normal PascalCase words (APIClient → API_Client)
    name = re.sub(r'([A-Z]+)([A-Z][a-z])', r'\1_\2', name)

    # Step 2: Split lowercase/digit to uppercase (fooBar → foo_Bar)
    name = re.sub(r'(?<=[a-z0-9])(?=[A-Z])', '_', name)

    # Step 3: Split letter-digit transitions only if digit is followed by uppercase letter  
    name = re.sub(r'(?<=[a-zA-Z])(?=[0-9][A-Z])', '_', name)

    # Step 4: Split digit-letter transitions (RGBA32Float → RGBA_32_Float)
    name = re.sub(r'(?<=[0-9])(?=[a-zA-Z])', '_', name)

    # Step 5: Fix accidental splits like '_2_D' → '_2d'
    name = re.sub(r'_(\d+)_([a-z])', r'_\1\2', name, flags=re.IGNORECASE)

    return name.lower()

# Get all .cpp/.h/.hpp/.c files in the project (excluding vendor/third-party folders)
def get_source_files(root_dir):
    skip_dirs = {"vendor", "external", "third_party", "Dependencies", "build"}
    for path in pathlib.Path(root_dir).rglob("*"):
        if path.suffix.lower() in {".cpp", ".h", ".hpp", ".c"}:
            if not any(part in skip_dirs for part in path.parts):
                yield path

# Extract PascalCase function names from definitions
def extract_pascal_functions(code):
    # Collect all class/struct names
    class_names = set(re.findall(r'\b(class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)', code))
    class_names = {name for _, name in class_names}

    # Match PascalCase function names, not prefixed with ~
    candidates = re.findall(r'\b(?:[A-Za-z_][\w:<>]*)\s+([A-Z][A-Za-z0-9_]*)\s*\(', code)

    valid_funcs = set()
    for name in candidates:
        if name.startswith("~"):
            continue  # Skip destructors
        if name in class_names:
            continue  # Skip constructors
        valid_funcs.add(name)

    return valid_funcs

# Rename function names in content
def rename_usages(content, rename_map):
    for original, replacement in rename_map.items():
        # Word-boundary replace: only full function names (not part of other identifiers)
        content = re.sub(rf'\b{original}\b', replacement, content)
    return content

def main():
    parser = argparse.ArgumentParser(description="Rename project-defined PascalCase functions to snake_case")
    parser.add_argument("project_dir", help="Path to project root")
    parser.add_argument("--apply", action="store_true", help="Actually modify files")
    args = parser.parse_args()

    project_dir = args.project_dir
    defined_functions = set()

    print("[+] Scanning for function definitions...")
    # First pass: collect function definitions
    for file_path in get_source_files(project_dir):
        try:
            text = file_path.read_text(encoding='utf-8')
            matches = extract_pascal_functions(text)
            for name in matches:
                if name.isidentifier() and not name.startswith("ImGui"):  # crude 3rd-party filter
                    defined_functions.add(name)
        except Exception as e:
            print(f"[!] Error reading {file_path}: {e}")

    if not defined_functions:
        print("[-] No PascalCase function definitions found.")
        return

    rename_map = {name: to_snake_case(name) for name in defined_functions if name != to_snake_case(name)}

    print(f"[+] Found {len(rename_map)} functions to rename:")
    for orig, snake in rename_map.items():
        print(f"    {orig} → {snake}")

    if not args.apply:
        print("\n[DRY RUN] No files will be modified. Use --apply to perform renaming.\n")

    # Second pass: apply renaming
    for file_path in get_source_files(project_dir):
        try:
            content = file_path.read_text(encoding='utf-8')
            new_content = rename_usages(content, rename_map)
            if new_content != content:
                print(f"[~] Updating {file_path}")
                if args.apply:
                    file_path.write_text(new_content, encoding='utf-8')
        except Exception as e:
            print(f"[!] Error processing {file_path}: {e}")

if __name__ == "__main__":
    main()
