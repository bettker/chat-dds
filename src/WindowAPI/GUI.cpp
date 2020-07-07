#include "GUI.h"

namespace WAPI
{
	bool GUI::Initialized = false;

	void GUI::Init()
	{
		if(GUI::Initialized) return;

		GUI::Initialized = true;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_InitForOpenGL(Window::windowPtr, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		auto* style = &ImGui::GetStyle();
		
		style->WindowRounding = 0.0f;
		style->GrabRounding = style->FrameRounding = 2.3f;
		style->ScrollbarRounding = 5.0f;
		style->FrameBorderSize = 1.0f;
		style->ItemSpacing.y = 6.5f;

		style->Colors[ImGuiCol_Text] = { 0.73333335f, 0.73333335f, 0.73333335f, 1.00f };
		style->Colors[ImGuiCol_TextDisabled] = { 0.34509805f, 0.34509805f, 0.34509805f, 1.00f };
		style->Colors[ImGuiCol_WindowBg] = { 0.23529413f, 0.24705884f, 0.25490198f, 0.94f };
		style->Colors[ImGuiCol_ChildBg] = { 0.23529413f, 0.24705884f, 0.25490198f, 0.00f };
		style->Colors[ImGuiCol_PopupBg] = { 0.23529413f, 0.24705884f, 0.25490198f, 0.94f };
		style->Colors[ImGuiCol_Border] = { 0.33333334f, 0.33333334f, 0.33333334f, 0.50f };
		style->Colors[ImGuiCol_BorderShadow] = { 0.15686275f, 0.15686275f, 0.15686275f, 0.00f };
		style->Colors[ImGuiCol_FrameBg] = { 0.16862746f, 0.16862746f, 0.16862746f, 0.54f };
		style->Colors[ImGuiCol_FrameBgHovered] = { 0.453125f, 0.67578125f, 0.99609375f, 0.67f };
		style->Colors[ImGuiCol_FrameBgActive] = { 0.47058827f, 0.47058827f, 0.47058827f, 0.67f };
		style->Colors[ImGuiCol_TitleBg] = { 0.04f, 0.04f, 0.04f, 1.00f };
		style->Colors[ImGuiCol_TitleBgCollapsed] = { 0.16f, 0.29f, 0.48f, 1.00f };
		style->Colors[ImGuiCol_TitleBgActive] = { 0.00f, 0.00f, 0.00f, 0.51f };
		style->Colors[ImGuiCol_MenuBarBg] = { 0.27058825f, 0.28627452f, 0.2901961f, 0.80f };
		style->Colors[ImGuiCol_ScrollbarBg] = { 0.27058825f, 0.28627452f, 0.2901961f, 0.60f };
		style->Colors[ImGuiCol_ScrollbarGrab] = { 0.21960786f, 0.30980393f, 0.41960788f, 0.51f };
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = { 0.21960786f, 0.30980393f, 0.41960788f, 1.00f };
		style->Colors[ImGuiCol_ScrollbarGrabActive] = { 0.13725491f, 0.19215688f, 0.2627451f, 0.91f };
		// style->Colors[ImGuiCol_ComboBg]               = {0.1f, 0.1f, 0.1f, 0.99f};
		style->Colors[ImGuiCol_CheckMark] = { 0.90f, 0.90f, 0.90f, 0.83f };
		style->Colors[ImGuiCol_SliderGrab] = { 0.70f, 0.70f, 0.70f, 0.62f };
		style->Colors[ImGuiCol_SliderGrabActive] = { 0.30f, 0.30f, 0.30f, 0.84f };
		style->Colors[ImGuiCol_Button] = { 0.33333334f, 0.3529412f, 0.36078432f, 0.49f };
		style->Colors[ImGuiCol_ButtonHovered] = { 0.21960786f, 0.30980393f, 0.41960788f, 1.00f };
		style->Colors[ImGuiCol_ButtonActive] = { 0.13725491f, 0.19215688f, 0.2627451f, 1.00f };
		style->Colors[ImGuiCol_Header] = { 0.33333334f, 0.3529412f, 0.36078432f, 0.53f };
		style->Colors[ImGuiCol_HeaderHovered] = { 0.453125f, 0.67578125f, 0.99609375f, 0.67f };
		style->Colors[ImGuiCol_HeaderActive] = { 0.47058827f, 0.47058827f, 0.47058827f, 0.67f };
		style->Colors[ImGuiCol_Separator] = { 0.31640625f, 0.31640625f, 0.31640625f, 1.00f };
		style->Colors[ImGuiCol_SeparatorHovered] = { 0.31640625f, 0.31640625f, 0.31640625f, 1.00f };
		style->Colors[ImGuiCol_SeparatorActive] = { 0.31640625f, 0.31640625f, 0.31640625f, 1.00f };
		style->Colors[ImGuiCol_ResizeGrip] = { 1.00f, 1.00f, 1.00f, 0.85f };
		style->Colors[ImGuiCol_ResizeGripHovered] = { 1.00f, 1.00f, 1.00f, 0.60f };
		style->Colors[ImGuiCol_ResizeGripActive] = { 1.00f, 1.00f, 1.00f, 0.90f };
		style->Colors[ImGuiCol_PlotLines] = { 0.61f, 0.61f, 0.61f, 1.00f };
		style->Colors[ImGuiCol_PlotLinesHovered] = { 1.00f, 0.43f, 0.35f, 1.00f };
		style->Colors[ImGuiCol_PlotHistogram] = { 0.90f, 0.70f, 0.00f, 1.00f };
		style->Colors[ImGuiCol_PlotHistogramHovered] = { 1.00f, 0.60f, 0.00f, 1.00f };
		style->Colors[ImGuiCol_TextSelectedBg] = { 0.18431373f, 0.39607847f, 0.79215693f, 0.90f };

		io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/arial.ttf", 20, NULL, io.Fonts->GetGlyphRangesDefault());
		io.Fonts->Build();
	}

	void GUI::Release()
	{
		if(!GUI::Initialized) return;

		GUI::Initialized = false;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::BeginWindow(std::string windowName, glm::vec2 size, glm::vec2 pos)
	{
		ImGuiWindowFlags window_flags = 0;

		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;

		ImGui::SetNextWindowSize({size.x, size.y});
		ImGui::SetNextWindowPos({pos.x, pos.y});

		ImGui::Begin(windowName.c_str(), 0, window_flags);
	}

	bool GUI::isWindowFocused()
	{
		return ImGui::IsWindowFocused();
	}

	void GUI::EndWindow()
	{
		ImGui::End();
	}

	void GUI::ContinueSameLine()
	{
		ImGui::SameLine();
	}

	bool GUI::MakeSubSection(std::string name)
	{
		return ImGui::CollapsingHeader(name.c_str());
	}

	void GUI::MakeSpace()
	{
		ImGui::Spacing();
	}

	void GUI::MakeSeparator()
	{
		ImGui::Separator();
	}

	void GUI::MakeSlider(std::string label, float* val, float initRange, float endRange)
	{
		ImGui::SliderFloat(label.c_str(), val, initRange, endRange);
	}

	void GUI::MakeSlider(std::string label, int* val, int initRange, int endRange)
	{
		ImGui::SliderInt(label.c_str(), val, initRange, endRange);
	}

	void GUI::MakeSlider(std::string label, glm::vec2* val, float initRange, float endRange)
	{
		static float v[2];

		v[0] = val->x;
		v[1] = val->y;

		ImGui::SliderFloat2(label.c_str(), v, initRange, endRange);

		val->x = v[0];
		val->y = v[1];
	}

	void GUI::MakeSlider(std::string label, glm::vec3* val, float initRange, float endRange)
	{
		static float v[3];

		v[0] = val->x;
		v[1] = val->y;
		v[2] = val->z;

		ImGui::SliderFloat3(label.c_str(), v, initRange, endRange);

		val->x = v[0];
		val->y = v[1];
		val->z = v[2];
	}

	void GUI::MakeSlider(std::string label, glm::vec4* val, float initRange, float endRange)
	{
		static float v[4];

		v[0] = val->x;
		v[1] = val->y;
		v[2] = val->z;
		v[3] = val->w;

		ImGui::SliderFloat4(label.c_str(), v, initRange, endRange);

		val->x = v[0];
		val->y = v[1];
		val->z = v[2];
		val->w = v[3];
	}

	void GUI::MakeMultiLineInput(std::string label, std::string* val, glm::vec2 size)
	{
		char* c = _strdup(val->c_str());

		ImGuiInputTextFlags flags = ImGuiInputTextFlags_ReadOnly;

		ImGui::InputTextMultiline(label.c_str(), c, val->size()+1024, {size.x, size.y}, flags);

		*val = c;

		// delete[] c;
	}

	void GUI::MakeInput(std::string label, int* val)
	{
		ImGui::InputInt(label.c_str(), val);
	}

	void GUI::MakeInput(std::string label, float* val)
	{
		ImGui::InputFloat(label.c_str(), val);
	}

	void GUI::MakeInput(std::string label, double* val)
	{
		ImGui::InputDouble(label.c_str(), val);
	}

	void GUI::MakeInput(std::string label, std::string* val)
	{
		char* c = _strdup(val->c_str());

		ImGui::InputText(label.c_str(), c, 100);

		*val = c;
		
		//delete[] c;
	}

	void GUI::MakeInput(std::string label, std::string hint, std::string* val)
	{
		//static char* c = new char[100];

		char* c = _strdup(val->c_str());

		ImGui::InputTextWithHint(label.c_str(), hint.c_str(), c, 100);

		*val = c;

		//delete[] c;
	}

	void GUI::MakeInput(std::string label, glm::vec2* val)
	{
		ImGui::InputFloat2(label.c_str(), (float*)val);
	}

	void GUI::MakeInput(std::string label, glm::vec3* val)
	{
		ImGui::InputFloat3(label.c_str(), (float*)val);
	}

	void GUI::MakeInput(std::string label, glm::vec4* val)
	{
		ImGui::InputFloat4(label.c_str(), (float*)val);
	}

	void GUI::MakeCheckBox(std::string name, bool* val)
	{
		ImGui::Checkbox(name.c_str(), val);
	}

	void GUI::MakeText(std::string text)
	{
		ImGui::Text(text.c_str());
	}

	void GUI::MakeText(std::string text, glm::vec3 color)
	{
		ImGui::TextColored(ImVec4(color.x, color.y, color.z, 1.0f), text.c_str());
	}

	void GUI::MakeItemText(std::string text)
	{
		ImGui::BulletText(text.c_str());
	}

	void GUI::MakeColorPicker(std::string label, glm::vec4* color)
	{
		ImGui::ColorEdit4(label.c_str(), (float*)color);
	}

	void GUI::MakeColorPicker(std::string label, glm::vec3* color)
	{
		ImGui::ColorEdit3(label.c_str(), (float*)color);
	}

	bool GUI::MakeButton(std::string buttonName)
	{
		return ImGui::Button(buttonName.c_str());
	}

	bool GUI::MakeColorBox(std::string buttonName, glm::vec3 color)
	{
		return ImGui::ColorButton(buttonName.c_str(), ImVec4(color.x, color.y, color.z, 1.0f));
	}

	void GUI::MakeRadioButton(std::string buttonName, bool* value)
	{
		*value = ImGui::RadioButton(buttonName.c_str(), *value);
	}

	void GUI::MakeHelpMarker(std::string name)
	{
		ImGui::TextDisabled("(?)");

		if(ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}