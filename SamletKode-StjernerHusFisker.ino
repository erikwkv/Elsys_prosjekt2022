//DCmotor
const int in_1 = 4 ;
const int in_2 = 5 ;
const int buttonPin = 6 ;
int buttonState = 0 ;

//Lys i hus
const int lys1{3};
const int lys2{9};
const int lys3{10};
const int lys4{11};
const int knapp1{A0};
const int knapp2{A1};
const int knapp3{A2};
const int knapp4{A3};


void setup() {
  //LYSSENSOR
   pinMode(7, OUTPUT); //setter pin 7 til output

  //DCmotor
   pinMode(in_1,OUTPUT) ; 
   pinMode(in_2,OUTPUT) ;
   pinMode(buttonPin, INPUT) ;

  //Lys i hus
  Serial.begin(9600);
  pinMode(lys1, OUTPUT);
  pinMode(lys2, OUTPUT);
  pinMode(lys3, OUTPUT);
  pinMode(lys4, OUTPUT);
  pinMode(knapp1, INPUT);
  pinMode(knapp2, INPUT);
  pinMode(knapp3, INPUT);
  pinMode(knapp4, INPUT);

   
}


//--------------lys i hus--------------------
//Generelle globale variabler
int intervall = 50;
int wait = 1500 / intervall;
byte index{};
byte inkrement = 5;

bool samples1[256]{}; // Liste med 256 siste samples
bool samples2[256]{};
bool samples3[256]{};
bool samples4[256]{};

//variabler for av/på lys
bool tilstand1 = false;
bool tilstand2 = false;
bool tilstand3 = false;
bool tilstand4 = false;
bool* tilst1 = &tilstand1;
bool* tilst2 = &tilstand2;
bool* tilst3 = &tilstand3;
bool* tilst4 = &tilstand4;
bool endre1{};
bool endre2{};
bool endre3{};
bool endre4{};
bool* endr1 = &endre1;
bool* endr2 = &endre2;
bool* endr3 = &endre3;
bool* endr4 = &endre4;

//variabler for fade
byte analog1 = 255;
byte analog2 = 255;
byte analog3 = 255;
byte analog4 = 255;
byte* ana1 = &analog1;
byte* ana2 = &analog2;
byte* ana3 = &analog3;
byte* ana4 = &analog4;
bool rising1{};
bool rising2{};
bool rising3{};
bool rising4{};
bool* ris1 = &rising1;
bool* ris2 = &rising2;
bool* ris3 = &rising3;
bool* ris4 = &rising4;


//returnerer high om de det siste intervallet i samples er høy.
bool holdbtn(bool samples[]){ 
  bool flag = true;
  byte index_2 = index;
  
  for(int i = 0; i < intervall; i++){
    if (!samples[index_2--]){
      flag = false;
    };
  };
  return flag;
}

//vurderer hvordan inkrementeringen burde skje og inkrementerer
void sickFade(byte &analog, bool &rising){
  if (analog <= inkrement)        {rising = true;}
  if (analog >= (255 - inkrement)){rising = false;}
  
  if (rising) {analog += inkrement;}
  else        {analog -= inkrement;}
}

//hus 
void hus(bool samples[], const int knapp, const int lys, bool &tilst, byte &analog, bool &endre, bool* rising){
  samples[index] = digitalRead(knapp);  //leser tilstanden og setter inn i listen
  
  if (digitalRead(knapp)){              //om knappen er inne
    if (holdbtn(samples)){              //om knappen er holdt inne lenge
      sickFade(analog, *rising);        //inkrementerer lysstyrken
      analogWrite(lys, (analog));       //let there be light
    }
    else{
      if (endre){
        tilst = !tilst;                 //tilstanden endres hvis knappen blir trykket inn fresh
        
        if ((analog != 255)&!tilst 
          | (analog != 0)&tilst){       //skrur av dersom den var analog sist
          tilst = false;}
          
        digitalWrite(lys, tilst);}       //let there be light (or not)
      
      if (tilst){analog = 255;}         //fade begynner fra høy hvis lyset er på
      else      {analog = 0;}           //fade begynner fra lav hvis lyset er av
      
      endre = false;}                    //for å ikke endre neste kjøring
  }
  else{endre = true;}                       //endrer tilstand neste gang knappen trykkes
}




void loop() {
  // ---------------------LYSSENSOR ------------------------
   // leser av input paa analog pin A0 (verdi mellom 0 og 1023), dvs. spenningen over motstanden
  int analogValue = analogRead(A0);

 
  if (analogValue < 500) {
    digitalWrite(7, HIGH); // skrur paa diodene hvis det er mørkt nok
  } else {
    digitalWrite(7, LOW); //skrur av diodene hvis det er lyst nok
  }

  delay(500);



  //------------------------DCmotor---------------------------
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
  }

  //--------------------LYS I HUS--------------------------------
  hus(samples1, knapp1, lys1, *tilst1, *ana1, *endr1, ris1);
  hus(samples2, knapp2, lys2, *tilst2, *ana2, *endr2, ris2);
  hus(samples3, knapp3, lys3, *tilst3, *ana3, *endr3, ris3);
  hus(samples4, knapp4, lys4, *tilst4, *ana4, *endr4, ris4);

  delay(wait);                            //definerer hvor lenge et "langt" trykk skal være
  ++index;

}
