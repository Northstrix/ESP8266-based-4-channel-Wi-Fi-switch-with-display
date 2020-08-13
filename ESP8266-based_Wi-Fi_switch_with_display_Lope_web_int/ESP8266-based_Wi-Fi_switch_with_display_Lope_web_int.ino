// ESP8266-based 4 channel Wi-Fi switch with display (Lope web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
// Button template was designed by masuwa. You can find it here: https://codepen.io/ma_suwa/pen/qBBYKNy
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
"      body {\n"
"    margin: 0;\n"
"    height: 100vh;\n"
"    display: flex;\n"
"    align-items: top;\n"
"    justify-content: center;\n"
"    background: #141818;\n"
"    width: 300px;\n"
"    margin: auto;\n"
"}\n"
"p {\n"
"  color: white;\n"
"  text-align: center;\n"
"  }\n"
"ul {\n"
"    justify-content: center;\n"
"    padding: 0;\n"
"    list-style-type: none;\n"
"    \n"
"}\n"
"\n"
"\n"
"ul li {\n"
"    box-sizing: border-box;\n"
"    width: 15em;\n"
"    height: 3em;\n"
"    font-size: 20px;\n"
"    border-radius: 0.5em;\n"
"    margin: 0.5em;\n"
"    box-shadow: 0 0 1em rgba(0,0,0,0.2);\n"
"    color: white;\n"
"  \tfont-family: Arial,Helvetica Neue,Helvetica,sans-serif; \n"
"    line-height: 3em;\n"
"    transition: 0.3s;\n"
"    cursor: pointer;\n"
"}\n"
"\n"
"ul li:nth-child(odd) {\n"
"    background: linear-gradient(to right, #0066ff, #ff0080);\n"
"    text-align: left;\n"
"    padding-left: 10%;\n"
"    transform: perspective(500px) rotateY(45deg);\n"
"}\n"
"\n"
"ul li:nth-child(even) {\n"
"    background: linear-gradient(to left, #0066ff, #ff0080);\n"
"    text-align: right;\n"
"    padding-right: 10%;\n"
"    transform: perspective(500px) rotateY(-45deg);\n"
"}\n"
"\n"
"ul li:nth-child(odd):hover {\n"
"    transform: perspective(200px) rotateY(45deg);\n"
"    padding-left: 5%;\n"
"}\n"
"\n"
"ul li:nth-child(even):hover {\n"
"    transform: perspective(200px) rotateY(-45deg);\n"
"    padding-right: 5%;\n"
"}\n"
"\n"
"    </style>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>ESP8266-based 4 channel Wi-Fi switch with display</title>\n"
"  </head>\n"
"  <body>\n"
"    <ul>\n"
"        <p>ESP8266-based 4 channel Wi-Fi switch with display</p>\n"
"        <p>Developed by Maxim Bortnikov</p>\n"
"        <p>For more information visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display </p>\n"
"   </br>\n"
"    <a href=\"/ch1=ON\"\"><li>Turn the channel 1 ON</li></a>\n"
"    <a href=\"/ch1=OFF\"\"><li>Turn the channel 1 OFF</li></a>\n"
"    <a href=\"/ch2=ON\"\"><li>Turn the channel 2 ON</li></a>\n"
"    <a href=\"/ch2=OFF\"\"><li>Turn the channel 2 OFF</li></a>\n"
"    <a href=\"/ch3=ON\"\"><li>Turn the channel 3 ON</li></a>\n"
"    <a href=\"/ch3=OFF\"\"><li>Turn the channel 3 OFF</li></a>\n"
"    <a href=\"/ch4=ON\"\"><li>Turn the channel 4 ON</li></a>\n"
"    <a href=\"/ch4=OFF\"\"><li>Turn the channel 4 OFF</li></a>\n"
"</ul>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
