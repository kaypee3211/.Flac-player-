#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <JC_Button.h>
#include <vector>
#include <map>

#include <string>
using namespace std;
#define screen_width 128
#define screen_height 64


std::map<int, std::string> elements;//map for elements 
std::vector<int> removedElements;



int nav = 1;
int currentMenu=0;

Adafruit_SSD1306 display(screen_width,screen_height,&Wire,-1);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Button btn1(32);
Button btn2(27);
Button btn3(14);



//menu - choice 1
void musicPlaying(){
  
  int flag = 0;
  
  while (flag == 0)
 {
  u8g2.clearBuffer();
  btn1.read();
  btn2.read();
  btn3.read();
  if (btn1.pressedFor(1000)) { //not working
    flag = 1;
  }
  u8g2.setFont(u8g2_font_ncenB08_tf);
  u8g2.drawStr(0,50,"MUSIC...");
  u8g2.drawLine(0,0,0,100);
  u8g2.sendBuffer();
 }
 
}

static void music() {
  int flag = 0;
  
  int navMusic = 0;
  while (flag == 0) {
    btn1.read();
    btn2.read();
    btn3.read();
    u8g2.clearBuffer();
    if (btn1.wasPressed()){
      Serial.println("music playing");
      musicPlaying();

    }
    if (btn2.wasPressed()){
      Serial.println("Vol up");
    }
    if (btn3.wasPressed()){
      Serial.println("Vol down");
    }
    if (btn3.pressedFor(1000)) {
    flag = 1;
  }

  u8g2.setFont(u8g2_font_ncenB08_tf);
  u8g2.drawStr(0,15,"1-Play music");
  u8g2.drawStr(0,30,"2-Vol up");
  u8g2.drawStr(0,45,"3-Vol down");

  u8g2.sendBuffer();
  }
}
//example values

//menu - choice 2
int navTodolist = 1;

//how many erased elements
int removed = 0;

//after pressing btn3 for 5 seconds the map is cleared

//how many pages oled will have
int pages = (elements.size()/3) + 1;
int currentPage = 0;



//for btn2.pressedFor to not update so quickly
static unsigned long lastPageChange = 0;


void todolist() {
  
  int flag  = 0;
  int navTodolist = 1;
  
  while (flag == 0) {
  int counter = 0;
  btn1.read();
  btn2.read();
  btn3.read();
  int row = 0;
  u8g2.clearBuffer();
  // for (i=elements.begin();i!=elements.end();i++)
  //drawing first 3 elements
  u8g2.setFont(u8g2_font_ncenB08_tf);
    for (auto const& [key, val] : elements) {
      if (counter >= 3 * currentPage && counter < 3 * (currentPage + 1)) {
        int yPos = (row + 1) * 15;

        u8g2.drawStr(0, yPos, (std::to_string(key) + " : " + val).c_str());
        row++;
      }
      counter ++;

  }
  
  if (btn1.wasPressed()) {
    navTodolist++;
  }
  if (btn1.pressedFor(2000)) {
    flag=1;
  }

  if (btn2.wasPressed()) {
    navTodolist--;
  }
  if (btn2.pressedFor(2000) && (millis() - lastPageChange>5000)) {
    currentPage++; 
    navTodolist = 1;
    if (currentPage * 3 >= elements.size()) {
      currentPage = 0;
    }

    lastPageChange = millis();
    navTodolist = (currentPage * 3) + 1;
  }
  if (btn3.wasPressed()) {
    //underline on current element
    //fix = underline on current element based on current page
    removedElements.push_back(navTodolist + 3*currentPage);
  }
  if (btn3.pressedFor(5000)) {
    elements.clear();
    removedElements.clear();
  }
  
  for (int i= 0; i < removedElements.size();i++) {
    u8g2.drawLine(0,-(u8g2.getAscent()/2)+(removedElements[i]*15),100,-(u8g2.getAscent()/2)+(removedElements[i]*15));
  
  }




  if (btn1.pressedFor(1000)) {
    flag = 1;
    currentPage=0;
  }
  //getAscent() - zwraca wyoskosc liczby od linii

  Serial.println("navtodolist");
  Serial.println(navTodolist);
  Serial.println("currentpage");
  Serial.println(currentPage);
  u8g2.sendBuffer();
 
  }

}

void korki() {
  int flag =0;
  while (flag==0) {
    btn1.read();
    btn2.read();
    btn3.read();
    


  }
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
      
      if (btn1.wasPressed()){
        nav++;
      }
      if (btn2.wasPressed()){
        nav--;
      }
      if (btn3.wasPressed()){
        currentMenu=nav;
        switch(nav) {
          case 1:
            music();
            break;
          case 2:
            todolist();
            break;
          case 3:
            korki();
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
  for (int i = 1; i <= 10; i++) {
    elements[i] = "task" + std::to_string(i);
}
  
}


void loop() {
  btn1.read();
  btn2.read();
  btn3.read();
  menu();


}
