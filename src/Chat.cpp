#include "Chat.h"

Chat::Chat() {
    username = "";
    lang = 0;
    room = "";
    messagesMultiLine = "";
    messageTyped = "";
    messagesSent = 0;
    state = ChatState::LOGIN;
}

void Chat::Login() {
    GUI::MakeSpace(); GUI::MakeSpace();
    GUI::MakeSeparator();
    GUI::MakeSpace(); GUI::MakeSpace();

    GUI::MakeText("                             Chat DDS");

    GUI::MakeSpace(); GUI::MakeSpace();
    GUI::MakeSeparator();
    GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

    GUI::MakeText("Apelido");
    GUI::ContinueSameLine();
    GUI::MakeHelpMarker("Nome que aparecerá ao enviar uma mensagem");

    GUI::MakeInput("##labelusername", &username);

    GUI::MakeSpace(); GUI::MakeSpace();

    GUI::MakeText("Servidor");
    GUI::ContinueSameLine();
    GUI::MakeHelpMarker("Servidor do bate-papo");
    const char* items[] = { "Brasil", "Estados Unidos", "Espanha", "Alemanha", "França" };
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

    if (ImGui::Button("Conectar", { Window::GetSize().x * (float)0.65, 30 })) {
        if (username == "")
            username = "Visitante" + std::to_string(rand() % 999 + 1);

        std::replace(username.begin(), username.end(), ' ', '_');
        std::replace(room.begin(), room.end(), '@', '_');

        chatter = new Chatter(username, room, lang);
        messageBoard = new MessageBoard(username, room, lang);

        JoinRoom(room);

        state = ChatState::CHATROOM;
    }

    if (ImGui::Button("Sair", { Window::GetSize().x * (float)0.65, 30 })) {
        state = ChatState::QUIT;
    }
}

void Chat::Chatroom() {
    GUI::MakeText("Conectado como " + username + "\nSala: " + room + " (" + LangIdToString(lang) + ")");

    GUI::MakeSpace();

    glm::vec2 size = { Window::GetSize().x - 20, Window::GetSize().y - 100 };
    GUI::MakeMultiLineInput("##textboxshow", GetMultiLineMessages(size.x), size);

    GUI::MakeInput("##textboxtype", "Digite a mensagem", &messageTyped);

    GUI::ContinueSameLine();
    if (GUI::MakeButton("Enviar")) {

        if (messageTyped[0] == '/') {
            std::size_t spaceIdx = messageTyped.find(" ");
            std::string command = messageTyped.substr(0, spaceIdx);
            std::string arg = messageTyped.substr(spaceIdx + 1);

            if (command == "/join" || command == "/room") {
                if (arg != room) {
                    chatter->quitRoom();
                    JoinRoom(arg);
                    room = arg;
                }
            }
            else if (command == "/ignore") {
                messageBoard->ignoreUser(arg);
            }
            else {
                messageBoard->writeMessage(">> Comando \"" + command + "\" não encontrado");
            }
        }
        else {
            chatter->sendMessage(messageTyped);
        }
        messageTyped = "";
    }

    GUI::ContinueSameLine();
    if (GUI::MakeButton("Sair")) {
        chatter->quitRoom();
        state = ChatState::QUIT;
    }
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
    while (state != ChatState::QUIT) {

        GUI::Begin();
        GUI::BeginWindow("Chat DDS", Window::GetSize(), { 0,0 });

        if (state == ChatState::LOGIN) {
            Login();
        }
        else if (state == ChatState::CHATROOM) {
            Chatroom();
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

void Chat::JoinRoom(std::string room) {
    messageBoard->joinRoom(room);
    chatter->joinRoom(room);
}

std::string* Chat::GetMultiLineMessages(float larg) {
    std::vector<std::string> newMessages = messageBoard->GetNewMessages();

    if (newMessages.size() > 0) {
        for (int i = 0; i < newMessages.size(); i++) {
            if (newMessages[i].find(">> " + username) == std::string::npos)
                messagesMultiLine += (messagesMultiLine.size() == 0 ? "" : "\n") + newMessages[i];
        }
    }

    return &messagesMultiLine;
}

std::string Chat::LangIdToString(int l) {
    const char* items[] = {"BR", "EN", "ES", "DE", "FR"};
    return items[l];
}