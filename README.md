## Frame Gimp Plugin
![image](https://github.com/LinuxBeaver/Basic-Frame-Gimp-Plugin/assets/78667207/225429f5-6d86-4f01-ad4d-f377c563ecb8)

Glossy Balloon applying on GEGL Frame
![image](https://github.com/LinuxBeaver/Basic-Frame-Gimp-Plugin/assets/78667207/a6bf32f8-50cc-4042-9be2-e0218b8081f6)

## OS specific location to put GEGL Filter binaries 

**Windows**
C:\Users\USERNAME\AppData\Local\gegl-0.4\plug-ins
 
**Linux**
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 **Linux (Flatpak)**
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins

![image](https://github.com/LinuxBeaver/GEGL-glossy-balloon-text-styling/assets/78667207/f15fb5eb-c8d7-4c08-bbac-97048864e657)


## Compiling and Installing
**Linux**

To compile and install you will need the GEGL header files (libgegl-dev on Debian based distributions or gegl on Arch Linux) and meson (meson on most distributions).

meson setup --buildtype=release build
ninja -C build


If you have an older version of gegl you may need to copy to ~/.local/share/gegl-0.3/plug-ins instead (on Ubuntu 18.04 for example).

**Windows**

The easiest way to compile this project on Windows is by using msys2. Download and install it from here: https://www.msys2.org/

Open a msys2 terminal with C:\msys64\mingw64.exe. Run the following to install required build dependencies:

pacman --noconfirm -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-gegl

Then build the same way you would on Linux:

meson setup --buildtype=release build
ninja -C build





## Enjoy

![image](https://github.com/LinuxBeaver/GEGL-glossy-balloon-text-styling/assets/78667207/0ab62e35-33bb-4a88-a420-37a3d721e56f)

