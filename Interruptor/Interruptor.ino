#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Wire.h>

WiFiServer server(80);                     // WebServer

const char* ssid = "<wifi_here>";
const char* password = "<password_here>";

int inPin = 4;         // D2 in the NodeMCU, from the button
int outPin = 2;       // D1 in the NodeMCU, to the relay
int ledPin = 5;       // D4 in the NodeMCU, to the LED Halo

int state = LOW;      // the current state of the output pin - defaulted to OFF in case of sudden restarts
int led = HIGH;       // current state of the LED Halo - always oposite of state

int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long moment = 0;         // the last time the output pin was toggled
long debounce = 150;   // the debounce time, increase if the output flickers


void setup() {

  Serial.begin(9600);

  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  EEPROM.begin(8);
  state = (EEPROM.read(0)!=0) ? HIGH : LOW;
  led = (EEPROM.read(0)==0) ? LOW : HIGH;
  EEPROM.end();
  digitalWrite(outPin, state);
  digitalWrite(ledPin, led);

  // config static IP
  IPAddress ip(192, 168, 1, 101); // Desired IP Address in the local network
  IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Servidor iniciado");
 
  // Print the IP address
  Serial.print("Use esta URL para conectar: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  reading = digitalRead(inPin);

  // Treatment for the Button Control
  if (reading == LOW && previous == HIGH && millis() - moment > debounce) {
    switchState();    // Switch the state of the Relay
    Serial.println("Switch State!");
    moment = millis();
    previous = reading;
    return;
  }
  previous = reading;



  // Treatment for the WiFi Control
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  if (client.available()) {
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
   
    // Match the request
   
    int value = LOW;
    if (request.indexOf("/SWITCH_STATE") != -1)  {
      client.println("HTTP/1.1 204 OK");    //Code 204: OK, no body required in response
      client.println("Content-Type: text/plain");
      client.println("");
      switchState();  //Switch the state of the Relay
      Serial.println("Switch State!");
      client.println("State Switched");
    } else {
      // Return the response
      client.println("HTTP/1.1 200 OK");  //Code 200: Ok, reponding with an html body
      client.println("Content-Type: text/html");
      client.println(""); //  THIS IS IMPORTANT do not forget this one
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
     
      client.println("<br><br>");
      client.println("<a href=\"/SWITCH_STATE\"\"><button>Switch Light State</button></a>");
      client.println("</html>");
    }
   
    delay(1);
    //Serial.println("Client disconnected");
    Serial.println("");
  }
}

void switchState() {
  EEPROM.begin(8);
  if (state == HIGH) {
    state = LOW;
    led = HIGH;
    EEPROM.write(0,0);
  } else {
    state = HIGH;
    led = LOW;
    EEPROM.write(0,1);
  }
  EEPROM.end();
    
  digitalWrite(outPin, state);
  digitalWrite(ledPin, led);
}
