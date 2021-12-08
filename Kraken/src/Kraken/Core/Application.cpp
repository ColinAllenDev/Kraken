#include "kepch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Kraken {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		KE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(KE_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			//  Update all Layers on LayerStack
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update Window
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		// Event dispatch handling
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KE_BIND_EVENT_FN(Application::OnWindowClosed));

		// Traverse backwards through layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			// Process layer event
			(*--it)->OnEvent(e);
			// If the event is handled, do not continue
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		m_Running = false;
		return e.GetIsClosed();
	}


}

