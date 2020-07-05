#include "Window.hpp"

namespace WAPI
{
    GLFWwindow* Window::windowPtr = nullptr;

	WindowConfigStruct Window::config;

	ResizeWindowCallback Window::resizeWindowCallback = nullptr;
	RepositionWindowCallback Window::repositionWindowCallback = nullptr;
	MaximizeWindowCallback Window::maximizeWindowCallback = nullptr;
	MinimizeWindowCallback Window::minimizeWindowCallback = nullptr;
	CloseWindowCallback Window::closeWindowCallback = nullptr;
	FocusWindowCallback Window::focusWindowCallback = nullptr;

	bool Window::_isInit = false;
	bool Window::_isFullscreen = false;
	bool Window::_isHide = false;
	bool Window::_isMinimized = false;
	bool Window::_isFocus = true;

	void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Window::config.windowSize = {width, height};

		if(Window::resizeWindowCallback != nullptr) Window::resizeWindowCallback({width, height});

		glViewport(0, 0, width, height);
	}

	void Window::WindowCloseCallback(GLFWwindow* window)
	{
		if(Window::closeWindowCallback != nullptr) Window::closeWindowCallback();
	}

	void Window::WindowPositionCallback(GLFWwindow* window, int xpos, int ypos)
	{
		Window::config.windowPosition = glm::vec2(xpos, ypos);

		if(Window::repositionWindowCallback != nullptr) Window::repositionWindowCallback({ xpos, ypos });
	}

	void Window::WindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		if(Window::maximizeWindowCallback != nullptr) Window::maximizeWindowCallback((bool)maximized);
	}

	void Window::WindowMinimizeCallback(GLFWwindow* window, int minimized)
	{
		Window::_isMinimized = (bool)minimized;

		if(Window::minimizeWindowCallback != nullptr) Window::minimizeWindowCallback((bool)minimized);
	}

	void Window::WindowFocusCallback(GLFWwindow* window, int focused)
	{
		Window::_isFocus = (bool)focused;

		if(Window::focusWindowCallback != nullptr) Window::focusWindowCallback((bool)focused);
	}

	bool Window::Create(WindowConfigStruct config)
	{
		if(Window::_isInit) return false;

		Window::_isInit = true;
		Window::config = config;

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		bool HaveMSAA = (config.MSAA > 0);

		if(HaveMSAA) glfwWindowHint(GLFW_SAMPLES, config.MSAA);

		Window::windowPtr = glfwCreateWindow(config.windowSize.x, config.windowSize.y, config.windowName.c_str(), NULL, NULL);

		if(Window::windowPtr == NULL)
		{
			return false;
		}

		glfwMakeContextCurrent(Window::windowPtr);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwDestroyWindow(Window::windowPtr);

			return false;
		}

		glfwSetWindowPos(Window::windowPtr, config.windowPosition.x, config.windowPosition.y);
		glfwSetFramebufferSizeCallback(Window::windowPtr, WindowResizeCallback);
		glfwSetWindowCloseCallback(Window::windowPtr, WindowCloseCallback);
		glfwSetWindowPosCallback(Window::windowPtr, WindowPositionCallback);
		glfwSetWindowMaximizeCallback(Window::windowPtr, WindowMaximizeCallback);
		glfwSetWindowIconifyCallback(Window::windowPtr, WindowMinimizeCallback);
		glfwSetWindowFocusCallback(Window::windowPtr, WindowFocusCallback);

		if(HaveMSAA) glEnable(GL_MULTISAMPLE);

		Keyboard::Init();
		Mouse::Init();

		return true;
	}

	void Window::Destroy()
	{
		if(!Window::_isInit) return;

		Window::_isInit = false;

		glfwDestroyWindow(Window::windowPtr);

		glfwTerminate();
	}

	bool Window::ShouldRun()
	{
		if(!Window::_isInit) return true;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		return !glfwWindowShouldClose(Window::windowPtr);
	}

	void Window::Resize(glm::vec2 newSize)
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		glfwSetWindowSize(Window::windowPtr, newSize.x, newSize.y);

		int x, y;

		glfwGetWindowSize(Window::windowPtr, &x, &y);

		Window::config.windowSize.x = x;
		Window::config.windowSize.y = y;
	}

	glm::vec2 Window::GetSize()
	{
		return Window::config.windowSize;
	}

	void Window::SetPosition(glm::vec2 pos)
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		glfwSetWindowPos(Window::windowPtr, pos.x, pos.y);

		int x, y;

		glfwGetWindowPos(Window::windowPtr, &x, &y);

		Window::config.windowPosition.x = x;
		Window::config.windowPosition.y = y;
	}

	glm::vec2 Window::GetPosition()
	{
		return Window::config.windowPosition;
	}

	std::string Window::GetName()
	{
		return Window::config.windowName;
	}

	void Window::SetName(std::string title)
	{
		if(!Window::_isInit) return;

		glfwSetWindowTitle(Window::windowPtr, title.c_str());
	}

	void Window::SetFullscreen()
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwSetWindowMonitor(Window::windowPtr, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

		int x, y;

		glfwGetWindowSize(Window::windowPtr, &x, &y);

		Window::config.windowSize.x = x;
		Window::config.windowSize.y = y;

		glfwGetWindowPos(Window::windowPtr, &x, &y);

		Window::config.windowPosition.x = x;
		Window::config.windowPosition.y = y;

		Window::_isFullscreen = true;
	}

	void Window::RemoveFullscreen(glm::vec2 newSize, glm::vec2 newPos)
	{
		if(!Window::_isInit || !Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		glfwSetWindowMonitor(Window::windowPtr, NULL, 0, 0, newSize.x, newSize.y, GLFW_DONT_CARE);

		int x, y;
		glfwGetWindowSize(Window::windowPtr, &x, &y);

		Window::config.windowSize.x = x;
		Window::config.windowSize.y = y;

		Window::_isFullscreen = false;

		Window::SetPosition(newPos);
	}

	void Window::Hide()
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		glfwHideWindow(Window::windowPtr);

		Window::_isHide = true;
	}

	void Window::Show()
	{
		if(!Window::_isInit || Window::_isFullscreen || !Window::_isHide || Window::_isMinimized) return;

		glfwShowWindow(Window::windowPtr);

		Window::_isHide = false;
	}

	void Window::Maximize()
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || Window::_isMinimized) return;

		glfwMaximizeWindow(Window::windowPtr);

		int x, y;

		glfwGetWindowSize(Window::windowPtr, &x, &y);

		Window::config.windowSize.x = x;
		Window::config.windowSize.y = y;

		glfwGetWindowPos(Window::windowPtr, &x, &y);

		Window::config.windowPosition.x = x;
		Window::config.windowPosition.y = y;
	}

	void Window::Minimize()
	{
		if(!Window::_isInit || Window::_isHide || Window::_isMinimized) return;

		glfwIconifyWindow(Window::windowPtr);

		Window::_isMinimized = true;
	}

	void Window::RemoveMinimize()
	{
		if(!Window::_isInit || Window::_isFullscreen || Window::_isHide || !Window::_isMinimized) return;

		glfwRestoreWindow(Window::windowPtr);

		Window::_isMinimized = false;
	}

	void Window::Close()
	{
		if(!Window::_isInit) return;

		glfwSetWindowShouldClose(Window::windowPtr, 1);
	}

	void Window::RequestAttention()
	{
		if(Window::_isFullscreen || Window::_isHide) return;

		glfwRequestWindowAttention(Window::windowPtr);
	}

	void Window::SwapAndPollEvents()
	{
		Mouse::LastScroll = 0;
		Mouse::ScrollAcumulation = 0;

		if(!Window::_isInit) return;

		glfwSwapBuffers(Window::windowPtr);
		glfwPollEvents();
	}

	void Window::SetResizeWindowCallback(ResizeWindowCallback callback)
	{
		Window::resizeWindowCallback = callback;
	}

	void Window::SetRepositionWindowCallback(RepositionWindowCallback callback)
	{
		Window::repositionWindowCallback = callback;
	}

	void Window::SetMaximizeWindowCallback(MaximizeWindowCallback callback)
	{
		Window::maximizeWindowCallback = callback;
	}

	void Window::SetMinimizeWindowCallback(MinimizeWindowCallback callback)
	{
		Window::minimizeWindowCallback = callback;
	}

	void Window::SetCloseWindowCallback(CloseWindowCallback callback)
	{
		Window::closeWindowCallback = callback;
	}

	void Window::SetFocusWindowCallback(FocusWindowCallback callback)
	{
		Window::focusWindowCallback = callback;
	}

	void Window::EnableVSync()
	{
		glfwSwapInterval(1);
	}

	void Window::DisableVSync()
	{
		glfwSwapInterval(0);
	}

	bool Window::isMinimized()
	{
		return Window::_isMinimized;
	}

	bool Window::isHide()
	{
		return Window::_isHide;
	}

	bool Window::isFullscreen()
	{
		return Window::_isFullscreen;
	}

	bool Window::isInFocus()
	{
		return Window::_isFocus;
	}

	glm::vec2 Window::GetScreenLimits()
	{
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        return {mode->width, mode->height};
	}
}
