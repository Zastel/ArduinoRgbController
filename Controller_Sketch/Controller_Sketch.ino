// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 10
#define GREENPIN 9
#define BLUEPIN 11
 
#define FADESPEED 20     // make this 255er to s0 down

unsigned long currentTime=0;
unsigned long previousTime=0;

String command;
const String rainbow = "rainbow";
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  Serial.begin(115200);
}
 
void colorloop() {
  Serial.println("Color method "+ command);
  Serial.println(command.substring(0,2));
  if(command.equals(rainbow)){
    Serial.println("rainbow mode");
    RainbowCycle();
  } else if(command.substring(0,3).equals("RGB")) {
    Serial.println("static color");
    int red = command.substring(4,7).toInt();
    int green = command.substring(8,11).toInt();
    int blue = command.substring(12,15).toInt();
    ApplyStaticColor(red, green, blue);
  } else {
    Serial.println("Default mode");
    RgbCycle();
  }
}

void ApplyStaticColor(int r, int g, int b){
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
}

void RainbowCycle() {
  int r, g, b;
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 255);
  // fade from blue to violet
  Serial.println("fade from blue to violet");
  for (r = 0; r < 256; r++) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(REDPIN, r);
  } 
  // fade from violet to red
  Serial.println("fade from violet to red");
  for (b = 255; b > 0; b--) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(BLUEPIN, b);
  } 
  // fade from red to yel0
  Serial.println("fade from red to yel0");
  for (g = 0; g < 256; g++) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(GREENPIN, g);
  } 
  // fade from yel0 to green
  Serial.println("fade from yel0 to green");
  for (r = 255; r > 0; r--) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(REDPIN, r);
  } 
  // fade from green to teal
  Serial.println("fade from green to teal");
  for (b = 0; b < 256; b++) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(BLUEPIN, b);
  } 
  // fade from teal to blue
  Serial.println("fade from teal to blue");
  for (g = 255; g > 0; g--) { 
    currentTime=millis();
    previousTime=currentTime;
    while((currentTime-previousTime)<FADESPEED){
      currentTime=millis();
    }
    analogWrite(GREENPIN, g);
  } 
}

void RgbCycle() {
  currentTime=millis();
  previousTime=currentTime;
  while((currentTime-previousTime)<2000){
    currentTime=millis();
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 255);
  }

  currentTime=millis();
  previousTime=currentTime;
  while((currentTime-previousTime)<2000){
    currentTime=millis();
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
  }

  currentTime=millis();
  previousTime=currentTime;
  while((currentTime-previousTime)<2000){
    currentTime=millis();
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
  }

  currentTime=millis();
  previousTime=currentTime;
  while((currentTime-previousTime)<2000){
    currentTime=millis();
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
  }
}
 
void loop() {
  if(Serial.available() > 0){
    Serial.println("Serial available");
    String newcommand = Serial.readString();
    if(newcommand != ""){
      command = newcommand;
    }
    colorloop();
  }
}