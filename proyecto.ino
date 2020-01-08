
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PubSubClient.h>
#include "WiFi.h"
#include <DHT.h>

/******************************DISPLAY*********************************************/
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  18 //default 9
#define OLED_CLK   5 //default 10
#define OLED_DC    27 //default 11
#define OLED_CS    12
#define OLED_RESET 13

#define SCREEN_WIDTH 128 // Anchura del display en pixeles
#define SCREEN_HEIGHT 64 //Altura del display en pixeles

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

  
/*********************************  valores para el zumbaor  **************************************/
#define zumbador A0//pendiente

/*********************************  valores para la conexion con ubidots  **************************************/
#define TOKEN "BBFF-BHYz9cvSDQyJVRZrA0ndtBW4Sb1QJC" // Put your Ubidots' TOKEN           
#define MQTT_CLIENT_NAME "esp32" // nombre que usara la placa para publicar
#define VARIABLE_LABEL_1 "DHT11" // Assing the variable label
#define VARIABLE_LABEL_2 "MQ6" // Assing the variable label
#define VARIABLE_LABEL_3 "MQ7" // Assing the variable label
#define VARIABLE_LABEL_4 "mq135" // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

char mqttBroker[]  = "ldhiot7.industrial.ubidots.com";
char payload[100];
char topic[150];

// Space to store values to send
char str_sensor[10];
char str_lat[6];
char str_lng[6];
WiFiClient ubidots;
PubSubClient client(ubidots);

/******************pines de los sensores conectados****************************************/
#define mq135 A3  /*entrada digital humo*/
#define mq7 A4    /*entrada digital monoxido de carbono*/
#define mq6 A2    /*entrada digital gas lp*/
#define dht11 A1  /*entrada digital temperatura*/


// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(dht11, DHTTYPE);
//*****************************variables para el wifi**********************************************
const char* ssid = "villa";
const char* password = "villa12345";

void setup() {
  Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC); // Inicia la comunicacion.
  conectar_wifi();  
  //inicia la comuniacion con el servidor de ubidots
  client.setServer(mqttBroker, 1883); 
  client.setCallback(callback); 
  pinMode(zumbador, OUTPUT);
  dht.begin();
}

void conectar_wifi(){
  WiFi.begin(ssid, password); /*Conectarse a la inalambrica*/
}

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {//reconectar al servidor de ubidots
  client.connect(MQTT_CLIENT_NAME, TOKEN, "");
}

void publicar_variable1(){
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL_1); // Adds the variable label
  float sensor = dht.readTemperature();; 
  float lat = 6.101;
  float lng= -1.293;

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  dtostrf(lat, 4, 2, str_lat);
  dtostrf(lng, 4, 2, str_lng);  
  
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor); // Adds the value
  sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);
}

void publicar_variable2(){
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL_2); // Adds the variable label
  float sensor = analogRead(mq6); 
  float lat = 6.101;
  float lng= -1.293;

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  dtostrf(lat, 4, 2, str_lat);
  dtostrf(lng, 4, 2, str_lng);  
  
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor); // Adds the value
  sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);  
}
void publicar_variable3(){
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL_3); // Adds the variable label
  float sensor = analogRead(mq7); 
  float lat = 6.101;
  float lng= -1.293;

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  dtostrf(lat, 4, 2, str_lat);
  dtostrf(lng, 4, 2, str_lng);  
  
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor); // Adds the value
  sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);  
}
void publicar_variable4(){
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL_4); // Adds the variable label
  float sensor = analogRead(mq135); 
  float lat = 6.101;
  float lng= -1.293;

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  dtostrf(lat, 4, 2, str_lat);
  dtostrf(lng, 4, 2, str_lng);  
  
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor); // Adds the value
  sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);  
}

void loop() {
  int adc_mq135 = 0;
  int adc_mq7 = 0;
  int adc_mq6 = 0;
  int adc_dht11 = 0;
  
  display.clearDisplay();             //Limpiar pantalla
  display.setTextSize(1);             // tamaño de letra  
  display.setTextColor(BLACK);        // color del texto
  
  //validar si esta conectado
  if(WiFi.status() == WL_CONNECTED)
  {
    display.fillRect(0, 0, 128, 10, WHITE);
    display.setCursor(2,2);
    display.println(String("Conectado: ")+ssid);
  }
  else
  {
    display.fillRect(0, 0, 128, 10, WHITE);
    display.setCursor(2,2);
    display.println(String("No conectado"));
    
    conectar_wifi();
  }  
   
  display.drawRect(0, 10, 128, 53, WHITE);
  display.setTextColor(WHITE);
  /* descomentar lo siguiente si se quiere mostrar la ip*/ 
  //display.setCursor(1,13);
  //display.println("IP:");
  //display.setCursor(20,13);
  //display.println(WiFi.localIP());

  //lectura para el mq135
  adc_mq135 = analogRead(mq135);
  display.setCursor(2,14);
  display.println(String("Humo: ")+adc_mq135+String(" PPM"));
  
  //lectura para el mq7
  display.setCursor(2,24);  
  adc_mq7 = analogRead(mq7);
  display.println(String("CO: ")+adc_mq7+String(" PPM") );

  //lectura para el mq6
  display.setCursor(2,34);  
  adc_mq6 = analogRead(mq6);
  display.println(String("LP: ")+adc_mq6+String(" PPM") );

  //lectura para el DHT11
  display.setCursor(2,44);  
  adc_dht11 = dht.readTemperature();
  display.println(String("temperatura: ")+adc_dht11+String(" °") );

  if(adc_mq135>2000 || adc_mq7>2000 || adc_mq6>200 || adc_dht11>35)
  {
    digitalWrite(zumbador, HIGH);    // inicia el zumbido
    delay(2000);                    
    digitalWrite(zumbador, LOW); 
    delay(1000);                                
  }
  else
  {
    digitalWrite(zumbador, LOW);              // lo detiene a los dos segundos
  }

  display.fillRect(0, 50, 128, 12, WHITE);
  display.setTextColor(BLACK);
  if (!client.connected()) {
    display.setCursor(2,51);
    display.println("No conectado");
    digitalWrite(zumbador, HIGH);    // inicia el zumbido
    delay(2000);                    
    digitalWrite(zumbador, LOW);              // lo detiene a los dos segundos
    reconnect();
  }
  else
  {
    display.setCursor(1,51);
    display.println("conectado/publicando");
    publicar_variable1();
    publicar_variable2();
    publicar_variable3();
    publicar_variable4();
    client.loop();
  } 
  delay(2000);
  display.display();
}
