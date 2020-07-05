#pragma once

#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm.hpp>

#include <GLFW/glfw3.h>

#include "Mouse.hpp"
#include "Keyboard.hpp"

#include <functional>
#include <iostream>
#include <string>

namespace WAPI
{
	struct WindowConfigStruct
	{
		std::string windowName = "OpenGL";

		glm::vec2 windowPosition = {40, 40}, windowSize = {800, 600};

		std::uint8_t MSAA = 0;

		bool VSync = true;
	};

	typedef std::function<void(glm::vec<2,int>)> ResizeWindowCallback;
	typedef std::function<void(glm::vec<2,int>)> RepositionWindowCallback;
	typedef std::function<void(bool)> MaximizeWindowCallback;
	typedef std::function<void(bool)> MinimizeWindowCallback;
	typedef std::function<void(bool)> FocusWindowCallback;
	typedef std::function<void(void)> CloseWindowCallback;

	class Window
	{
		friend class Keyboard;
		friend class Mouse;
		friend class GUI;
	private:
		static GLFWwindow* windowPtr;

		static ResizeWindowCallback resizeWindowCallback;
		static RepositionWindowCallback repositionWindowCallback;
		static MaximizeWindowCallback maximizeWindowCallback;
		static MinimizeWindowCallback minimizeWindowCallback;
		static CloseWindowCallback closeWindowCallback;
		static FocusWindowCallback focusWindowCallback;

		static WindowConfigStruct config;

		static bool _isInit;
		static bool _isMinimized;
		static bool _isFullscreen;
		static bool _isHide;
		static bool _isFocus;

		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowPositionCallback(GLFWwindow* window, int xpos, int ypos);
		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);
		static void WindowMinimizeCallback(GLFWwindow* window, int maximized);
		static void WindowFocusCallback(GLFWwindow* window, int focused);
	public:
		static bool Create(WindowConfigStruct config);
		static void Destroy();

		static bool ShouldRun();

		static void Resize(glm::vec2 newSize);
		static glm::vec2 GetSize();

		static void SetPosition(glm::vec2 pos);
		static glm::vec2 GetPosition();

		static std::string GetName();
		static void SetName(std::string title);

		static void SetFullscreen();
		static void RemoveFullscreen(glm::vec2 newSize, glm::vec2 newPos);

		static void Hide();
		static void Show();

		static void Maximize();
		static void Minimize();
		static void RemoveMinimize();
		static void Close();

		static void RequestAttention();
		static void SwapAndPollEvents();

		static void SetResizeWindowCallback(ResizeWindowCallback callback);
		static void SetRepositionWindowCallback(RepositionWindowCallback callback);
		static void SetMaximizeWindowCallback(MaximizeWindowCallback callback);
		static void SetMinimizeWindowCallback(MinimizeWindowCallback callback);
		static void SetCloseWindowCallback(CloseWindowCallback callback);
		static void SetFocusWindowCallback(FocusWindowCallback callback);

		static void EnableVSync();
		static void DisableVSync();

		static bool isMinimized();
		static bool isHide();
		static bool isFullscreen();
		static bool isInFocus();

		static glm::vec2 GetScreenLimits();
	};
}
