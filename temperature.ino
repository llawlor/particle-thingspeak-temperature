// This #include statement was automatically added by the Particle IDE.
#include "ThingSpeak/ThingSpeak.h"

// variables to store the temperature values
double temperature_c = 0.0;
double temperature_f = 0.0;

// set up the tcp client
TCPClient client;

// thingspeak channel and write key
unsigned long myChannelNumber = 77720;
const char * myWriteAPIKey = "K7Q41NE7LK2JVFO2";

void setup()
{
  // set A5 as an input
  pinMode(A5, INPUT);
  
  // start the thingspeak client
  ThingSpeak.begin(client);
}

void loop()
{
  // read the value from pin A5
  int analogValue = analogRead(A5);
  
  // calculate the voltage
  double voltage = 3.3 * ((double)analogValue / 4095.0);

  // calculate the temperature in celsius
  temperature_c = (voltage - 0.5) * 100;
  
  // calculate the temperature in fahrenheit
  temperature_f = (temperature_c * 9 / 5) + 32;
  
  // create the output string
  String data = String("temperature_f=" + String(temperature_f));

  // publish the data
  Particle.publish("mydata", data);
  
  // send the data to thingspeak
  ThingSpeak.writeField(myChannelNumber, 1, String(temperature_f), myWriteAPIKey);
  
  // wait 60 seconds before looping again
  delay(60000);
}


