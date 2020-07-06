#include <iostream>
#include <string>

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

class Chatter {
private:
    std::string username;
    int messagesSent;

    dds::domain::DomainParticipant dp = dds::core::null;
    
     dds::topic::qos::TopicQos topicQos;
     dds::topic::Topic<ChatDDS::Message> topic_room = dds::core::null;
     dds::topic::Topic<ChatDDS::SystemMessage> topic_sys = dds::core::null;

     dds::pub::qos::PublisherQos pubQos;
     dds::pub::Publisher pub = dds::core::null;

     dds::pub::qos::DataWriterQos dwQos;
     dds::pub::DataWriter<ChatDDS::Message> dwM = dds::core::null;
     dds::pub::DataWriter<ChatDDS::SystemMessage> dwSM = dds::core::null;

public:
    Chatter(std::string _username, std::string room, int lang) {
        username = _username;
        messagesSent = 0;

        dp = dds::domain::DomainParticipant(lang);

        topicQos = dp.default_topic_qos()
                << dds::core::policy::Durability::TransientLocal()
                << dds::core::policy::Reliability::Reliable()
                << dds::core::policy::Deadline(dds::core::Duration(1, 0));

        topic_room = dds::topic::Topic<ChatDDS::Message>(dp, "RoomMsgTopic", topicQos);
        topic_sys = dds::topic::Topic<ChatDDS::SystemMessage>(dp, "SystemMsgTopic", topicQos);

        pubQos = dp.default_publisher_qos() << dds::core::policy::Partition(room);
        pub = dds::pub::Publisher(dp, pubQos);

        dwQos = topicQos;
        dwQos << dds::core::policy::WriterDataLifecycle::ManuallyDisposeUnregisteredInstances();
        dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, topic_room, dwQos);
        dwSM = dds::pub::DataWriter<ChatDDS::SystemMessage>(pub, topic_sys, dwQos);

        dds::topic::TopicDescription td = dwM.topic_description();
        std::cout << dwM.topic_description().name() << std::endl;
    }

    void joinRoom(std::string room) {
        pubQos = dp.default_publisher_qos() << dds::core::policy::Partition(room);
        pub = dds::pub::Publisher(dp, pubQos);
    }

    void sendMessage(std::string message) {
        if (dwM.topic_description().name() != "RoomMsgTopic")
            dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, topic_room, dwQos);

        dwM << ChatDDS::Message(messagesSent++, username, "00:00", message);
    }

    void privateMessage(std::string username, std::string message) {
        if (dwM.topic_description().name() != (username + "_PrivateMsgTopic"))
            dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, dds::topic::Topic<ChatDDS::Message>(dp, username + "_PrivateMsgTopic", topicQos), dwQos);

        dwM << ChatDDS::Message(messagesSent++, username, "00:00", message);
    }
};
