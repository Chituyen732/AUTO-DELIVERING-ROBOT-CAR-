#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL-ZQnNvU1"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "JPqCvT7vW1JQy2eW1n8SbroQqsTj3vKS"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

int tram_1;
int tram_2;
int tram_3;
int Start;


char auth[]="JPqCvT7vW1JQy2eW1n8SbroQqsTj3vKS"; 
char ssid[]="Haha";
char pass []="12345678";


String v2STM; // values to arduino
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int tram_1_on, tram_2_on, tram_3_on, Start_status, Done;
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.



void setup(){
      Serial.begin(9600);
      Blynk.begin(auth, ssid, pass);
}

void loop () {
      if (Serial.available() == 0 ) 
      {
            Blynk.run();
            toSTM();
      }
      
      if (Serial.available() > 0 ) 
      {
          rdata = Serial.read(); 
          myString = myString + rdata; 
          // Serial.print(rdata);
          if( rdata == '\n')
          {
      
                // new code
                String r_tram_1 = getValue(myString, ',', 0);
                String r_tram_2 = getValue(myString, ',', 1);
                String r_tram_3 = getValue(myString, ',', 2);
                String r_Start = getValue(myString, ',', 3);
                String r_Done = getValue(myString, ',', 4);
                      
                tram_1_on = r_tram_1.toInt();
                tram_2_on = r_tram_2.toInt();
                tram_3_on = r_tram_3.toInt();
                Start_status =  r_Start.toInt();
                Done = r_Done.toInt();
          Serial.print(Done);

                if(Done >= 2){
                   Blynk.virtualWrite(V9, 1);
                  }
                myString = "";

                
      // end new code
          } 
      }

     
}

BLYNK_WRITE (V0) {
 tram_1 = param.asInt ();
 int sdata = tram_1_on;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}

BLYNK_WRITE (V1) {
 tram_2 = param.asInt ();
 int sdata = tram_2_on;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}

BLYNK_WRITE (V2) {
 tram_3 = param.asInt ();
 int sdata = tram_3_on;
// You can send any value at any time.
// Please don't send more that 10 values per second.
}

BLYNK_WRITE (V8) {
 Start = param.asInt ();
 int sdata = Start_status;
// You can send any value at any time.
// Please don't send more that 10 values per second.
}


void toSTM()
{
      v2STM = v2STM + tram_1 + "," + tram_2 + "," + tram_3 + "," + Start + "," + Done; 
      Serial.println(v2STM); 
      delay(100); 
      v2STM = ""; 
}

String getValue(String data, char separator, int index)
{
      int found = 0;
      int strIndex[] = { 0, -1 };
      int maxIndex = data.length() - 1;
  
      for (int i = 0; i <= maxIndex && found <= index; i++) {
            if (data.charAt(i) == separator || i == maxIndex) {
                  found++;
                  strIndex[0] = strIndex[1] + 1;
                  strIndex[1] = (i == maxIndex) ? i+1 : i;
            }
      }
      return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
