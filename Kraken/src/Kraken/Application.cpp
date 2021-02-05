#include "Application.h"
#include "Kraken/Events/ApplicationEvent.h"
#include "Kraken/Log.h"


namespace Kraken {
	Application::Application() {}
	Application::~Application() {}
	void Application::Run() {
		// Test WindowResize event
		WindowResizeEvent wre(1280, 720);
		KR_TRACE(wre);
		
		while (true);
	}
}

