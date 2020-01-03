#! /bin/bash

# Camera Server files
echo "Installing SystemD files for camera server"
mkdir -p /home/nvidia/frc/CameraServer
sudo cp "${SRC_TOP}/systemd/CameraServer.service" "/etc/systemd/system/"
sudo systemctl daemon-reload
sudo systemctl start CameraServer.service
#sudo systemctl status CameraServer.service

echo "Installing SystemD files for logger"
mkdir -p /home/nvidia/frc/Logger
sudo cp "${SRC_TOP}/systemd/NTLogger.service" "/etc/systemd/system/"
sudo systemctl daemon-reload
sudo systemctl start NTLogger.service

