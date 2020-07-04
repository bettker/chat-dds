#ifndef ISOCPP2_ChatData_H
#define ISOCPP2_ChatData_H

#include "dds/dds.hpp"

#include "ChatData.h"
#include "ChatDataSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<ChatData::Message>
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
        return "user";
    }

    static const char *getTypeName()
    {
        return "ChatData::Message";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"ChatData\"><Struct name=\"Message\"><Member name=\"user\">",
"<String/></Member><Member name=\"time\"><ULong/></Member><Member name=\"content\"><String/></Member></Struct>",
"</Module></MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(230);
        for (int i = 0; i < 3; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __ChatData_Message__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __ChatData_Message__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<ChatData::Message>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<ChatData::Message>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(ChatData::Message)

#endif /* ISOCPP2_ChatData_H */
