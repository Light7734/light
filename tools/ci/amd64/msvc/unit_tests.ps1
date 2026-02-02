# @ref https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category

# @todo(Light): fetch path and uuid from environment
Import-Module 'C:\Program Files\Microsoft Visual Studio\18\Enterprise\Common7\Tools\Microsoft.VisualStudio.DevShell.dll'
Enter-VsDevShell 1a3e2aa7 -SkipAutomaticLocation -DevCmdArguments '-arch=x64 -host_arch=x64'

if (Test-Path "./build") {
    Remove-Item "./build" -r -force
}

cmake `
    -S . `
    -B build `
    -G Ninja `
    -D ENABLE_UNIT_TESTS=ON `
    -D CMAKE_BUILD_TYPE=Debug `
    -D CMAKE_EXPORT_COMPILE_COMMANDS=True `
    -D CMAKE_CXX_FLAGS="/std:c++latest /EHsc /Zi /Oy- /WX /W4"

cmake --build ./build

$tests = Get-ChildItem -Path "./build" -Recurse -File | Where-Object {
    $_.Name -like "*_tests.exe"
}

foreach ($test in $tests) {
    Write-Host ""
    Write-Host "| $($test.BaseName) |"
    & $test.FullName
    if ($LASTEXITCODE -ne 0) {
      Write-Error "Test $($test.Name) failed! T_T"
        exit $LASTEXITCODE
    }
}

