#include <iostream>
#include <string>
#include <vector>

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

#include "ChatListener.h"

class MessageBoard {
private:
    std::string username;
    std::vector<std::string> newMessages;

    std::string expressionIgnore;

    ChatListener* listener;

    dds::domain::DomainParticipant dp = dds::core::null;
    
    dds::topic::qos::TopicQos topicQos;
    dds::topic::Topic<ChatDDS::Message> topicRoom = dds::core::null;
    dds::topic::Topic<ChatDDS::SystemMessage> topicSys = dds::core::null;

    dds::topic::ContentFilteredTopic<ChatDDS::Message> cfTopicRoom = cfTopicRoom;

    dds::sub::qos::SubscriberQos subQos;
    dds::sub::Subscriber sub = dds::core::null;

    dds::core::status::StatusMask mask;

    dds::sub::qos::DataReaderQos drQos;
    dds::sub::DataReader<ChatDDS::Message> drM = dds::core::null;
    dds::sub::DataReader<ChatDDS::SystemMessage> drSM = dds::core::null;

public:
    MessageBoard(std::string _username, std::string room, int lang);

    std::vector<std::string> GetNewMessages();

    void writeMessage(std::string msg);
};
