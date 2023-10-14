#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace std;

class Signs {
public:
    double temperature;
    int heartRate;
    int bloodPressure;
    int sugar_levels;

    Signs(double temp, int hr, int bp, int sugar)
        : temperature(temp), heartRate(hr), bloodPressure(bp), sugar_levels(sugar) {}
};

class Patient {
public:
    string name;
    int age;
    Signs vitals;

    Patient(const string& n, int a, double temp, int hr, int bp, int sugar)
        : name(n), age(a), vitals(temp, hr, bp, sugar) {}

    void show() {
        cout << "Admitted patient name is " << name << endl;
        cout << "Patient age is " << age << " years" << endl;
        cout << "Temperature: " << vitals.temperature << " °F" << endl;
        cout << "Heart Rate: " << vitals.heartRate << " bpm" << endl;
        cout << "Blood Pressure: " << vitals.bloodPressure << " mmHg" << endl;
        cout << "Sugar Levels: " << vitals.sugar_levels << " mg/dL" << endl;
    }

    // Add methods to update and retrieve patient data.
};

class HealthcareSystem {
public:
    vector<Patient> patients;

    // Add methods for patient management, data analysis, and alerts.

    // Function to monitor heart rate
    void monitorHeartRate() {
        // Define the range for heart rate (adjust as needed)
        int minHeartRate = 60;
        int maxHeartRate = 120; // Increased max rate to detect abnormal values

        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        while (true) {
            // Generate a random heart rate within the specified range
            int heartRate = minHeartRate + (std::rand() % (maxHeartRate - minHeartRate + 1));

            // Print the heart rate to the console
            cout << "Heart Rate: " << heartRate << " bpm" << endl;

            // Check for abnormal heart rate
            if (heartRate > 100) {
                // If the heart rate is abnormal, call the family
                callFamily(patients[0].name); // Assuming the first patient's name is used
            }

            // Sleep for a short interval (simulating real-time monitoring)
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // Function to call family members
    void callFamily(const std::string& familyMember) {
        cout << "Calling family member: " << familyMember << endl;
        // You can implement calling functionality here (e.g., using a library or API).
    }
};

int main() {
    HealthcareSystem system;

    // Add patient data to the system.
    system.patients.push_back(Patient("John Doe", 70, 98.6, 80, 120, 90));
    system.patients.push_back(Patient("Jane Smith", 75, 98.0, 70, 130, 95));

    // Start monitoring heart rate in a separate thread
    std::thread heartRateMonitor(&HealthcareSystem::monitorHeartRate, &system);

    // Allow the program to run for a while
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop monitoring (you can add your own termination condition)
    heartRateMonitor.join();

    return 0;
}
