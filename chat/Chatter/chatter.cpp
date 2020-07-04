#include <iostream>
#include <algorithm>
#include <ChatData_DCPS.hpp>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<ChatData::Message> topic(dp, "Aa");
    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<ChatData::Message> dr(sub, topic);

    while (true) {
        auto samples = dr.read();
        std::for_each(samples.begin(),
            samples.end(),
            [](const dds::sub::Sample<ChatData::Message>& s) {
                std::cout << "user = " << s.data().user() << ", mensagem = " << s.data().content() << std::endl;
            });
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
