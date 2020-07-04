#ifndef _ChatData_H_
#define _ChatData_H_

#include <dds/core/ddscore.hpp>

namespace ChatData
{
    class Message OSPL_DDS_FINAL
    {
    public:
        std::string user_;
        uint32_t time_;
        std::string content_;

    public:
        Message() :
                time_(0) {}

        explicit Message(
            const std::string& user,
            uint32_t time,
            const std::string& content) : 
                user_(user),
                time_(time),
                content_(content) {}

        Message(const Message &_other) : 
                user_(_other.user_),
                time_(_other.time_),
                content_(_other.content_) {}

#ifdef OSPL_DDS_CXX11
        Message(Message &&_other) : 
                user_(::std::move(_other.user_)),
                time_(::std::move(_other.time_)),
                content_(::std::move(_other.content_)) {}

        Message& operator=(Message &&_other)
        {
            if (this != &_other) {
                user_ = ::std::move(_other.user_);
                time_ = ::std::move(_other.time_);
                content_ = ::std::move(_other.content_);
            }
            return *this;
        }
#endif

        Message& operator=(const Message &_other)
        {
            if (this != &_other) {
                user_ = _other.user_;
                time_ = _other.time_;
                content_ = _other.content_;
            }
            return *this;
        }

        bool operator==(const Message& _other) const
        {
            return user_ == _other.user_ &&
                time_ == _other.time_ &&
                content_ == _other.content_;
        }

        bool operator!=(const Message& _other) const
        {
            return !(*this == _other);
        }

        const std::string& user() const { return this->user_; }
        std::string& user() { return this->user_; }
        void user(const std::string& _val_) { this->user_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void user(std::string&& _val_) { this->user_ = _val_; }
#endif
        uint32_t time() const { return this->time_; }
        uint32_t& time() { return this->time_; }
        void time(uint32_t _val_) { this->time_ = _val_; }
        const std::string& content() const { return this->content_; }
        std::string& content() { return this->content_; }
        void content(const std::string& _val_) { this->content_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void content(std::string&& _val_) { this->content_ = _val_; }
#endif
    };

}

#endif /* _ChatData_H_ */
