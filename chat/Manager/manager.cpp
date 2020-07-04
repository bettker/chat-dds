#include <iostream>
#include <ChatData_DCPS.hpp>
#include <thread>
#include <chrono>
#include <time.h>

int main(int argc, char* argv[]) {
    std::string user = "usuario";

    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<ChatData::Message> topic(dp, "Aa");
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<ChatData::Message> dw(pub, topic);

    ChatData::Message msg(user, 1, "mensagem");

    for (unsigned int i = 0; i < 100; ++i) {
        dw.write(msg);
        std::cout << "user = " << msg.user() << ", mensagem = " << msg.content() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
