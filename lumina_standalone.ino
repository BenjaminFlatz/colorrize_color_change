#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 14
#define NUM_PIXELS 25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

String redString;
String greenString;
String blueString;

int R;
int G;
int B;

int swVersion = 2;
int hwVersion = 2;

 
void setup() {
  pixels.begin();
}

String led_control(int red, int green, int blue, int modeInt, int duration, int brightness, char* active_mode){
  uint32_t color_rgb = pixels.Color(red, green, blue);
  uint32_t color_warmWhite = pixels.Color(red,red,red);
  uint32_t color_coolWhite = pixels.Color(blue,blue,blue);
  

  Serial.println(active_mode);
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);
  
  if (active_mode == "rgb"){
    pixels.fill(color_rgb, 0, NUM_PIXELS);
    pixels.show();    
  }

  else if (active_mode == "tw"){
    int i = 0;
    for(i=0; i<NUM_PIXELS; i++){
      if(i%2 == 0){//Warmweiß
        pixels.setPixelColor(i, color_warmWhite); 
      }
      else if (i%2 == 1){
        pixels.setPixelColor(i, color_coolWhite); 
      }
    }
    pixels.show(); 
  }
  else if (active_mode == "off"){
    
  } 
 
  if (modeInt == 10){  //sine
    int i = 0;
    float deg = 0;
    for(i=0; i<(duration/10); i++){
      for(deg=0; deg<360; deg++){
        pixels.fill(pixels.Color((sin(deg*PI/180)*128/1)+127.5, (sin((deg*PI/180)+2.0944)*128/1)+128, (sin((deg*PI/180)+4.18879)*128/1)+128), 0, NUM_PIXELS);
        pixels.show();
        delay(10);
        
      }
    }
  }
  else if (modeInt == 20){  //rect
    
    int j = 0;
    int i = 0;
    for(j=0; j<(duration/10); j++){
      for(i=0; i<360; i++){
  
        if(i == 0){
          pixels.fill(pixels.Color(255, 0, 0), 0, NUM_PIXELS);
        }
        else if (i == 60){
          pixels.fill(pixels.Color(255, 255, 0), 0, NUM_PIXELS);
        }
        else if (i == 120){
          pixels.fill(pixels.Color(255, 255, 255), 0, NUM_PIXELS); 
        }
        else if (i == 180){
          pixels.fill(pixels.Color(0, 255, 255), 0, NUM_PIXELS); 
        }
        else if (i == 240){
          pixels.fill(pixels.Color(0, 0, 255), 0, NUM_PIXELS); 
        }
        else if (i == 300){
          pixels.fill(pixels.Color(255, 0, 255), 0, NUM_PIXELS); 
        }
      
  
        pixels.show();
        delay(10);
      }
      
    }
  }
    
  else if (modeInt == 30){  //tri
    red = 0;
    green = 239;
    blue = 239;
    int j = 0;
    int deg = 0;
    for(j=0; j<(duration/10); j++){
      for(deg=0; deg<360; deg++){
        if ((sin(deg*PI/180)*128/1)+128 >= 128)
        {
          red += 1;
        }
        else
        {
          red -= 1;
        }
        
        if (((sin((deg*PI/180)+2.0944)*128/1)+128) >= 128)
        {
          green += 1;
        }
        else
        {
          green -= 1;
        }
        if (((sin((deg*PI/180)+4.18879)*128/1)+128) >= 128)
        { 
          blue += 1;
        }
        else 
        {
          blue -= 1;
          
        }
        pixels.fill(pixels.Color(red, green, blue), 0, NUM_PIXELS);
        pixels.show();
        delay(10);
      }
    }
  }
  return("done");
}

void loop() {

  Serial.println("R="+String(R)+" G="+String(G)+" B="+String(B));
  led_control(R, G, B, 10, 10, 255, "rgb");
  Serial.println("");
  Serial.println("");
  
  delay(10);
  
  
}
