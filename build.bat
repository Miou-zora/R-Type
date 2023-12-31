@echo off
setlocal

rem Set some environment variables
set VCPKG_PATH=.\vcpkg
set VCPKG_EXE=%VCPKG_PATH%\vcpkg.exe
set VCPKG_TRIPLET=x64-windows-static
set "VCPKG_TOOLCHAIN=%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake"

set "VCPKG_TAG=2023.08.09"
set "VCPKG_URL=https://github.com/microsoft/vcpkg/archive/refs/tags/%VCPKG_TAG%.zip"

set "BUILD_DIR=.\build"

if exist %VCPKG_PATH% (
    echo VCPKG found, building
    rem Use fetched vcpkg to install needed packages
    echo "Installing packages"
    %VCPKG_EXE% install --triplet %VCPKG_TRIPLET% --feature-flags=manifests raylib boost-core boost-asio boost-crc boost-thread boost-uuid boost-system boost-filesystem gtest cmakerc zstd

    rem Build the project using cmake
    cmake -S . -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN% -DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET% -DCMAKE_BUILD_TYPE=Release

    rem Build the project using builded cmake cache
    cmake --build %BUILD_DIR% --config Release
    echo Build finished
) else (
    echo VCPKG not found, installing

    rem Download vcpkg from github repo using CURL
    curl -L %VCPKG_URL% -o vcpkg.zip

    if %ERRORLEVEL% NEQ 0 (
        echo Failed to download vcpkg, exiting
        exit /b 1
    )

    rem Extract vcpkg
    tar -xf vcpkg.zip

    rem Delete vcpkg.zip
    del vcpkg.zip

    rem Rename vcpkg-version to vcpkg
    for /d %%i in (vcpkg-*) do ren "%%i" vcpkg

    rem Bootstrap vcpkg
    cd vcpkg
    bootstrap-vcpkg.bat
    rem if path exist and exe exist
    if exist %VCPKG_EXE% (
        echo VCPKG installation successful
        rem Use fetched vcpkg to install needed packages
        echo "Installing packages"
        %VCPKG_EXE% install --triplet %VCPKG_TRIPLET% --feature-flags=manifests raylib boost-core boost-asio boost-crc boost-thread boost-uuid boost-system boost-filesystem gtest cmakerc zstd

        rem Build the project using cmake
        cmake -S . -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN% -DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET% -DCMAKE_BUILD_TYPE=Release

        rem Build the project using builded cmake cache
        cmake --build %BUILD_DIR% --config Release
        echo Build finished
    ) else (
        echo VCPKG installation failed, exiting
        exit /b 1
    )
)
