void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Beginning CSV-serial");
}


void loop() {
  int x = 0;
  while (x<20) {
 Serial.print(x);
  Serial.print(","); 
 Serial.println(x*x);
 delay(1000);
 x++;}
 

}
while(1);
