/* 
  Will Bradford
  Children's Prosthetics 2022-24
  Read and output weight values from pressure sensors
  Last edited 04/04/23
*/


// Name sensors that are being used. Add or comment/uncomment variables based on number of used sensors
char sensor1[] = "Sensor 1";
//char sensor2[] = "Sensor 2";
//char sensor3[] = "Sensor 3";
//char sensor4[] = "Sensor 4";
// char sensor5[] = "Sensor 5";

// Define variable for sensor data and V_out
int sensorData = 0;
float vout;


float measureWeight(char* sensorNum, int pinNum) {

  // Read voltage value from pin
  sensorData = analogRead(pinNum);
  
  // Calculate voltage
  vout = (sensorData * 3.3) / 1023.0;

  // Print weight to serial monitor
  Serial.print(sensorNum);
  Serial.print(" reads: ");
  Serial.print(vout, 3);
  Serial.println(" V");

  return vout;

}
  

  void setup() {

  // Open the serial port with baud rate (bits/sec), set pins to input (add or comment/uncomment pins as needed)
  Serial.begin(9600);
  pinMode(A0, INPUT);
  //pinMode(A1, INPUT);
  //pinMode(A2, INPUT);
  //pinMode(A3, INPUT);
  // pinMode(A4, INPUT);

}

void loop() {
  //Start program
   while (Serial.available()>0)
   {
      // Temporarily store weight readings from each sensor
      // Add or comment/uncomment function calls based on number of sensors
      float weight1 = measureWeight(sensor1, A0);
      //float weight2 = measureWeight(sensor2, A1);
      //float weight3 = measureWeight(sensor3, A2);
      //float weight4 = measureWeight(sensor4, A3);
      //float weight5 = measureWeight(sensor5, A4);

      //Delay between readings (ms)
      delay(1000);
   }
}
