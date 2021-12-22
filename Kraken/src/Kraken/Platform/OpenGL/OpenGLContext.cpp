#include "kepch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Kraken {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		KE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	/* Initialize GLFW and make this window context current.
	 * Load OpenGL (GLAD) and assert that it was succesfull.
	 */
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	/* Swap chain operations in OpenGL using GLFW
	 */
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}