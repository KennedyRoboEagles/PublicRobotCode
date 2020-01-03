# Jetson2019

## Install dependencies
```
sudo apt-get install liblog4cxx-dev libsqlite3-dev sqlite3
```

## Initialize Git Submodules
```
git submodule init
git submodule update
``` 

## Installing
Run the following on the jetson
```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/frc
make -j4
sudo make install

```
### SystemD
```
mkdir -p /home/nvidia/frc/CameraServer
mkdir -p /home/nvidia/frc/Logger
sudo cp systemd/CameraServer.service /etc/systemd/system/
sudo cp systemd/NTLogger.service /etc/systemd/system/
sudo systemctl daemon-reload

sudo systemctl enable CameraServer.service
sudo systemctl start CameraServer.service
sudo systemctl status CameraServer.service

sudo systemctl enable NTLogger.service
sudo systemctl start NTLogger.service
sudo systemctl status NTLogger.service
```

View logs
```
journalctl -u CameraServer.service
```