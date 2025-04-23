/*
Name: Nate, Pranav, Stratton
Program: Arduino Project
Date: 4/23/25
*/

//define pins and vars
const int red = 9;
const int blue = 11;
const int green = 10;
const int trigPin = 6;
const int echoPin = 7;
const int buzzer = 3;

float duration, distance, avgDistance;
float distances[10] = {};

int runs = 1;

//set pinmodes and any states that do not change
void setup() {
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  analogWrite(blue, 0);
}

void loop() {
  //sends signal out
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // converts distance and prints
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  //adds to list, and calculates average
  distances[(runs - 1) % 10] = distance;
  avgDistance = calcAvg();
  Serial.print("Average: ");
  Serial.println(avgDistance);

  //led is green and no sound if obj detected to be in the sameish spot
  if (abs(avgDistance - distance) <= 250) {
    analogWrite(red, 0);
    analogWrite(green, 255);
    noTone(buzzer);
  } else {
    //led turns red and buzzer plays
    analogWrite(red, 255);
    analogWrite(green, 0);
    tone(buzzer, 130);
    delay(50);
    tone(buzzer, 600);
    delay(50);
  }

  runs++;
  delay(100);
}

// calculates average
float calcAvg() {
  float sum = 0;
  for (float dist : distances) {
    sum += dist;
  }
  return sum / 10;
}
