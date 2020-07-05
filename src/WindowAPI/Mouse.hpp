#pragma once

#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm.hpp>

#include <GLFW/glfw3.h>

#include <functional>

#include "Definitions.hpp"
#include "Window.hpp"

namespace WAPI
{
	enum class MouseMode
	{
		NORMAL = GLFW_CURSOR_NORMAL,
		HIDDEN = GLFW_CURSOR_HIDDEN,
		DISABLED = GLFW_CURSOR_DISABLED
	};

	enum class MouseButton
	{
		MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_1,
		MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_2,
		MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_3,
		MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
		MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
		MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
		MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
		MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
		MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
		MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
		MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8
	};

	typedef std::function<void(MouseButton, InputAction, InputModifier)> MouseButtonCallback;
	typedef std::function<void(glm::vec<2,int>)> MousePositionCallback;
	typedef std::function<void(float)> MouseScrollCallback;
	typedef std::function<void(bool)> MouseEnterWindowCallback;

	class Mouse
	{
		friend class Window;
	private:
		static MouseButtonCallback mouseButtonCallback;
		static MousePositionCallback mousePositionCallback;
		static MouseScrollCallback mouseScrollCallback;
		static MouseEnterWindowCallback mouseEnterWindowCallback;

		static float ScrollAcumulation;
		static float LastScroll;
		static bool EnterDisplay;

		static void MasterCursorEnterWindow(GLFWwindow* window, int entered);
		static void MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
		static void MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void Init();
	public:
		static void SetMouseButtonCallback(MouseButtonCallback callback);

		static void SetMousePositionCallback(MousePositionCallback callback);

		static void SetMouseScrollCallback(MouseScrollCallback callback);

		static void SetMouseEnterWindowCallback(MouseEnterWindowCallback callback);

		static InputAction GetMouseButtonState(MouseButton button);

		static glm::vec<2,int> GetMousePosition();

		static void SetMouseMode(MouseMode mode);

		static float GetScrollVariantion();

		static float GetScrollCumulativeVariation();

		static void ResetScrollVariation();

		static void ResetScrollCumulativeVariation();

		static bool IsMouseInsideWindow();
	};
}



