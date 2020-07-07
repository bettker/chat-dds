#include "MessageBoard.h"

MessageBoard::MessageBoard(std::string _username, std::string room, int lang) {
    username = _username;
    filter_expression = "";

    try {
        dp = dds::domain::DomainParticipant(lang);

        topicQos = dp.default_topic_qos()
            << dds::core::policy::Durability::TransientLocal()
            << dds::core::policy::Reliability::Reliable()
            << dds::core::policy::Deadline(dds::core::Duration(1, 0));

        topic_room = dds::topic::Topic<ChatDDS::Message>(dp, "RoomMsgTopic", topicQos);
        topic_sys = dds::topic::Topic<ChatDDS::SystemMessage>(dp, "SystemMsgTopic", topicQos);

        mask << dds::core::status::StatusMask::data_available();
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (MessageBoard constructor): " << e.what() << std::endl;
        exit(1);
    }
}

std::vector<std::string> MessageBoard::GetNewMessages() {
    std::vector<std::string> m;
    for (int i = 0; i < newMessages.size(); i++)
        m.push_back(newMessages[i]);
    newMessages.clear();
    return m;
}

void MessageBoard::joinRoom(std::string room) {
    try {
        subQos = dp.default_subscriber_qos() << dds::core::policy::Partition(room);
        sub = dds::sub::Subscriber(dp, subQos);
        drM = dds::sub::DataReader<ChatDDS::Message>(sub, topic_room, drQos, &listener, mask);
        drSM = dds::sub::DataReader<ChatDDS::SystemMessage>(sub, topic_sys, drQos, &listener, mask);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (joinRoom): " << e.what() << std::endl;
        exit(1);
    }
}

void MessageBoard::ignoreUser(std::string _username) {
    try {
        if (ignoredUsers.size() == 0) {
            filter_expression = "(username = \%0)";
        }
        else {
            filter_expression += " AND (username <> \%" + std::to_string(ignoredUsers.size()) + ")";
        }

        ignoredUsers.push_back(_username);

        std::cout << "Filtro: " << filter_expression << std::endl;
        for (int i = 0; i < ignoredUsers.size(); i++) {
            std::cout << '"' << ignoredUsers[i] << "\" ";
        }
        std::cout << std::endl;

        dds::topic::Filter filter(filter_expression, ignoredUsers);
        dds::topic::ContentFilteredTopic<ChatDDS::Message> cfTopic(topic_room, "RoomMsgTopic", filter);

        drM = dds::sub::DataReader<ChatDDS::Message>(sub, cfTopic, drQos, &listener, mask);

        writeMessage(">> Voce nao recebera mais mensagens de " + _username);
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (ignoreUser): " << e.what() << std::endl;
        exit(1);
    }
}

void MessageBoard::writeMessage(std::string msg) {
    newMessages.push_back(msg);
}