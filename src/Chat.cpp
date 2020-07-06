#include "Chat.h"

Chat::Chat() {
    username = "";
    lang = 0;
    room = "";
    messagesMultiLine = "";
    messageTyped = "";
    messagesSent = 0;
    initChat = false;
}

void Chat::Start() {
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

void Chat::Run() {
    bool shouldRun = true;
    while(shouldRun) {

        GUI::Begin();
        GUI::BeginWindow("Chat DDS", Window::GetSize(), {0,0});
        
        if (initChat) {
            GUI::MakeText("Conectado como " + username + "\nSala: " + room + " (" + LangIdToString(lang) + ")");

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
                        room = v[1];
                    
                    } else if (v[0] == "/pm") {
                        chatter->sendPrivateMessage(v[1], v[2]);
                    
                    } else if (v[0] == "/ignore") {
                        messageBoard->ignoreUser(v[1]);
                    
                    } else {
                        messageBoard->writeMessage(">> Comando \"" + v[0] + "\" não encontrado");
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
            GUI::MakeSeparator();
            GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

            GUI::MakeText("                             Chat DDS");

            GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();
            GUI::MakeSeparator();
            GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

            GUI::MakeText("Apelido");
            GUI::ContinueSameLine();
            GUI::MakeHelpMarker("Nome que aparecerá ao enviar uma mensagem");

            GUI::MakeInput("##labelusername", &username);

            GUI::MakeSpace(); GUI::MakeSpace();

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
            
            GUI::MakeSpace(); GUI::MakeSpace();

            GUI::MakeText("Sala");
            GUI::ContinueSameLine();
            GUI::MakeHelpMarker("Assunto do bate-papo");
            GUI::MakeInput("##labelroom", &room);

            GUI::MakeSpace(); GUI::MakeSpace();

            if (ImGui::Button("Conectar", {Window::GetSize().x * (float)0.65, 30})) {
                if (username == "")
                    username = "Visitante" + std::to_string(rand() % 999 + 1);

                chatter = new Chatter(username, room, lang);
                messageBoard = new MessageBoard(username, room, lang);

                chatter->joinRoom(room);

                initChat = true;
            }
            
            GUI::ContinueSameLine();
            if (ImGui::Button("Sair", { Window::GetSize().x * (float)0.29, 30 })) {
                shouldRun = false;
            }
        }

        GUI::EndWindow();
        GUI::End();

        Window::SwapAndPollEvents();
    }
}

void Chat::Exit() {
    GUI::Release();
    Window::Destroy();
}

std::string* Chat::GetMultiLineMessages(float larg) {
    std::vector<std::string> newMessages = messageBoard->GetNewMessages();

    if (newMessages.size() > 0) {
        for (int i = 0; i < newMessages.size(); i++)
            messagesMultiLine += (messagesMultiLine.size() == 0 ? "" : "\n") + newMessages[i];
    }

    return &messagesMultiLine;
}

std::string Chat::LangIdToString(int l) {
    const char* items[] = {"PT", "EN", "ES", "DE", "IT", "FR"};
    return items[l];
}