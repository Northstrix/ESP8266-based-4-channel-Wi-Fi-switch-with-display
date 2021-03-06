// ESP8266-based 4 channel Wi-Fi switch with display (Ascend blue web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
// Button template was designed by Chance Squires. You can find it here: https://codepen.io/chancesq/pen/ExVGxJR
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
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>Switch</title>\n"
"    <style>\n"
"      * {\n"
"\tmargin: 0;\n"
"\tpadding: 0;\n"
"\tbox-sizing: border-box;\n"
"}\n"
"\n"
"body {\n"
"\theight: 100vh;\n"
"\toverflow: hidden;\n"
"\tdisplay: flex;\n"
"\talign-items: top;\n"
"  margin-top: 7.5vh;\n"
"\tjustify-content: center;\n"
"\tbackground-color: #045de9;\n"
"\tbackground-image: linear-gradient(315deg, #045de9 0%, #09c6f9 74%);\n"
"}\n"
"h4 {\n"
"  text-align: center;\n"
"  color: #FFF;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 1em;\n"
"  margin: 0 0 1em;\n"
"  margin-top: 20px;\n"
"}\n"
"a{text-decoration:none}\n"
".noselect {\n"
"  -webkit-touch-callout: none;\n"
"    -webkit-user-select: none;\n"
"     -khtml-user-select: none;\n"
"       -moz-user-select: none;\n"
"        -ms-user-select: none;\n"
"            user-select: none;\n"
"\t\t-webkit-tap-highlight-color: transparent;\n"
"}\n"
"\n"
".rainbow {\n"
"\twidth: 135px;\n"
"\theight: 40px;\n"
"\tcursor: pointer;\n"
"\tfont-family: Segoe UI,Frutiger,Frutiger Linotype,Dejavu Sans,Helvetica Neue,Arial,sans-serif; \n"
"\tfont-size: 32px;\n"
"\tcolor: white;\n"
"\tborder: none;\n"
"\tbox-shadow: inset 1px 1px 4px rgba(0,0,0,0.6), inset -1px -1px 4px rgba(255,255,255,0.2);\n"
"\tbackground-color: #63a4ff;\n"
"\tbackground-image: linear-gradient(315deg, #045de9 0%, #09c6f9 74%);\n"
"\t-webkit-tap-highlight-color: transparent;\n"
"}\n"
"\n"
".rainbow:hover {\n"
"\tanimation: rainbow 3s infinite linear;\n"
"}\n"
"\n"
"@keyframes rainbow {\n"
"\tto {\n"
"\t\tfilter: hue-rotate(360deg);\n"
"\t}\n"
"}\n"
"\n"
".rainbow:focus {\n"
"\toutline: none;\n"
"}\n"
"    </style>\n"
"  </head>\n"
"  <body>\n"
"    <table style=margin-left:auto;margin-right:auto;text-align:center;max-width:350px>\n"
"\n"
"<tr>\n"
"<th colspan=\"2\"><h4>ESP8266-based 4 channel Wi-Fi switch</h4></th>\n"
"</tr>\n"
"<tr>\n"
"<td colspan=\"2\"><h4>Developed by Maxim Bortnikov</h4></td>\n"
"</tr>\n"
"<tr>\n"
"<td colspan=\"2\"><h4>Channel 1</h4></td>\n"
"</tr>\n"
"<tr>\n"
"<td><a href=\"/ch1=ON\"\" button class=\"rainbow noselect\">&nbsp;&emsp;ON&emsp;&nbsp;</button></td>\n"
"<td><a href=\"/ch1=OFF\"\" button class=\"rainbow noselect\">&nbsp;&emsp;OFF&emsp;&nbsp;</button></td>\n"
"</tr>\n"
"<tr>\n"
"<td colspan=\"2\"><h4>Channel 2</h4></td>\n"
"</tr>\n"
"<tr>\n"
"<td><a href=\"/ch2=ON\"\" button class=\"rainbow noselect\">&nbsp;&emsp;ON&emsp;&nbsp;</button></td>\n"
"<td><a href=\"/ch2=OFF\"\" button class=\"rainbow noselect\">&nbsp;&emsp;OFF&emsp;&nbsp;</button></td>\n"
"</tr>\n"
"<tr>\n"
"<td colspan=\"2\"><h4>Channel 3</h4></td>\n"
"</tr>\n"
"<tr>\n"
"<td><a href=\"/ch3=ON\"\" button class=\"rainbow noselect\">&nbsp;&emsp;ON&emsp;&nbsp;</button></td>\n"
"<td><a href=\"/ch3=OFF\"\" button class=\"rainbow noselect\">&nbsp;&emsp;OFF&emsp;&nbsp;</button></td>\n"
"</tr>\n"
"<tr>\n"
"<td colspan=\"2\"><h4>Channel 4</h4></td>\n"
"</tr>\n"
"<tr>\n"
"<td><a href=\"/ch4=ON\"\" button class=\"rainbow noselect\">&nbsp;&emsp;ON&emsp;&nbsp;</button></td>\n"
"<td><a href=\"/ch4=OFF\"\" button class=\"rainbow noselect\">&nbsp;&emsp;OFF&emsp;&nbsp;</button></td>\n"
"</tr>\n"
"</table>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
