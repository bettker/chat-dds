#include "ChatDDS_DCPS.hpp"

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ChatDDS_Time__copyIn(
    c_type dbType,
    const class ::ChatDDS::Time *from,
    struct _ChatDDS_Time *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->hour = (c_ushort)from->hour();
    to->min = (c_ushort)from->min();
    to->sec = (c_ushort)from->sec();
    return result;
}

v_copyin_result
__ChatDDS_Message__copyIn(
    c_type dbType,
    const class ::ChatDDS::Message *from,
    struct _ChatDDS_Message *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->username = c_stringNew(c_getBase(dbType), from->username_.c_str());
    if(V_COPYIN_RESULT_IS_OK(result)){
        extern v_copyin_result __ChatDDS_Time__copyIn(c_type, const ChatDDS::Time *, _ChatDDS_Time *);
        result = __ChatDDS_Time__copyIn(c_memberType(c_structureMember(dbType, 1)), &from->time(), &to->time);
    }
    to->content = c_stringNew(c_getBase(dbType), from->content_.c_str());
    return result;
}

v_copyin_result
__ChatDDS_SystemMessage__copyIn(
    c_type dbType,
    const class ::ChatDDS::SystemMessage *from,
    struct _ChatDDS_SystemMessage *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->username = c_stringNew(c_getBase(dbType), from->username_.c_str());
    if((((c_long)from->type()) >= 0) && (((c_long)from->type()) < 2) ){
        to->type = (enum _ChatDDS_SystemMessageType)from->type();
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'ChatDDS::SystemMessage.type' of type 'SystemMessageType' is out of range.");
        result = V_COPYIN_RESULT_INVALID;
    }
    return result;
}

void
__ChatDDS_Time__copyOut(
    const void *_from,
    void *_to)
{
    const struct _ChatDDS_Time *from = (const struct _ChatDDS_Time *)_from;
    class ::ChatDDS::Time *to = (class ::ChatDDS::Time *)_to;
    to->hour((uint16_t)from->hour);
    to->min((uint16_t)from->min);
    to->sec((uint16_t)from->sec);
}

void
__ChatDDS_Message__copyOut(
    const void *_from,
    void *_to)
{
    const struct _ChatDDS_Message *from = (const struct _ChatDDS_Message *)_from;
    class ::ChatDDS::Message *to = (class ::ChatDDS::Message *)_to;
    to->username(from->username ? from->username : "");
    {
        extern void __ChatDDS_Time__copyOut(const void *, void *);
        ChatDDS::Time &tmp = to->time();
        __ChatDDS_Time__copyOut((const void *)&from->time, &tmp);
    }
    to->content(from->content ? from->content : "");
}

void
__ChatDDS_SystemMessage__copyOut(
    const void *_from,
    void *_to)
{
    const struct _ChatDDS_SystemMessage *from = (const struct _ChatDDS_SystemMessage *)_from;
    class ::ChatDDS::SystemMessage *to = (class ::ChatDDS::SystemMessage *)_to;
    to->username(from->username ? from->username : "");
    to->type((ChatDDS::SystemMessageType)from->type);
}

