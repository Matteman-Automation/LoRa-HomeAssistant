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
 *     Project    : Lora Sender
 *     Versie     : 0.9
 *     Datum      : 09-2023
 *     Schrijver  : Ap Matteman
 *     

 */    



#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

//Lora local and destination address
byte LoraDestination = 0x01;
byte LoraLocal = 0x10;

int Teller = 1;


void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  if (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

//Send Lora Packet
void SendLora(String LoraPayload) {
  LoRa.beginPacket();
  LoRa.write(LoraDestination);    //destination address
  LoRa.write(LoraLocal);
  LoRa.print(LoraPayload);
  LoRa.endPacket();
}


void loop() {

  String SendPackage;

   
    
  SendPackage = "Hello World: ";
  SendPackage = SendPackage.substring(0,20);  // MQTT Topic = max 20 long
  SendPackage = SendPackage + Teller;

  Serial.print("Sending packet: ");
  Serial.println(SendPackage);
  
  //Send LoRa packet to receiver
  SendLora(SendPackage);
  

  Teller = Teller + 1;
  if (Teller > 99){
    Teller = 1;
  }
  
  delay(1000);

  
}
