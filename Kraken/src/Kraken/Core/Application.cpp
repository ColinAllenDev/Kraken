#include "kepch.h"
#include "Application.h"

#include "Kraken/Core/Log.h"
#include "Kraken/Events/WindowEvent.h"

namespace Kraken {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run() {
		while (true) {
			m_Window->OnUpdate();
		}
	}
}

