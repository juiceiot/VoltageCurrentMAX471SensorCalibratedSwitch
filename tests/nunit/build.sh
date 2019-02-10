echo "Starting build for project"
echo "Dir: $PWD"

DIR=$PWD

xbuild src/VoltageCurrentMAX471SensorCalibratedSwitch.sln /p:Configuration=Release
