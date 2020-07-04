#include <iostream>
#include <algorithm>
#include <ExampleData_DCPS.hpp>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<ExampleData::TempSensorType> topic(dp, "TTempSensor");
    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<ExampleData::TempSensorType> dr(sub, topic);

    while (true) {
        auto samples = dr.read();
        std::for_each(samples.begin(),
            samples.end(),
            [](const dds::sub::Sample<ExampleData::TempSensorType>& s) {
                std::cout << "(id = " << s.data().id()
                    << ", temp = " << s.data().temp()
                    << ", hum = " << s.data().hum()
                    << ")" << std::endl;
            });
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
