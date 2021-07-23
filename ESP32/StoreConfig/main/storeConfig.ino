#include <Preferences.h>

Preferences preferences;

const char *ssid = "";
const char *password = "";
const char *ap_ssid = "";
const char *ap_password = "";

void setup()
{
  Serial.begin(115200);
  Serial.println();

  preferences.begin("wifi", false);

  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.putString("ap_ssid", ap_ssid);
  preferences.putString("ap_password", ap_password);

  // Close the Preferences
  preferences.end();

  Serial.println("Config saved");
}

void loop()
{
}
