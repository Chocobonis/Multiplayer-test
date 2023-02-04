#!/bin/bash

echo " ____    |\/|   ";
echo " \  /\   / ..__.           _ __                  ";
echo "  \/  \__\   _/ | | _  _ _|_ | __  _ _|_ _  |  | ";
echo "   \__   __  \_ |^|(_)(_) | _|_| |_>  |_(_| |  | ";    
echo "      \____\___\\";
echo "";
echo "##################################################";
# credit for the fox ascii art goes to -Brian Kendig-
print_help() {
    echo "Usage: ./compile.sh [OPTION]"
    echo "This is a compiling script, it will verify libraries and compile the game."

    echo "  --server    compiles only the server program"
    echo "  --client    compiles only the client program"
    echo "  --both      compiles everything required client and server"
    echo "  --version   prints the version of the program"
    echo "  --help      prints the usage for help"

    echo "Examples:"
    echo "  ./compile.sh server - compiles the serverside part of the game"
    echo "  ./compile.sh client - compiles the clientside part of the game"
}

print_version() {
    echo "example 1.0.0"
    echo "Copyright (C) 2022 Boniikwiidz."
    echo "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>."
    echo "This is free software: you are free to change and redistribute it."
    echo "There is NO WARRANTY, to the extent permitted by law."
    echo ""
}
# 
# THIS IS THE SCRIPT THAT WILL ASSEMBLE THE COMPLETE CODE OF THE GAME INCLUDING THE SERVER
#
strval1=""$1
strval2="--server"
strval3="--client"
strval4="--both"
strval5="--version"
strval6="--help"
strval7=""$2
strval8="--emscripten"

#verify what will happen
# echo "just write down the thing to compile";
# read -p "input source to compile ((server),(client) Or (both)): " strval1;
#Check equality two string variables
if [ -z $strval1 ]; then echo "please use --help for usage"; print_help; exit 0; fi
if [ $strval1 == $strval5 ]; then print_version; exit 0; fi
if [ $strval1 == $strval6 ]; then print_help; exit 0; fi
if [ $strval1 == $strval2 ]; then echo "only server will be compiled"; fi
if [ $strval1 == $strval3 ]; then echo "only client will be compiled"; fi
if [ $strval1 == $strval4 ]; then echo "both sources will be compiled"; fi

echo "installer will now set up dev environment....";

if [ -n "$(command -v g++)" ]; then # first we must verify if the required libraries are installed
 echo "compiler g++ is installed...";
else
 echo "G++ compiler is not installed please install compiler";
 echo "trying to install g++...";
  if [ -n "$(command -v yum)" ]; then sudo yum install g++; fi
  if [ -n "$(command -v pacman)" ]; then sudo pacman -S g++; fi
  if [ -n "$(command -v apt-get)" ]; then sudo apt-get install g++; fi
  if [[ "$OSTYPE" == "win32" ]]; then "this script cannot install g++ on windows :/"; fi
  echo "this script tried installing g++ run again if g++ was installed";
  exit 0;
fi

if [ -n "$(command -v git)" ]; then # first we must verify if the required libraries are installed
 echo "program git is installed...";
else
 echo "git for lib install is not installed please install compiler";
 echo "trying to install git...";
  if [ -n "$(command -v yum)" ]; then sudo yum install git; fi
  if [ -n "$(command -v pacman)" ]; then sudo pacman -S git; fi
  if [ -n "$(command -v apt-get)" ]; then sudo apt-get install git; fi
  if [[ "$OSTYPE" == "win32" ]]; then echo "this script cannot install git on windows :/"; fi
  echo "this script tried installing git run again if git was installed";
  exit 0;
fi

if test -f "/usr/include/GL/glut.h"; then # first we must verify if the required libraries are installed
 echo "glut installed...";
else
 echo "glut is not installed, and it's required";
 echo "trying to install glut...";
  if [ -n "$(command -v yum)" ]; then sudo yum install freeglut; fi
  if [ -n "$(command -v pacman)" ]; then sudo pacman -S freeglut; fi
  if [ -n "$(command -v apt-get)" ]; then sudo apt-get install freeglut3-dev; fi
  if [[ "$OSTYPE" == "win32" ]]; then echo "this script cannot install glut on windows :/"; fi
  echo "this script tried installing glut run again if glut was installed";
  exit 0;
fi

echo "Development environment setup complete!";
#
# this compiles the client of the game
#
if [ $strval1 == $strval3 ] || [ $strval1 == $strval4 ]; then 
echo "assembling client program!"
 if [ $strval7 == $strval8 ]; then 
  cp -r ./assets ./Server/website/launcher
  emcc -fpermissive -w -o ./Server/website/launcher/game.html main.cpp -s LEGACY_GL_EMULATION=1 -lglut -lGLU -lGL lib/imgui/backends/imgui_impl_glut.cpp lib/imgui/backends/imgui_impl_opengl2.cpp lib/imgui/imgui*.cpp -sFORCE_FILESYSTEM -D __EMCC__
  if [ -d "/srv/http" ] && echo "Directory /srv/http exists."; then # first we must verify if the required libraries are installed
    sudo rm -r /srv/http/launcher
    sudo cp -r ./Server/website/launcher /srv/http
  fi
 else
  g++ -fpermissive -w -o Xenon main.cpp -lGLU -lglut -lGL lib/imgui/backends/imgui_impl_glut.cpp lib/imgui/backends/imgui_impl_opengl2.cpp lib/imgui/imgui*.cpp;
 fi
fi

#
# this compiles the complete server of the game
#
if [ $strval1 == $strval2 ] || [ $strval1 == $strval4 ]; then 
echo "assembling server.cpp ....."
cd Server;
g++ -fpermissive -w -o server main.cpp 
cd ..
fi

if [ -n "$(command -v aplay)" ]; then aplay assets/sounds/woof.wav; fi

echo "script finished :D ...";
echo ""
echo "##################################################";
print_version;

