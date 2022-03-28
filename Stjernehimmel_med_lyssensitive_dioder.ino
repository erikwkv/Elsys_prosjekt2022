void setup() {
  pinMode(7, OUTPUT); //setter pin 7 til output
}

void loop() {
  // leser av input paa analog pin A0 (verdi mellom 0 og 1023), dvs. spenningen over motstanden
  int analogValue = analogRead(A0);

 
  if (analogValue < 500) {
    digitalWrite(7, HIGH); // skrur paa diodene hvis det er mørkt nok
  } else {
    digitalWrite(7, LOW); //skrur av diodene hvis det er lyst nok
  }

  delay(500);
}
