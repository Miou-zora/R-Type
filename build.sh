#!/bin/bash

# Set some environment variables
VCPKG_PATH="./vcpkg"
VCPKG_EXE="${VCPKG_PATH}/vcpkg"
VCPKG_TRIPLET="x64-linux"
VCPKG_TOOLCHAIN="${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake"

VCPKG_TAG="2023.08.09"
VCPKG_URL="https://github.com/microsoft/vcpkg/archive/refs/tags/${VCPKG_TAG}.zip"

BUILD_DIR="./build"

# Check if vcpkg dependencies (curl, zip, unzip, tar) are installed using which
which curl zip unzip tar > /dev/null
if [ $? -eq 0 ]; then
    echo "VCPKG dependencies found"
else
    echo "VCPKG dependencies not found, installing"

    if [ -e /etc/os-release ]; then
        source /etc/os-release

        if [[ $NAME == *"Fedora"* ]]; then
            sudo dnf install curl zip unzip tar
        elif [[ $NAME == *"CentOS"* ]]; then
            sudo yum install curl zip unzip tar
        elif [[ $NAME == *"Ubuntu"* ]]; then
            sudo apt-get install curl zip unzip tar
        else
            echo "Unknown Linux distribution"
            exit 1
        fi
    else
        echo "Unable to detect Linux distribution"
        exit 1
    fi
fi

if [ -d "$VCPKG_PATH" ]; then
    echo "VCPKG found, building"
else
    echo "VCPKG not found, installing"

    # Download vcpkg from github repo using CURL
    curl -L "$VCPKG_URL" -o vcpkg.zip

    if [ $? -ne 0 ]; then
        echo "Failed to download vcpkg, exiting"
        exit 1
    fi

    # Extract vcpkg
    unzip vcpkg.zip

    # Delete vcpkg.zip
    rm vcpkg.zip

    # Rename vcpkg-version to vcpkg
    mv "vcpkg-${VCPKG_TAG}" vcpkg

    # Bootstrap vcpkg
    cd vcpkg || exit
    ./bootstrap-vcpkg.sh
    # Return to the original directory
    cd ..

    if [ -x "$VCPKG_EXE" ]; then
        echo "VCPKG installation successful"
    else
        echo "VCPKG installation failed, exiting"
        exit 1
    fi
fi

# Use fetched vcpkg to install needed packages
"${VCPKG_EXE}" install --triplet "${VCPKG_TRIPLET}" --feature-flags=manifests raylib boost-core boost-asio boost-thread boost-system boost-filesystem gtest

# Build the project using cmake
cmake -S . -B "${BUILD_DIR}" -DCMAKE_TOOLCHAIN_FILE="${VCPKG_TOOLCHAIN}" -DVCPKG_TARGET_TRIPLET="${VCPKG_TRIPLET}" -DCMAKE_BUILD_TYPE=Release

# Build the project using built cmake cache
cmake --build "${BUILD_DIR}" --config Release
