#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
#include <FastLED.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "BLYNK_AUTH_TOKEN_FROM_EMAIL";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI_NAME"; // REPLACE with your WiFi network name
char pass[] = "WIFI_PASSWORD"; // REPLACE with your WiFi password

BlynkTimer timer;

#define NUM_LEDS 10 // change number of leds here to match your setup
#define DATA_PIN 2 // GPIO2. Change to another pin if your setup is diffrent

int brightness = 255; // default brightness
CRGB color = CRGB(255,0,0); // default color

CRGB leds[NUM_LEDS]; // led array

void setup()
{
  // Connect to WIFI and to BLYNK application. Once done you would
  // see "connected" message on your smartphone.
  Blynk.begin(auth, ssid, pass);

  // Initialize LED array
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
  Blynk.run(); // check new data coming from Blynk

  for(int dot = 0; dot < NUM_LEDS; dot++) {
        leds[dot] = color;
        leds[dot].nscale8_video(brightness);
  }

  FastLED.show();
}

BLYNK_WRITE(V0) // Called when you change color in an app
{
  // get a RED channel value
  int r = param[0].asInt();
  // get a GREEN channel value
  int g = param[1].asInt();
  // get a BLUE channel value
  int b = param[2].asInt();

  color = CRGB(r,g,b);
}

BLYNK_WRITE(V1) // Called when you change brightness change in an app
{
  brightness = param.asInt();
}