// C++ code
#include <LiquidCrystal.h>
#define SENSOR_TMP A5
#define BTN1 10
#define BTN2 9
#define BTN3 8
#define BTN4 7
#define AZUL 13
#define VERDE 12
#define ROJO 11

LiquidCrystal lcd(A0, A1, A2, A3, A4, 3);

int leds[] = {AZUL, VERDE, ROJO};

void setup(){
    Serial.begin(9600);
    pinMode(SENSOR_TMP, INPUT); // No es necesario
    lcd.begin(16,2);
    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);
    pinMode(BTN3, INPUT_PULLUP);
    pinMode(BTN4, INPUT_PULLUP);
    pinMode(AZUL, OUTPUT);
    pinMode(VERDE, OUTPUT);
    pinMode(ROJO, OUTPUT);
    // lcd.print("hello, world!");
}

// NUEVO
void ApagarLeds(int leds[]){
    for (int i = 0; i < 3; i++){
        digitalWrite(leds[i], LOW);
    }
}

void MostrarNivelLCD(int nro){
    lcd.clear();
    switch(nro){
        case 0:
            lcd.print("Nivel: 0");
            lcd.setCursor(0,1);
            lcd.print("Sin hacer");
        break;
        case 1:
            lcd.print("Nivel: 1");
            lcd.setCursor(0,1);
            lcd.print("Hecho");
        break;
        case 2:
            lcd.print("Nivel: 2");
        break;
        case 3:
            lcd.print("Nivel: 3");
        break;
    }
}

// void Mostrar


int temperatura_anterior = 0;
void loop(){
    int temperatura = analogRead(SENSOR_TMP);
    temperatura = map(temperatura, 20, 358, -40, 125);
    int _BTN1 = digitalRead(BTN1);
    int _BTN2 = digitalRead(BTN2);
    int _BTN3 = digitalRead(BTN3);
    int _BTN4 = digitalRead(BTN4);


    if (temperatura < 20 && temperatura != temperatura_anterior){
        temperatura_anterior = temperatura;
        ApagarLeds(leds);
        MostrarNivelLCD(0);
        // digitalWrite(AZUL, HIGH);
        // lcd.setCursor(0,1);
        // lcd.print("a");
    } else {
        if (temperatura >= 20 && temperatura <= 80) {
            ApagarLeds(leds);
            digitalWrite(VERDE, HIGH);
        } else {
            if (temperatura > 80){
                ApagarLeds(leds);
                digitalWrite(ROJO, HIGH);
            }
        }
    }

    if(!_BTN1){
        MostrarNivelLCD(0);
    } 
    if (!_BTN2) {
        MostrarNivelLCD(1);
    }
    if (!_BTN3) {
      	MostrarNivelLCD(2);
    }
    if (!_BTN4) {
      	MostrarNivelLCD(3);
    }
  	// lcd.home();
    // lcd.print("hello, world!");
    // sprintf(lcd, "Temp: %d", temperatura);

    // if 
}