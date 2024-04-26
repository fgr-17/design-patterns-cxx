#!/bin/bash

cd ..

SOURCE_DIR=./src
TEST_DIR=./test
STYLE=Google

find ${SOURCE_DIR}  -iname *.hpp -o -iname *.cpp | xargs clang-format --style=${STYLE} -i 
find ${TEST_DIR}  -iname *.hpp -o -iname *.cpp | xargs clang-format --style=${STYLE} -i