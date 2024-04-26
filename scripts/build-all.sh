#!/bin/bash

cd ..

cwd=$(pwd)
OUTPUT_DIR=build
SOURCE_DIR=./
TEST_DIR=./test
SCRIPTS_DIR=./scripts

if [ $# == 1 ]; then
    if [ $1 == "clean" ]; then

        echo "Deleting output files ..."
        rm -rf ${OUTPUT_DIR}
        cd ${SOURCE_DIR}
        make clean
        exit 0

    else [ $1 == "doc" ];
        echo -e '\nGenerating the docs ...'
        cd ${cwd}
        doxygen Doxyfile
        exit 0
    fi
fi

echo -e "\nChecking code style"
cd ${cwd}
cd ${SCRIPTS_DIR}
bash check-style.sh


echo -e '\nBuilding the project ...'
cd ${cwd}
mkdir -p ${OUTPUT_DIR}
cd ${OUTPUT_DIR}
cmake ../
make

# if the building process run flawlessly, run the tests
if [ $? == 0 ]; then
    echo -e "\nRunning unit tests ..."
    cd ${cwd}
    cd ${OUTPUT_DIR}
    cd ${TEST_DIR}
    ./test_suite
fi