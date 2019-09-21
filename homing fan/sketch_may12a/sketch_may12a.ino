#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <DHT.h>
#include <DHT_U.h>

#include "DHT.h"

#include <NewPing.h>
#include <Servo.h>

#define DHTPIN 5
#define DHTTYPE DHT11
#define PIN_TRIG 6
#define PIN_ECHO 7
#define MAX_DISTANCE 400
NewPing sonar(PIN_TRIG,PIN_ECHO,MAX_DISTANCE);
DHT dht(DHTPIN,DHT11,6);
boolean pin_state=0;
boolean dist_flag=0;
unsigned long cur_time=0;
boolean fix_flag=0;
boolean on_off_flag=0;
Servo servo1;
void setup() {
  pinMode(3, OUTPUT);
  //pinMode(5, INPUT);
  Serial.begin(9600);
  dht.begin();
  servo1.attach(9);

}

void loop() {
  int spd,round_t;
  int min_angle=50;
  int max_angle=130;
  int distances[max_angle-min_angle];
  bool flag=0;
  bool flag1=0;
   /*
 while(1){
 servo1.write(min_angle);
 analogWrite(3, 0);
 }
  */
  //delay(10000);
  /*for (int i=0;i<10;i++){
  delay(500);  
  if (i%2==0){
  servo1.write(0);
    }  
  else{
  //servo1.write(150);  
    }  
    }
    
   */ 
  if (on_off_flag==1){ 
  if (fix_flag==0){
  analogWrite(3, 0);   
  servo1.write(min_angle);
  delay(1000); 
  for (int i=0;i<(max_angle-min_angle-1); i++){
  // if ((millis()-cur_time)>50){
  //  cur_time=millis();
   delay(50);
   distances[i] = sonar.ping_cm();
   servo1.write(min_angle+i);
    }
 // }  
  //servo1.write(0);
  for (int i=0;i<(max_angle-min_angle-1); i++){
  Serial.print(distances[i]);
  Serial.print(" ,");
  }
  Serial.println("end");
  int minim;
  int pos_min;
  for (int i=0;i<(max_angle-min_angle-1); i++){
  if (distances[i]!=0){
  minim=distances[i];
  pos_min=i;
  break;  
    }  
    }
  
  
  for (int i=0;i<(max_angle-min_angle-1); i++){
  if (distances[i]<minim && distances[i] !=0){
  minim=distances[i];
  pos_min=i;  
    }
  }
  int j=0;
  int counter=0;
  while (flag==0){
     if (distances[pos_min+j]==distances[pos_min] or abs(distances[pos_min]-distances[pos_min+j])<=2){
       j++;
       counter++;
     }
     else if (distances[pos_min+j+1]==distances[pos_min] or abs(distances[pos_min]-distances[pos_min+j+1])<=2) {
      j+=2;
      counter+=2; 
     }
     else flag=1;
   }
   j=0;
   int counter1=0;
   int pos_min_first;
   while (flag1==0){
     if (distances[pos_min-j]==distances[pos_min] or abs(distances[pos_min]-distances[pos_min-j])<=2){
       pos_min_first=pos_min-j;
       j++;
       counter1++;
       
     }
     else if (distances[pos_min-j-1]==distances[pos_min] or abs(distances[pos_min]-distances[pos_min-j-1])<=2) {
      j+=2;
      pos_min_first=pos_min-j+1;
      counter1+=2; 
     }
     else flag1=1;
   }
  int len_smaller_obj=counter+counter1-1;
  int min1;
  int pos_min1;
  ///////////////////////////
  if (len_smaller_obj<=3){
  for (int i=0;i<(max_angle-min_angle-1); i++){
  if (distances[i]!=0 and distances[i]!=minim){
  min1=distances[i];
  pos_min1=i;
  break;  
    }  
    }  
    for (int i=0;i<(max_angle-min_angle-1); i++){
      if ((distances[i] <min1 and distances[i]!=0)and( i<pos_min-counter1-1 or i>pos_min+counter-1)){
        min1=distances[i];
        pos_min1=i;
    }
     
   }
  j=0;
  counter=0;
  flag=0;
  flag1=0;
  while (flag==0){
     if (distances[pos_min1+j]==distances[pos_min1] or abs(distances[pos_min1]-distances[pos_min1+j])<=2){
       j++;
       counter++;
     }
     else if (distances[pos_min1+j+1]==distances[pos_min1] or abs(distances[pos_min1]-distances[pos_min1+j+1])<=2) {
      j+=2;
      counter+=2; 
     }
     else flag=1;
   }
   j=0;
   counter1=0;
   while (flag1==0){
     if (distances[pos_min1-j]==distances[pos_min1] or abs(distances[pos_min1]-distances[pos_min1-j])<=2){
       pos_min_first=pos_min1-j;
       j++;
       counter1++;
       
     }
     else if (distances[pos_min1-j-1]==distances[pos_min1] or abs(distances[pos_min1]-distances[pos_min1-j-1])<=2) {
      j+=2;
      pos_min_first=pos_min1-j+1;
      counter1+=2; 
     }
     else flag1=1;
   }
  pos_min=pos_min1; 
  len_smaller_obj=counter+counter1-1;
   }
  Serial.print("min1=");
  Serial.println(min1);
  Serial.print("min=");
  Serial.println(minim);
  Serial.print("pos_min=");
  Serial.println(pos_min);
  Serial.print("len=");
  Serial.print(counter);
  Serial.print("+");
  Serial.println(counter1-1);
  Serial.print("object starts at=");
  Serial.println(pos_min_first);
  Serial.print("servo.write=");
  Serial.println(min_angle+pos_min_first+round(len_smaller_obj/2));
  servo1.write(min_angle+pos_min_first+round(len_smaller_obj/2));
  analogWrite(3, 250);
  //Serial.print("Angle_min=");
  //Serial.println(min_angle);
  //Serial.print("Angle_pos=");
  //Serial.println(pos_min);
  fix_flag=1;
  }
  }
  if (sonar.ping_cm()<15){
    delay(2000);
    if (sonar.ping_cm()<15){
        on_off_flag=!on_off_flag;
         Serial.print("onoff=");
         Serial.println(on_off_flag);
        if (fix_flag==1) fix_flag=0;
        if (on_off_flag==0) analogWrite(3, 0);  
      }
    }
  //Serial.print("Min=  ");
  //Serial.println(minim);
  //Serial.print("Pos=  ");
  //Serial.println(pos_min);
 /*
  if ((millis()-cur_time)>50){
  //servo1.write(90);
  cur_time=millis();
  //delay(50);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println("см");
  if (distance<20){
    analogWrite(3, 200);
    dist_flag=1;
    }
  else{
    analogWrite(3, 0);
    }  
  //analogWrite(3, 170);
  
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (t>30){
    round_t=round(t);
    spd=170+(round_t-30)*19;
    Serial.print("spd=  ");
    Serial.println(spd);
    analogWrite(3, spd);
  }
  else {
  if (t<29  && dist_flag==0){
     analogWrite(3, 0);
    }
  }
  //pin_state=digitalRead(5);
  
  Serial.print("Temp=  ");
  Serial.println(t);
  Serial.print("Humidity=  ");
  Serial.print(h);
  Serial.println("%");
}
*/
}
