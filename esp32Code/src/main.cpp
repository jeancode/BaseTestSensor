#include <Arduino.h>
#include <SparkFunMPU9250-DMP.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define BUTTON_PIN 15 // Pin conectado al botón


// Configuración Wi-Fi
const char* ssid = "NameRedPassword";           // Reemplaza con tu SSID
const char* password = "password";   // Reemplaza con tu contraseña

// Configuración UDP
WiFiUDP udp;
const char* serverAddress = "192.168.0.193"; // Dirección IP del servidor UDP
const int serverPort = 50;                // Puerto del servidor UDP
bool state = false;



void setup() {
  Serial.begin(115200);

  // Conectar al Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado al Wi-Fi");
  Serial.print("Dirección IP local: ");
  Serial.println(WiFi.localIP());

  pinMode(BUTTON_PIN, INPUT_PULLUP);



}

bool dataSend = 0;

void loop() {

  state =  digitalRead(BUTTON_PIN);

  if(state != dataSend){


    Serial.println("Datos del sensor:"+String(state));

    String data = String(state);

    
    // Enviar datos al servidor UDP
    udp.beginPacket(serverAddress, serverPort);
    udp.print(data);

    if (udp.endPacket() == 1) {
        Serial.println("Datos enviados al servidor UDP");
    } else {
        Serial.println("Error al enviar datos");
    }

    Serial.println("Datos enviados al servidor UDP: " + data);

    dataSend = state;
  }




   delay(10);
}
