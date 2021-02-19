/*        
               STUPIDCREATIVITY

                  Code by:-
                            Divij Vignesh
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int trigPin  = 2; //This can be  any pin on  the digital port
const int echoPin = 4; //Any  pin on  the digital port
void setup()  {
  //  initialize  serial  communication:
  lcd.begin(20,4);
}
void loop()
{
  //  establish variables for duration  of  the ping,
  //  and the distance  result  in  inches  and centimeters:
  long duration,  inches, cm;
  //  The sensor  is  triggered by  a HIGH  pulse of  10  or  more  microseconds.
  //  Give  a short LOW pulse beforehand  to  ensure  a clean HIGH  pulse:
  pinMode(trigPin,  OUTPUT); //Since  you use this  pin on  the Arduino board to  send  a
  //  trigger pulse to  the sonar sensor, configure the pin to  an  OUTPUT
  digitalWrite(trigPin, LOW); //First reset the pin to  LOW.
  delayMicroseconds(2); //Wait  for 2 micro seconds
  digitalWrite(trigPin, HIGH); //Send the trigger pulse by  setting its voltage to  HIGH
  //  HIGH  means its voltage will  be  5V  in  transistor-transistor logic (TTL).
  delayMicroseconds(10); //Hold the pulse for 10  microsecond (you  can change  this)
  digitalWrite(trigPin, LOW); //Then  set it  back  to  LOW (0V)
  //  Read  the signal  from  the sensor: a HIGH  pulse whose
  //  duration  is  the time  (in microseconds) from  the sending
  //  of  the ping  to  the reception of  its echo  off of  an  object.
  pinMode(echoPin,  INPUT); //Since the voltage of  the echo  pin of  the sensor  has to  be  read
  //by  this  pin,  configure it  as  an  INPUT pin.
  duration  = pulseIn(echoPin,  HIGH); //get  the duration  this  echo  pin kept  its voltage at  HIGH  (5V)
  //  convert the time  into  a distance
  inches  = microsecondsToInches(duration); //Then  use thiss function  to  compute the distance  to
  //the object in inches
  cm  = microsecondsToCentimeters(duration); //In cm
  lcd.setCursor(2,0);
lcd.print("StupidCreativity");
lcd.setCursor(3,2);
lcd.print("Distance:");
 if(cm<10)
 {
  lcd.print("00");
  lcd.print(cm);
  lcd.setCursor(15,2);
  lcd.print("cm");
  }
 
  else if(cm>=10&&cm<=99)
  {
  lcd.print("0");
  lcd.print(cm);
  lcd.setCursor(15,2);
  lcd.print("cm");
  }
  else
  {
    lcd.print(cm);
    lcd.setCursor(15,2);
    lcd.print("cm");
    }
  delay(100); //Use a 100ms delay before  going to  the next  iteration
}
long microsecondsToInches(long microseconds)
{
  //  According to  Parallax's  datasheet for the PING))),  there are
  //  73.746  microseconds  per inch  (i.e. sound travels at  1130  feet  per
  //  second).    This  gives the distance  travelled by  the ping, outbound
  //  and return, so  we  divide  by  2 to  get the distance  of  the obstacle.
  //  See:  http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 /  2;
}
long microsecondsToCentimeters(long microseconds)
{
  //  The speed of  sound is  340 m/s or  29  microseconds  per centimeter.
  //  The ping  travels out and back, so  to  find  the distance  of  the
  //  object  we  take  half  of  the distance  travelled.
  return microseconds / 29 /  2;
}

