const int buzzer = 8;
const int trigger = 10; // the pin which gives a signal for the sending of he ultrasound.
const int relay = 9;
const int echo_pins[6] = {
	2,3,4,5,6,7
}; // the pin which receives the signal after deflection from object

int echo;
long duration;
long distance;

// 3 - highest
// 2 - lower
// 1 - lower 
// 0 - lowest 
int max_severity;

void setup() {
    Serial.begin(9600);
  	
  	pinMode(relay, OUTPUT);
    pinMode(buzzer, OUTPUT);
  
    for(int i=0;i<6;i++){
      duration = distance = 0.0;
      echo = echo_pins[i];
      pinMode(echo, INPUT);
      pinMode(trigger, OUTPUT);

    }
  max_severity = -1;
}

int get_severity(int dist){ 

    if(dist > 0 && dist<= 20)
        return 3;
    else if(dist > 20 && dist<= 40)
      	return 2;
    else if(dist > 40 && dist< 60)
      	return 1;
    else 
        return 0;
      
}
     
void loop() {
    
    //calibrate echo pin's pulse input
    max_severity = -1;
    for(int i=0; i<6; i++){
      
	  digitalWrite(trigger, HIGH); //trigpin's output pulse
      delay(10); // waiting for the pulse to return
      digitalWrite(trigger, LOW);
      
      
      echo = echo_pins[i];
      duration= pulseIn(echo, HIGH);
      
      // distanceCm is half the duration multiplied by 0.034
      distance= duration* 0.034 / 2; 
      
      Serial.print("Distance for sensor");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(distance);
      Serial.print("\n");
      max_severity = max(max_severity,get_severity(distance)); 
         
   }
  
     Serial.print("Current severity is :");
     Serial.print(max_severity);
     Serial.print("\n");
  
    // cases for different distances
    if (max_severity  == 3)
    {   
        digitalWrite(buzzer, HIGH);
        digitalWrite(relay, HIGH);
        

    } else if (max_severity == 2)
    {   digitalWrite(buzzer, HIGH);
        delay(20);
        digitalWrite(buzzer, LOW);
        delay(20); 
        
        digitalWrite(buzzer, HIGH);
        delay(20);
        digitalWrite(buzzer, LOW);
        delay(20);
        
        // switch
        digitalWrite(relay, LOW);

    } else if (max_severity == 1)
    {   digitalWrite(buzzer, HIGH);
        delay(20);
        
        digitalWrite(buzzer, LOW);
        delay(20);
        
        digitalWrite(relay, LOW);

    } else{
         digitalWrite(buzzer, LOW);
         digitalWrite(relay, LOW);

    }
}
