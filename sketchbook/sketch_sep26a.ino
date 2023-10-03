//---JMU 2024 Childrens Prostetics---\\

// The goal of this code is to use the {sensors} to detect gait and pressure if there is a
// simultaneous reaction between both, then the system will detect if there needs to be an adjustment to the prostetic
// The code will not record the data if there is not enough movement, once there is enough movement
// the code will run, if there is a drastic increase in the average pressure value in each step taken, then there will be an alert

//Placeholder Values and imports that must be before the code
#include <Arduino_BMI270_BMM150.h>
#include <iostream>
#include <fstream>
#include <ctime> // Time Library

using namespace std;

float x, y, z; // X, Y, Z axis
const int N = 10; // The "Moving Average" Range
int mag[N]; // The "Magnitude of each data point"
int idx = 0; // Placeholder variable
int diff[N]; // The Difference between 2 magnitudes
int sqr[N]; // Magnifying each data point to detect the large movement
const int AVG_LEN = 80;
int avg[AVG_LEN];
int lower_bound = 3000; //Bounds to only allow readings of steps must be between this values
int upper_bound = 7000;

float sum = 0;
int steps = 0;
int pause = 0;

long timeAcquire = 0;
long timeProcess = 0;
long timeDecide = 0;
long algorithmDone = 0;

const int VOL_PIN_0 = A0;
const int VOL_PIN_1 = A1;
const int VOL_PIN_2 = A2;


// Pressure Sensor 0
int mag_p0[N]; // The "Magnitude of pressure sensor 0"
int idx_p0 = 0; // Placeholder variable
int diff_p0[N]; // The Difference between 2 magnitudes
int sqr_p0[N]; // Magnifying each data point to detect the large movement

/// Detect the step


/// Gyroscope
// Gyroscope set up
void setup() 
{

    Serial.begin(9600);
    while (!Serial);
    Serial.println("Started");

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println(" Hz");
    Serial.println();
    Serial.println("Gyroscope in degrees/second");
}

void loop()
{
    step_detect(); // Call function to detect steps
}


// Gyroscope Verification
void step_detect()
{
    int lower_bound = 3000; //Bounds to only allow readings of steps must be between this values
    int upper_bound = 7000;

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(x, y, z);
    }
    //Calculations to detect the major changes in the movement

    mag[idx % N] = sqrt((x * x) + (y * y) + (z * z)); // Calculates Magnitude
    diff[idx % N] = mag[idx % N] - mag[(idx - 1) % N]; // Calculates Difference
    sqr[idx % N] = diff[idx % N] * diff[idx % N]; // Calculates Difference


    ///"Smoothing out" calculations

    if (idx > 10) // Index based on moving average
    {
        double temp = 0; //temporary value,required to make the code more smooth


        for (int i = 0; i < 10; i++) // for loop to find the average
        {
            temp += sqr[(idx - N + i) % N];
        }
        avg[idx % AVG_LEN] = temp / N;
        //cout << "Average: " << avg[idx] ; // displays the average
    }


    //Creating bounds so that when you take a step it will read a step
    if ((avg[idx % AVG_LEN] >= lower_bound) && (avg[idx % AVG_LEN] <= upper_bound))
    {
        if (idx >= pause + 20) // pause when counting steps so that that when reading the data, it won't just crash
        {
            steps++; //add step
            pause = idx;
        }
    }

  Serial.print(mag[idx % N]);
  Serial.print(",");
  Serial.print(avg[idx%AVG_LEN]);
  Serial.print(",");
  Serial.print("total steps " );
  Serial.print(steps); //print back the magnitude for fun so we can see if the calculation was done correctly.


    ///Pressure Sensor

    int value_0;
    int value_1;
    int value_2;

    float volt_0;
    float volt_1;
    float volt_2;

    // Read analog output from pins w/ sensors
    value_0 = analogRead(VOL_PIN_0);
    value_1 = analogRead(VOL_PIN_1);
    value_2 = analogRead(VOL_PIN_2);

    // Convert analog reading to Voltage 0 - 3.3v
    volt_0 = (value_0 * (3.3 / 1023.0));
    volt_1 = (value_1 * (3.3 / 1023.0));
    volt_2 = (value_2 * (3.3 / 1023.0));

    // Apply calibration curve to voltage reading to get force in newtons
    float sensorZero = ((volt_0 / .1065) - 8.8) * 9.807;
    float sensorOne = ((volt_1 / .1065) - 8.8) * 9.807;
    float sensorTwo = ((volt_2 / .1065) - 8.8) * 9.807;

    //Calculations of Pressure Sensor 0

    mag_p0[idx_p0 % N] = sqrt((sensorZero * sensorZero)); // Calculates Magnitude
    diff_p0[idx_p0 % N] = mag[idx % N] - mag[(idx - 1) % N]; // Calculates Difference
    sqr_p0[idx_p0 % N] = diff[idx % N] * diff[idx % N]; // Calculates Difference


    ///"Smoothing out" calculations

    if (idx_p0 > 10) // Index based on moving average
    {
        double temp = 0; //temporary value,required to make the code more smooth


        for (int i = 0; i < 10; i++) // for loop to find the average
        {
            temp += sqr_p0[(idx_p0 - N + i) % N];
        }
        avg[idx_p0 % AVG_LEN] = temp / N;
        //cout << "Average: " << avg[idx] ; // displays the average
    }
  Serial.print( "  Sensor 0 Force (N): " );
  Serial.print( sensorZero );

  // Prints readings from sensor 1
  Serial.print( "  Sensor 1 Force (N): " );
  Serial.print( sensorOne );

  // Prints readings from sensor 2
  Serial.print( "  Sensor 2 Force (N): " );
  Serial.print( sensorTwo );

  Serial.print(",");
  Serial.print(mag_p0[idx_p0 % N]);
  Serial.print(",");
  Serial.print(avg_p0[idx_p0%AVG_LEN]);

    idx++;
}

 