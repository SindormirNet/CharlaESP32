#include <WiFi.h>

const char* ssid     = "sindormir.net";
const char* password = "aquituclave"";

WiFiServer server(80);

char linebuf[80];
int charcount=0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {    
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Conectado!. IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println();
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1>ESP32 - Web Server</h1>");
          client.println("<p>LED <br><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>");          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
          if (strstr(linebuf,"GET /on") > 0){
            Serial.println("LED ON");
            digitalWrite(BUILTIN_LED, HIGH);
          }
          else if (strstr(linebuf,"GET /off") > 0){
            Serial.println("LED OFF");
            digitalWrite(BUILTIN_LED, LOW);
          }          
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
   
    delay(1);
    client.stop();
    Serial.println("Cliente desconectado");
  }
}

