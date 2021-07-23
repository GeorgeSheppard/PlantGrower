#include "WiFi.h"
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>

Preferences preferences;
HTTPClient http;

String ssid;
String password;
String ap_ssid;
String ap_password;

bool connected = false;

AsyncWebServer server(80);

void ConnectToWiFi()
{
  WiFi.disconnect();

  Serial.println("Connecting to WiFi");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  Serial.print("AP password: ");
  Serial.println(ap_password);

  WiFi.onEvent(WiFiConnected, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(WiFiDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

  WiFi.softAP(ap_ssid.c_str(), ap_password.c_str());
  WiFi.begin(ssid.c_str(), password.c_str());
}

void LoopWiFiRetry()
{
  while (!connected)
  {
    ConnectToWiFi();
    delay(1000 * 60);
  }
}

void WiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.print("LocalIP: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
  connected = true;
}

void WiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  connected = false;
  Serial.print("Connection lost because of: ");
  Serial.println(info.disconnected.reason);
  Serial.println("Attempting to reconnect");

  LoopWiFiRetry();
}

void setup()
{
  Serial.begin(115200);

  // Can send to a from the ESP32
  WiFi.mode(WIFI_MODE_APSTA);
  delay(100);

  WiFi.disconnect();

  preferences.begin("wifi", false);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  ap_ssid = preferences.getString("ap_ssid", "");
  ap_password = preferences.getString("ap_password", "");

  if (ssid == "" || password == "")
  {
    Serial.println("No values saved for ssid or password");
  }

  if (ap_ssid == "" || ap_password == "")
  {
    Serial.println("No values saved for ssid or password");
  }

  LoopWiFiRetry();

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (ON_STA_FILTER(request))
              {
                request->send(200, "text/plain", "Hello from STA");
                return;
              }
              else if (ON_AP_FILTER(request))
              {
                request->send(200, "text/plain", "Hello from AP");
                return;
              }

              request->send(200, "text/plain", "Hello from undefined");
            });

  server.begin();

  Serial.println("Main loop starting");
}

void loop()
{
  http.begin("http://jsonplaceholder.typicode.com/comments?id=10"); //Specify the URL
  int httpCode = http.GET();                                        //Make the request

  if (httpCode > 0)
  { //Check for the returning code

    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }

  else
  {
    Serial.println("Error on HTTP request");
  }

  http.end(); //Free the resources
  delay(5000);
}
