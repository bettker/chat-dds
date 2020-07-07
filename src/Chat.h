#include <string>
#include <stdlib.h>

#include "WindowAPI/Window.hpp"
#include "WindowAPI/GUI.h"

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

#include "Chatter.h"
#include "MessageBoard.h"

using namespace WAPI;

class Chat {
private:
    Chatter* chatter;
    MessageBoard* messageBoard;

    std::string username;
    int lang;
    std::string room;

    std::string messagesMultiLine;
    std::string messageTyped;

    int messagesSent;

    bool initChat;

public:
    Chat();

    void Start();

    void Run();

    void Exit();

private:
    void JoinRoom(std::string room);

    std::string* GetMultiLineMessages(float larg);

    std::string LangIdToString(int l);
};

