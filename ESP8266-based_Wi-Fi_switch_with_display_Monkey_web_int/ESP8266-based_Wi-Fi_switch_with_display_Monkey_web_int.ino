// ESP8266-based 4 channel Wi-Fi switch with display (Monkey web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
// Button template was designed by Monkey Company. You can find it here: https://codepen.io/monkey-company/pen/zZZvRp
#include <ESP8266WiFi.h>       // Include ESP8266WiFi library
#include <SPI.h>               // Include SPI library
#include <Adafruit_GFX.h>      // Include Adafruit graphics library
#include <Adafruit_PCD8544.h>  // Include Adafruit PCD8544 (Nokia 5110) library
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);
const char* ssid     = "Blackberry";  // Your SSID (Network's name)
const char* password = "seasidehills99"; // Password from your network
int ch1 = 14; // pin D5
int ch2 = 12; // pin D6
int ch3 = 13; // pin D7
int ch4 = 15; // pin D8
WiFiServer server(80);
void setup(){
  display.begin();          // Initialise the display
  display.setContrast(60);  // Set the contrast
  display.setRotation(0);   // Set the orientation
  display.clearDisplay();   // Clear the screen (In case something was in it)
  display.setTextSize(1);   // Set the text size 
  display.setTextColor(BLACK); // Set the text color
  display.setCursor(10,8);
  display.println("Connecting");
  display.setCursor(22,18);
  display.println("to the");
  display.setCursor(5,28);
  display.println("Access Point");
  display.display();       // Display the text
  pinMode(ch1, OUTPUT); // Setting all 4 pins as OUTPUTS
  digitalWrite(ch1, LOW); // Setting 0 to all 4 pins
  pinMode(ch2, OUTPUT);
  digitalWrite(ch2, LOW);
  pinMode(ch3, OUTPUT);
  digitalWrite(ch3, LOW);
  pinMode(ch4, OUTPUT);
  digitalWrite(ch4, LOW);
  Serial.begin(115200); // Baudrate
  Serial.print("Connecting to the Newtork"); // This all will be displayed in the Serial Monitor
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  server.begin(); // Starting the server
  Serial.println("Server started");
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP()); // Display device's IP address in serial monitor
  Serial.println("/");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(19,5);
  display.println("Device's");
  display.setCursor(10,15);
  display.println("IP address:");
  display.setCursor(0,25);
  display.println(WiFi.localIP()); // Display device's IP address on display
  display.display();
}

 

void loop(){

  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while(!client.available())  
  {
    delay(1);
  } 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int c1 = LOW;
  int c2 = LOW;
  int c3 = LOW;
  int c4 = LOW;
  
    if(request.indexOf("/ch1=ON") != -1)

  {
    digitalWrite(ch1, HIGH); // Turn ch1 ON
    c1 = HIGH;
  }
  if(request.indexOf("/ch1=OFF") != -1)
  {
    digitalWrite(ch1, LOW); // Turn ch1 OFF
    c1 = LOW;
  }
    if(request.indexOf("/ch2=ON") != -1)

  {
    digitalWrite(ch2, HIGH); // Turn ch2 ON
    c2 = HIGH;
  }
  if(request.indexOf("/ch2=OFF") != -1)
  {
    digitalWrite(ch2, LOW); // Turn ch2 OFF
    c2 = LOW;
  }
      if(request.indexOf("/ch3=ON") != -1)

  {
    digitalWrite(ch3, HIGH); // Turn ch3 ON
    c3 = HIGH;
  }
  if(request.indexOf("/ch3=OFF") != -1)
  {
    digitalWrite(ch3, LOW); // Turn ch3 OFF
    c3 = LOW;
  }
      if(request.indexOf("/ch4=ON") != -1)

  {
    digitalWrite(ch4, HIGH); // Turn ch4 ON
    c4 = HIGH;
  }
  if(request.indexOf("/ch4=OFF") != -1)
  {
    digitalWrite(ch4, LOW); // Turn ch4 OFF
    c4 = LOW;
  }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html"); // All below is a web page code written in HTML
  client.println("");
  client.println("<!DOCTYPE html>\n"
"<html>\n"
"  <head>\n"
"    <style>\n"
"body {\n"
"  font-family: Helvetica Neue,Arial,sans-serif; \n"
"}\n"
"body, .button:after {\n"
"  background: #121414;\n"
"}\n"
".ctn {\n"
"  display: block;\n"
"  margin: auto;\n"
"  text-align: center;\n"
"  max-width: 1000px;\n"
"}\n"
"h1 {\n"
"  text-align: center;\n"
"  color: #CCC;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 1.2em;\n"
"  margin: 0 0 1em;\n"
"}\n"
"p {\n"
"  text-align: center;\n"
"  color: #CCC;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 1em;\n"
"  margin: 0 0 1em;\n"
"}\n"
"h4 {\n"
"  text-align: center;\n"
"  color: #CCC;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 0.75em;\n"
"  margin: 0 0 1em;\n"
"}\n"
"  .b-orange, .b-orange:before {\n"
"    background: rgba(255,193,7,1);\n"
"    background: -moz-linear-gradient(45deg, rgba(255,193,7,1) 0%, rgba(255,87,34,1) 100%);\n"
"    background: -webkit-gradient(left bottom, right top, color-stop(0%, rgba(255,193,7,1)), color-stop(100%, rgba(255,87,34,1)));\n"
"    background: -webkit-linear-gradient(45deg, rgba(255,193,7,1) 0%, rgba(255,87,34,1) 100%);\n"
"    background: -o-linear-gradient(45deg, rgba(255,193,7,1) 0%, rgba(255,87,34,1) 100%);\n"
"    background: -ms-linear-gradient(45deg, rgba(255,193,7,1) 0%, rgba(255,87,34,1) 100%);\n"
"    background: linear-gradient(45deg, rgba(255,193,7,1) 0%, rgba(255,87,34,1) 100%);\n"
"    filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#ffc107', endColorstr='#ff5722', GradientType=1 );\n"
"  }\n"
"  .b-blue, .b-blue:before {\n"
"    background: rgba(5,118,255,1);\n"
"    background: -moz-linear-gradient(45deg, rgba(5,118,255,1) 0%, rgba(36,248,255,1) 100%);\n"
"    background: -webkit-gradient(left bottom, right top, color-stop(0%, rgba(5,118,255,1)), color-stop(100%, rgba(36,248,255,1)));\n"
"    background: -webkit-linear-gradient(45deg, rgba(5,118,255,1) 0%, rgba(36,248,255,1) 100%);\n"
"    background: -o-linear-gradient(45deg, rgba(5,118,255,1) 0%, rgba(36,248,255,1) 100%);\n"
"    background: -ms-linear-gradient(45deg, rgba(5,118,255,1) 0%, rgba(36,248,255,1) 100%);\n"
"    background: linear-gradient(45deg, rgba(5,118,255,1) 0%, rgba(36,248,255,1) 100%);\n"
"    filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#0576ff', endColorstr='#24f8ff', GradientType=1 );\n"
"  }\n"
"\n"
".button:hover {\n"
"  text-shadow: 0px 0px 0px rgba(255, 255, 255, .75);\n"
"}\n"
".button:hover:after {\n"
"  left: 100%;\n"
"  top: 100%;\n"
"  bottom: 100%;\n"
"  right: 100%;\n"
"}\n"
".button:before {\n"
"  content: '';\n"
"  display: block;\n"
"  position: absolute;\n"
"  left: 0;\n"
"  top: 0;\n"
"  bottom: 0;\n"
"  right: 0;\n"
"  z-index: -1;\n"
"  border-radius: 5px;\n"
"  transition: all .5s;\n"
"}\n"
".button:after {\n"
"  content: '';\n"
"  display: block;\n"
"  position: absolute;\n"
"  left: 2px;\n"
"  top: 2px;\n"
"  bottom: 2px;\n"
"  right: 2px;\n"
"  z-index: -1;\n"
"  border-radius: 5px;\n"
"  transition: all .5s;\n"
"}\n"
".button2 {\n"
"  display: inline-block;\n"
"  font-size: 2em;\n"
"  margin: .5em;\n"
"  padding: .5em;\n"
"  border-radius: 5px;\n"
"  transition: all .5s;\n"
"  filter: hue-rotate(0deg);\n"
"  color: #FFF;\n"
"  text-decoration: none;\n"
"}\n"
"\n"
".rot-360-noscoop:hover {\n"
"  filter: hue-rotate(360deg);\n"
"  transform: rotate(360deg);\n"
"}\n"
".rot-135:hover {\n"
"  filter: hue-rotate(135deg);\n"
"}\n"
".rot-90:hover {\n"
"  filter: hue-rotate(90deg);\n"
"}\n"
"    </style>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>ESP8266-based 4 channel Wi-Fi switch</title>\n"
"  </head>\n"
"  <body>\n"
"<div>\n"
"      <h1>ESP8266-based 4 channel Wi-Fi switch</h1>\n"
"      <p>Developed by Maxim Bortnikov</p>\n"
"      <h4>For more information visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display</h4>\n"
"</div>\n"
"<div class=\"ctn\">\n"
"<a href=\"/ch1=ON\"\" class=\"button2 b-blue rot-135\">Turn the channel 1 on</a>\n"
"<a href=\"/ch1=OFF\"\" class=\"button2 b-orange rot-135\">Turn the channel 1 off</a>\n"
"</div>\n"
"<div class=\"ctn\">\n"
"<a href=\"/ch2=ON\"\" class=\"button2 b-blue rot-135\">Turn the channel 2 on</a>\n"
"<a href=\"/ch2=OFF\"\" class=\"button2 b-orange rot-135\">Turn the channel 2 off</a>\n"
"</div>\n"
"<div class=\"ctn\">\n"
"<a href=\"/ch3=ON\"\" class=\"button2 b-blue rot-135\">Turn the channel 3 on</a>\n"
"<a href=\"/ch3=OFF\"\" class=\"button2 b-orange rot-135\">Turn the channel 3 off</a>\n"
"</div>\n"
"<div class=\"ctn\">\n"
"<a href=\"/ch4=ON\"\" class=\"button2 b-blue rot-135\">Turn the channel 4 on</a>\n"
"<a href=\"/ch4=OFF\"\" class=\"button2 b-orange rot-135\">Turn the channel 4 off</a>\n"
"</div>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
