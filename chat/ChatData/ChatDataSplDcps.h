#ifndef ChatDataSPLDCPS_H
#define ChatDataSPLDCPS_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ChatData.h"
#include "C:\SIMAF\OpenSplice\HDE\x86_64.win64\examples/include/examples_export.h"

extern c_metaObject __ChatData_ChatData__load (c_base base);

extern const char *ChatData_Message_metaDescriptor[];
extern const c_ulong ChatData_Message_metaDescriptorArrLength;
extern const c_ulong ChatData_Message_metaDescriptorLength;
extern c_metaObject __ChatData_Message__load (c_base base);
struct _ChatData_Message ;
extern OS_EXAMPLE_API v_copyin_result __ChatData_Message__copyIn(c_type dbType, const class ChatData::Message *from, struct _ChatData_Message *to);
extern OS_EXAMPLE_API void __ChatData_Message__copyOut(const void *_from, void *_to);
struct _ChatData_Message {
    c_string user;
    c_ulong time;
    c_string content;
};

#undef OS_API
#endif
