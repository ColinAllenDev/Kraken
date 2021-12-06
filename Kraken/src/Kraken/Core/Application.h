/* Kraken::Application - Client application framework */

#pragma once
#include "Base.h"
#include "Kraken/Events/Event.h"
#include "Kraken/Core/Window.h"

namespace Kraken {

	class KRAKEN_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


