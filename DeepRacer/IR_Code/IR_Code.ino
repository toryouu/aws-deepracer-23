int inputPin =12; // D6 choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status

void setup() 
{  
  Serial.begin(9600);
   pinMode(inputPin, INPUT); // declare Infrared sensor as input
}


void loop() {
  // put your main code here, to run repeatedly:
   val = digitalRead(inputPin); // read input value 
   if (val == HIGH)
   { // check if the input is HIGH
      Serial.print(val);
      Serial.println("IR Sensor Value with out Object in front of the Sensor");
 
   } 
   else 
   { 
      Serial.print(val);
      Serial.println("IR Sensor Value with an Object in front of the Sensor");
      delay(10000);
   } 
}
