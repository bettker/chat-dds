#include <iostream>
#include <ExampleData_DCPS.hpp>
#include <thread>
#include <chrono>
#include <time.h>

int main(int argc, char* argv[]) {
    int sid = 18;
    const int N = 100;

    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<ExampleData::TempSensorType> topic(dp, "TTempSensor");
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<ExampleData::TempSensorType> dw(pub, topic);

    const float avgT = 25;
    const float avgH = 0.6;
    const float deltaT = 5;
    const float deltaH = 0.15;
    // Initialize random number generation with a seed
    srand(time(NULL));

    // Write some temperature randomly changing around a set point
    float temp = avgT + ((rand() * deltaT) / RAND_MAX);
    float hum = avgH + ((rand() * deltaH) / RAND_MAX);

    ExampleData::TempSensorType sensor(sid, temp, hum, ExampleData::TemperatureScale::CELSIUS);

    for (unsigned int i = 0; i < N; ++i) {
        dw.write(sensor);
        std::cout << "(id = " << sensor.id()
            << ", temp = " << sensor.temp()
            << ", hum = " << sensor.hum()
            << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp = avgT + ((rand() * deltaT) / RAND_MAX);
        sensor.temp(temp);
        hum = avgH + ((rand() * deltaH) / RAND_MAX);
        sensor.hum(hum);
    }
    return 0;
}
