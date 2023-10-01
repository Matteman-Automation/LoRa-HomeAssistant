/*
 *     M      M     AA    TTTTTTT  TTTTTTT  EEEEEEE M      M     AA     NN    N
 *     MM    MM    A  A      T        T     E       MM    MM    A  A    NN    N
 *     M M  M M   A    A     T        T     E       M M  M M   A    A   N  N  N
 *     M  MM  M   AAAAAA     T        T     EEEE    M  MM  M   AAAAAA   N  N  N - AUTOMATION
 *     M      M  A      A    T        T     E       M      M  A      A  N   N N 
 *     M      M  A      A    T        T     E       M      M  A      A  N    NN  
 *     M      M  A      A    T        T     EEEEEEE M      M  A      A  N    NN  
 *     
 *     
 *     Project    : Lora Receiver
 *     Versie     : 0.9
 *     Datum      : 09-2023
 *     Schrijver  : Ap Matteman
 *     
 */    


#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

String mqttTopic;
String mqttValue;
int iWaarde = 0;


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() { 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("LoRa Receiver");
  display.display();
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
  
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //note: the frequency should match the sender's frequency
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  if (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.println("LoRa Initializing OK!");
  display.display();
}

void loop() {
  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    String LoRaData = LoRa.readString(); 
    float rssiValue = LoRa.packetRssi();
    

    Serial.print("mqttTopic: "); Serial.println(mqttTopic);
    Serial.print("mqttValue: "); Serial.println(mqttValue); 
    Serial.print("RSSI: "); Serial.println(rssiValue); 

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Receive package");
    display.setCursor(0,10);
    display.println(LoRaData);
    display.setCursor(0,30);
    display.print("RSSI: ");
    display.println(rssiValue);
    
    display.display();
  }
}
