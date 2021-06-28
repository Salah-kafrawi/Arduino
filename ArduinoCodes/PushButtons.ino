// Push buttons indicators
// Taibah Valley
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int BUTTON_PIN = 4; //Button is connected to GPIO 5
int BUTTON_PIN2= 5; //Button is connected to GPIO 4
int status1;
int status2;
// Update these with values suitable for your network.
const char* ssid = "*****";//put your wifi ssid here
const char* password = "*****";//put your wifi password here.
const char* mqtt_server = "mqtt.eclipse.org";
//const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("OsoyooCommand");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(BUTTON_PIN,INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  int status;
  //send message every 2 second
  if (now - lastMsg > 1000) {
     lastMsg = now;
     status1= status =digitalRead(BUTTON_PIN);
     status2= status= digitalRead(BUTTON_PIN2);
    
     String msg="Water Bottle A\t Water Bottle B\n";
    { if(status1==HIGH )
     {
        msg= msg+ "attached\t   ";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("tvt", message);
       }
     else
     {
      msg= msg+ " Not attached";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("tvt", message);
     }}
     {

if (status2==HIGH )
     {
        msg= msg+ "\t attached";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("tvt", message);
       }
     else
     {
      msg= msg+ "\tNot attached";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("tvt", message);
     }
      
      }
    }
     
}
