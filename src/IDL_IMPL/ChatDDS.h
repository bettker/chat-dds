#ifndef _ChatDDS_H_
#define _ChatDDS_H_

#include <dds/core/ddscore.hpp>

namespace ChatDDS
{
    class Message OSPL_DDS_FINAL
    {
    public:
        int32_t userID_;
        std::string userName_;
        std::string message_;

    public:
        Message() :
                userID_(0) {}

        explicit Message(
            int32_t userID,
            const std::string& userName,
            const std::string& message) : 
                userID_(userID),
                userName_(userName),
                message_(message) {}

        Message(const Message &_other) : 
                userID_(_other.userID_),
                userName_(_other.userName_),
                message_(_other.message_) {}

#ifdef OSPL_DDS_CXX11
        Message(Message &&_other) : 
                userID_(::std::move(_other.userID_)),
                userName_(::std::move(_other.userName_)),
                message_(::std::move(_other.message_)) {}

        Message& operator=(Message &&_other)
        {
            if (this != &_other) {
                userID_ = ::std::move(_other.userID_);
                userName_ = ::std::move(_other.userName_);
                message_ = ::std::move(_other.message_);
            }
            return *this;
        }
#endif

        Message& operator=(const Message &_other)
        {
            if (this != &_other) {
                userID_ = _other.userID_;
                userName_ = _other.userName_;
                message_ = _other.message_;
            }
            return *this;
        }

        bool operator==(const Message& _other) const
        {
            return userID_ == _other.userID_ &&
                userName_ == _other.userName_ &&
                message_ == _other.message_;
        }

        bool operator!=(const Message& _other) const
        {
            return !(*this == _other);
        }

        int32_t userID() const { return this->userID_; }
        int32_t& userID() { return this->userID_; }
        void userID(int32_t _val_) { this->userID_ = _val_; }
        const std::string& userName() const { return this->userName_; }
        std::string& userName() { return this->userName_; }
        void userName(const std::string& _val_) { this->userName_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void userName(std::string&& _val_) { this->userName_ = _val_; }
#endif
        const std::string& message() const { return this->message_; }
        std::string& message() { return this->message_; }
        void message(const std::string& _val_) { this->message_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void message(std::string&& _val_) { this->message_ = _val_; }
#endif
    };

}

#endif /* _ChatDDS_H_ */
