# Runtime++

Runtime++ is a fast, efficient, easy-to-use, and open-source C++ interactive application framework. It is intended for the fast creation of reactive and reliable applications such as 2D/3D video games, general software applications, or any other reasonable "creative coding" endeavors. It offers support of well-known and powerful tools such as SDL, OpenGL, GLAD, SOIL, Dear Imgui, and the CMake build system offers fast and easy multiplatform compilation for Windows/OSX/Linux.

## Built for Creative Coders

Runtime++ is a catch-all framework for any application that is intended to run in its window and context. Built on the sturdy foundation of the Simple DirectMedia Layer, Runtime++ allows access to a cross-platform hardware abstraction layer for computer multimedia hardware components. 

With access to easy-to-use Runtime++ abstracted tools such as OpenGL and Dear Imgui, the stage is set for the creation of any interactive software you can think of. The list grows as features are added, but as of now, you may consider using Runtime++ for projects such as...

* Simple or complex 2D/3D video games.
* GUI utilities for completing tasks such as installation, file management, or networking.
* Video editing software.
* Audio editing software.
* Animation software.
* Server-side or client-side GUI applications.
* GUI hardware monitoring.
* Chat rooms or other social media.
* Video or audio streaming.
* Text editing software.
* Internet explorers.
* Much, much more: anything you can think of!

## How to Use

Ready to jump in? All you need to do is follow the instructions below to start writing your first Runtime++ application. Because this project relies on many external dependencies, some setup is required. Do not worry, it is built to be simple so this part should (hopefully) not take too long.

### Installing Dependencies

The Runtime++ build system fundamentally utilizes CMake, and there are a couple dependancies that require global installation (unlike the library sources included in runtime-plus-plus/lib/)...

### macOS
```bash
# Homebrew required! If not, use the following line to install...
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# CMake: Required...
brew install cmake
# OpenGL: Required...
brew install glfw3 && brew install glew
# SDL2: Required...
brew install SDL2
```

### Linux
```bash
# CMake: Required...
sudo apt-get install cmake
# OpenGL: Required...
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
# SDL2: Required...
sudo apt-get install libsdl2-dev
```

### Windows

Windows is a bit simpler as most of the libaries are included in the runtime++/lib/ directory. However, there are still a few instructions to follow below...

#### Checking for OpenGL

Runtime++ obivously requires OpenGL. Most machines comes with support, but check if opengl32.dll and glu32.dll are present at C:\Windows\System32\. It should mostly come with the system at this location. Go [here](https://www.khronos.org/opengl/wiki/Getting_Started) for more help.

#### Installing MinGW (GCC Compiler)
* Install [MinGW for Windows x64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download). Make sure to install the 64-bit compiler x86_64. This allows your machine C/C++ compiler support.
* After the installer is done you need to add the mingw directory to PATH. Open the start menu and search for "Edit the system environment variables" -> click "Environment Variables" -> select "Path" under System variables and click "Edit" -> add mingw64\bin

#### Installing CMake

Visit [CMake's website](https://cmake.org/install/) and follow the instructions for installing CMake.

## ReadME still under construction...
