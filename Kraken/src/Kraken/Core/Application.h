/* Kraken::Application - Client application framework */

#pragma once
#include "Base.h"
#include "Kraken/Core/LayerStack.h"
#include "Kraken/Events/Event.h"
#include "Kraken/Core/Window.h"
#include "Kraken/Core/Log.h"
#include "Kraken/Events/ApplicationEvent.h"
#include "Kraken/Events/WindowEvent.h"

#include "Kraken/ImGui/ImGuiLayer.h"

namespace Kraken {

	class KRAKEN_API Application {
	public:
		Application();
		virtual ~Application();

		/**
	     * Main engine loop. Updates all layers on the LayerStack
		 * as well as any Windows. 
		 */
		void Run();

		/**
		 * Proccess events as they arrive. 
		 * @param e - Reference to the Event object.
		 */
		void OnEvent(Event& e);

		/**
		 * Push Layer to end of LayerStack.
		 * @param layer - Pointer to Layer object.
		 */
		void PushLayer(Layer* layer);
		
		/**
		* Push Overlay to front of LayerStack.
		* @param overlay - Pointer to Layer object.
		*/
		void PushOverlay(Layer* overlay);

		/**
		 * @return reference to the Window object.
		 */
		inline Window& GetWindow() { return *m_Window; }
		
		/**
		 * @return reference to the Application instance.
		 */
		inline static Application& Get() { return *s_Instance; }
	private:
		bool m_Running = true;
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in client application
	Application* CreateApplication();
}


