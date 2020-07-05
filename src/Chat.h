#pragma once

#include "WindowAPI/Window.hpp"
#include "WindowAPI/GUI.h"

#include "IDL_IMPL/ChatDDS_DCPS.hpp"

using namespace WAPI;

class Chat {
private:
    std::string username;
    std::string lang;
    std::string room;

    std::string messages = "Texto\nsdada\nsdsf";
    std::string send_message = "Message";

    bool initChat = false;

public:
    Chat() {

    }

    void Start() {

        WindowConfigStruct config;

        config.windowName = "Chat DDS";
        config.windowPosition = {20, 40};
        config.windowSize = {400, 400};
        config.VSync = true;
        config.MSAA = 2;

        if (!Window::Create(config)) {
            exit(1);
        }

        GUI::Init();
    }

    void Run() {
        bool shouldRun = true;
        while(shouldRun) {

            GUI::Begin();
            GUI::BeginWindow("Chat DDS", Window::GetSize(), {0,0});
            
            if (this->initChat) {
                GUI::MakeText("Sala: " + this->room + "\n" + "0" + " online(s)");

                GUI::MakeSpace();

                GUI::MakeMultiLineInput("##textboxshow", &messages, {Window::GetSize().x * 0.95, Window::GetSize().y * 0.75});

                GUI::MakeInput("##textboxtype", "Digite sua mensagem", &send_message);
                
                GUI::ContinueSameLine();
                if (GUI::MakeButton("Enviar")) {

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
                GUI::MakeInput("##labelusername", &this->username);

                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();
                
                GUI::MakeText("Idioma");
                GUI::ContinueSameLine();
                GUI::MakeHelpMarker("Idioma do bate-papo");
                GUI::MakeInput("##labellang", &this->lang);

                GUI::MakeText("Sala");
                GUI::ContinueSameLine();
                GUI::MakeHelpMarker("Assunto do bate-papo");
                GUI::MakeInput("##labelroom", &this->room);

                GUI::MakeSpace(); GUI::MakeSpace(); GUI::MakeSpace();

                if (GUI::MakeButton("Conectar"))
                    this->initChat = true;
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
};

