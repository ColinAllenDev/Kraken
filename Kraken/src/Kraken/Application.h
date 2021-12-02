/* Kraken::Application - Client application framework */

#pragma once
#include "Core.h"

namespace Kraken {

	class KRAKEN_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


