#ifndef ChatDDSSPLDCPS_H
#define ChatDDSSPLDCPS_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ChatDDS.h"


extern c_metaObject __ChatDDS_ChatDDS__load (c_base base);

extern const char *ChatDDS_Message_metaDescriptor[];
extern const c_ulong ChatDDS_Message_metaDescriptorArrLength;
extern const c_ulong ChatDDS_Message_metaDescriptorLength;
extern c_metaObject __ChatDDS_Message__load (c_base base);
struct _ChatDDS_Message ;
extern  v_copyin_result __ChatDDS_Message__copyIn(c_type dbType, const class ChatDDS::Message *from, struct _ChatDDS_Message *to);
extern  void __ChatDDS_Message__copyOut(const void *_from, void *_to);
struct _ChatDDS_Message {
    c_long userID;
    c_string userName;
    c_string message;
};

#undef OS_API
#endif
