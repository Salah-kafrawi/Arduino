

void setup() {
  // put your setup code here, to run once:
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
     // Initialize the BUILTIN_LED pin as an output
 
   }
void loop()
{
  delay(1000);
    digitalWrite(4, HIGH);
   digitalWrite(5,HIGH);
   delay(1000);
    digitalWrite(4, LOW);
   digitalWrite(5,LOW);
  }
