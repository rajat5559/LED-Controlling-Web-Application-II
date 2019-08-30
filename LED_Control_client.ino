#include<ESP8266WiFi.h> //Including ESP8266 Library
#include<ESP8266WebServer.h>  //Including ESP8266 web server library

 IPAddress IP(192,168,4,15); //Static IP address of ESP8266
 IPAddress gateway(192,168,4,1); //Gateway of the network 
 IPAddress mask(255, 255, 255, 0);
 WiFiServer server(80);
 const char* ssid = "ESP8266";  //SSID of the hotspot of ESP8266 acting as local server
 const char* password = "12345678"; //Password of the hotspot of ESP8266 local server

void setup()
{
    pinMode(D1, OUTPUT); //Define pin mode of D1
    pinMode(D2, OUTPUT); // Define pin mode of D2
    pinMode(D3, OUTPUT); //Define pin mode of D3
    digitalWrite(D1, 0); //Write LOW on pin D1
    digitalWrite(D2, 0); //Write LOW on pin D2
    digitalWrite(D3, 0); //Write LOW on pin D3
    WiFi.mode(WIFI_STA); //station mode
    Serial.begin(9600); //Serial communication at baud rate of 9600 for debugging purpose
    delay(100);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.config(IP,gateway,mask);
    WiFi.begin(ssid,password);
    while(WiFi.status()!= WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("LocalIP:"); 
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    WiFiClient client = server.available(); //Waiting for incomming data
    if(!client){ return;}
    String led_1 = client.readStringUntil('\r'); //reads data for LED1
    String led_2 = client.readStringUntil('\r'); //reads data for LED2
    String led_3 = client.readStringUntil('\r'); //reads data for LED3
    if(led_1 == "1") //if LED1 commond is HIGH
    {
        digitalWrite(D1, 1);  //Turn on the LED1
        Serial.println("D1 is On..!"); //Message on the serial monitor
    }
    else if(led_1 == "0") //if LED1 command is LOW
    {
        digitalWrite(D1, 0); //turn off the LED1
        Serial.println("D1 is Off..!"); //message on serial monitor
    }
    if(led_2 == "1") //if LED2 command is HIGH
    {
        digitalWrite(D2, 1);  //Turn ON LED2
        Serial.println("D2 is On..!"); //message on Serial Monitor
    }
    else if(led_2 == "0") // if LED2 command is LOW
    {
        digitalWrite(D2, 0); //Turn OFF LED2
        Serial.println("D2 is Off..!"); //message on serial monitor
    }
    if(led_3 == "1") //if LED3 command is HIGH
    {
        digitalWrite(D3, 1); //Turn ON LED3
        Serial.println("D3 is On..!"); //message on serial monitor
    }
    else if(led_3 == "0") //if LED3 command is LOW
    {
        digitalWrite(D3, 0); // Turn OFF the LED3
        Serial.println("D3 is Off..!"); //message on serial monitor
    }
}
