// Force readings MQTT broker & LED lights indicator
// Tabiah Valley 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int LEDup;
int LEDdown;
int Green = 4;
int Red = 5; 
int  Force = A0;
int ForceReading;
int  force1;
int  force2;
const char* ssid = "HDKF 4G";
const char* password = "079640585asdf";
const char* mqtt_server = "mqtt.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("tvt", "hello world");
      // ... and resubscribe
      client.subscribe("tvt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(Green, OUTPUT);
pinMode(Red, OUTPUT);
 delay(1000);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
    
  }

  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 200) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "%d",ForceReading);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("tvt", msg);
    ForceReading = analogRead(A0);
    LEDup = map(ForceReading, 0, 1023, 0, 255);
    LEDdown = map(ForceReading, 0, 1023, 255, 0);// LED gets brighter the harder you press
    analogWrite(Green, LEDup);
    analogWrite(Red, LEDdown);
   
  }
}
