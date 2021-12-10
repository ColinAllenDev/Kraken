#include "kepch.h"
#include "WindowsInput.h"

#include "Kraken/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Kraken {
	// Create this Input instance as WindowsInput
	Input* Input::s_Instance = new WindowsInput();

	bool Kraken::WindowsInput::IsKeyPressedImpl(int keyCode) {
		// Retrieve GLFWwindow pointer from our Applications' Window.
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Get key state from GLFW window
		auto state = glfwGetKey(window, keyCode);
		
		// If key is pressed OR repeated, return true
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		
		return state = GLFW_PRESS;
	}
	
	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {(float)xPos, (float)yPos};
	}

	float WindowsInput::GetMouseXImpl() {
		auto [x, y] = GetMousePositionImpl(); // C++17 tuples are coooool
		return x;
	}
	
	float WindowsInput::GetMouseYImpl() {
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}


