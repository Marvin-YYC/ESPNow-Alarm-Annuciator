
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
  Serial.println("Open Message Signal");
  message_open_to_signal(""); // use message_to_signal function to send your message
}

void  message_open_to_signal(String message)       // user define function to send message via Signal
{
  //use signal/whatsapp/telegram api url here
Serial.println("Open Message URL");

  url_1 = "https://api.callmebot.com/signal/send.php?phone= YOUR API HERE";

 Serial.println("post data 1");
  postData_1(); // calling postData to run the above-generated url once so that you will receive a message.
}
void postData_1()     //userDefine function used to call api(POST data)
{
  Serial.println("Int HTTP Code");
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url_1);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url_1); // Finaly Post the URL with this function and it will store the http code
  Serial.println("HTTP Code Bottom");  
  //add below if you want message to be sent twice
    /* http.begin(url);
      httpCode = http.POST(url);
    */
    
  if (httpCode == 200)      // Check if the response http code is 200
  {
    Serial.println("Sent OPEN Ok."); // print message sent ok message 
    http.end();          // After calling API end the HTTP client object.
    Serial.println("HTTP End ok");
  }
  
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("ERROR sending OPEN."); // print error message.
    http.end();          // After calling API end the HTTP client object.
    Serial.println("Flash Blue LED.");
    //digitalWrite(BLUE_LED, HIGH);
    //delay(3000);
    //digitalWrite(BLUE_LED, LOW);
    //delay(250);
    digitalWrite(BLUE_LED, HIGH);
    Serial.println("Blue LED Stay ON");
  }
     Serial.println("Message Tab End");
 }
