#include <Adafruit_NeoPixel.h>
#define PIN 6

//Magnet pins
#define mag_1 1
#define mag_2 2
#define mag_3 3
#define mag_4 4
#define mag_5 5
#define mag_6 10
#define mag_7 7
#define mag_8 8

#define NUM_LEDS 210
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();

  pinMode(mag_1, INPUT);
  pinMode(mag_2, INPUT);
  pinMode(mag_3, INPUT);
  pinMode(mag_4, INPUT);
  pinMode(mag_5, INPUT);
  pinMode(mag_6, INPUT);
  pinMode(mag_7, INPUT);
  pinMode(mag_8, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  RGBLoop();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void RGBLoop(){
  for(int j = 0; j < 2; j++ ) { 
    // Fade IN
    for(int k = 0; k < 120; k++) { 
      switch(j) { 
        case 0: setAllPixels(0,0,k);
        Check_for_boat(0,0,k);
          break;
        case 1: setAllPixels(0,k/2,k);
        Check_for_boat(0,k/2,k);
          break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 120; k >= 0; k--) { 
      switch(j) { 
        case 0: setAllPixels(0,0,k);
        Check_for_boat(0,0,k);
          break;
        case 1: setAllPixels(0,k/2,k);
        Check_for_boat(0,k/2,k);
          break;
      }
      showStrip();
      delay(3);
    }
  }
}

// Funksjon som deler inn området båten kan kjøre på i 8 3x3 bokser.
void Check_for_boat(int r,int g,int b){
  int Box_1[9] = {206, 205, 204, 173, 172, 171, 164, 163, 162};
  int Box_2[9] = {199, 201, 200, 177, 176, 178, 157, 159, 158};
  int Box_3[9] = {194, 195, 196, 181, 182, 183, 152, 153, 154};
  int Box_4[9] = {191, 193, 192, 185, 184, 186, 149, 151, 150};
  int Box_5[9] = {131, 130, 129, 122, 121, 120, 89, 88, 87};
  int Box_6[9] = {135, 134, 136, 115, 117, 116, 93, 92, 94};
  int Box_7[9] = {139, 140, 141, 110, 111, 112, 97, 98, 99};
  //int Box_8[9] = {143, 142, 141, 110, 109, 108, 101, 100, 99}; //Magnetsensor 8 er ødelagt. Denne biten er dermed kommentert ut.
  //setPixel(4, 120, 0, 0);
  
  // Sjekker om det er et magnetfelt i nærheten av boksene, hvis LOW, dvs magnetfelt detektert, setter den boksen til rød, hvis HIGH endrer den ikke farge
  if(digitalRead(mag_1) == LOW){ 
    for(int i=0; i<9; i++){
      setPixel(Box_1[i], 120, 0, 0);
      }
      
      showStrip();
    }
  if(digitalRead(mag_2) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_2[i], 120, 0, 0);
      }
      showStrip();
    }
  if(digitalRead(mag_3) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_3[i], 120, 0, 0);
      }
      showStrip();
    }
  if(digitalRead(mag_4) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_4[i], 170, 0, 0);
      }
      showStrip();
    }
  if(digitalRead(mag_5) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_5[i], 120, 0, 0);
      }
      showStrip();
    }
  if(digitalRead(mag_6) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_6[i], 120, 0, 0);
      }
      showStrip();
    }
  if(digitalRead(mag_7) == LOW){
    for(int i=0; i<9; i++){
      setPixel(Box_7[i], 120, 0, 0);
      }
      showStrip();
    }
 /* if(digitalRead(mag_8) == LOW){    //Magnetsensor 8 er ødelagt. Denne biten er dermed kommentert ut.
    for(int i=0; i<9; i++){
      setPixel(Box_8[i], 120, 0, 0);
      }
      showStrip();
    }*/

    
  if(digitalRead(mag_1) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_1[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_2) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_2[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_3) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_3[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_4) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_4[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_5) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_5[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_6) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_6[i], r, g, b);
      }
      showStrip();
    }
  if(digitalRead(mag_7) == HIGH){
    for(int i=0; i<9; i++){
      setPixel(Box_7[i], r, g, b);
      }
      showStrip();
    }
  /*if(digitalRead(mag_8) == HIGH){     //Magnetsensor 8 er ødelagt. Denne biten er dermed kommentert ut.
    for(int i=0; i<9; i++){
      setPixel(Box_8[i], r, g, b);
      }
      showStrip();
    }*/
  }

  // Funksjon som styrer alle LEDsene som ikke skal bli påvirket av båten
  void setAllPixels(int r, int g, int b){
    int AllLeft[147] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,
    42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,
    90,91,95,96,100,101,102,103,104,105,106,107,108,109,113,114,118,119,123,124,125,126,127,128,132,133,137,138,142,143,144,145,146,147,148,155,156,160,161,165,166,167,168,169,
    170,174,175,179,180,187,188,189,190,197,198,203,207,208,209,202};
    for(int i=0; i<147; i++){
      setPixel(AllLeft[i], r, g, b);
      }
    }
  
