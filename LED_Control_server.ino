#include<ESP8266WiFi.h>  //Including ESP8266 WiFi library
#include<ThingSpeak.h>   //Including ThingSpeak library 

 IPAddress server(192,168,4,15); //Static IP address of local server
 WiFiClient client;
 unsigned long channel = 814917;  //Replace according to your channel ID
 const char* softAPssid = "ESP8266"; //SSID of the hotspot of ESP8266 acting as local server
 const char* password = "12345678"; //Password of the hotspot of ESP8266 acting as local server
 const char* wifissid = "hello"; //SSID of WIFI router providing internet access
 const char* pass = "12345678";  // Passwprd of router providing internet acccess
 unsigned int led1 = 1; //Channel field 1
 unsigned int led2 = 2; //Channel field 2
 unsigned int led3 = 3; // Channel field 3

void setup()
{
     WiFi.mode(WIFI_AP_STA); //station mode and access point mode both at the same time
     Serial.begin(9600);  //Serial communication at baud rate of 9600 for debugging purpose
     delay(100);
     Serial.println(WiFi.getMode());
     delay(10);
     Serial.println("Setting SoftAP...");
     Serial.println(WiFi.softAP(softAPssid,password));
     delay(10);
     Serial.println(WiFi.softAPIP());
     delay(500);
     WiFi.begin(wifissid,pass);
     while(WiFi.status()!=WL_CONNECTED)
     {
          Serial.print(".");
          delay(500);
     }
     Serial.print("Connected to Wifi with ssid ");
     Serial.println(wifissid);
     Serial.print("WiFi IP address: ");
     Serial.println(WiFi.localIP()); // WIFI router IP address
     ThingSpeak.begin(client);
}

void loop()
{
    int led_1 = ThingSpeak.readFloatField(channel, led1);
    int led_2 = ThingSpeak.readFloatField(channel, led2);
    int led_3 = ThingSpeak.readFloatField(channel, led3);
    if(client.connect(server,80))
    {
        Serial.print("LED1: ");
        Serial.println(led_1);
        Serial.print("LED_2: ");
        Serial.println(led_2);
        Serial.print("LED3: ");
        Serial.println(led_3);
        String Led1 = String(led_1);
        Led1 += "\r";
        client.print(Led1);
        String Led2 = String(led_2);
        Led2 += "\r";
        client.print(Led2);
        String Led3 = String(led_3);
        Led3 += "\r";
        client.print(Led3);
        Serial.println("LEDs Data is sent to another ESP8266 ");
        delay(1000);
        client.stop();
     }
}
