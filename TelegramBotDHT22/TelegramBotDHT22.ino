#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

#define WIFI_SSID "***"
#define WIFI_PASSWORD "***"
#define BOT_TOKEN "***"
#define CHAT_ID "***"
#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
const unsigned long botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  Serial.begin(9600);
  dht.begin();
  configTime(0, 0, "pool.ntp.org");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  client.setTrustAnchors(&cert);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    if (from_name == "") {
      from_name = "Guest";
    }
    if (bot.messages[i].type == "callback_query") {
      if (text == "DHT22") {
        float h = dht.readHumidity();

        float t = dht.readTemperature();
        String mensaje = "";
        if (isnan(h) || isnan(t)) {
          mensaje += "Error DHT22.\n";
        } else {
          float st = dht.computeHeatIndex(t, h, false);
          mensaje += "Humedad: " + String(h) + "%.\n";
          mensaje += "Temperatura: " + String(t) + "°C.\n";
          mensaje += "Sensación térmica: " + String(st) + "°C.\n";
        }


        bot.sendMessage(chat_id, mensaje, "Markdown");
      }
    } else {
      if (text == "/options") {
        String keyboardJson = "[[{ \"text\" : \"Ir a GitHub\", \"url\" : \"https://github.com/JorgeValGil\" }],[{ \"text\" : \"Datos DHT22\", \"callback_data\" : \"DHT22\" }]]";
        bot.sendMessageWithInlineKeyboard(chat_id, "Elige una de las opciones", "", keyboardJson);
      }
      if (text == "/start") {
        String welcome = "Bienvenido a JorgeValGil Bot, " + from_name + ".\n";
        welcome += "/options\n";
        bot.sendMessage(chat_id, welcome, "Markdown");
      }
    }
  }
}