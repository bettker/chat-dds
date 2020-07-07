#include <iostream>
#include <string>
#include <vector>

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

#include "ChatListener.h"

class MessageBoard {
private:
    std::string username;
    std::vector<std::string> newMessages;

    std::string ignoredFilter;

    ChatListener listener = ChatListener(&newMessages);

    dds::domain::DomainParticipant dp = dds::core::null;
    
    dds::topic::qos::TopicQos topicQos;
    dds::topic::Topic<ChatDDS::Message> topic_room = dds::core::null;
    dds::topic::Topic<ChatDDS::SystemMessage> topic_sys = dds::core::null;

    //dds::topic::Filter filter = dds::topic::Filter("(username = '10')");
    //dds::topic::ContentFilteredTopic<ChatDDS::Message> cfTopic = dds::core::null;

    dds::sub::qos::SubscriberQos subQos;
    dds::sub::Subscriber sub = dds::core::null;

    dds::core::status::StatusMask mask;

    dds::sub::qos::DataReaderQos drQos;
    dds::sub::DataReader<ChatDDS::Message> drM = dds::core::null;
    dds::sub::DataReader<ChatDDS::SystemMessage> drSM = dds::core::null;

public:
    MessageBoard(std::string _username, std::string room, int lang);

    std::vector<std::string> GetNewMessages();

    void joinRoom(std::string room);

    void ignoreUser(std::string user);

    void writeMessage(std::string msg);
};
