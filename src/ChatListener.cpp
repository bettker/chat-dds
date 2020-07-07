#include "ChatListener.h"

ChatListener::ChatListener(std::vector<std::string>* _messages)
{
    messages = _messages;
}

void ChatListener::on_data_available(dds::sub::DataReader<ChatDDS::Message>& reader)
{
    char time[10];
    try {
        dds::sub::LoanedSamples<ChatDDS::Message> samples = reader.take();

        if ((*samples.begin()).info().valid())
        {
            for (dds::sub::LoanedSamples<ChatDDS::Message>::const_iterator sample = samples.begin(); sample < samples.end(); ++sample)
            {
                if (sample->info().valid()) {
                    ChatDDS::Time t = sample->data().time();
                    snprintf(time, 10, "%02d:%02d:%02d", t.hour(), t.min(), t.sec());
                    std::string timeStr(time);

                    messages->push_back("[" + timeStr + "] " + sample->data().username() + ": " + sample->data().content());
                }
            }
        }
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (ChatListener Message): " << e.what() << std::endl;
        exit(1);
    }
}

void ChatListener::on_data_available(dds::sub::DataReader<ChatDDS::SystemMessage>& reader)
{
    char time[10];
    try {
        dds::sub::LoanedSamples<ChatDDS::SystemMessage> samples = reader.take();

        if ((*samples.begin()).info().valid())
        {
            for (dds::sub::LoanedSamples<ChatDDS::SystemMessage>::const_iterator sample = samples.begin(); sample < samples.end(); ++sample)
            {
                if (sample->info().valid()) {
                    if (sample->data().type() == ChatDDS::SystemMessageType::JOIN) {
                        messages->push_back(">> " + sample->data().username() + " entrou na sala");
                    }
                    else if (sample->data().type() == ChatDDS::SystemMessageType::QUIT) {
                        messages->push_back(">> " + sample->data().username() + " saiu da sala");
                    }
                }
            }
        }
    }
    catch (const dds::core::Exception& e) {
        std::cout << "Error (ChatListener SystemMessage): " << e.what() << std::endl;
        exit(1);
    }
}
