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

BUILD_LIST=(
"ASG_EVO/ASG_EVO.APPLI"
"ASG_EVO/ASG_EVO.FSBL"
"N6570_DK/N6570_EVAL.APPLI"
"N6570_DK/N6570_EVAL.FSBL"
"N6570_DK/N6570_NOOS.APPLI"
"N6570_DK/N6570_NOOS.FSBL"
"N6570_DK/N6570_TEST.APPLI"
"N6570_DK/N6570_TEST.FSBL"
)

for build_object in "${BUILD_LIST[@]}"; do
	echo "$build_object"
	cd $build_object
	./_make.sh $BUILD_TYPE $NUM_CORES
	if ! [ $? -eq 0 ]; then
		echo "BuildError in project $build_object"
		echo "STOP"
		exit 1
	fi
	cd ../..
done
echo "ALL DONE!"
exit 0


