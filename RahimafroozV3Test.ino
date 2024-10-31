#include <SoftwareSerial.h>
//#include <stdlib.h>

SoftwareSerial mySerial(3, 2); // RX, TX

//for Timer
unsigned long previousMillis = 0;
long interval = 2000;

//for voltage sensor
int analogInput = A0;
//float vout = 0.0;
//float vin = 0.0, volt;
float R1 = 30000.0; //  
float R2 = 7500.0; // 



//for smoothing
const int numReadings = 20;
float readings[numReadings];      // the readings from the analog input

char buff[5];
                 



void setup(){   
    pinMode(analogInput, INPUT);
    Serial.begin(9600);
    
    Serial.println("Type AT commands!");    
    mySerial.begin(9600);    
}



void loop() {

   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis > interval){//       Serial.println("Ticking every 2 seconds"); //2=interval
       previousMillis = currentMillis;

      float volt = readAvg();
      Serial.println(volt,1);
      sendData(volt);
   }
}//loop ends here







float readCorrectVoltage(){
  // read normal Arduino value
  int adcVal = analogRead(A0);
  
  // read correct supply voltage
  float supply = readVcc() / 1000.0;

  //test
//  float voltCorrected2 = (adcVal / 1023.0) * supply ;  //should be 1023 not 1024  //https://majenko.co.uk/blog/making-accurate-adc-readings-arduino


  float voltage = adcVal * 5.0 / 1024.0;  //AS's way
  float voltCorrected = supply / 5 * voltage;  //AS's way

  return voltCorrected*5;
}




long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Calculate Vcc (in mV); 1126400 = 1.1*1024*1000
  return result;
}






float readNominalVoltage(){
      
    int value = analogRead(analogInput);
    float vout = (value * 5.0) / 1024.0; // see text
    float vin = vout / (R2/(R1+R2)); 
       
//    Serial.print("INPUT V= ");
//    Serial.println(vin,2);
    return vin;    
}


float readAvg(){
  
  float total = 0.0;

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0.0;
  }

  for(int readIndex = 0; readIndex < numReadings; readIndex++){
    
    // subtract the last reading:
//    total = total - readings[readIndex];

    readings[readIndex] = readCorrectVoltage();
    total = total + readings[readIndex];//incremental total
    delay(1);
  }

  float averageV = total/numReadings;   // the average

  
  return averageV; 
  
}





float read_running_average(){
  
  int total = 0;

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  for(int readIndex = 0; readIndex < numReadings; readIndex++){
    
    // subtract the last reading:
//    total = total - readings[readIndex];

    readings[readIndex] = analogRead(analogInput);

//    Serial.println(readings[readIndex]);

    total = total + readings[readIndex];//incremental total
//    delay(2);
  }

  int average = total/numReadings;   // the average
  float vout = (average * 5.0) / 1024.0; // see text
  float vin = vout / (R2/(R1+R2));
  return vin; 
       
//    Serial.print("INPUT V= ");
//    Serial.println(vin,2);
}








void sendData(float volt){

        dtostrf(volt, 4 , 1 , buff);

        String data = "#"+String(buff)+"~";

//        Serial.println("High");
//        char msgBuff[50];
  //      sprintf(buff, "Aconcagua is %02.02f metres height.", volt);
//        sprintf(msgBuff,"%s",s); //converts and stores float to char array
//        Serial.println(String("")+"Voltage is "+volt+" Volt");
//        Serial.println(msgBuff);
//        delay(10);
        mySerial.print(data);
  
}
