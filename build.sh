#!/bin/bash

mkdir -p build
cd build

if command -v ninja > /dev/null 2>&1;
then
  echo "> CONFIGURING BUILD SETTINGS..."
  echo ""

  cmake .. -G Ninja "$@"
  
  echo ""
  echo "> BUILDING PROJECT..."
  echo ""

  ninja

  exit $?
else
  echo "> CONFIGURING BUILD SETTINGS..."
  echo ""

  cmake .. "$@"

  echo ""
  echo "> BUILDING PROJECT..."
  echo ""

  make
  
  exit $?
fi
