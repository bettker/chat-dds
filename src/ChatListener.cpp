#include "ChatListener.h"

ChatListener::ChatListener(std::vector<std::string>* _messages)
{
    messages = _messages;
}

void ChatListener::on_data_available(dds::sub::DataReader<ChatDDS::Message>& reader)
{
    dds::sub::LoanedSamples<ChatDDS::Message> samples = reader.take();

    if((*samples.begin()).info().valid())
    {
        for(dds::sub::LoanedSamples<ChatDDS::Message>::const_iterator sample = samples.begin();  sample < samples.end(); ++sample)
        {
            messages->push_back("[" + sample->data().time() + "] " + sample->data().username() + ": " + sample->data().content());
        }
    }
}
