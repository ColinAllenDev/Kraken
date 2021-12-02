#include <Kraken.h>

class Sandbox : public Kraken::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Kraken::Application* Kraken::CreateApplication() {
	return new Sandbox();
}