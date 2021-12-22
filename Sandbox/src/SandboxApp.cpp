#include <Kraken.h>
#include <imgui/imgui.h>

class ExampleLayer : public Kraken::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnImGuiRender() override {
		
	}
};

class Sandbox : public Kraken::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Kraken::Application* Kraken::CreateApplication() {
	return new Sandbox();
}