#include <Kraken.h>
#include <imgui/imgui.h>

class ExampleLayer : public Kraken::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnImGuiRender() override {
		ImGui::Begin("Sandbox Test"); // Begin rendering
		ImGui::Text("Hello World from Client!");
		ImGui::End(); // End Rendering
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