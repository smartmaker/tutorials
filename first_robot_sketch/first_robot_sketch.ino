int M1 = 5;
int M2 = 6;

int E1 = 4;
int E2 = 7;

int PIRPin = 8;
int buzzerPin = 9;

void forward(int);
void reverse(int);
void left(int);
void right(int);

int PIRState = LOW;
int val = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(PIRPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  delay(60000);
}

void loop()
{
  val = digitalRead(PIRPin);

  if(val == HIGH )
  {
    forward(2000);
    left(1000);
    reverse(3000);
    right(1000);
    tone(buzzerPin, 5000, 1000);
    delay(150);

    if(PIRState == LOW)
    {
      Serial.println("Motion Detected!");

      PIRState = HIGH;
      
    }
  }
  else
  {
    noTone(buzzerPin);
    Stop();
    delay(300);
    if (PIRState == HIGH)
    {
      Serial.println("Motion Ended!");
      //recalibrate
      delay(5000);
      PIRState = LOW;
    }
  }
  
}

void Stop()
{
  digitalWrite(M1, LOW);
  digitalWrite(E1, LOW);

  digitalWrite(M2, LOW);
  digitalWrite(E2, LOW);
}

void forward(int time)
{
  digitalWrite(M1, HIGH);
  digitalWrite(E1, HIGH);

  digitalWrite(M2, HIGH);
  digitalWrite(E2, HIGH);
  delay(time);
}
void reverse(int time)
{
  digitalWrite(M1, HIGH);
  digitalWrite(E1, LOW);

  digitalWrite(M2, HIGH);
  digitalWrite(E2, LOW);
  delay(time);
}
void left(int time)
{
  digitalWrite(M1, HIGH);
  digitalWrite(E1, HIGH);

  digitalWrite(M2, HIGH);
  digitalWrite(E2, LOW);
  delay(time);
}
void right(int time)
{
  digitalWrite(M1, HIGH);
  digitalWrite(E1, LOW);

  digitalWrite(M2, HIGH);
  digitalWrite(E2, HIGH);
  delay(time);
}

