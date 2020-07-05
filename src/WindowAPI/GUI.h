#pragma once

#include "Window.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace WAPI
{
	class GUI
	{
	private:
		static bool Initialized;
	public:
		static void Init(); // init gui resources
		static void Release();

		static void Begin(); // init of frame and end
		static void End();

		static void BeginWindow(std::string windowName, glm::vec2 size, glm::vec2 pos);
		static bool isWindowFocused();
		static void EndWindow();

		static void ContinueSameLine();
		static bool MakeSubSection(std::string name);
		static void MakeSpace();

		static void MakeSeparator();

		/* Sliders */
		static void MakeSlider(std::string label, float* val, float initRange, float endRange);

		static void MakeSlider(std::string label, int* val, int initRange, int endRange);

		static void MakeSlider(std::string label, glm::vec2* val, float initRange, float endRange);

		static void MakeSlider(std::string label, glm::vec3* val, float initRange, float endRange);

		static void MakeSlider(std::string label, glm::vec4* val, float initRange, float endRange);

		/* Input */
		static void MakeMultiLineInput(std::string label, std::string* val, glm::vec2 = {0,0});

		static void MakeInput(std::string label, int* val);

		static void MakeInput(std::string label, float* val);

		static void MakeInput(std::string label, double* val);

		static void MakeInput(std::string label, std::string* val);

		static void MakeInput(std::string label, std::string hint, std::string* val);

		static void MakeInput(std::string label, glm::vec2* val);

		static void MakeInput(std::string label, glm::vec3* val);

		static void MakeInput(std::string label, glm::vec4* val);
		/* Checkbox */
		static void MakeCheckBox(std::string name, bool* val);

		/* Text Label */
		static void MakeText(std::string text);
		
		static void MakeText(std::string text, glm::vec3 color);

		static void MakeItemText(std::string text);

		/* Color pickers */
		static void MakeColorPicker(std::string label, glm::vec4* color);

		static void MakeColorPicker(std::string label, glm::vec3* color);
		/* Buttons */
		static bool MakeButton(std::string buttonName);
			
		static bool MakeColorBox(std::string buttonName, glm::vec3 color);

		static void MakeRadioButton(std::string buttonName, bool* value);

		static void MakeHelpMarker(std::string name);
	};
}

