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

# VSCode Workflow

It is possible to avoid the Arduino IDE and develop entirely in VSCode.

- Install the Arduino extension in VSCode
- Open the VSCode UI settings, search for 'Arduino: Path', and set it to the install path for the Arduino IDE (in my case 'C:\\Program Files (x86)\\Arduino') (note: if you have installed through the Microsoft Store then uninstall this and download the Arduino IDE not through the store)
- Next search for 'Intelli Sense Engine' and set it to Tag Parser (this removes the syntax highlighting errors when including libraries)
- Set the path to the Arduino libraries by searching for 'browse path' in the UI settings (in my case 'C:\\Program Files (x86)\\Arduino\\libraries')
- To see the available features for the extension open the command palette (Ctrl + Shift + P) and type Arduino
- Make sure the Baud Rate, Com port, and Board type are set correctly

- There is no need to compile with this setup, just run 'Arduino: Upload'
- You can then open the serial monitor with 'Arduino: Open Serial Monitor'

# Preferences Library

There are three main sketches used in this project, of which two relate to storing of the WiFi credentials.

If you are using the VSCode workflow, then on the bottom toolbar there should be a tab that says 'ESP32\PlantGrower\main\*'. You can click here to switch between each of the sketches, and then use the normal workflow from there.

## storeConfig

Use this to set the WiFi ssid and password, then once uploaded make sure to reset the file to it's original state so it is not committed into the version history.

## wipeConfig

The namespaces associated with the Preferences library can be reset using this, otherwise the storage slowly fills over time.

## main

This is the actual code for the plant grower.

# Additional Libraries  

To add an extra library given a git just download the repository as a zip, then click Sketch -> Include Library -> Add .ZIP Library in Arduino IDE and select the ZIP.

## Required libraries for this project  
[ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
[AsyncTCP](https://github.com/me-no-dev/AsyncTCP)

