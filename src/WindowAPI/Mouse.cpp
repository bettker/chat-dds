#include "Mouse.hpp"

namespace WAPI
{
	MouseButtonCallback Mouse::mouseButtonCallback = nullptr;
	MousePositionCallback Mouse::mousePositionCallback = nullptr;
	MouseScrollCallback Mouse::mouseScrollCallback = nullptr;
	MouseEnterWindowCallback Mouse::mouseEnterWindowCallback = nullptr;

	float Mouse::ScrollAcumulation = 0;
	float Mouse::LastScroll = 0;

	bool Mouse::EnterDisplay = true;

	void Mouse::MasterCursorEnterWindow(GLFWwindow* window, int entered)
	{
		Mouse::EnterDisplay = (bool)entered;

		if(Mouse::mouseEnterWindowCallback != nullptr) Mouse::mouseEnterWindowCallback((bool)entered);
	}

	void Mouse::MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if(Mouse::mousePositionCallback != nullptr) Mouse::mousePositionCallback({xpos, ypos});
	}

	void Mouse::MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod)
	{
		if(Mouse::mouseButtonCallback != nullptr) Mouse::mouseButtonCallback((MouseButton)button, (InputAction)action, (InputModifier)mod);
	}

	void Mouse::MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Mouse::LastScroll = yoffset;
		Mouse::ScrollAcumulation += yoffset;

		if(Mouse::mouseScrollCallback != nullptr) Mouse::mouseScrollCallback(yoffset);
	}

	void Mouse::Init()
	{
		glfwSetScrollCallback(Window::windowPtr, MasterScrollCallback);
		glfwSetCursorEnterCallback(Window::windowPtr, MasterCursorEnterWindow);
	}

	void Mouse::SetMouseButtonCallback(MouseButtonCallback callback)
	{
		Mouse::mouseButtonCallback = callback;

		glfwSetMouseButtonCallback(Window::windowPtr, MasterMouseButtonCallback);
	}

	void Mouse::SetMousePositionCallback(MousePositionCallback callback)
	{
		Mouse::mousePositionCallback = callback;

		glfwSetCursorPosCallback(Window::windowPtr, MasterCursorPositionCallback);
	}

	void Mouse::SetMouseScrollCallback(MouseScrollCallback callback)
	{
		Mouse::mouseScrollCallback = callback;
	}

	void Mouse::SetMouseEnterWindowCallback(MouseEnterWindowCallback callback)
	{
		Mouse::mouseEnterWindowCallback = callback;
	}

	InputAction Mouse::GetMouseButtonState(MouseButton button)
	{
		return (InputAction)glfwGetMouseButton(Window::windowPtr, (int)button);
	}

	glm::vec<2,int> Mouse::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Window::windowPtr, &xpos, &ypos);

		return {xpos, ypos};
	}

	void Mouse::SetMouseMode(MouseMode mode)
	{
		glfwSetInputMode(Window::windowPtr, GLFW_CURSOR, (int)mode);
	}

	float Mouse::GetScrollVariantion()
	{
		return Mouse::LastScroll;
	}

	float Mouse::GetScrollCumulativeVariation()
	{
		return Mouse::ScrollAcumulation;
	}

	void Mouse::ResetScrollVariation()
	{
		Mouse::LastScroll = 0;
	}

	void Mouse::ResetScrollCumulativeVariation()
	{
		Mouse::ScrollAcumulation = 0;
	}

	bool Mouse::IsMouseInsideWindow()
	{
		return Mouse::EnterDisplay;
	}
}
