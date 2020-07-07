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

extern const char *ChatDDS_Time_metaDescriptor[];
extern const c_ulong ChatDDS_Time_metaDescriptorArrLength;
extern const c_ulong ChatDDS_Time_metaDescriptorLength;
extern c_metaObject __ChatDDS_Time__load (c_base base);
struct _ChatDDS_Time ;
extern  v_copyin_result __ChatDDS_Time__copyIn(c_type dbType, const class ChatDDS::Time *from, struct _ChatDDS_Time *to);
extern  void __ChatDDS_Time__copyOut(const void *_from, void *_to);
struct _ChatDDS_Time {
    c_ushort hour;
    c_ushort min;
    c_ushort sec;
};

extern const char *ChatDDS_Message_metaDescriptor[];
extern const c_ulong ChatDDS_Message_metaDescriptorArrLength;
extern const c_ulong ChatDDS_Message_metaDescriptorLength;
extern c_metaObject __ChatDDS_Message__load (c_base base);
struct _ChatDDS_Message ;
extern  v_copyin_result __ChatDDS_Message__copyIn(c_type dbType, const class ChatDDS::Message *from, struct _ChatDDS_Message *to);
extern  void __ChatDDS_Message__copyOut(const void *_from, void *_to);
struct _ChatDDS_Message {
    c_ushort id;
    c_string username;
    struct _ChatDDS_Time time;
    c_string content;
};

extern c_metaObject __ChatDDS_SystemMessageType__load (c_base base);
enum _ChatDDS_SystemMessageType {
    _ChatDDS_JOIN,
    _ChatDDS_QUIT
};

extern const char *ChatDDS_SystemMessage_metaDescriptor[];
extern const c_ulong ChatDDS_SystemMessage_metaDescriptorArrLength;
extern const c_ulong ChatDDS_SystemMessage_metaDescriptorLength;
extern c_metaObject __ChatDDS_SystemMessage__load (c_base base);
struct _ChatDDS_SystemMessage ;
extern  v_copyin_result __ChatDDS_SystemMessage__copyIn(c_type dbType, const class ChatDDS::SystemMessage *from, struct _ChatDDS_SystemMessage *to);
extern  void __ChatDDS_SystemMessage__copyOut(const void *_from, void *_to);
struct _ChatDDS_SystemMessage {
    c_string username;
    enum _ChatDDS_SystemMessageType type;
};

#undef OS_API
#endif
