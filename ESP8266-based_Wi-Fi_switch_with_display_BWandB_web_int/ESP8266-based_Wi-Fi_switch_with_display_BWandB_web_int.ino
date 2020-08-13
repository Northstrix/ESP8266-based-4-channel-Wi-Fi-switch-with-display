// ESP8266-based 4 channel Wi-Fi switch with display (Black, white and blue web interface)
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
"      * {\n"
"  box-sizing: border-box;\n"
"}\n"
"\n"
"/* Create two equal columns that floats next to each other */\n"
".column {\n"
"  float: left;\n"
"  width: 100px;\n"
"    display: inline-block;\n"
"  align-items: center;\n"
"  display: flex;\n"
"  flex-direction: column;\n"
"  justify-content: top;\n"
"  text-align: center;\n"
"}\n"
"\n"
"\n"
"\n"
"{\n"
"  margin: 0;\n"
"  padding: 0;\n"
"}\n"
"\n"
"body {\n"
"\n"
"  background: #121414;\n"
"  font-family: Segoe UI,Frutiger,Frutiger Linotype,Dejavu Sans,Helvetica Neue,Arial,sans-serif; \n"
"  font-weight: 400;\n"
"    box-sizing: border-box;\n"
"  height: 99%;\n"
"  width: 99%;\n"
"}\n"
"\n"
".buttons {\n"
"  display: flex;\n"
"  flex-direction: row;\n"
"      flex-wrap: wrap;\n"
"  justify-content: center;\n"
"  text-align: center;\n"
"  width: 100%;\n"
"  height: 100%;\n"
"  margin: 0 auto;\n"
"/*   padding: 2em 0em; */\n"
"}\n"
"\n"
".container {\n"
"  display: inline-block;\n"
"  align-items: center;\n"
"  display: flex;\n"
"  flex-direction: column;\n"
"  justify-content: top;\n"
"  text-align: center;\n"
"  background-color: #EEE;\n"
"  padding:  40px 0px;\n"
"  width: 300px;\n"
"}\n"
"\n"
"h1 {\n"
"  text-align: center;\n"
"  color: #444;\n"
"  letter-spacing: 0.05em;\n"
"  margin: 0 0 0.4em;\n"
"  font-size: 1em;\n"
"}\n"
"\n"
"p {\n"
"  text-align: left;\n"
"  color: #444;\n"
"  letter-spacing: 0.05em;\n"
"  font-size: 0.8em;\n"
"  margin: 0 0 2em;\n"
"}\n"
"\n"
"\n"
".btn {\n"
"  letter-spacing: 0.1em;\n"
"  cursor: pointer;\n"
"  font-size: 14px;\n"
"  font-weight: 400;\n"
"  line-height: 45px;\n"
"  max-width: 90px;\n"
"  position: relative;\n"
"  text-decoration: none;\n"
"  text-transform: uppercase;\n"
"  width: 100%;\n"
"}\n"
".btn:hover {\n"
"  text-decoration: none;\n"
"}\n"
"\n"
"/*btn_background*/\n"
".effect04 {\n"
"  --uismLinkDisplay: var(--smLinkDisplay, inline-flex);\n"
"  display: var(--uismLinkDisplay);\n"
"  color: #000;\n"
"  outline: solid  2px #000;\n"
"  position: relative;\n"
"  transition-duration: 0.4s;\n"
"  overflow: hidden;\n"
"}\n"
"\n"
".effect04::before,\n"
".effect04 span{\n"
"    margin: 0 auto;\n"
"\ttransition-timing-function: cubic-bezier(0.86, 0, 0.07, 1);\n"
"\ttransition-duration: 0.4s;\n"
"}\n"
"\n"
"/* 文字1を上に */\n"
".effect04:hover{\n"
"\n"
"  background-color: #007BEB;\n"
"}\n"
"\n"
"/* HOVERしたら文字1を上に */\n"
".effect04:hover span{\n"
"  -webkit-transform: translateY(-400%) scale(-0.1,20);\n"
"          transform: translateY(-400%) scale(-0.1,20);\n"
"}\n"
"\n"
"/*文字2*/\n"
".effect04::before{\n"
"  content: attr(data-sm-link-text);\n"
"\tcolor: #FFF;\n"
"  position: absolute;\n"
"  left: 0;\n"
"  right: 0;\n"
"  margin: auto;\n"
"  -webkit-transform: translateY(500%) scale(-0.1,20);\n"
"          transform: translateY(500%) scale(-0.1,20);\n"
"}\n"
"\n"
"/* HOVERしたら文字2を上に */\n"
".effect04:hover::before{\n"
"  letter-spacing: 0.05em;\n"
"  -webkit-transform: translateY(0) scale(1,1);\n"
"          transform: translateY(0) scale(1,1);\n"
"}\n"
"    \n"
"</style>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>ESP8266-based 4 channel Wi-Fi switch with display</title>\n"
"    \n"
"  </head>\n"
"  <body>\n"
"  <div class=\"buttons\">\n"
"  <div class=\"container\">\n"
"      <h1>ESP8266-based 4 channel Wi-Fi switch with display</h1>\n"
"      <p>Developed by Maxim Bortnikov</p>\n"
"            <p>Channel 1</p>\n"
"          <div class=\"row\">\n"
"  <div class=\"column\">\n"
"   <a href=\"/ch1=ON\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>ON</span></a>\n"
"  </div>\n"
"  <div class=\"column\">\n"
"  <a href=\"/ch1=OFF\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>OFF</span></a>\n"
"  </div>\n"
"</div>\n"
"</br>\n"
"            <p>Channel 2</p>\n"
"          <div class=\"row\">\n"
"  <div class=\"column\">\n"
"   <a href=\"/ch2=ON\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>ON</span></a>\n"
"  </div>\n"
"  <div class=\"column\">\n"
"  <a href=\"/ch2=OFF\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>OFF</span></a>\n"
"  </div>\n"
"</div>\n"
"</br>\n"
"             <p>Channel 3</p>\n"
"          <div class=\"row\">\n"
"  <div class=\"column\">\n"
"   <a href=\"/ch3=ON\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>ON</span></a>\n"
"  </div>\n"
"  <div class=\"column\">\n"
"  <a href=\"/ch3=OFF\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>OFF</span></a>\n"
"  </div>\n"
"</div>\n"
"</br>\n"
"            <p>Channel 4</p>\n"
"          <div class=\"row\">\n"
"  <div class=\"column\">\n"
"   <a href=\"/ch4=ON\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>ON</span></a>\n"
"  </div>\n"
"  <div class=\"column\">\n"
"  <a href=\"/ch4=OFF\"\" class=\"btn effect04\" data-sm-link-text=\"Switch\"><span>OFF</span></a>\n"
"  </br>\n"
"  </div>\n"
"</div>\n"
"  </div>\n"
"</div>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
