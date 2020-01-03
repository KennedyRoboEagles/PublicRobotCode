#! /bin/bash

echo "Installing date service"
sudo -E go build -o /opt/frc/bin/dateservice dateservice
sudo cp "${SRC_TOP}/scripts/start_date_service.sh" "/opt/frc/bin/"

echo "Installing SystemD files for date service"
sudo cp "${SRC_TOP}/systemd/RioDateService.service" "/etc/systemd/system/"
sudo systemctl daemon-reload
sudo systemctl start RioDateService.service
