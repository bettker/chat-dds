#include "MessageBoard.h"

MessageBoard::MessageBoard(std::string _username, std::string room, int lang) {
    username = _username;

    dp = dds::domain::DomainParticipant(lang);

    topicQos = dp.default_topic_qos()
            << dds::core::policy::Durability::TransientLocal()
            << dds::core::policy::Reliability::Reliable()
            << dds::core::policy::Deadline(dds::core::Duration(1, 0));

    topic_room = dds::topic::Topic<ChatDDS::Message>(dp, "RoomMsgTopic", topicQos);
    topic_sys = dds::topic::Topic<ChatDDS::SystemMessage>(dp, "SystemMsgTopic", topicQos);

    subQos = dp.default_subscriber_qos() << dds::core::policy::Partition(room);
    sub = dds::sub::Subscriber(dp, subQos);

    dds::core::status::StatusMask mask;
    mask << dds::core::status::StatusMask::data_available();
    drM = dds::sub::DataReader<ChatDDS::Message>(sub, topic_room, drQos, &listener, mask);
}

std::vector<std::string> MessageBoard::GetNewMessages() {
    std::vector<std::string> m;
    for (int i = 0; i < newMessages.size(); i++)
        m.push_back(newMessages[i]);
    newMessages.clear();
    return m;
}

void MessageBoard::ignoreUser(std::string user) {
    std::cout << "Ignorou o usuario " << user << std::endl;
    ignoredUsers.push_back(user);
}

void MessageBoard::writeMessage(std::string msg) {
    newMessages.push_back(msg);
}