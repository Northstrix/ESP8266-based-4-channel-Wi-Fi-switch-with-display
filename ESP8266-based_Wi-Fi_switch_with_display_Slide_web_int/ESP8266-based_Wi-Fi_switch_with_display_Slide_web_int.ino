// ESP8266-based 4 channel Wi-Fi switch with display (Slide web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
// Button template was designed by Julia. You can find it here: https://codepen.io/sfoxy/pen/XpOoJe
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
  client.println("</html><!DOCTYPE html>\n"
"<html>\n"
"  <head>\n"
"    <style>\n"
"body {\n"
"  background-color: #121414;\n"
"  background: radial-gradient(ellipse at bottom, #1b2735 0%, #090a0f 100%);\n"
"  height: 100vh;\n"
"  overflow: hidden;\n"
"  display: grid;\n"
"  margin-top: 20px;\n"
"}\n"
"\n"
"h4 {\n"
"  text-align: center;\n"
"  color: #DDD;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 1em;\n"
"  margin: 0 0 1em;\n"
"}\n"
"\n"
"h41 {\n"
"  text-align: center;\n"
"  color: #DDD;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 0.7em;\n"
"  margin: 0 0 1em;\n"
"}\n"
"\n"
".btn {\n"
"  border: none;\n"
"  display: block;\n"
"  text-align: center;\n"
"  cursor: pointer;\n"
"  outline: none;\n"
"  overflow: hidden;\n"
"  position: relative;\n"
"  color: #DDD;\n"
"  font-weight: 700;\n"
"  font-size: 15px;\n"
"  background-color: #222;\n"
"  padding: 17px 60px;\n"
"  margin-bottom: 30px;\n"
"  box-shadow: 0 5px 15px rgba(0,0,0,0.20);\n"
"}\n"
"\n"
".btn2 {\n"
"  border: none;\n"
"  display: block;\n"
"  text-align: center;\n"
"  cursor: pointer;\n"
"  text-transform: uppercase;\n"
"  outline: none;\n"
"  overflow: hidden;\n"
"  position: relative;\n"
"  color: #fff;\n"
"  font-weight: 700;\n"
"  font-size: 15px;\n"
"  background-color: #222;\n"
"  padding: 17px 60px;\n"
"  margin-bottom: 30px;\n"
"  box-shadow: 0 5px 15px rgba(0,0,0,0.20);\n"
"}\n"
"\n"
".btn span {\n"
"  position: relative; \n"
"  z-index: 1;\n"
"}\n"
"\n"
".btn2 span {\n"
"  position: relative; \n"
"  z-index: 1;\n"
"}\n"
"\n"
".btn:after {\n"
"  content: \"\";\n"
"  position: absolute;\n"
"  left: 0;\n"
"  top: 0;\n"
"  height: 490%;\n"
"  width: 140%;\n"
"  background: #298149;\n"
"  -webkit-transition: all .5s ease-in-out;\n"
"  transition: all .5s ease-in-out;\n"
"  -webkit-transform: translateX(-98%) translateY(-25%) rotate(45deg);\n"
"  transform: translateX(-98%) translateY(-25%) rotate(45deg);\n"
"}\n"
"\n"
".btn2:after {\n"
"  content: \"\";\n"
"  position: absolute;\n"
"  left: 0;\n"
"  top: 0;\n"
"  height: 490%;\n"
"  width: 140%;\n"
"  background: #81293E;\n"
"  -webkit-transition: all .5s ease-in-out;\n"
"  transition: all .5s ease-in-out;\n"
"  -webkit-transform: translateX(-98%) translateY(-25%) rotate(45deg);\n"
"  transform: translateX(-98%) translateY(-25%) rotate(45deg);\n"
"}\n"
"\n"
".btn:hover:after {\n"
"  -webkit-transform: translateX(-9%) translateY(-25%) rotate(45deg);\n"
"  transform: translateX(-9%) translateY(-25%) rotate(45deg);\n"
"}\n"
"\n"
".btn2:hover:after {\n"
"  -webkit-transform: translateX(-9%) translateY(-25%) rotate(45deg);\n"
"  transform: translateX(-9%) translateY(-25%) rotate(45deg);\n"
"}\n"
"    </style>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>ESP8266-based 4 channel Wi-Fi switch</title>\n"
"      </head>\n"
"  <body>    \n"
"    <table style=\"margin-left:auto;margin-right:auto;text-align:center;max-width: 320px\";>\n"
"  <tr>\n"
"    <th colspan=\"2\"><h4>ESP8266-based 4 channel Wi-Fi switch</h4></th>\n"
"  </tr>\n"
"  <tr>\n"
"    <td colspan=\"2\"><h4>Developed by Maxim Bortnikov</h4></td>\n"
"  </tr>\n"
"   <tr>\n"
"    <td colspan=\"2\"><h4>Channel 1</h4></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td><a href=\"/ch1=ON\"\" button class=\"btn\"><span>ON</span></button></td>\n"
"    <td><a href=\"/ch1=OFF\"\" button class=\"btn2\"><span>OFF</span></button></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td colspan=\"2\"><h4>Channel 2</h4></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td><a href=\"/ch2=ON\"\" button class=\"btn\"><span>ON</span></button></td>\n"
"    <td><a href=\"/ch2=OFF\"\" button class=\"btn2\"><span>OFF</span></button></td>\n"
"  </tr>\n"
"      <td colspan=\"2\"><h4>Channel 3</h4></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td><a href=\"/ch3=ON\"\" button class=\"btn\"><span>ON</span></button></td>\n"
"    <td><a href=\"/ch3=OFF\"\" button class=\"btn2\"><span>OFF</span></button></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td colspan=\"2\"><h4>Channel 4</h4></td>\n"
"  </tr>\n"
"     <tr>\n"
"    <td><a href=\"/ch4=ON\"\" button class=\"btn\"><span>ON</span></button></td>\n"
"    <td><a href=\"/ch4=OFF\"\" button class=\"btn2\"><span>OFF</span></button></td>\n"
"      <tr>\n"
"    <td colspan=\"2\"><h41>For more information visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display</h41></td>\n"
"  </tr>\n"
"  </tr>\n"
"</table>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
