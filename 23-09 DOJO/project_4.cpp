#include <Adafruit_NeoPixel.h>
#define TIRA_LED 12
#define NUMPIXELS 6 
#define PULSADOR 7

Adafruit_NeoPixel pixels(NUMPIXELS, TIRA_LED, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(PULSADOR,INPUT);
  pixels.begin();
}

void ApagarLeds(int qty, int red, int green, int blue, int wait){
  for (int i = 0; i < qty; i++){
    pixels.setPixelColor(i,pixels.Color(red, green, blue));
    pixels.show();
    delay(wait);
  }
}

int i = -1;
void loop(){
  int presiona = digitalRead(PULSADOR);
  if (presiona == HIGH){
    i++;
    delay(300);
    if(i < NUMPIXELS){
      pixels.setPixelColor(i,pixels.Color(255, 0, 0));
      pixels.show();
    } else {
	  ApagarLeds(NUMPIXELS,0,0,0,0);
      i = -1;
    }
  }
}