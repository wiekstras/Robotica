/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //Required libraries

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //defining the parameters of the display

//IMPORTANT: XBee module is disconnected. Connecting it breaks communication with the arduino IDE (computer). This means that use of the XBEE module is only possible while the PC is disconnected/only used for power supply. 
//XBee model is S1, setup in Transparant mode. Baud is 9600 (will be changed if needed.)

//DIGITAL PINS
int AutoSwitch = A3;
int JoyButton = 13;

int buttonarray[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A3, A3, A3, A3};

//ANALOG PINS
int JoystickX = A0;
int JoystickY = A1;
int SpeedPot = A6;
int GrippPot = A2;
int HeightPot = A7;


//Carryover variables
int lastAutoSwitch, lastJoyButton, lastJoystickX, lastJoystickY, lastSpeedPot, lastGrippPot, lastHeightPot;
int currentbuttonarray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lastbuttonarray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  // initialize serial communication at 115200 bits per second. Undecided what baud the final project will run at, 115200 would be nice, assume this for now.
  Serial.begin(38400);
  pinMode(AutoSwitch, INPUT);
  pinMode(JoyButton, INPUT);
  
  pinMode(JoystickX, INPUT);
  pinMode(JoystickY, INPUT);
  pinMode(SpeedPot, INPUT);
  pinMode(GrippPot, INPUT);
  pinMode(HeightPot, INPUT);
  display.setRotation(90);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Adress of the display is 0x3C
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.display(); //Call this function whenever the display needs to be updated
  delay(2000); // Pause for 2 seconds 
}

/*Voor de seriele communicatie zal gebruik worden gemaakt van binaire waardes. hierbij is het makkelijk als alle informatie die wordt verstuurd mogelijk is binnen 8 bits: 1 volledig frame binnen UART.
 * Dit zal worden gedaan door de uitgelezen waardes van de joystick, knoppen etc om te bouwen naar een constructor. Deze zal er als volgt uitzienL
 * 
 * SCCCCVVVVT
 * 
 * S: Start bit (standaard in UART)
 * C: Commando. Dit zal betekenen dat deze 4 waardes het type commando aangeven welke wordt verstuurd
 * V: De uitgelezen waarde. Dit zal betekenen dat de 1024 van de joystick zal worden gecondenseerd naar 4 bits. Dit zou alsnog genoeg besturing moeten geven.
 * T: Stop bit.
 * Op deze manier is het hopelijk makkelijker om de juist waardes uit te lezen vanaf de controller naar de robot zonder te veel dataverkeer. 
 * 
 * Dit betekent dus het volgende:
 * 
 * Joystick X: 0001 VVVV
 * Joystick Y: 0010 VVVV
 * Grijper 1:  0011 VVVV
 * Grijper 2:  0100 VVVV
 * Snelheidspot: 0101 VVVV
 * 
 * Voor de knoppen kunnen we dan de waarde velden ook combineren:
 * 
 * Knopgroep LINKS: 0110 GBGR (groen, blauw, geel, rood LINKS)
 * Knopgroep RECHTS; 0111 GBGR (groen, blauw, geel, rood RECHTS)
 * Knopgroep OVERIG1: 1000 ZZZS(zwart, zwart, zwart (links naar rechts), switch)
 * Knopgroep OVERIG2: 1001 xxxJ (Joystick button)
 * 
 * Dit zou genoeg info moeten meegeven.
 */

// the loop routine runs over and over again forever:
void loop() {
  int tempnum = 0;
  int tempcount = 0;
  int checkupdate = 0;

  int analogJoyX = analogRead(JoystickX);
  analogJoyX = map(analogJoyX, 0, 1024, 0, 15);
  if (analogJoyX >= 6 && analogJoyX <= 8){
    analogJoyX = 7;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Idle"));
  }
  if (analogJoyX != lastJoystickX){
   Serial.write((16+analogJoyX)); //Joystick X: 0001 VVVV
   lastJoystickX = analogJoyX;
     if (analogJoyX < 7) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Naar"));
    display.println(F("Achter"));
  } else if (analogJoyX > 7) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Van"));
    display.println(F("Voor"));
  }
  display.display(); // Toon de bijgewerkte inhoud van de display
  }
  
  int analogJoyY = analogRead(JoystickY);
analogJoyY = map(analogJoyY, 0, 1024, 0, 15);
if (analogJoyY >= 6 && analogJoyY <= 8) {
  analogJoyY = 7;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Idle"));
}
if (analogJoyY != lastJoystickY) {
  Serial.write((32 + analogJoyY)); // Joystick Y: 0010 VVVV
  lastJoystickY = analogJoyY;
  if (analogJoyY < 7) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Van"));
    display.println(F("Links"));
  } else if (analogJoyY > 7) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Naar"));
    display.println(F("Rechts"));
  }
  display.display(); // Toon de bijgewerkte inhoud van de display
}

  int analogGripp = analogRead(GrippPot); //rechter
    analogGripp = map(analogGripp, 0, 1024, 0, 15); 
  if (analogGripp  < lastGrippPot - 1 || analogGripp  > lastGrippPot + 1){ //Meer debouncing, hierbij is het van belang dat er niet constante signalen worden verstuurd als de pot net tussen 2 waarden in zit.
   Serial.write((48+analogGripp)); //Grijper 1:  0011 VVVV
   lastGrippPot = analogGripp;
  }
  
  int analogHeight = analogRead(HeightPot); //linker
    analogHeight = map(analogHeight, 0, 1024, 0, 15);
  if (analogHeight < lastHeightPot - 1 || analogHeight > lastHeightPot + 1){
   Serial.write((64+analogHeight)); //Grijper 2:  0100 VVVV
   lastHeightPot = analogHeight;
  }
  
  int analogSpeed = analogRead(SpeedPot);
    analogSpeed = map(analogSpeed, 0, 1024, 0, 15);
  if (analogSpeed < lastSpeedPot - 1 || analogSpeed > lastSpeedPot + 1){
   Serial.write((80+analogSpeed)); //Snelheidspot: 0101 VVVV
   lastSpeedPot = analogSpeed;
  }
  tempnum = 0;
  //int calc = (255);
  // Serial.write(calc);
  // delay(300);
  for (int i = 0; i < 16; i++){
    currentbuttonarray[i] = digitalRead(buttonarray[i]); //Hierbij lezen we alle knoppen op de controller uit: dit zijn er eigenljk maar 13. Om een mooi aantal frames op te bouwen is er voor gekozen om knop 13 4x te kopieren om 16 waardes te krijgen. 
    tempnum = tempnum + (currentbuttonarray[i] * (1<<i%4)); //Nummer optellen, dit gebeurt 4 keer. Elke keer 1 maal bitshiften, hiermee zetten we dus 4 knopwaardes klaar. (xxxx 1234 <- 4 knoppen in 1 byte.)

    if (currentbuttonarray[i]!= lastbuttonarray[i]){ //als er een nieuwe knopwaarde wordt gevonden
      lastbuttonarray[i] = currentbuttonarray[i];
      checkupdate = 1; //laat weten dat er een update is
    }
    if (i%4 == 3){ //check elke 4 loops
      if(checkupdate == 1){ //knop geupdate in deze loop?
          int calc = (96+(tempcount*16)+tempnum); //verstuur commando + knopwaardes. Deze telt telkens op met 16 (binair bit 5)
          Serial.write(calc);
      checkupdate = 0;
      }
      tempnum = 0;
      tempcount++;
    }
  }
  tempcount = 0;
  delay(10);

  
}
