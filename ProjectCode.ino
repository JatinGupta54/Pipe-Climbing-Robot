#include <Arduino.h>

//pneumatic output 1-7 = pin 2,3,4,5,6,7,8 respectively 
#define topGripper 2
#define extender 3
#define lowGripper 4

//sensor input 1-4 = pin A0,A1,A2 respectively
#define button1 A0
#define button2 A1

// DO NOT CHANGE ANYTHING IN BUTTON DEBOUNCE
bool button[2] = {false, false};
bool lastButton[2] = {false, false};
bool buttonDebounce[2] = {false, false};
int buttonTime[2] = {0, 0};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  pinMode(topGripper, OUTPUT);
  pinMode(extender, OUTPUT);
  pinMode(lowGripper, OUTPUT);
  //pinMode(13, OUTPUT);
  digitalWrite(topGripper, HIGH);
  digitalWrite(extender, HIGH);
  digitalWrite(lowGripper, HIGH);

}
int state = 0;


void loop() {
 
  buttonFilter();
    Serial.println(getButton(1));
    Serial.println(getButton(2));
    Serial.println(state);
 // put your main code here, to run repeatedly:
  if (state == 0) { //intial state all relaxed with extender contracted
    digitalWrite(topGripper, LOW);
    digitalWrite(extender, LOW);
    digitalWrite(lowGripper, LOW);
    if (getButton(1) == true)
      state++;
    if (getButton(2) == true)
      state = 10;
  }
  else if (state == 1) { //lower gripper engaged
    digitalWrite(topGripper, LOW);
    digitalWrite(extender, LOW);
    digitalWrite(lowGripper, HIGH);
    if (getButton(1) == true)
      state++;
  }
  else if (state == 2) { //push upper gripper up
    digitalWrite(topGripper, LOW);
    digitalWrite(extender, HIGH);
    digitalWrite(lowGripper, HIGH);
    if (getButton(1) == true)
      state++;
  }
  else if (state == 3) { //upper gripper engage
    digitalWrite(topGripper, HIGH);
    digitalWrite(extender, HIGH);
    digitalWrite(lowGripper, HIGH);
    if (getButton(1) == true)
      state++;
  }
  else if (state == 4) { //lower gripper disengage
    digitalWrite(topGripper, HIGH);
    digitalWrite(extender, HIGH);
    digitalWrite(lowGripper, LOW);
    if (getButton(1) == true)
      state++;
  }

  else if (state == 5) { //raise lower gripper
    digitalWrite(topGripper, HIGH);
    digitalWrite(extender, LOW);
    digitalWrite(lowGripper, LOW);
    if (getButton(1) == true)
      state++;
  }

   else if (state == 6) { //lower gripper engage
    digitalWrite(topGripper, HIGH);
    digitalWrite(extender, LOW);
    digitalWrite(lowGripper, HIGH);
    if (getButton(1) == true)
      state = 1;
   }
   else if (state == 10) { //Write your automated Code here
   for (int i=1;i<=20;i++){
      digitalWrite(topGripper, LOW);
      digitalWrite(extender, LOW);
      digitalWrite(lowGripper, LOW);
      delay(1000);
      digitalWrite(topGripper, LOW);
      digitalWrite(extender, LOW);
      digitalWrite(lowGripper, HIGH);
      delay(1000);
      }
   }
}
   
// DO NOT CHANGE ANYTHING IN BUTTON DEBOUNCE
void buttonFilter() { 
  if (analogRead(button1) > 900)
    button[0] = true;
  else
    button[0] = false;
  if (analogRead(button2) > 900)
    button[1] = true;
  else
    button[1] = false;

  if (lastButton[0] == false and button[0] == true && millis() - buttonTime[0] > 200) {
    buttonDebounce[0] = true;
    buttonTime[0] = millis();
  }
  else buttonDebounce[0] = false;

  if (lastButton[1] == false && button[1] == true && millis() - buttonTime[1] > 200) {
    buttonDebounce[1] = true;
    buttonTime[1] = millis();
  }
  else buttonDebounce[1] = false;
  lastButton[0] = button[0];
  lastButton[1] = button[1];
  return;
}
bool getButton(int num) {
  if (num > 0 && num < 3) return buttonDebounce[num - 1];
  else return false;
}
