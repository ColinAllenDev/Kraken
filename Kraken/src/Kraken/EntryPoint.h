#pragma once

/* Windows API Entry Point*/
#ifdef KR_PLATFORM_WINDOWS 

extern Kraken::Application* Kraken::CreateApplication();

int main(int argc, char** argv) {
	auto app = Kraken::CreateApplication();
	app->Run();
	delete app;
}

#endif
