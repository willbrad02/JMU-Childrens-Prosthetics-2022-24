/* 
  Will Bradford
  Arduino Nano code to read and output voltage values from pressure sensors
*/

// Set the correction offset value, change as needed
int offset = 20;

// Name analog pins. Add/remove variables based on nunmber of used analog pins
char analog0 = A0;
char analog1 = A1;
char analog2 = A2;
char analog3 = A3;

void read_and_print_voltage(int volt, char pin_num) {

  // Map 0-1023 to 0-2500 mV and add correction offset
  double voltage = map(volt, 0, 1023, 0, 2500) + offset;

  // Divide by 100 to get decimal values
  voltage /= 100;

  // Turn voltage into a string
  char v_buffer[10];
  dtostrf(voltage, 1, 2, v_buffer);

  // Creating a buffer variable with more than enough characters, then printing the voltage
  char buffer[50];
  sprintf(buffer, "Pin %s voltage : %s V", pin_num, v_buffer);
  serial.printf(buffer);

}
  
  void setup() {

  // Open the serial port
  serial.begin(9600)

}

void loop() {
  
  // Read analog pins A0-A3. Add/remove variables based on nunmber of used analog pins
  int volt0 = analogRead(A0);
  int volt1 = analogRead(A1);
  int volt2 = analogRead(A2);
  int volt3 = analogRead(A3);

  // Read and print voltage values for each specified analog pin. Add/remove function calls based on nunmber of used analog pins
  read_and_print_voltage(volt0, analog0);
  read_and_print_voltage(volt1, analog1);
  read_and_print_voltage(volt2, analog2);
  read_and_print_voltage(volt3, analog3);

  // Time in between measuremnts (milliseconds)
  delay(500);

}
