/* 
 * Project: IoT_Midterm_1_Silva
 * Author: Cesar J. Silva
 * Date: July 1, 2025
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "IoTClassroom_CNM.h"
#include "hue.h"
#include "Colors.h"


SYSTEM_MODE(MANUAL);
Adafruit_BME280 bme;
bool sendHueCommand;
bool status;
bool buttonState;
bool AutoOrManual;
bool onOff;
float tempC;
float tempF;
float humidRH;
const int OLED_RESET = -1;
Adafruit_SSD1306 display(OLED_RESET);
const int ABULB = 1;
const int BBULB = 2;
const int CBULB = 3;
const int DBULB = 4;
const int EBULB = 5;
const int FBULB = 6;
const int AWEMO = 0;
const int BWEMO = 1;
const int CWEMO = 2;
const int DWEMO = 4;
const int EWEMO = 5;
const int hexAddress = 0x76;
const int REDPILL = D19;
const int BLUEPILL = D18;
Button matrixButton(D18);
Button realworldButton(D19);
int position;
int color;
int y, x;

void setup() {
  Serial.begin(9600);
  waitFor (Serial.isConnected, 10000);

WiFi.on();
WiFi.clearCredentials();
WiFi.setCredentials("IoTNetwork");

WiFi.connect();
while(WiFi.connecting()){
  Serial.printf(".");
}
Serial.printf("\n\n");
position = 255;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();

  display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 47);
  display.printf("1 1 01 001 01;? 0101; 070 1 ;1 7 ? 0 1!0 019 ;!09 ?917 01;0!01?0717; 1! 0 0<1 01;010.1;0 10, 1.1.01 9 0<!?1! 19100710!981>79871 0 0 1 0 0:1;0 1? 09 0 9 1 91!0 1 < 1 1 !0\n");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.printf("NEBUCHANDNEZZAR SYSTEM: ON_\n");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
  display.clearDisplay();



  status = bme.begin(hexAddress);
  if (status == false){
    Serial.printf("BME280 at address 0x%02X failed to start", hexAddress);
  }
  sendHueCommand = true;
}

void loop() {

  display.clearDisplay();
  display.setCursor(0,49);
  
  if (matrixButton.isClicked()){
    onOff = !onOff;
    display.printf("1 1 01 001 01;? 0101; 070 1 ;1 7 ? 0 1!0 019 ;!09 ?917 01;0!01?0717; 1! 0 0<1 01;010.1;0 10, 1.1.01 9 0<!?1! 19100710!981>79871 0 0 1 0 0:1;0 1? 09 0 9 1 91!0 1 < 1 1 !0\n");
    display.display();
    display.clearDisplay();
  }

  if (realworldButton.isClicked()){
    onOff = !onOff;
    display.printf("NEBUCHANDNEZZAR SYSTEM: ON_\n");
    display.display();
    display.clearDisplay();

  }
  tempC = bme.readTemperature();
  // convert tempC to tempF
  tempF = (tempC * 1.8) + 32;
  Serial.printf("temperature: %0.1f\n", tempF);
  // show humidity
  humidRH = bme.readHumidity();
  Serial.printf("TEMP = %0.1f, HUMID = %0.1f\n", tempF, humidRH);
  display.drawLine(0, 48, 128, 48, WHITE);
  display.printf("TEMP = %0.1f, HUMID = %0.1f\n", tempF, humidRH);
  display.display();
  if ((tempF <= 71.5)){
    Serial.printf("Setting color of bulb %i to color HueBlue\n", ABULB);
    setHue(ABULB, true, HueBlue, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueRed\n", BBULB);
    setHue(BBULB, true, HueRed, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueBlue\n", CBULB);
    setHue(CBULB, true, HueBlue, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueRed\n", DBULB);
    setHue(DBULB, true, HueRed, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueBlue\n", EBULB);
    setHue(EBULB, true, HueBlue, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueRed\n", FBULB);
    setHue(FBULB, true, HueRed, position, 255);
    Serial.printf("position = %i\n", position);
  }
  else{
     Serial.printf("Setting color of bulb %i to color HueGreen\n", ABULB);
    setHue(ABULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueGreen\n", BBULB);
    setHue(BBULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueGreen\n", CBULB);
    setHue(CBULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueGreen\n", DBULB);
    setHue(DBULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueGreen\n", EBULB);
    setHue(EBULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);

     Serial.printf("Setting color of bulb %i to color HueGreen\n", FBULB);
    setHue(FBULB, true, HueGreen, position, 255);
    Serial.printf("position = %i\n", position);
  }
  
  if ((tempF >= 71.5)){

    wemoWrite(AWEMO, HIGH);
    wemoWrite(BWEMO, HIGH);
    wemoWrite(CWEMO, HIGH);
    wemoWrite(DWEMO, HIGH);
    wemoWrite(EWEMO, HIGH);
  }
  else{
    wemoWrite(AWEMO, LOW);
    wemoWrite(BWEMO, LOW);
    wemoWrite(CWEMO, LOW);
    wemoWrite(DWEMO, LOW);
    wemoWrite(EWEMO, LOW);
  }
}
