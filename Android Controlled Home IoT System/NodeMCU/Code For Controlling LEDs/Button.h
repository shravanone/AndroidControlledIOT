class Button
{
  
  private :
  
  public :
    char* loc;
    char* value;
    String name;
    int pin;
    Button(char loc[30],char* value,String name,int pin)
    {
      this->loc=loc;
      this->value=value;
      this->name=name;
      this->pin=pin;
    }
    void found()
    {
      if((String)this->value=="1")
      {
        Serial.println(this->name+" Is On");
        digitalWrite(this->pin, HIGH);
      }
      else
      {
        Serial.println(this->name+" Is Off");
        digitalWrite(this->pin, LOW);
      }
    }
};

class FanSpeedButton
{
  public :
  char* loc;
  char* value;
  String name;
  FanSpeedButton(char loc[40],char* value,String name)
  {
    this->loc=loc;
    this->value=value;
    this->name=name;
  }
  void found()
  {
      Serial.println(this->name+" Is "+this->value);
  }
};
