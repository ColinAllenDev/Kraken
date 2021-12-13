#include "kepch.h"
#include "Application.h"
#include "Input.h"

#include <glad/glad.h>

namespace Kraken {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		// Create application singleton
		KE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;
		
		// Create window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(KE_BIND_EVENT_FN(Application::OnEvent));

		// Create ImGui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			//  Update all Layers on LayerStack
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();	

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

