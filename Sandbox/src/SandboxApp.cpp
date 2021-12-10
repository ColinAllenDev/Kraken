#include <Kraken.h>

class ExampleLayer : public Kraken::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		if (Kraken::Input::IsKeyPressed(KE_KEY_TAB))
			KE_TRACE("Tab key is pressed!");
	}

	void OnEvent(Kraken::Event& event) override {
		// KE_TRACE("{0}", event);
	}
};

class Sandbox : public Kraken::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		//PushOverlay(new Kraken::ImGuiLayer());
	}

	~Sandbox() {}
};

Kraken::Application* Kraken::CreateApplication() {
	return new Sandbox();
}