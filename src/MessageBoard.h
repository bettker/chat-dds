#include <iostream>
#include <string>
#include <vector>

class MessageBoard {
private:
    std::string username;
    std::vector<std::string> newMessages;
    std::vector<std::string> ignoredUsers;

public:
    MessageBoard(std::string username) {
        this->username = username;
    }

    std::vector<std::string> GetNewMessages() {
        std::vector<std::string> m;
        for (int i = 0; i < newMessages.size(); i++)
            m.push_back(newMessages[i]);
        newMessages.clear();
    }

    bool ignoreUser(std::string user) {
        std::cout << "Ignorou o usuario " << user << std::endl;
        ignoredUsers.push_back(user);
        return true;
    }
};
