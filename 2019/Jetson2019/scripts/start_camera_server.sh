#! /bin/bash
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/wpilib/lib
echo "Reloading UVC Video"
sudo modprobe -r uvcvideo && sleep 0.5 && sudo modprobe uvcvideo
echo "Sleeping..."
sleep 1
echo "Starting Camera server..."
/opt/frc/bin/camera_server --logconfig=/opt/frc/config/CameraServer/logger.config
