#!/bin/bash

LIB_PATH=lib
CATCH_FOLDER=Catch2

cd ..

git submodule update
cd "${LIB_PATH}/${CATCH_FOLDER}"
cmake -Bbuild -H. -DBUILD_TESTING=OFF
cmake --build build/ --target install