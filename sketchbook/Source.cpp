//---JMU 2024 Childrens Prostetics---\\

// The goal of this code is to use the {sensors} to detect gait and pressure if there is a
// simultaneous reaction between both, then the system will detect if there needs to be an adjustment to the prostetic
// The code will not record the data if there is not enough movement, once there is enough movement
// the code will run, if there is a drastic increase in the average pressure value in each step taken, then there will be an alert

//Placeholder Values and imports that must be before the code
#include <Arduino_BMI270_BMM150.h>

float x, y, z; // X, Y, Z axis
const int N = 10; // The "Moving Average" Range
int mag[N]; // The "Magnitude of each data point"
int idx = 0; // Placeholder variable
int diff[N]; // The Difference between 2 magnitudes
int sqr[N]; // Magnifying each data point to detect the large movement
const int AVG_LEN = 80;
int avg[AVG_LEN];
const float gait_requirement = 1.2; //Dependant on sensitivity of the gait sensor, adjust the values to match

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


// Detect the step
// The code will not keep recording the values if there is no enough change in the gait


// Gyroscope
// Gyroscope set up
void setup() {
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

// Gyroscope Verification
void loop()
{

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(x, y, z);
    }
    ///Calculations to detect the major changes in the movement
    
    mag[idx % N] = sqrt((x * x) + (y * y) + (z * z)); // Calculates Magnitude
    diff[idx % N] = mag[idx % N] - mag[(idx - 1) % N]; // Calculates Difference
    sqr[idx % N] = diff[idx % N] * diff[idx % N]; // Calculates Difference
    //Serial.println(sqr[idx % N]); //Check the Square Root Value
    //delay(500);

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

    // Verify if the gait is now larger than the minimum requirements
    if (avg[idx % AVG_LEN] >= gait_requirement) 
    {
        // Perform peak detection on live data
        if (isPeakDetected(avg[idx % AVG_LEN]))
        {
            steps++; // Add step
            pause = idx;
        }
    }

    idx++;
}


// Step Detection Function
bool isPeakDetected(float value) {
    // Check if the value is larger than its neighbors
    if (idx > 1 && value > mag[(idx - 1) % N] && value > mag[(idx - 2) % N]) {
        return true;
    }
    return false;
}