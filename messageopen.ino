/*
  Date: 07-05-21
  Code written by: Dharmik
  ESP32 sending a message to Signal messenger
  Find more on www.TechTOnions.com
*/

#include <WiFi.h>         //Including wifi.h library it will take care of all wifi related task
#include <HTTPClient.h>   //Including HTTPClient.h library to use all api 


String url_1;                            //url String will be used to store the final generated URL

void send_message_open() 
{
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);              // Try to connect with the given SSID and PSS
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {  // Wait until WiFi is connected
    delay(500);
    Serial.print("wait. . .");
  }
  Serial.println();
  Serial.println("Connected to WiFi"); // Print wifi connect message

  message_open_to_signal(""); // use message_to_signal function to send your message
}


void  message_open_to_signal(String message)       // user define function to send meassage to Signal app
{
  //use signal/whatsapp/telegram api url here

  url_1 = "https://api.callmebot.com/signal/send.php?phone=YOUR API INFORMATION";// your CallMeBot/Signal api information


  postData_1(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData_1()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url_1);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url_1); // Finaly Post the URL with this function and it will store the http code
    
  //add below if you want message to be sent twice
    /* http.begin(url);
      httpCode = http.POST(url);
    */
    
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent OPEN Ok."); // print message sent ok message 
    http.end();          // After calling API end the HTTP client object.
    delay(50);
  }
  
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("ERROR sending OPEN."); // print error message.
    http.end();          // After calling API end the HTTP client object.
    digitalWrite(GREEN_LED, HIGH);//red+green led flash on and off together six times and then red stays on, green blinks normal status to indicate send error
    digitalWrite(RED_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250); // off 100ms
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250); // off 100ms
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250); // off 100ms
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250); // off 100ms
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250); // off 100ms
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  
  }
 
}
