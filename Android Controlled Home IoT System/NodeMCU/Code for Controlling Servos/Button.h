#define servomin 70
#define servomax 480

class Button
{
  private :
    int currentAngle=0;
    
    int angleToPulse(int angle)
    {
      int pulse = map(angle,0,180,servomin,servomax);
      yield();
      return pulse;
    }

    void setServo(int servoNum,int angle,Adafruit_PWMServoDriver pwm)
    {
      currentAngle=angle;
      int pulse = angleToPulse(angle); 
      pwm.setPWM(servoNum,0,pulse);
      yield();
    }
  public :
    char* loc;
    char* value;
    String name;
    int servonum;
    Button(char loc[30],char* value,String name,int servonum)
    {
      this->loc=loc;
      this->value=value;
      this->name=name;
      this->servonum=servonum;
    }
    void found(Adafruit_PWMServoDriver pwm)
    {
      if((String)value=="1")
      {
        Serial.println(name+" Is On");
        if(currentAngle!=180)
        {
          setServo(servonum,180,pwm);
        }
      }
      else
      {
        Serial.println(name+" Is Off");
        if(currentAngle!=0)
        {
          setServo(servonum,0,pwm); 
        }
      }
    }
    void update(WiFiClientSecure client,Adafruit_PWMServoDriver pwm){
      if(client.find(loc))
      {
        client.readBytes(value, 1); 
        found(pwm);
      }
    }
};

class FanSpeedButton
{
  private :
    int currentAngle = 0;
  
    int angleToPulse(int angle){
    int pulse = map(angle,0,180,servomin,servomax);
    yield();
    return pulse;
  }

  void setServo(int servoNum,int angle,Adafruit_PWMServoDriver pwm)
  {
    int pulse = angleToPulse(angle);
    if(currentAngle<angle)
    {
      for(int i=angleToPulse(currentAngle);i<=pulse;i++)
      {
        pwm.setPWM(servoNum,0,i);
        delay(5);
        yield();
      }
    }
    else{
      for(int i=angleToPulse(currentAngle);i>=pulse;i--)
      {
        pwm.setPWM(servoNum,0,i);
        delay(5);
        yield();
      }
    }
    currentAngle=angle;
  }
  public :
    char* loc;
    char* value;
    String name;
    int servonum;
    FanSpeedButton(char loc[40],char* value,String name,int servonum)
    {
      this->loc=loc;
      this->value=value;
      this->name=name;
      this->servonum=servonum;
    }
    void found(Adafruit_PWMServoDriver pwm)
    {
      Serial.println(name+" Is "+value);
      if((String)value=="0"&&currentAngle!=0)
      {
        setServo(servonum,0,pwm);
      }
       if((String)value=="1"&&currentAngle!=36)
      {
        setServo(servonum,36,pwm);
      }
       if((String)value=="2"&&currentAngle!=72)
      {
        setServo(servonum,72,pwm);
      }
       if((String)value=="3"&&currentAngle!=108)
      {
        setServo(servonum,108,pwm);
      }
       if((String)value=="4"&&currentAngle!=144)
      {
        setServo(servonum,144,pwm);
      }
       if((String)value=="5"&&currentAngle!=180)
      {
        setServo(servonum,180,pwm);
      }
    }
    void update(WiFiClientSecure client,Adafruit_PWMServoDriver pwm){
      if(client.find(loc))
      {
        client.readBytes(value, 1); 
        found(pwm);
      }
    }
};
