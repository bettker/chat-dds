#include "Chatter.h"

Chatter::Chatter(std::string _username, std::string room, int lang) {
    try {
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
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (Chatter constructor): " << e.what() << std::endl;
        exit(1);
    }
}

void Chatter::joinRoom(std::string room) {
    try {
        pubQos = dp.default_publisher_qos() << dds::core::policy::Partition(room);
        pub = dds::pub::Publisher(dp, pubQos);
        dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, topic_room, dwQos);
        dwSM = dds::pub::DataWriter<ChatDDS::SystemMessage>(pub, topic_sys, dwQos);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (joinRoom): " << e.what() << std::endl;
        exit(1);
    }
}

void Chatter::sendMessage(std::string message) {
    try {
        if (dwM.topic_description().name() != "RoomMsgTopic")
            dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, topic_room, dwQos);

        dwM << ChatDDS::Message(messagesSent++, username, getTime(), message);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (sendMessage): " << e.what() << std::endl;
        exit(1);
    }
}

void Chatter::sendPrivateMessage(std::string username, std::string message) {
    try {
        if (dwM.topic_description().name() != ("PrivateMsgTopic"))
            dwM = dds::pub::DataWriter<ChatDDS::Message>(pub, dds::topic::Topic<ChatDDS::Message>(dp, "PrivateMsgTopic", topicQos), dwQos);

        dwM << ChatDDS::Message(messagesSent++, username, getTime(), message);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (sendPrivateMessage): " << e.what() << std::endl;
        exit(1);
    }
}

ChatDDS::Time Chatter::getTime() {
    try {
        time_t t = time(NULL);
        struct tm* tm = gmtime(&t);
        return ChatDDS::Time((tm->tm_hour < 3 ? tm->tm_hour + 24 - 3 : tm->tm_hour - 3),
            tm->tm_min,
            tm->tm_sec);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (getTime): " << e.what() << std::endl;
        exit(1);
    }
}