// Will Bradford with help from YouTube.com/Robojax

// Set the correction offset value, change as needed
  int offset = 20;
  
  void setup() {

  // Open the serial port
  serial.begin(9600)

}

void loop() {
  
  // Read analog pin A0
  int volt = analogread(A0);

  // Map 0-1023 to 0-2500 mV and add correction offset
  double voltage = map(volt, 0, 1023, 0, 2500) + offset;

  //Divide by 100 to get decimal values
  voltage /= 100;

  //Print the voltage
  serial.print("Voltage: ")
  serial.print(voltage);

}
