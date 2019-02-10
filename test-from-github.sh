#!/bin/bash

echo ""
echo "Testing VoltageCurrentMAX471SensorCalibratedSwitch project from github"
echo ""

BRANCH=$1

if [ $# -eq 0 ]
then
  BRANCH=$(git branch | sed -n -e 's/^\* \(.*\)/\1/p')
  echo "Branch not specified as argument. Using current branch: $BRANCH"
fi

TIMESTAMP=$(date +"%Y_%m_%d_%I_%M_%p_%s")
TEMPORARY_DIR="/tmp/$TIMESTAMP"

echo "Branch: $BRANCH"
echo "Tmp project dir:"
echo "  $TEMPORARY_DIR"

mkdir -p $TEMPORARY_DIR

cd $TEMPORARY_DIR

git clone http://github.com/GreenSense/VoltageCurrentMAX471SensorCalibratedSwitch -b $BRANCH && \

cd VoltageCurrentMAX471SensorCalibratedSwitch && \
sh init.sh && \
sh build.sh && \
sh upload.sh && \
sh upload-simulator.sh && \
sh test.sh

rm $TEMPORARY_DIR -rf

echo ""
echo "Finished testing VoltageCurrentMAX471SensorCalibratedSerial project from github"
echo ""
