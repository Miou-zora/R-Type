# R-Type

## How to build

### Linux

#### Requirements

- g++
- make
- cmake

Install them with the following command if needed :

```bash
sudo apt install g++ make cmake
```

For WSL users : some desktop system librairies are required. They are usually installed with the desktop environments on many Linux distributions which is not the case on WSL. You can install them with the following command :

```bash
sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
```

#### Build

The build script will automatically install the dependencies using vcpkg and build the project. Vcpkg will be installed in the project directory.

```bash
./build.sh
```

### Windows

#### Requirements

MSVC Build Tools are required. We recommend to install them along Visual Studio 2022.
<br>
See [this page](https://visualstudio.microsoft.com/fr/downloads/) for download links.
<br>
You will also need to run the command in the Developer Command Prompt for VS.

#### Build

The build script will automatically install the dependencies using vcpkg and build the project. Vcpkg will be installed in the project directory.

```cmd
.\build.bat
```

## How to run

Executables will be compiled at the root of the project directory, unter the names `rtype_server` and `rtype_client` (+ `.exe` on Windows). You can run them simply by running the executables.

