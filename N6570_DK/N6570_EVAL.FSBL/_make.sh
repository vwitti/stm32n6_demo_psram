#!/bin/bash
# Create cmake files for debug build with current project
#
# $1 : Build Type <Debug|Release>
# $2 : Number of Cores (Default is 4)

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

### make ###
# $1 = Debug/Release
BUILD_TYPE=$1
NUM_CORES="${2:-4}"		# Default value cpp lib take a lot of memory

case "$BUILD_TYPE" in
    Debug|Release)
        echo "Building version for $BUILD_TYPE"
        ;;
    *)
        echo "Unknown buildtype"
        exit 1
        ;;
esac

cd $BUILD_TYPE
make -j $NUM_CORES -f Makefile # choose more cores or run ninja
