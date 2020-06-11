
///Notes:
/// Programado|Implementado|nombre
///    No     -     Si    Dimmer
///                       -------->Reloj RTC
///                       -------->   **Las librerías nombraban las mismas variables ON y OFF, Todas las
///                       -------->     variables de RBDdimmer.h(grupo) fueron sustituidas por OFFF y ONN, es necesario
///                       -------->     tener en cuenta para la implementacion de las funciones
///    Si     -     Si    Humidificador
///    Si     -     Si    Sensor de temperatura
///                       -------->Habilitar deteccion de desconexión de DHT22
///                       -------->Fallo aleatorio, causa: ? (Fix - Taped)
///
///    No     -     Si    Sensor de humedad de suelo
///    No     -     No    Bomba de agua con relé
///Switch para lcd
///

#include <Time.h>
#include <TimeLib.h>

#include "RBDdimmer.h"
#define USE_SERIAL  Serial
#define outputPin  3
#define zerocross  2
dimmerLamp dimmer(outputPin);
int outVal = 0;
#include "DHT.h"
#define DHTTYPE DHT22 // used sensor, DHT11 or DHT22
#define DHTPIN 11

#define mosPIN 12
#define greenLED 4
#define blueLED 5
#define dimmerPIN 7

#define redLED 6
#define moisturePIN A7
DHT dht(DHTPIN, DHTTYPE);

long T1;
float Bh;
float Bt;
bool indicator = false;
long T2;
long passed;

#include <Wire.h>
#include "RTClib.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0xA7, 16, 2);
RTC_DS3231 rtc;

unsigned long readTimer;
float hum;
int pot;
float sensorValue = 0;

void setup() {
  if (! rtc.begin()) {
    Serial.println("No hay un módulo RTC");
    while (1);
  }
  //LCD
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.print("Iniciando...");
  //LCD

  //Dimmmmer
  pinMode(dimmerPIN, OUTPUT);
  digitalWrite(dimmerPIN, 0);
  //Dimmmmer

  USE_SERIAL.begin(9600);
  dimmer.begin(NORMAL_MODE, ONN); //dimmer initialisation: name.begin(MODE, STATE)
  USE_SERIAL.println("Dimmer Program is starting...");
  USE_SERIAL.println("Set value");

  // configure pins
  Serial.begin(9600);
  //Dimmer
  dimmer.begin(NORMAL_MODE, ONN); //dimmer initialisation: name.begin(MODE, STATE)
  USE_SERIAL.println("Dimmer Program is starting...");
  USE_SERIAL.println("Set value");
  //Dimmer

  dht.begin();
  delay(1000);
  pinMode(mosPIN, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  // configure pins


  //MOSFET
  digitalWrite(mosPIN, LOW); //MOSFET
  //MOSFET

  digitalWrite(dimmerPIN, 1);

  //Animación de inicio
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, HIGH);
  delay(1000);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(500);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, LOW);
  delay(500);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, HIGH);
  delay(300);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, HIGH);
  delay(1000);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(2000);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, 1);
  delay(150);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, LOW);
  delay(150);
  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, 1);
  digitalWrite(redLED, 1);

  //Animación de inicio

  digitalWrite(greenLED, 1);
  digitalWrite(blueLED, 0);
  digitalWrite(redLED, 0);

  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius

  T2 = millis();
}

void loop() {
  delay(50);
  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius

  //Sensor de humedad de tierra
  for (int i = 0; i <= 100; i++) {
    sensorValue = sensorValue + analogRead(moisturePIN);
    delay(1);
  }
  sensorValue = sensorValue / 100.0;
  //Sensor de humedad de tierra

  if ((!isnan(t)) && (!isnan(h))) {
    indicator = false;
    if ((t > 0) && (h > 0)) {
      Bt = t;
      Bh = h;
      //Serial.print(String(Bt) + " " + String(Bh) + "\n" );
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C");
    lcd.print(" ");
    lcd.print("L: ");
    lcd.print(((dimmer.getPower() - 27) * 100) / 53);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(h);
    lcd.print("%  ");
    lcd.print("HS:");
    lcd.print(sensorValue);
    lcd.print("% ");
  }
  else {
    unsigned long StartTime = millis();
    //Serial.println("Error" + String(Bt) + String(Bh));
    indicator = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(Bt);
    lcd.print((char)223);
    lcd.print("C");
    lcd.print(" ");
    lcd.print("L: ");
    lcd.print(((dimmer.getPower() - 27) * 100) / 53);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(Bh);
    lcd.print("%  ");
    lcd.print("HS:");
    lcd.print(sensorValue);
    lcd.print("% ");
  }
  if (indicator == true) {
    T1 = millis();
    long passed = T2 - T1;
    if (passed > 7000) {
      Bt = 0;
      Bh = 0;
    }
  } else {
    T1 = 0;
  }

  //Serial.print(String(indicator) + " " + String(passed) + " ");

  //Programación para encender MOSFET module
  if (Bh < 65) {
    digitalWrite(blueLED, 1);
    digitalWrite(mosPIN, 1);
  }
  else {
    digitalWrite(blueLED, 0);
    digitalWrite(mosPIN, 0);
  }
  //Programación para encender MOSFET module

  DateTime now = rtc.now();

  if (now.hour() == 0) {
    dimmer.setPower(f(0));
    delay(200);
  } else if (now.hour() == 1) {
    dimmer.setPower(f(0));
    delay(200);
  } else if (now.hour() == 2) {
    dimmer.setPower(f(0));
    delay(200);
  } else if (now.hour() == 3) {
    dimmer.setPower(f(0));
    delay(200);
  } else if (now.hour() == 4) {
    dimmer.setPower(f(5));
    delay(200);
  } else if (now.hour() == 5) {
    dimmer.setPower(f(10));
    delay(200);
  } else if (now.hour() == 6) {
    dimmer.setPower(f(15));
    delay(200);
  } else if (now.hour() == 7) {
    dimmer.setPower(f(35));
    delay(200);
  } else if (now.hour() == 8) {
    dimmer.setPower(f(55));
    delay(200);
  } else if (now.hour() == 9) {
    dimmer.setPower(f(80));
    delay(200);
  } else if (now.hour() == 10) {
    dimmer.setPower(f(85));
    delay(200);
  } else if (now.hour() == 11) {
    dimmer.setPower(f(90));
    delay(200);
  } else if (now.hour() == 12) {
    dimmer.setPower(f(100));
    delay(200);
  } else if (now.hour() == 13) {
    dimmer.setPower(f(100));
    delay(200);
  } else if (now.hour() == 14) {
    dimmer.setPower(f(100));
    delay(200);
  } else if (now.hour() == 15) {
    dimmer.setPower(f(100));
    delay(200);
  } else if (now.hour() == 16) {
    dimmer.setPower(f(90));
    delay(200);
  } else if (now.hour() == 17) {
    dimmer.setPower(f(90));
    delay(200);
  } else if (now.hour() == 18) {
    dimmer.setPower(f(75));
    delay(200);
  } else if (now.hour() == 19) {
    dimmer.setPower(f(65));
    delay(200);
  } else if (now.hour() == 20) {
    dimmer.setPower(f(40));
    delay(200);
  } else if (now.hour() == 21) {
    dimmer.setPower(f(20));
    delay(200);
  } else if (now.hour() == 22) {
    dimmer.setPower(f(10));
    delay(200);
  } else if (now.hour() == 23) {
    dimmer.setPower(f(0));
    delay(200);
  } else if (now.hour() == 24) {
    dimmer.setPower(f(0));
    delay(200);
  }

  Serial.println("Power :" + String(dimmer.getPower()) + " Power%: " + String((((dimmer.getPower() - 27) * 100) / 53)) + " Hour: " + now.hour());

}

int f(int x) {
  int result = ((x* 53) / 100) + 27;
  return result;
}
