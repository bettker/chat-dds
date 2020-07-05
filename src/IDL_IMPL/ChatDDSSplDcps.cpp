#include "ChatDDS_DCPS.hpp"

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ChatDDS_Message__copyIn(
    c_type dbType,
    const class ::ChatDDS::Message *from,
    struct _ChatDDS_Message *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->userID = (c_long)from->userID();
    to->userName = c_stringNew(c_getBase(dbType), from->userName_.c_str());
    to->message = c_stringNew(c_getBase(dbType), from->message_.c_str());
    return result;
}

void
__ChatDDS_Message__copyOut(
    const void *_from,
    void *_to)
{
    const struct _ChatDDS_Message *from = (const struct _ChatDDS_Message *)_from;
    class ::ChatDDS::Message *to = (class ::ChatDDS::Message *)_to;
    to->userID((int32_t)from->userID);
    to->userName(from->userName ? from->userName : "");
    to->message(from->message ? from->message : "");
}

