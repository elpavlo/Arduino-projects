boolean flag=0;
boolean led_flag=0;
boolean is_holded=0;
unsigned long last_pressed;
int counter1=0;
int counter2=0;
int result=0;
unsigned long last_lighted=0;
void setup() {
pinMode(A3,INPUT_PULLUP);
//pinMode(12,INPUT);
pinMode(13,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
//digitalWrite(13,1 );
//digitalWrite(A5,1 );
Serial.begin(9600);

}
void loop() {
 
 boolean button1=!digitalRead(A3);
 if (button1==1&&flag==0&&millis()-last_pressed>300&&is_holded==0) {
 
  flag=1;
  led_flag=!led_flag;
  digitalWrite(13,led_flag);
  last_pressed=millis();
  Serial.println("press");
  counter1+=1;
  Serial.println(counter1);
  }
  
  if (button1==1&&flag==0&&millis()-last_pressed>300&&is_holded==1) {
  flag=1;
  led_flag=!led_flag;
  digitalWrite(13,led_flag);
  last_pressed=millis();
  Serial.println("press");
  counter2+=1;
  Serial.println(counter2);
  }
  
 if (button1==0&&flag==1){
  flag=0;
  } 

 if(is_holded==1&&millis()-last_pressed>3000&&counter2!=0){
  result=counter1+counter2-1;
  digitalWrite(5,1);
    delay(500);
    digitalWrite(5,0);
  for (int i=1; i<= result;i=i+1){
     
     digitalWrite(4,1);
     Serial.println("lighted");
     last_lighted=millis(); 
     while(1){
       //Serial.println("in while");
      if(millis()-last_lighted>1000){
        // Serial.println(last_lighted);
      break;
      }
      }
     
     //delay(500);
     
     digitalWrite(4,0);
      //Serial.println("no-lighted");
     while(1){
       //Serial.println("in while");
      if(millis()-last_lighted>1500){
         //Serial.println(last_lighted);
      break;
      }
      } 
     //delay(1000);
    }
    digitalWrite(5,1);
    delay(500);
    digitalWrite(5,0);
  Serial.println("result here");
 
  counter1=0;
  counter2=0;
  is_holded=0;
  }
 if (button1==1&&millis()-last_pressed>600){
  while(1){
    Serial.println("hold");
    digitalWrite(6,1);
    is_holded=1;
    boolean button2=!digitalRead(A3);
    if (button2==0){
      digitalWrite(6,0);
      break;
      }
    }
  }


}
