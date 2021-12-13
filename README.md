# Kraken
Kraken Game Engine

## Setup
First clone the repository with `git clone --recursive <URL>`
> Note: If the repository has already been cloned non-recursively, use `git submodule update --init` to clone necessary submodules.

Kraken uses [_Premake 5_](https://premake.github.io/) as a build generation tool. Follow [these](https://premake.github.io/download.html) instructions to install.

## Windows
Premake can generate project files for several Visual Studio versions.
You can run `premake vs2019` to generate the relevent solution and project files for Visual Studio 2019.
> Note: provided is a batch file that automatically runs this command. Modify it with your relevant IDE for easier use.

## Linux
Kraken has some extra dependencies on Linux. In particular, the following development packages are needed:
- `libxcursor`
- `libxrandr`
- `libxinerama`
- `libxi`
- `libglew`

Install by these by running:
#### Debian and Derivatives
`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglew-dev`
#### Arch Linux
`sudo pacman -S libxcursor libxrandr libxinerama libxi glew`

Then configure and compile Kraken with:
```bash
premake5 gmake2
make
```
