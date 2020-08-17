// ESP8266-based 4 channel Wi-Fi switch with display (Simple web interface)
// Developed by Maxim Bortnikov
// For more information and for the circuit of this device visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display
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
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta charset=\"utf-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<title>ESP8266-based 4 channel Wi-Fi relay</title>"); // The name of the web page
  client.println("<head> ");
  client.print("<style>");
  client.print("   body{");
  client.print("   background-color: #181818;"); // Background color
  client.print("} ");
  client.print("   p {");
  client.print( "   color: white;"); // Text color
  client.print("</style>");
  client.print("</head>");
  client.print("<body>");
  client.print("<table style=""width:100%"" text-align: center;>"); // Creating a table to store all the elements
  client.print("  <tr>");
  client.print("  <th>");
  client.print("<p>ESP8266-based 4 channel Wi-Fi relay</p>");
  client.print("<p>Developed by Maxim Bortnikov</p>");
  client.print("<p>For more information visit: https://github.com/Northstrix/ESP8266-based-4-channel-Wi-Fi-switch-with-display </p>");
  client.print("  </th>");
  client.print("  </tr>");
  client.print("  <tr>");
  client.print("<th><p> Channel 1"); // Printing the state of each channel
  client.print("  </th>");
  client.print("  </tr>");
 // client.print("  <br></br>");
  client.print("  <th>");
  client.println("<a href=\"/ch1=ON\"\"><button>ON</button></a>"); // "ON" button
  client.println("<a href=\"/ch1=OFF\"\"><button>OFF</button></a><br />"); // "OFF" button
  client.print("  </th>");
  client.print(" </tr>");
  client.print(" <tr>");
  client.print("<th><p> Channel 2");
  client.print("  </th>");
  client.print("  </tr>");
  client.print("  <br></br>");
  client.print("  <th>");
  client.println("<a href=\"/ch2=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/ch2=OFF\"\"><button>OFF</button></a><br />");
  client.print("  </th>");
  client.print("  <tr>");
  client.print("<th><p> Channel 3");
  client.print("  </th>");
  client.print("  </tr>");
//  client.print("  <br></br>");
  client.print("  <th>");
  client.println("<a href=\"/ch3=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/ch3=OFF\"\"><button>OFF</button></a><br />");
  client.print("  </th>");
  client.print(" </tr>");
    client.print(" <tr>");
  client.print("<th><p> Channel 4");
  client.print("  </th>");
  client.print("  </tr>");
//  client.print("  <br></br>");
  client.print("  <th>");
  client.println("<a href=\"/ch4=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/ch4=OFF\"\"><button>OFF</button></a><br />");
  client.print("  </th>");
  client.print(" </tr>");
  client.println("</table>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
