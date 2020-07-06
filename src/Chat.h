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
    std::string teste = "";
    int lang;
    std::string room;

    std::string messagesMultiLine;
    std::string messageTyped;

    int messagesSent;

    bool initChat;

public:
    Chat() {
        username = "";
        lang = 0;
        room = "";
        messagesMultiLine = "1asfasffas";
        messageTyped = "";
        messagesSent = 0;
        initChat = false;
    }

    void Start() {
        WindowConfigStruct config;

        config.windowName = "Chat DDS";
        config.windowPosition = {20, 40};
        config.windowSize = {400, 400};
        config.VSync = true;
        config.MSAA = 2;

        if (!Window::Create(config))
            exit(1);

        GUI::Init();
    }

    void Run() {
        bool shouldRun = true;
        while(shouldRun) {

            GUI::Begin();
            GUI::BeginWindow("Chat DDS", Window::GetSize(), {0,0});
            
            if (initChat) {
                GUI::MakeText("Sala: " + room + "\n" + "0" + " online(s)");

                GUI::MakeSpace();

                glm::vec2 size = {Window::GetSize().x - 20, Window::GetSize().y - 100};
                GUI::MakeMultiLineInput("##textboxshow", GetMultiLineMessages(size.x), size);

                GUI::MakeInput("##textboxtype", "Digite a mensagem", &messageTyped);
                
                GUI::ContinueSameLine();
                if (GUI::MakeButton("Enviar")) {

                    if (messageTyped[0] == '/') {

                        // Separa por espacos
                        std::vector<std::string> v;
                        std::string word = "";
                        for (auto x : messageTyped) {
                            if (x == ' ') {
                                v.push_back(word);
                                word = "";
                            } else {
                                word += x;
                            }
                        }
                        v.push_back(word);

                        if (v[0] == "/join") {
                            chatter->joinRoom(v[1]);
                        
                        } else if (v[0] == "/pm") {
                            chatter->privateMessage(v[1], v[2]);
                        
                        } else if (v[0] == "/ignore") {
                            messageBoard->ignoreUser(v[1]);
                        
                        } else {
                            // "Comando \"" + v[0] + "\" não encontrado"
                        }

                    } else {
                        chatter->sendMessage(messageTyped);
                    }

                    messageTyped = "";
                }
                
                GUI::ContinueSameLine();
                if (GUI::MakeButton("Sair")) {
                    shouldRun = false;
                }

            } else {
                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();
                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

                GUI::MakeText("Chat DDS");

                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

                GUI::MakeText("Apelido");
                GUI::ContinueSameLine();
                GUI::MakeHelpMarker("Nome que aparecerá ao enviar uma mensagem");
                GUI::MakeInput("##labelusername", &teste);

                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();
                
                GUI::MakeText("Idioma");
                GUI::ContinueSameLine();
                GUI::MakeHelpMarker("Idioma do bate-papo");
                const char* items[] = {"Português", "Inglês", "Espanhol", "Alemão", "Italiano", "Francês"};
                if (ImGui::BeginCombo("##combo", items[lang]))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (items[lang] == items[n]);
                        if (ImGui::Selectable(items[n], is_selected))
                            lang = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                GUI::MakeText("Sala");
                GUI::ContinueSameLine();
                GUI::MakeHelpMarker("Assunto do bate-papo");
                GUI::MakeInput("##labelroom", &room);

                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

                if (GUI::MakeButton("Conectar")) {
                    if (username == "")
                        username = "Visitante" + std::to_string(rand() % 999 + 1);

                    chatter = new Chatter(username, room, lang);
                    messageBoard = new MessageBoard(username);

                    chatter->joinRoom(room);

                    initChat = true;
                }
                
                GUI::ContinueSameLine();
                if (GUI::MakeButton("Sair"))
                    shouldRun = false;
            }

            GUI::EndWindow();
            GUI::End();

            Window::SwapAndPollEvents();
        }
    }

    void Exit() {
        GUI::Release();
        Window::Destroy();
    }

private:
    std::string* GetMultiLineMessages(float larg) {
        std::vector<std::string> newMessages = messageBoard->GetNewMessages();

        if (newMessages.size() > 0) {
            for (int i = 0; i < newMessages.size(); i++)
                messagesMultiLine += (messagesMultiLine.size() == 0 ? "" : "\n") + newMessages[i];
        }

        return &messagesMultiLine;
    }
};

