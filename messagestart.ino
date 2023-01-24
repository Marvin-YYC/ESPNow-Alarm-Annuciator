#include <WiFi.h>         //Including wifi.h library it will take care of all wifi related task
#include <HTTPClient.h>   //Including HTTPClient.h library to use all api 



String url_2;                            //url String will be used to store the final generated URL

void send_message_start() 
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);              // Try to connect with the given SSID and PSS
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {  // Wait until WiFi is connected
    delay(500);
    Serial.print("wait");
  }
  Serial.println();
  Serial.println("Connected to WiFi"); // Print wifi connect message

  message_start_to_signal(""); // use message_to_signal function to send your message
}


void  message_start_to_signal(String message)       // user define function to send meassage to Signal app
{
  //use signal/whatsapp/telegram api url here this is the the initalization message to send when powered up
  
  url_2 = "https://api.callmebot.com/signal/send.php?phone=YOUR API INFORMATION";// your CallMeBot/Signal api information
  

  postData_2(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData_2()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url_2);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url_2); // Finaly Post the URL with this function and it will store the http code
  
  //add below if you want message to be sent twice
    /* http.begin(url);
      httpCode = http.POST(url);
    */
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent Start Ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error sending Start."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}
