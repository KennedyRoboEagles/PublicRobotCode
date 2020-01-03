#! /bin/bash
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/wpilib/lib
echo "Starting Network Tables logger..."
/opt/frc/bin/logger --logconfig=/opt/frc/config/Logger/logger.config --db=/home/nvidia/frc/Logger/main.db
