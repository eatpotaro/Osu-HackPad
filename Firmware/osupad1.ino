#include <Keyboard.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32   // Change to 64 if your OLED is 128x64

#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C  // Most common I2C address

const int buttonPin1 = D7;     // the number of the pushbutton pin
const int buttonPin2 = D8;
const int buttonPin3 = D9;
const int buttonPin4 = D10;

const int ledPin =  25;      // the number of the LED pin
 
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

int lastbuttonState1 = 0;         // variable for reading the pushbutton status
int lastbuttonState2 = 0;
int lastbuttonState3 = 0;
int lastbuttonState4 = 0;
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastTime = 0;
const unsigned long interval = 1000; // 1 second

unsigned long resetlastTime = 0;
const unsigned long resetinterval = 10000; // 1 second
bool reset = false;

int clicksLast5Seconds[5] = {0, 0, 0, 0, 0};
int clicks = 0;
float highestCPS = 0;
int longclicks = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  
  Keyboard.begin();
  delay(5000);
  
  Wire.setSDA(6);   // XIAO RP2040 SDA
  Wire.setSCL(7);   // XIAO RP2040 SCL
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true); // Stop if display not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("OSUBOARD");
  display.println("Clicks: " + clicks);
  display.display();
  
}

float getCPS()
{
  float sum = 0;
  for(int i = 0; i < 5; i++)
  {
    sum += clicksLast5Seconds[i];
  }
  return sum / 5;
}

void doClick()
{
  clicks++;
  longclicks++;
  reset = false;
}
 
void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;
    clicksLast5Seconds[0] = clicksLast5Seconds[1];
    clicksLast5Seconds[1] = clicksLast5Seconds[2];
    clicksLast5Seconds[2] = clicksLast5Seconds[3];
    clicksLast5Seconds[3] = clicksLast5Seconds[4];
    clicksLast5Seconds[4] = clicks;
    clicks = 0;
  }
  
  if (currentTime - resetlastTime >= resetinterval) {
    resetlastTime = currentTime;
    if(reset)
    {
      longclicks = 0;
      highestCPS = 0;
    }
    reset = true;
  }
  
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == LOW) {
    // turn LED on:
    Keyboard.press('d');
    if(lastbuttonState1 == HIGH)
    {
      doClick();
    }

  } else {
    // turn LED off:
    Keyboard.release('d');
  }

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState2 == LOW) {
    // turn LED on:
    Keyboard.press('f');
    
    if(lastbuttonState2 == HIGH)
    {
      doClick();
    }
  } else {
    // turn LED off:
    Keyboard.release('f');
  }

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState3 == LOW) {
    // turn LED on:
    Keyboard.press('j');
    
    if(lastbuttonState3 == HIGH)
    {
      doClick();
    }
  } else {
    // turn LED off:
    Keyboard.release('j');
  }

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState4 == LOW) {
    // turn LED on:jkdfjkdfjdkfjdkfjdkfjdkjfdkjfkdjfkdjk
    Keyboard.press('k');
    
    if(lastbuttonState4 == HIGH)
    {
      doClick();
    }
  } else {
    // turn LED off:
    Keyboard.release('k');
  }
  
  if(getCPS() > highestCPS)
  {
    highestCPS = getCPS();
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);


  display.println("OSUBOARD");
  display.println("Clicks: " + String(clicks));
  display.println("Recent: " + String(longclicks));
  display.println("CPS: " + String(getCPS()));
  display.println("Highest CPS: " + String(highestCPS));
  display.display();

  lastbuttonState1 = buttonState1;
  lastbuttonState2 = buttonState2;
  lastbuttonState3 = buttonState3;
  lastbuttonState4 = buttonState4;
}
