#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
//#include <PubSubClient.h>
#include <ArduinoMqttClient.h>

#include <header.h>

String IP = "-1.-1.-1.-1";
String MAC = "";

//ntp things
static const char* ntpserver = "pool.ntp.org";
static long gmtoffset_sec = 3600;
static int daylightoffset_sec = 3600;

char time_str[32];
char mqtt_time[32];

unsigned long tasktime = millis();
const unsigned long timeout = 30000;

//mqtt things
char broker[] = "192.168.103.126";
const int port = 1883;
static String clientid = "";
const char* topic = "";

/*
const char* broker = "192.168.103.126";
static uint16_t port = 1883;
*/

String message;
int sepIndex = message.indexOf(';');

WiFiClient espClient;
//PubSubClient client(espClient);
MqttClient mqttClient(espClient);

void connectwifi(String mode) {
    WiFi.mode(WIFI_STA);
    if (mode == "normal") {
        WiFi.begin(ssid, password);
    } else if (mode == "fallback") {
        WiFi.begin(ssidfallback, passwordfallback);
    }
    
    Serial.println("Connecting to WiFi Network ...");
    delay(2000);

    //wait until wifi is connected 
    while(WiFi.status() != WL_CONNECTED && millis() - tasktime < timeout) {
        Serial.print(".");
        delay(100);
    }
  
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to the " + String(ssid) + " network");
        IP = WiFi.localIP().toString();
        MAC = WiFi.macAddress();

        Serial.println("IP:" + IP);
        Serial.println("Mac:"+ MAC);
    } else {
        if (ssid == ssidfallback && password == passwordfallback) {
            errormenu(2);
            esp_sleep_enable_timer_wakeup(300000000);
            esp_deep_sleep_start();
        } else {
            connectwifi("fallback");
        }
    }
}

void rtctimeset() {
    configTime(gmtoffset_sec, daylightoffset_sec, ntpserver);
    struct tm timeinfo;
    getLocalTime(&timeinfo);

    Serial.println(&timeinfo, "Aktuelle Zeit: %Y-%m-%d %H:%M:%S");

    strftime(time_str, sizeof(time_str), "%d.%m.%Y um %H:%M:%S", &timeinfo); 
    strftime(mqtt_time, sizeof(mqtt_time), "%H:%M:%S", &timeinfo); 
}

/*void connectmqtt() {
    client.setServer(broker, port);
    client.setCallback(callback);
    Serial.println("Try connecting to the MQTT Server ...");
    while (!client.connected()) {
        if (client.connect(String(id).c_str())) {
            client.subscribe(topic);
            Serial.println("Connecting to the MQTT Server!");
        } else {
            errormenu(3);
            esp_sleep_enable_timer_wakeup(300000000);
            esp_deep_sleep_start();
        }
    }
}
    */

void connectmqtt() {
    Serial.println("Try connecting to the MQTT Server ...");
    unsigned long start = millis();
    if (!mqttClient.connect(broker, port)) {
        delay(500);
        if (millis() - start > 5000) {
            errormenu(3);
            esp_sleep_enable_timer_wakeup(300000000);
            esp_deep_sleep_start();
        }
    }
    mqttClient.subscribe(topic);
    Serial.println("Connected to the MQTT Server!");
}

void sendmqtthello() {
    Serial.println("Send Hello Messange over MQTT");

    mqttClient.beginMessage(topic);
    String message = "hello; "+clientid+"; 100;"+mqtt_time+"";
    mqttClient.print(message);
    mqttClient.endMessage();

}

void waitofinitmsg() {
    mqttClient.poll();
    delay(10);
}

/* void sendmqtthello() {
    Serial.println("Send Hello Messange over MQTT");
    String message = "hello; "+clientid+"; 100;"+mqtt_time+"";
    client.publish(topic, message.c_str());
}

void waitofinitmsg(boolean status) {
    while (status)
    {
        client.loop();
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        String message;
        message += (char)payload[i];
    }
    Serial.println(message);
    delay(100);


    //if (sepIndex != -1) {
      //  String command = message.substring(0, sepIndex);
       // command.trim();  // Leerzeichen entfernen

        //String mclient = message.substring(sepIndex + 1);
        //mclient.trim();

        //Serial.println("Command: " + command);
        //Serial.println("Client: " + mclient);
    //}
} */
