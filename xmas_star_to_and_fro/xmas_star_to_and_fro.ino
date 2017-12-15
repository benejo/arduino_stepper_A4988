
// User variables
int revs = 20;
int _fast = 1000;

// Constants
int index;
int motion = 0;
int count = 0;
int halfrevs = revs / 2;
int _slow = _fast * 2;
int delay_speed;
char cw_dir = HIGH;
char acw_dir = LOW;
char set_dir;



void setup()
{
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction
  pinMode(10, INPUT); //Motion

  digitalWrite(6,LOW);
}

void _direction(char set_dir) {
  digitalWrite(4,set_dir);
}


void _motion(int delay_speed)
{

  for(index = 0; index < 200; index++)
  {
    digitalWrite(5,HIGH);
    delayMicroseconds(delay_speed);
    digitalWrite(5,LOW);
    delayMicroseconds(delay_speed);
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
        _direction(cw_dir);
        _motion(_fast);
      } else {
        Serial.println("TO - Slow motion detected!");
        count = count +1;
        Serial.println(count);
        _direction(cw_dir);
        _motion(_slow);
      }
    }
    if (count == halfrevs) {
      
      delay(1000);
      _direction(acw_dir);
      count = count +1;
      Serial.println("Changing only direction in this step");
      Serial.println(count);
      
    }
    if (count > halfrevs) {
      if (motion == HIGH) {
        Serial.println("FRO - Fast motion detected!");
        count = count +1;
        Serial.println(count);
        _direction(acw_dir);
        _motion(_fast);
      } else {
        Serial.println("FRO - Slow motion detected!");
        count = count +1;
        Serial.println(count);
        _direction(acw_dir);
        _motion(_slow);
      }
    }
    if (count == revs) {
      delay(1000);
      _direction(cw_dir);
      count = count +1;
      Serial.println("Changing only direction in this step");
      Serial.println(count);
    }
    
  } else {
    count = 0;
  }
}
