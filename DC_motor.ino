
const int in_1 = 4 ;
const int in_2 = 5 ;
const int buttonPin = 6 ;

int buttonState = 0 ;

//For providing logic to L298 IC to choose the direction of the DC motor

void setup() {
   pinMode(in_1,OUTPUT) ; //Logic pins are also set as output
   pinMode(in_2,OUTPUT) ;
   pinMode(buttonPin, INPUT) ;
}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){
   //For Clock wise motion , in_1 = High , in_2 = Low
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,LOW) ;
   //Clockwise for 2 secs
   delay(2000) ;
     
   //For brake
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,LOW) ;
   delay(1000) ;
     
   //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,HIGH) ;
   delay(2000) ;
     
   //For brake
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,LOW) ;
   delay(1000) ;
  //}
}
