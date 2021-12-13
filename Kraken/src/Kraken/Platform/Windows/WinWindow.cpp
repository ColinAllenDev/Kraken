#include "kepch.h"

#include <glad/glad.h>

#include "WinWindow.h"

#include "Kraken/Events/WindowEvent.h"
#include "Kraken/Events/KeyEvent.h"
#include "Kraken/Events/MouseEvent.h"

namespace Kraken {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc) {
		KE_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WinWindow(props);
	}

	WinWindow::WinWindow(const WindowProps& props) {
		Init(props);
	}

	WinWindow::~WinWindow() {
		Shutdown();
	}

	void WinWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		KE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// Initialize GLFW if it hasn't been already
		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			// Check if glfw was initialized succesfully, otherwise break
			KE_CORE_ASSERT(success, "Could not initialize GLFW!");

			// Set Error Callback
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		// Make GLFW window context
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// Load OpenGL (GLAD)
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to initialize GLAD!");

		// Window properties
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		/// ==== GLFW CALLBACKS ==== ///
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			// Return GLFW window pointer as a WindowData pointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			// Create and dispatch event
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event(true);
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action) {
				case GLFW_PRESS : {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					return;
				}
				case GLFW_RELEASE : {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					return;
				}					
				case GLFW_REPEAT : {
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					return;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action) {
				case GLFW_PRESS : {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					return;
				}
				case GLFW_RELEASE : {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					return;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xPos, yPos);
			data.EventCallback(event);
		});

	}

	void WinWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	// Main window update loop
	void WinWindow::OnUpdate() {
		// Swap front/back buffers
		glfwSwapBuffers(m_Window);
		// Proccess event callbacks
		glfwPollEvents();
	}

	void WinWindow::SetVSync(bool enabled) {
		// (X=0): FPS has no limit.
		// (X=1): FPS would be set to monitor's refresh rate.
		// (X=2): FPS would be half monitors refresh rate
		if (enabled)
			glfwSwapInterval(1); 
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const {
		return m_Data.VSync;
	}
}