#define servomin 0
#define servomax 480

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

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

    void setServo(int servoNum,int angle)
    {
      currentAngle=angle;
      int pulse = angleToPulse(angle);
      if(angle==180)
      {
        for(int i=0;i<=pulse;i++)
        {
          pwm.setPWM(servoNum,0,i);
          delay(5);
          yield();
        }
      }
      else
      {
        for(int i=480;i>=pulse;i--)
        {
          pwm.setPWM(servoNum,0,i);
          delay(5);
          yield();
        }
      }
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
    void found()
    {
      if((String)value=="1")
      {
        Serial.println(name+" Is On");
        if(currentAngle!=180)
        {
          setServo(servonum,180);
        }
      }
      else
      {
        Serial.println(name+" Is Off");
        if(currentAngle!=0)
        {
          setServo(servonum,0); 
        }
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

  void setServo(int servoNum,int angle)
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
    void found()
    {
      Serial.println(name+" Is "+value);
      if((String)value=="0"&&currentAngle!=0)
      {
        setServo(servonum,0);
      }
       if((String)value=="1"&&currentAngle!=36)
      {
        setServo(servonum,36);
      }
       if((String)value=="2"&&currentAngle!=72)
      {
        setServo(servonum,72);
      }
       if((String)value=="3"&&currentAngle!=108)
      {
        setServo(servonum,108);
      }
       if((String)value=="4"&&currentAngle!=144)
      {
        setServo(servonum,144);
      }
       if((String)value=="5"&&currentAngle!=180)
      {
        setServo(servonum,180);
      }
    }
};
