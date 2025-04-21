const int red = 9;
const int blue = 11;
const int green = 10;
const int trigPin = 6;
const int echoPin = 7;
const int buzzer = 3;

float duration, distance;

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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance <= 500) {
    analogWrite(red, 0);
    analogWrite(green, 255);
    noTone(buzzer);
  } else {
    analogWrite(red, 255);
    analogWrite(green, 0);
    tone(buzzer, 130);
    delay(50);
    tone(buzzer, 600);
    delay(50);
  }
  delay(100);
}
