# Programming ESP32 first time setup

- Open Arduino IDE
- File -> Preferences
- Under 'Additional Boards Manager URLs' paste  
  https://dl.espressif.com/dl/package_esp32_index.json (note: if there are URLs here already then comma separate them)
- Exit menu, and go to Tools -> Board -> Boards Manager
- Type in ESP32 into the search bar and install
- Now can select ESP32 Dev Module from Tools -> Board

- Open device manager, and check that a new device appears under Ports when the ESP32 is plugged in

- If a new device does not appear

  - Does the device appear under 'Other devices'?
  - If so you need to install the CP2102 driver
  - This can be installed from [silicon labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

- Back in the Arduino IDE under Tools -> Port select the port the ESP32 appears under in devicer manager
- Select File -> Examples -> WiFi -> WiFiScan
- Under Tools -> Upload speed select 115200
- Click Upload

- If the upload does not complete correctly

  - If the error is "A fatal error has occurred: Failed to connect to ESP32" then
  - Hold down the BOOT button on the ESP32
  - Click Upload
  - Release BOOT once "Connecting..." appears in the console

- Select Tools -> Serial Monitor
- Set the baud rate to 115200
- There should be logs of the available wifi networks
