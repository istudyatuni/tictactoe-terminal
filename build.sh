#!/bin/bash
clear

exec_name=game

# BUILD=Release
BUILD=Debug

if [ -n "$1" ]; then
    BUILD=$1
fi

# MAKE=ninja
MAKE=make

if [ $MAKE = ninja ]; then
    makefile=build.ninja
    gen="-G Ninja"
elif [ $MAKE = make ]; then
    makefile=Makefile
    # Unix Makefiles as default
fi

build_dir=bin/$BUILD

if [ ! -d $build_dir ]; then
    mkdir -p $build_dir
fi
cd $build_dir

if [ ! -e $makefile ]; then
    cmake $gen -DCMAKE_BUILD_TYPE=$BUILD ../..
fi
rm -f $exec_name

$MAKE
if [ -e $exec_name ]; then
    cd ../..
    echo -e '\n'
    $build_dir/$exec_name
    echo
fi
