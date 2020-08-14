// Attenion!!! This interface doesn't work correctly on mobile devices.
// ESP8266-based 4 channel Wi-Fi switch with display (Green web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
// Button template was designed by Sarah Fossheim. You can find it here: https://codepen.io/fossheim/pen/RwPeVKG
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
":root {\n"
"  background: #121914;\n"
"  --light: #92DE34;\n"
"  --dark: #69BC22;\n"
"  --text: #FFF;\n"
"}\n"
"\n"
"body {\n"
"  background-color: var(--background);\n"
"  background-image: linear-gradient(\n"
"    var(--background-accent-2) 50%,\n"
"    var(--background-accent) 50%\n"
"  ), linear-gradient(\n"
"    var(--background-accent) 50%,\n"
"    var(--background-accent-2) 50%\n"
"  );\n"
"  background-repeat: no-repeat;\n"
"  background-size: 100% 30px;\n"
"  background-position: top left, bottom left;\n"
"  min-height: 98vh;\n"
"}\n"
"p {\n"
"  color: white;\n"
"  text-align: center;\n"
"  }\n"
"  \n"
".item {\n"
"    font-size: 1.6rem;\n"
"    color: #FFF;\n"
"    border: 0px solid #EEE;\n"
"}\n"
".container {\n"
"    display: grid;\n"
"}\n"
".buttons {\n"
"    height: 50px;\n"
"    grid-template-columns: 105px 105px;\n"
"  \n"
"}\n"
"\n"
"div {\n"
"  display: block;\n"
"  width: 210px;\n"
"  margin: 0 auto 0 auto;\n"
"  position: relative;\n"
"  left: 0;\n"
"  right: 0;\n"
"  top: 5vh;\n"
"}\n"
"\n"
"button {\n"
"  display: block;\n"
"  cursor: pointer;\n"
"  outline: none;\n"
"  border: none;\n"
"  background-color: var(--light);\n"
"  width: 100px;\n"
"  height: 45px;\n"
"  border-radius: 45px;\n"
"  font-size: 1.5rem;\n"
"  font-weight: 600;\n"
"  color: var(--text);\n"
"  background-size: 100% 100%;\n"
"  box-shadow: 0 0 0 7px var(--light) inset;\n"
"  margin-bottom: 15px;\n"
"}\n"
"\n"
"button:hover {\n"
"  background-image: linear-gradient(\n"
"    145deg,\n"
"    transparent 10%,\n"
"    var(--dark) 10% 20%,\n"
"    transparent 20% 30%,\n"
"    var(--dark) 30% 40%,\n"
"    transparent 40% 50%,\n"
"    var(--dark) 50% 60%,\n"
"    transparent 60% 70%,\n"
"    var(--dark) 70% 80%,\n"
"    transparent 80% 90%,\n"
"    var(--dark) 90% 100%\n"
"  );\n"
"  animation: background 3s linear infinite;\n"
"}\n"
"\n"
"@keyframes background {\n"
"  0% {\n"
"    background-position: 0 0;\n"
"  }\n"
"  100% {\n"
"    background-position: 400px 0;\n"
"  }\n"
"}\n"
"    </style>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width\">\n"
"    <title>ESP8266-based 4 channel Wi-Fi switch with display</title>\n"
"  </head>\n"
"  <body>\n"
"    <div>\n"
"       <p>ESP8266-based 4 channel Wi-Fi switch with display</p>\n"
"       <p>Developed by Maxim Bortnikov</p>\n"
"       <p>For more information visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display </p>\n"
"    </div>\n"
"    <div>\n"
"      <p>Channel 1</p>\n"
"    </div>\n"
"    <div class=\"container buttons\">\n"
"      <a href=\"/ch1=ON\"\"><button>ON</button></a>\n"
"      <a href=\"/ch1=OFF\"\"><button>OFF</button></a>\n"
"    </div>\n"
"    <div>\n"
"      <p>Channel 2</p>\n"
"    </div>\n"
"    <div class=\"container buttons\">\n"
"      <a href=\"/ch2=ON\"\"><button>ON</button></a>\n"
"      <a href=\"/ch2=OFF\"\"><button>OFF</button></a>\n"
"    </div>\n"
"    <div>\n"
"      <p>Channel 3</p>\n"
"    </div>\n"
"    <div class=\"container buttons\">\n"
"      <a href=\"/ch3=ON\"\"><button>ON</button></a>\n"
"      <a href=\"/ch3=OFF\"\"><button>OFF</button></a>\n"
"    </div>\n"
"    <div>\n"
"      <p>Channel 4</p>\n"
"    </div>\n"
"    <div class=\"container buttons\">\n"
"      <a href=\"/ch4=ON\"\"><button>ON</button></a>\n"
"      <a href=\"/ch4=OFF\"\"><button>OFF</button></a>\n"
"    </div>\n"
"  </body>\n"
"</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
