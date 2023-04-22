const int VOL_PIN_0 = A0;
const int VOL_PIN_1 = A1;
const int VOL_PIN_2 = A2;

void setup(){
    Serial.begin( 9600 );
}

void loop(){
    int value_0;
    int value_1;
    int value_2;

    float volt_0;
    float volt_1;
    float volt_2;

    // Read analog output from pins w/ sensors
    value_0 = analogRead( VOL_PIN_0 );
    value_1 = analogRead( VOL_PIN_1 );
    value_2 = analogRead( VOL_PIN_2 );

    // Convert analog reading to Voltage 0 - 3.3v
    volt_0 = (value_0 * (3.3 / 1023.0)) ;
    volt_1 = (value_1 * (3.3 / 1023.0)) ;
    volt_2 = (value_2 * (3.3 / 1023.0)) ;

    // Apply calibration curve to voltage reading to get force in newtons
    float sensorZero = ((volt_0 / .1065) - 8.8) * 9.807; 
    float sensorOne = ((volt_1 / .1065) - 8.8) * 9.807; 
    float sensorTwo = ((volt_2 / .1065) - 8.8) * 9.807; 

    // Prints readings from sensor 0
    Serial.print( "  Sensor 0 Force (N): " );
    Serial.print( sensorZero );

    // Prints readings from sensor 1
    Serial.print( "  Sensor 1 Force (N): " );
    Serial.print( sensorOne );

    // Prints readings from sensor 2
    Serial.print( "  Sensor 2 Force (N): " );
    Serial.println( sensorTwo );


    delay( 2000 );
}