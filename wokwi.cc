#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <JC_Button.h>

#define screen_width 128
#define screen_height 64

int nav = 0;
int currentMenu=0;

Adafruit_SSD1306 display(screen_width,screen_height,&Wire,-1);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Button btn1(32);
Button btn2(27);
Button btn3(14);



static void music() {
  int navMusic = 0;
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tf);
    u8g2.drawStr(0,15,"1-Play music");
    u8g2.drawStr(0,30,"2-Vol up");
    u8g2.drawStr(0,45,"3-Vol down");
    if (btn1.isPressed()){
      Serial.println("music playing");
    }
    if (btn2.isPressed()){
      Serial.println("Vol up");
    }
    if (btn3.isPressed()){
      Serial.println("Vol down");
    }

  } while (u8g2.nextPage());
}

static void handleClick() {
  Serial.println("Clicked!");
}

static void menu() {
    u8g2.firstPage();
    do {
      Serial.println(nav);
      u8g2.setFont(u8g2_font_ncenB08_tf);
      u8g2.drawStr(0,0,"Menu");
      u8g2.drawStr(0,20,"Muza");
      u8g2.drawStr(0,40,"todolist");
      u8g2.drawStr(0,60,"korki");
      u8g2.drawStr(0,80,"lofi");
      if (btn1.isPressed()){
        nav++;
      }
      if (btn2.isPressed()){
        nav--;
      }
      if (btn3.isPressed()){
        currentMenu=nav;
        switch(nav) {
          case 1:
            music();
            break;
          case 2:
            // todolist();
            break;
          case 3:
            // timer();
            break;
        }

  }} while (u8g2.nextPage());
}




void setup() {
  Serial.begin(115200);
  Serial.println("siema");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  u8g2.begin();
  btn1.begin();
  btn2.begin();
  btn3.begin();
}


void loop() {
  btn1.read();
  btn2.read();
  btn3.read();
  if (currentMenu == 0) {
    menu();
  }
  if (currentMenu == 1) {
    music();
  }


}



