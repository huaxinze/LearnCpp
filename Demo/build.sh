#!/usr/bin/env bash

set -e

mode="clear"

if [ $# -lt 1 ]; then
  echo "input illegal"
  exit 0
fi

mode=$1
build_dir="./build"
if [ $mode == "clean" ]; then
  [ -d $build_dir ] && rm -rf $build_dir
  echo "clean over"
elif [ $mode == "make" ]; then
  cd "./IflyVersion1"
  rm -rf $build_dir
  mkdir $build_dir
  cd $build_dir
  cmake ..
  make -j4 install
  cd ..
  rm -rf $build_dir

  cd "../IflyVersion2"
  rm -rf $build_dir
  mkdir $build_dir
  cd $build_dir
  cmake ..
  make -j4 install
  cd ..
  rm -rf $build_dir

  cd ".."
  rm -rf $build_dir
  mkdir $build_dir
  cd $build_dir

  cmake ..
  make -j4 install
  cd ..
  rm -rf $build_dir

fi