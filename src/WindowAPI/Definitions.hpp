#pragma once

namespace WAPI
{
	enum class InputModifier
	{
		SHIFT = GLFW_MOD_SHIFT,
		CONTROL = GLFW_MOD_CONTROL,
		ALT = GLFW_MOD_ALT,
		SUPER = GLFW_MOD_SUPER,
		CAPS_LOCK = GLFW_MOD_CAPS_LOCK,
		NUM_LOCK = GLFW_MOD_NUM_LOCK
	};

	enum class InputAction
	{
		RELEASE = GLFW_RELEASE,
		PRESS = GLFW_PRESS,
		REPEAT = GLFW_REPEAT,
		NONE = -1
	};
}
