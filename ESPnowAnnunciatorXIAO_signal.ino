
#include "Arduino.h"

const char* ssid = "SSID";             //Add your WiFi ssid
const char* password =  "SSID PW";    //Add your WiFi password

#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>
#define RED_LED  D3
#define GREEN_LED  D2
#define BLUE_LED D0
#define BUZZER D1
#define CHN 0

typedef struct struct_message {
    bool a;
} struct_message;
struct_message myData;

boolean GateOpen = false;

void WaitFunc(float duration, boolean value) {
  int timer = 0;
  while (timer < duration*2 && GateOpen != value) {
    timer++;
    delay(500);
    }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  GateOpen = myData.a;
}

void FlashRedLED(int duration) {
  Serial.println("void Flash Red LED");
  for (int i=0; i<duration;i++) {
    digitalWrite(RED_LED, HIGH);
    WaitFunc(0.1,false);//on for 100ms
    digitalWrite(RED_LED, LOW);
    WaitFunc(0.1,false); //off for 100ms
   Serial.println("void Flash Red LED complete");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("void setup");
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  ledcSetup(CHN, 0, 10); //setup pwm channel
  ledcAttachPin(BUZZER, CHN);
  
    //this sequences all the LEDs once at power-up
    delay(2000);
    digitalWrite(BLUE_LED, HIGH);
    delay(500);
    digitalWrite(BLUE_LED, LOW);
    delay(100);
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
    delay(100);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
    
    //send_message_start();// This sends SIGNAL Start-up message one time at reset or power up after it cycles the LEDs but stops the sketch at this tab.
    
  Serial.println("void setup complete");
  WiFi.mode(WIFI_STA);
  Serial.println("ESP Now OK");
  if (esp_now_init() != ESP_OK) {
 Serial.println("Error initializing ESP-NOW");
  return;
  }
  esp_now_register_recv_cb(OnDataRecv);  //function run when received data
}

void loop() {
  //send_message_start(); //HERE this sends the signal "startup" message but stops the code after it?
    Serial.println(GateOpen);
  while (GateOpen == 0){
  Serial.println("Gate Not Open");
  Serial.println("Flash Green LED");
    digitalWrite(GREEN_LED, HIGH);
    WaitFunc(30,true); //on 30 seconds
    digitalWrite(GREEN_LED, LOW);
    WaitFunc(0.1,true); // off 100ms
  Serial.println("Gate Not Open End");
  
    //send_message_closed();//this sends the signal "closed" message but sends every 10 seconds. don't know how to send once when initially closed
}

   Serial.println(GateOpen);
    while (GateOpen == 1){
   Serial.println("Gate Open");
   Serial.println("Send Open Message");
   send_message_open();//HERE this sends the signal "open" message before buzzer but when door closes will not reset to green and then sends message again after cycle 500 seconds
  
   Serial.println("Initiate Buzz");     
        for (int i=0; i<2;i++) {  // number of beep cycles (4)
        for (int i=0; i<2;i++) {  // number of beeps in cycle (4)
      
    Serial.println("Red Buzzer");   
            ledcWriteTone(CHN, 1300);  // frequency of tone (2000)
            digitalWrite(RED_LED, HIGH);
            FlashRedLED(2);  // beep duration was 1 sec
            ledcWriteTone(CHN, 0);
            digitalWrite(RED_LED, LOW);
            
    Serial.println("Buzz Pause 1");
         
           FlashRedLED(1);  // pause between beeps was 1 sec
                
   }
    Serial.println("Buzz Pause 10");
         
          FlashRedLED(10);  // pause between beeps cycles was 10 sec
   }
    Serial.println("Buzz Pause 500");
           
          FlashRedLED(500);  // 500 seconds=8.33 minutes after cycle ends (pause between beep groups was 45)    
          
    Serial.println("Buzz Pause 500 after");    
                 
   }
    Serial.println("End End End");           
}
