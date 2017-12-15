
// User variables
int revs = 20;
int _speed = 1000;

// Constants
int Index;
int motion = 0;
int count = 0;
int halfrevs = revs / 2;
int _slow = _speed * 2;
int revsplus = revs + 1;




void setup()
{
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction
  pinMode(10, INPUT); //Motion

  digitalWrite(6,LOW);
}

void cw_direction() {
  digitalWrite(4,HIGH);
}
void acw_direction() {
  digitalWrite(4,LOW);
}


void high_motion()
{

  for(Index = 0; Index < 200; Index++)
  {
    digitalWrite(5,HIGH);
    delayMicroseconds(_speed);
    digitalWrite(5,LOW);
    delayMicroseconds(_speed);
  }
}

void low_motion()
{

  for(Index = 0; Index < 200; Index++)
  {
    digitalWrite(5,HIGH);
    delayMicroseconds(_slow);
    digitalWrite(5,LOW);
    delayMicroseconds(_slow);
  }
}

void loop() 
{
  Serial.begin(9600);
  if (count < revs) {
    motion = digitalRead(10);
    Serial.println(motion);
    if (count < halfrevs) {
      if (motion == HIGH) {
        Serial.println("TO - Fast motion detected!");
        count = count +1;
        Serial.println(count);
        cw_direction();
        high_motion();
      } else {
        Serial.println("TO - Slow motion detected!");
        count = count +1;
        Serial.println(count);
        cw_direction();
        low_motion();
      }
    }
    if (count == halfrevs) {
      
      delay(1000);
      acw_direction();
      count = count +1;
      Serial.println("Changing only direction in this step");
      Serial.println(count);
      
    }
    if (count > halfrevs) {
      if (motion == HIGH) {
        Serial.println("FRO - Fast motion detected!");
        count = count +1;
        Serial.println(count);
        acw_direction();
        high_motion();
      } else {
        Serial.println("FRO - Slow motion detected!");
        count = count +1;
        Serial.println(count);
        acw_direction();
        low_motion();
      }
    }
    if (count == revs) {
      delay(1000);
      cw_direction();
      count = count +1;
      Serial.println("Changing only direction in this step");
      Serial.println(count);
    }
    
  } else {
    count = 0;
  }
}
