////////////////////////////////
// Programme d'apprentissage  //
//      de la maitrise        //
//     des rubans de led      //
////////////////////////////////
// basÃ© sur le programme
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
/*
                               
                                          +-----+
             +----[PWR]-------------------| USB |--+
             |                            +-----+  |
             |         GND/RST2  [ ][ ]            |
             |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] | 
             |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   
             |                             AREF[ ] |
             |                              GND[X] | - masse du ruban de LED
             | [ ]N/C                    SCK/13[ ] |  
             | [ ]IOREF                 MISO/12[ ] |   
             | [ ]RST                   MOSI/11[ ]~|   
             | [ ]3V3    +---+               10[ ]~|  
alim ruban - | [x]5v    -| A |-               9[ ]~|   
             | [ ]GND   -| R |-               8[ ] |  
             | [ ]GND   -| D |-                    |
             | [ ]Vin   -| U |-               7[ ] |    
             |          -| I |-               6[x]~| - D in du ruban de LED 
             | [ ]A0    -| N |-               5[ ]~|    
             | [ ]A1    -| O |-               4[ ] |    
             | [ ]A2     +---+           INT1/3[ ]~|    
             | [ ]A3                     INT0/2[ ] |    
             | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |  
             | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |  
             |            [ ] [ ] [ ]              |
             |  UNO_R3    GND MOSI 5V  ____________/
              \_______________________/
MatÃ©riel :
- des fils dupont.
- un ruban de led
- un Arduino
- ...
SchÃ©ma de l'Arduino en ASCII-ART CC-By http://busyducks.com/ascii-art-arduinos
Sous licence CC-By-Sa (http://creativecommons.org/licenses/by-nc-sa/3.0/)
*/
/*
   ___
 / ___ \
|_|   | |
     /_/ 
     _   ___   _ 
    |_| |___|_| |_
         ___|_   _|
        |___| |_|
Les petits DÃ©brouillards - CC-By-Sa http://creativecommons.org/licenses/by-nc-sa/3.0/
*/

#include <Adafruit_NeoPixel.h>
#include "pacman.h"




#define BROCHE        0 // broche de l'Arduino sur laquelle est connectÃ© le ruban

// Nombre de led du ruban ?
#define NBPIXELS NEW_PISKEL_FRAME_WIDTH*NEW_PISKEL_FRAME_HEIGHT 






Adafruit_NeoPixel pixels(NBPIXELS, BROCHE, NEO_GRB + NEO_KHZ800);


#define delai 3 // durÃ©e de la pause en millisecondes
byte rgb_tmp[3];
byte image[NBPIXELS][3];
int pixel_to_light = 0;
byte r,g,b;


void colorConverter(uint32_t rgb)
{

  byte red, green, blue;
  red = rgb >> 16 ;
  
  green = (rgb & 0x00ff00) >> 8;
  
  blue = (rgb & 0x0000ff);
  
  rgb = 0;
  
  rgb |= red <<16;
  rgb |= blue <<8;
  rgb |=green;
  rgb_tmp[0] = red;
  rgb_tmp[1] = green;
  rgb_tmp[2] = blue;
  /*Serial.print("RED = ");
  Serial.print(red);
  Serial.print("   GREEN = ");
  Serial.print(green);
  Serial.print("   BLUE = ");
  Serial.print(blue);
  Serial.println();*/

}

/*void tab_maker() {
  for (int i = 0; i < NBPIXELS; i++) {
    colorConverter(new_piskel_data[0][i]);
    //colorConverter(0xff09f2ff);
    for (int j = 0; j < 3; j++) 
      image[i][j] = rgb_tmp[2-j];
    //Serial.println(image[i][0]);
  } 
}*/

void setup() {
  //Serial.begin(9600);
  //Serial.println(sizeof(new_piskel_data[0][0]));
  //Serial.println(sizeof(0xff09f2ff));
  //tab_maker();
  pixels.begin();           // INITIALISE l'object ruban NeoPixel
  pixels.fill(pixels.Color(0,0,0));
  pixels.show();            // Ã©teint tout les pixels aussi vite que possible.
  pixels.setBrightness(255); // met la luminositÃ© Ã  1/5 (max = 255)
}

void loop() {
  animated();
 //move_to_right();
}

void animated() {
  for (int i = 0; i < NEW_PISKEL_FRAME_COUNT; i ++){
    display_image(0, i);
    delay(10);
    pixels.fill(pixels.Color(0,0,0));
  }

}

void display_image(int decalage, int nb) {
  for(int i=0; i<NBPIXELS; i++) { // Les pixels sont numÃ©rotÃ©s de 0 Ã  ...
    //Serial.println(new_piskel_data[0][i]);
    colorConverter(pgm_read_dword(&new_piskel_data[nb][i]));
    r = rgb_tmp[2];
    g = rgb_tmp[1];
    b = rgb_tmp[0];

    if ((i/NEW_PISKEL_FRAME_WIDTH)%2 == 0) {
      pixel_to_light = i + decalage;
      if (pixel_to_light >= (i/NEW_PISKEL_FRAME_WIDTH+1)*NEW_PISKEL_FRAME_WIDTH) {
        pixel_to_light -= NEW_PISKEL_FRAME_WIDTH;
      }
    } else {
      pixel_to_light = NEW_PISKEL_FRAME_WIDTH*((i/NEW_PISKEL_FRAME_WIDTH)+1) - (i - ((i/NEW_PISKEL_FRAME_WIDTH)*NEW_PISKEL_FRAME_WIDTH))-1;
      pixel_to_light -= decalage;
      if (pixel_to_light < (i/NEW_PISKEL_FRAME_WIDTH)*NEW_PISKEL_FRAME_WIDTH) {
        pixel_to_light += NEW_PISKEL_FRAME_WIDTH;
      }
    }
    //Serial.println(pixel_to_light);
    pixels.setPixelColor(pixel_to_light, pixels.Color(r,g,b));
    //delay(5);
  }
  pixels.show();
  
}

void move_to_right() {
  for (int i = 0; i < NEW_PISKEL_FRAME_WIDTH  ; i++) {
    display_image(i, 0);
    delay(4);
    pixels.fill(pixels.Color(0,0,0));
    
  }
}
