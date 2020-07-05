#ifndef ISOCPP2_ChatDDS_H
#define ISOCPP2_ChatDDS_H

#include "dds/dds.hpp"

#include "ChatDDS.h"
#include "ChatDDSSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<ChatDDS::Message>
{
public:
    static ::org::opensplice::topic::DataRepresentationId_t getDataRepresentationId()
    {
        return ::org::opensplice::topic::OSPL_REPRESENTATION;
    }

    static ::std::vector<os_uchar> getMetaData()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getTypeHash()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getExtentions()
    {
        return ::std::vector<os_uchar>();
    }

    static const char *getKeyList()
    {
        return "userID";
    }

    static const char *getTypeName()
    {
        return "ChatDDS::Message";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"ChatDDS\"><Struct name=\"Message\"><Member name=\"userID\">",
"<Long/></Member><Member name=\"userName\"><String/></Member><Member name=\"message\"><String/></Member>",
"</Struct></Module></MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(234);
        for (int i = 0; i < 3; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __ChatDDS_Message__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __ChatDDS_Message__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<ChatDDS::Message>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<ChatDDS::Message>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(ChatDDS::Message)

#endif /* ISOCPP2_ChatDDS_H */
