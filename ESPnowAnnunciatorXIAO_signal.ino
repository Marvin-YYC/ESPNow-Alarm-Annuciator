
#include "Arduino.h"

const char* ssid = "SSID";             //Add your WiFi ssid
const char* password =  "PASSWORD";    //Add your WiFi password

#include <esp_now.h>
#include <WiFi.h>
#define GREEN_LED  D2
#define RED_LED  D3
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
  for (int i=0; i<duration;i++) {
    digitalWrite(RED_LED, HIGH);
    WaitFunc(0.1,false);//on for 100ms
    digitalWrite(RED_LED, LOW);
    WaitFunc(0.1,false); //off for 100ms
  }
  //send_message_start();//this sends the signal "start" message
}

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  ledcSetup(CHN, 0, 10); //setup pwm channel
  ledcAttachPin(BUZZER, CHN);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW");
  return;
  }

  esp_now_register_recv_cb(OnDataRecv);             //function run when received data
}

void loop() {
  Serial.println(GateOpen);
  while (GateOpen == 0){
  
    digitalWrite(GREEN_LED, HIGH);
    WaitFunc(10,true); //on ten seconds
    digitalWrite(GREEN_LED, LOW);
    WaitFunc(0.1,true); // off 100ms
    //send_message_start();//this sends the signal "start" message
}
  Serial.println(GateOpen);
    while (GateOpen == 1){
      
          delay(25);
      send_message_open();//this sends the signal "open" message
          delay(25);
    
        for (int i=0; i<5;i++) {  // number of beep cycles
        for (int i=0; i<4;i++) {  // number of beeps in cycle
            ledcWriteTone(CHN, 1300);  // frequency of tone (2000)
            digitalWrite(RED_LED, HIGH);
            FlashRedLED(1);  // beep duration 
            ledcWriteTone(CHN, 0);
            digitalWrite(RED_LED, LOW);
            FlashRedLED(1);  // pause between beeps
   }
  
          FlashRedLED(10);  // pause between beeps cycles 
   }
    
          FlashRedLED(500);  // 500 seconds=8.33 minutes after cycle ends (pause between beep groups was 45)
         
         
   }
             
}
