#!/bin/bash

if [[ $1 == "-g" ]] || [[ $1 == "--debug" ]]
then
    if ! grep -q "CMAKE_BUILD_TYPE:STRING=Debug" build/CMakeCache.txt > /dev/null 2>&1
    then
        echo "> REMOVING BUILD DIRECTORY..."
        rm -rf build
    fi

    echo "> PREPARING TO BUILD PROJECT..."

    ./build.sh -DCMAKE_BUILD_TYPE=Debug
    EXIT_CODE=$?

    echo ""

    if [[ $EXIT_CODE != 0 ]]
    then
        echo "~ BUILD FAILED!"
        exit $EXIT_CODE
    else
        echo "~ BUILD SUCCESS."
        echo "> RUNNING GDB..."
        echo ""

        sudo gdb build/src/main
    fi
else
    if grep -q "CMAKE_BUILD_TYPE:STRING=Debug" build/CMakeCache.txt > /dev/null 2>&1
    then
        echo "> REMOVING BUILD DIRECTORY..."
        rm -rf build
    fi

    echo "> PREPARING TO BUILD PROJECT..."

    ./build.sh -DCMAKE_BUILD_TYPE=Release
    EXIT_CODE=$?

    echo ""

    if [[ $EXIT_CODE != 0 ]]
    then
        echo "~ BUILD FAILED!"
        exit $EXIT_CODE
    else
        echo "~ BUILD SUCCESS."
        echo "> RUNNING EXECUTABLE..."
        echo ""

        sudo build/src/main "$@"
    fi
fi
