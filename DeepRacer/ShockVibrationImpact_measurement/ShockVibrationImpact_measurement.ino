int vibr_Pin = D2;

void setup(){
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurmentnn
  Serial.begin(9600); //init serial 9600
 // Serial.println("----------------------Vibration demo------------------------");
}
void loop(){
  long measurement =TP_init();
  delay(250);
 // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 25000){
    Serial.println("Ya.. otw meet maker.. >o<");
  }
}

long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}