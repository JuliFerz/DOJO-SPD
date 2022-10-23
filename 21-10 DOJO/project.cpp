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
  #define BUZZ 5

  LiquidCrystal lcd(A0, A1, A2, A3, A4, 3);

  int leds[] = {AZUL, VERDE, ROJO};

  void setup(){
      Serial.begin(9600);
      pinMode(SENSOR_TMP, INPUT);
      lcd.begin(16,2);
      pinMode(BTN1, INPUT_PULLUP);
      pinMode(BTN2, INPUT_PULLUP);
      pinMode(BTN3, INPUT_PULLUP);
      pinMode(BTN4, INPUT_PULLUP);
      pinMode(AZUL, OUTPUT);
      pinMode(VERDE, OUTPUT);
      pinMode(ROJO, OUTPUT);
      pinMode(BUZZ, OUTPUT);
  }

  void ApagarLeds(int leds[]){
      for (int i = 0; i < 3; i++){
          digitalWrite(leds[i], LOW);
      }
  }

  void PrenderBuzzer(int qty){
    for (int i = 0; i < qty; i++){
        tone(BUZZ, 350, 250);
        delay(500);
    }
  }

  int temperatura_anterior = 0;
  int from = 0;
  int to = 0;
  char texto[10];
  int lvl = 0;
  bool running = false;
  bool flag = true;
  String estado = "Apagado";
  String estadoAnterior = estado;
  
  void loop(){
      int temperatura = analogRead(SENSOR_TMP);
      temperatura = map(temperatura, 20, 358, from, to);
      int _BTN1 = digitalRead(BTN1);
      int _BTN2 = digitalRead(BTN2);
      int _BTN3 = digitalRead(BTN3);
      int _BTN4 = digitalRead(BTN4);
      
      if (estado != estadoAnterior){
        estadoAnterior = estado;
        lcd.clear();
      }
      lcd.home();
      sprintf(texto, "Nivel: %d", lvl);
      lcd.print(texto);
      lcd.setCursor(0, 1);
      lcd.print(estado);

      if ((temperatura >= from + 5 && temperatura <= to - 5)  && running){
          estado = "Hecho";
          ApagarLeds(leds);
          digitalWrite(VERDE, HIGH);
          flag = true;
      } else if (temperatura < from + 5 && running) {
          estado = "Sin hacer";
          ApagarLeds(leds);
          digitalWrite(AZUL, HIGH);
          flag = true;
      } else if (running && flag){
          estado = "Quemado";
          ApagarLeds(leds);
          digitalWrite(ROJO, HIGH);
          PrenderBuzzer(3);
          flag = false;
      }
      

      if(!_BTN1){
          running = true;
          lvl = 1;
          from = 20;
          to = 40;
      } 
      if (!_BTN2) {
          running = true;
          lvl = 2;
          from = 40;
          to = 60;
      }
      if (!_BTN3) {
          running = true;
          lvl = 3;
          from = 60;
          to = 80;
      }
      if (!_BTN4) {
          running = true;
          lvl = 4;
          from = 80;
          to = 100;
      }
  }