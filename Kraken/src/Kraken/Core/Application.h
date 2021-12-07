/* Kraken::Application - Client application framework */

#pragma once
#include "Base.h"
#include "Kraken/Events/Event.h"
#include "Kraken/Core/Window.h"
#include "Kraken/Core/Log.h"
#include "Kraken/Events/ApplicationEvent.h"
#include "Kraken/Events/WindowEvent.h"

namespace Kraken {

	class KRAKEN_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


