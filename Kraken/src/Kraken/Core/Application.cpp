#include "kepch.h"
#include "Application.h"
#include "Input.h"

#include "Kraken/Renderer/ShaderData.h"
#include "Kraken/Renderer/Renderer.h"


namespace Kraken {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		// Create application singleton
		KE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;
		
		// Create window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(KE_BIND_EVENT_FN(Application::OnEvent));

		// Create ImGui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		// == OPENGL (TEMPORARY) == //
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7]{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Temporary shader stuff
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;	
			layout(location = 1) in vec4 a_Color;		
	
			out vec4 v_Color;
			
			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;
						
			void main() {
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			// Background color
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);
			
			Renderer::EndScene();

			//  Update all Layers on LayerStack
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// ImGui Render Loop
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();	

			// Update Window
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		// Event dispatch handling
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KE_BIND_EVENT_FN(Application::OnWindowClosed));

		// Traverse backwards through layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			// Process layer event
			(*--it)->OnEvent(e);
			// If the event is handled, do not continue
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		m_Running = false;
		return e.GetIsClosed();
	}


}

