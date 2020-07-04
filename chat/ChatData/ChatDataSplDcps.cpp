#include "ChatData_DCPS.hpp"

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ChatData_Message__copyIn(
    c_type dbType,
    const class ::ChatData::Message *from,
    struct _ChatData_Message *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->user = c_stringNew(c_getBase(dbType), from->user_.c_str());
    to->time = (c_ulong)from->time();
    to->content = c_stringNew(c_getBase(dbType), from->content_.c_str());
    return result;
}

void
__ChatData_Message__copyOut(
    const void *_from,
    void *_to)
{
    const struct _ChatData_Message *from = (const struct _ChatData_Message *)_from;
    class ::ChatData::Message *to = (class ::ChatData::Message *)_to;
    to->user(from->user ? from->user : "");
    to->time((uint32_t)from->time);
    to->content(from->content ? from->content : "");
}

