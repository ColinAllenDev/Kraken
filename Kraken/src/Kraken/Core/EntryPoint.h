/* Kraken Engine entry point class. Defines application entry point behavior based on platform. (Currently only supports Windows) */
#pragma once

// Windows API Entry Point
#ifdef KE_PLATFORM_WINDOWS 

extern Kraken::Application* Kraken::CreateApplication();

int main(int argc, char** argv) {
	Kraken::Log::Init();
	KE_CORE_WARN("Hello Core!");
	KE_INFO("Hello Client!");
	
	auto app = Kraken::CreateApplication();
	app->Run();
	delete app;
}

#endif
