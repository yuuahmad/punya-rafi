#include <Arduino.h>
#define pin_relay 14 // D5 pada node mcu
#define BLYNK_TEMPLATE_ID "TMPL2X2mSDh0"
#define BLYNK_DEVICE_NAME "maling template"
#define BLYNK_AUTH_TOKEN "3TAbntYuM_ZhTTy30_kcZPdUokrJ7UIL"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KONTRAKAN UYE";
char pass[] = "KUSANG123";
BlynkTimer timer;

// sensor maling
const int pinSensorMaling = D1;
int nilaiMaling; // sekaligus menghidupkan relay
// led built in untuk notifikasi dan testing
const int pinLed = D4;
int nilaiLed;
// relay
const int pinRelay = D3;

BLYNK_WRITE(V2)
{
  nilaiLed = param.asInt();
}
void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);
  Blynk.virtualWrite(V3, nilaiMaling);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  pinMode(pinSensorMaling, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinRelay, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
  // baca sensor maling
  nilaiMaling = digitalRead(pinSensorMaling);
  Serial.print("nilai maling :");
  Serial.println(nilaiMaling);

  if (nilaiLed == 1)
    digitalWrite(pinLed, HIGH);
  else
    digitalWrite(pinLed, LOW);

  if (nilaiMaling == 1)
    digitalWrite(pinRelay, LOW);
  else
    digitalWrite(pinRelay, HIGH);
}
