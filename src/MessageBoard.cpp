#include "MessageBoard.h"

MessageBoard::MessageBoard(std::string _username, std::string room, int lang) {
    username = _username;
    listener = new ChatListener(username, &newMessages);

    try {
        dp = dds::domain::DomainParticipant(lang);

        topicQos = dp.default_topic_qos()
            << dds::core::policy::Durability::TransientLocal()
            << dds::core::policy::Reliability::Reliable()
            << dds::core::policy::Deadline(dds::core::Duration(1, 0));

        topicRoom = dds::topic::Topic<ChatDDS::Message>(dp, "RoomMsgTopic", topicQos);
        topicSys = dds::topic::Topic<ChatDDS::SystemMessage>(dp, "SystemMsgTopic", topicQos);

        expressionIgnore = "(username <> 'Visitante')";
        dds::topic::Filter filterM(expressionIgnore);
        cfTopicRoom = dds::topic::ContentFilteredTopic<ChatDDS::Message>(topicRoom, "RoomMsgTopic", filterM);

        subQos = dp.default_subscriber_qos() << dds::core::policy::Partition(room);
        sub = dds::sub::Subscriber(dp, subQos);

        mask << dds::core::status::StatusMask::data_available();
        drM = dds::sub::DataReader<ChatDDS::Message>(sub, cfTopicRoom, drQos, listener, mask);
        drSM = dds::sub::DataReader<ChatDDS::SystemMessage>(sub, topicSys, drQos, listener, mask);

        writeMessage(">> Voce entrou na sala " + room);
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

void MessageBoard::writeMessage(std::string msg) {
    newMessages.push_back(msg);
}
