from git import Repo
import re

repo = Repo(search_parent_directories=True)
assert not repo.bare

file_path = "generated/changelog.rst"

messages = []
short_shas = []
hex_shas = []
logs = []

remote_url = "https://git.light7734.com/light7734/light/commit"
def format_log(commit_type, message, major, minor, patch, short_sha, hex_sha):
    href = f"{remote_url}/{hex_sha}"
    version = f"{major}.{minor}.{patch}-kitten+{short_sha}";
    link = f"`{version} <{remote_url}/{hex_sha}>`__"
    return f"| **{message}** ({link})"

for commit in repo.iter_commits():
    messages.append(commit.summary)
    short_shas.append(repo.git.rev_parse(commit.hexsha, short=5))
    hex_shas.append(commit.hexsha)

ver_major = 0
ver_minor = 0
ver_patch = 0

idx = len(messages)
for message in reversed(messages):
    idx = idx - 1;

    commit_type = re.match("^(feat|fix|refactor|perf|build|asset|test|chore|ci|docs)", message)
    if not commit_type:
        continue

    match commit_type.group(0):
        case "feat":
            ver_minor = ver_minor + 1
            ver_patch = 0

        case "fix":
            ver_patch = ver_patch + 1

        case "refactor":
            ver_patch = ver_patch + 1

        case "perf":
            ver_patch = ver_patch + 1

        case "build":
            ver_patch = ver_patch + 1

        case "asset":
            ver_patch = ver_patch + 1

    logs.append(format_log(commit_type, message, ver_major, ver_minor, ver_patch, short_shas[idx], hex_shas[idx]))

with open(file_path, "w") as f:
    f.write(".. changelogs\n\n\n")
    f.write(".. include:: ../.special.rst\n\n\n")
    f.write("Changelogs\n")
    f.write("==================================================\n\n")

    f.write("KITTEN\n")
    f.write("--------------------------------------------------\n\n")
    for log in reversed(logs):
          f.write(log + '\n')
