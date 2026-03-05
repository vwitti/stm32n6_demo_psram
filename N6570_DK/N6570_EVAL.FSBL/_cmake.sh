#!/bin/bash
# Create cmake files for debug build with current project

### source environment ###
ASGEVO_ENV_PATH=~/.asgevo/env.sh
if [ -f $ASGEVO_ENV_PATH ]; then
  source $ASGEVO_ENV_PATH
else
  echo "ERROR: $ASGEVO_ENV_PATH not found"
  echo "       Please see scripts/.asgevo/env.sh.default for a blueprint." 
  echo "       Rename to env.sh and copy file to folder ~/.asgevo"
  exit 1
fi
 
### cmake ###
# $1 = Debug/Release
BUILD_TYPE=$1

case "$BUILD_TYPE" in
    Debug|Release)
        echo "Building version for $BUILD_TYPE"
        ;;
    *)
        echo "Unknown buildtype"
        exit 1
        ;;
esac

# Create Folder debug if not exist
mkdir -p Debug
cmake -S . -B $BUILD_TYPE -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake

echo "cmake files created. Build with"
echo "cd $BUILD_TYPE"
echo "make -j x -f Makefile"
echo "where x is the number of cores"