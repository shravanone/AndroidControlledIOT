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
      if((String)value=="1")
      {
        Serial.println(name+" Is On");
        digitalWrite(pin, HIGH);
      }
      else
      {
        Serial.println(name+" Is Off");
        digitalWrite(pin, LOW);
      }
    }

    void update(WiFiClientSecure client)
    {
      if(client.find(loc))
      {
        client.readBytes(value, 1); 
        found();
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
      Serial.println(name+" Is "+value);
  }
  void update(WiFiClientSecure client)
  {
    if(client.find(loc))
    {
      client.readBytes(value, 1); 
      found();
    }
  }
};
