#ifndef _ChatDDS_H_
#define _ChatDDS_H_

#include <dds/core/ddscore.hpp>

namespace ChatDDS
{
    class Time OSPL_DDS_FINAL
    {
    public:
        uint16_t hour_;
        uint16_t min_;
        uint16_t sec_;

    public:
        Time() :
                hour_(0),
                min_(0),
                sec_(0) {}

        explicit Time(
            uint16_t hour,
            uint16_t min,
            uint16_t sec) : 
                hour_(hour),
                min_(min),
                sec_(sec) {}

        Time(const Time &_other) : 
                hour_(_other.hour_),
                min_(_other.min_),
                sec_(_other.sec_) {}

#ifdef OSPL_DDS_CXX11
        Time(Time &&_other) : 
                hour_(::std::move(_other.hour_)),
                min_(::std::move(_other.min_)),
                sec_(::std::move(_other.sec_)) {}

        Time& operator=(Time &&_other)
        {
            if (this != &_other) {
                hour_ = ::std::move(_other.hour_);
                min_ = ::std::move(_other.min_);
                sec_ = ::std::move(_other.sec_);
            }
            return *this;
        }
#endif

        Time& operator=(const Time &_other)
        {
            if (this != &_other) {
                hour_ = _other.hour_;
                min_ = _other.min_;
                sec_ = _other.sec_;
            }
            return *this;
        }

        bool operator==(const Time& _other) const
        {
            return hour_ == _other.hour_ &&
                min_ == _other.min_ &&
                sec_ == _other.sec_;
        }

        bool operator!=(const Time& _other) const
        {
            return !(*this == _other);
        }

        uint16_t hour() const { return this->hour_; }
        uint16_t& hour() { return this->hour_; }
        void hour(uint16_t _val_) { this->hour_ = _val_; }
        uint16_t min() const { return this->min_; }
        uint16_t& min() { return this->min_; }
        void min(uint16_t _val_) { this->min_ = _val_; }
        uint16_t sec() const { return this->sec_; }
        uint16_t& sec() { return this->sec_; }
        void sec(uint16_t _val_) { this->sec_ = _val_; }
    };

    class Message OSPL_DDS_FINAL
    {
    public:
        uint16_t id_;
        std::string username_;
        ChatDDS::Time time_;
        std::string content_;

    public:
        Message() :
                id_(0) {}

        explicit Message(
            uint16_t id,
            const std::string& username,
            const ChatDDS::Time& time,
            const std::string& content) : 
                id_(id),
                username_(username),
                time_(time),
                content_(content) {}

        Message(const Message &_other) : 
                id_(_other.id_),
                username_(_other.username_),
                time_(_other.time_),
                content_(_other.content_) {}

#ifdef OSPL_DDS_CXX11
        Message(Message &&_other) : 
                id_(::std::move(_other.id_)),
                username_(::std::move(_other.username_)),
                time_(::std::move(_other.time_)),
                content_(::std::move(_other.content_)) {}

        Message& operator=(Message &&_other)
        {
            if (this != &_other) {
                id_ = ::std::move(_other.id_);
                username_ = ::std::move(_other.username_);
                time_ = ::std::move(_other.time_);
                content_ = ::std::move(_other.content_);
            }
            return *this;
        }
#endif

        Message& operator=(const Message &_other)
        {
            if (this != &_other) {
                id_ = _other.id_;
                username_ = _other.username_;
                time_ = _other.time_;
                content_ = _other.content_;
            }
            return *this;
        }

        bool operator==(const Message& _other) const
        {
            return id_ == _other.id_ &&
                username_ == _other.username_ &&
                time_ == _other.time_ &&
                content_ == _other.content_;
        }

        bool operator!=(const Message& _other) const
        {
            return !(*this == _other);
        }

        uint16_t id() const { return this->id_; }
        uint16_t& id() { return this->id_; }
        void id(uint16_t _val_) { this->id_ = _val_; }
        const std::string& username() const { return this->username_; }
        std::string& username() { return this->username_; }
        void username(const std::string& _val_) { this->username_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void username(std::string&& _val_) { this->username_ = _val_; }
#endif
        const ChatDDS::Time& time() const { return this->time_; }
        ChatDDS::Time& time() { return this->time_; }
        void time(const ChatDDS::Time& _val_) { this->time_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void time(ChatDDS::Time&& _val_) { this->time_ = _val_; }
#endif
        const std::string& content() const { return this->content_; }
        std::string& content() { return this->content_; }
        void content(const std::string& _val_) { this->content_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void content(std::string&& _val_) { this->content_ = _val_; }
#endif
    };

    OSPL_ENUM SystemMessageType {
        JOIN,
        QUIT
    };

    class SystemMessage OSPL_DDS_FINAL
    {
    public:
        std::string username_;
        ChatDDS::SystemMessageType type_;

    public:
        SystemMessage() :
                type_(OSPL_ENUM_LABEL(ChatDDS,SystemMessageType,JOIN)) {}

        explicit SystemMessage(
            const std::string& username,
            ChatDDS::SystemMessageType type) : 
                username_(username),
                type_(type) {}

        SystemMessage(const SystemMessage &_other) : 
                username_(_other.username_),
                type_(_other.type_) {}

#ifdef OSPL_DDS_CXX11
        SystemMessage(SystemMessage &&_other) : 
                username_(::std::move(_other.username_)),
                type_(::std::move(_other.type_)) {}

        SystemMessage& operator=(SystemMessage &&_other)
        {
            if (this != &_other) {
                username_ = ::std::move(_other.username_);
                type_ = ::std::move(_other.type_);
            }
            return *this;
        }
#endif

        SystemMessage& operator=(const SystemMessage &_other)
        {
            if (this != &_other) {
                username_ = _other.username_;
                type_ = _other.type_;
            }
            return *this;
        }

        bool operator==(const SystemMessage& _other) const
        {
            return username_ == _other.username_ &&
                type_ == _other.type_;
        }

        bool operator!=(const SystemMessage& _other) const
        {
            return !(*this == _other);
        }

        const std::string& username() const { return this->username_; }
        std::string& username() { return this->username_; }
        void username(const std::string& _val_) { this->username_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void username(std::string&& _val_) { this->username_ = _val_; }
#endif
        ChatDDS::SystemMessageType type() const { return this->type_; }
        ChatDDS::SystemMessageType& type() { return this->type_; }
        void type(ChatDDS::SystemMessageType _val_) { this->type_ = _val_; }
    };

}

#endif /* _ChatDDS_H_ */
