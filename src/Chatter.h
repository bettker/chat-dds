#include <iostream>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

class Chatter {
private:
    std::string username;

    dds::domain::DomainParticipant dp = dds::core::null;
    
     dds::topic::qos::TopicQos topicQos;
     dds::topic::Topic<ChatDDS::Message> topicRoom = dds::core::null;
     dds::topic::Topic<ChatDDS::SystemMessage> topicSys = dds::core::null;

     dds::pub::qos::PublisherQos pubQos;
     dds::pub::Publisher pub = dds::core::null;

     dds::pub::qos::DataWriterQos dwQos;
     dds::pub::DataWriter<ChatDDS::Message> dwM = dds::core::null;
     dds::pub::DataWriter<ChatDDS::SystemMessage> dwSM = dds::core::null;

public:
    Chatter(std::string _username, std::string room, int lang);

    void quitRoom();

    void sendMessage(std::string message);

private:
    ChatDDS::Time getTime();
};
