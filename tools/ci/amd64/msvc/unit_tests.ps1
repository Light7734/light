conan profile detect
conan build . -s compiler.cppstd=20 -s build_type=Release

$tests = Get-ChildItem -Path "./build" -Recurse -File | Where-Object {
    $_.Name -like "*_tests.exe"
}

foreach ($test in $tests) {
    Write-Host "Running $($test.FullName)"
    & $test.FullName
    if ($LASTEXITCODE -ne 0) {
      Write-Error "Test $($test.Name) failed! T_T"
        exit $LASTEXITCODE
    }
}

