# R-Type
![272206977-5cbffad1-884d-4164-9742-152b58a0c3e9](https://github.com/Miou-zora/R-Type/assets/91665686/bebc54cd-92d3-4f7d-aa4d-1e9d2adc9f26)

[R-Type](https://fr.wikipedia.org/wiki/R-Type_(jeu_vid%C3%A9o)) is a classic side-scrolling shoot 'em up video game with a cooperative multiplayer feature. In this game, players can team up with a friend to control small spacecraft as they navigate through a series of challenging levels filled with various enemy spacecraft and obstacles. The objective is to defeat the waves of enemies and powerful bosses while avoiding their attacks, and this cooperative multiplayer mode allows players to work together to overcome the game's challenges, making it even more enjoyable as a team.
This is an [Epitech](https://www.epitech.eu/) project involving the development of a network game with an [ECS (Entity Component System)](https://github.com/Miou-zora/R-Type/wiki/Librairies).

## How to build ?

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

## How to run ?

Executables will be compiled at the root of the project directory, unter the names `rtype_server` and `rtype_client` (+ `.exe` on Windows). You can run them simply by running the executables.

## How to play ?

Launch the client and enter the **server's IP address**, then click on **Start**.
Then choose your preferred game mode.
If you choose **join game**, be sure to enter a room that has already been created by another player.\
To play, use your **keyboard arrows** to move around, and the **space bar** to fire missiles.  You only have 10 lives!
The game ends once all players are dead, or you've beaten the final boss.\
**Enjoy the game!**

## More informations ?

Go to [this wiki](https://github.com/Miou-zora/R-Type/wiki), the project will be detailed more technically, enjoy!

## Contributors

| <a href="https://github.com/Miou-zora"><img alt="Miou-zora" src="https://avatars.githubusercontent.com/u/91665686?v=4" width="100"></a> | <a href="https://github.com/ripel2"><img alt="Ripel2" src="https://avatars.githubusercontent.com/u/70372762?v=4" width="100"></a> | <a href="https://github.com/Queng123"><img alt="Queng123" src="https://avatars.githubusercontent.com/u/91665380?v=4" width="100"></a> | <a href="https://github.com/FoxaxeWasTaken"><img alt="FoxaxeWasTaken" src="https://avatars.githubusercontent.com/u/91660228?v=4" width="100"></a> | 
| --- | --- | --- | --- |
| [Miou-zora](https://github.com/Miou-zora) | [Ripel2](https://github.com/ripel2) | [Queng123](https://github.com/Queng123) | [FoxaxeWasTaken](https://github.com/FoxaxeWasTaken) |
