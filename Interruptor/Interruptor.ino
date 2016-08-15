
#include <ESP8266WiFi.h>
#include <Wire.h>


WiFiServer server(80);                     // WebServer

const char* ssid = "<WIFI_HERE>";
const char* password = "<wifi_password_here>";


void setup() {

  Serial.begin(9600);

  pinMode(13, OUTPUT);

  // config static IP
  IPAddress ip(192, 168, 1, 101); // where xx is the desired IP Address
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
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  //Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/SWITCH_STATE") != -1)  {
    // AQUI VC MUDA O ESTADO DO RELÉ
    Serial.println("Cheguei aqui");
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.println("<br><br>");
  client.println("<a href=\"/SWITCH_STATE\"\"><button>Switch Light State</button></a>");
  client.println("</html>");
 
  delay(1);
  //Serial.println("Client disconnected");
  Serial.println("");
}

