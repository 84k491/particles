#!/bin/bash

build_dir="build"
mkdir $build_dir
cd $build_dir
cmake cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cmake --build . -j3
