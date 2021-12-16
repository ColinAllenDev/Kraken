#pragma once
#include "Kraken/Core/Layer.h"
#include "Kraken/Events/MouseEvent.h"
#include "Kraken/Events/KeyEvent.h"
#include "Kraken/Events/WindowEvent.h"

namespace Kraken {
	class KRAKEN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		/* Called when Layer is attached to layer stack. 
		 * Can be thought of like a Layer constructor.
		 */
		virtual void OnAttach();
		
		/* Called when Layer is attached to layer stack.
		 * Can be thought of like a Layer destructor.
		 */
		virtual void OnDetach();

		/* Begins the ImGui Render process. Starts a new ImGui frame 
		 * which is ended with either ImGui::Render() or ImGui::EndFrame()
		 */
		void Begin();

		/* Does any kind of ImGui Rendering, process sits in between
		 * ImGui::BeginRender() and ImGui::EndRender()
		 */
		virtual void OnImGuiRender();

		/* Ends the ImGui Render process. Renders the frame that was
		 * processed during OnImGuiRender(). 
		 */
		void End();
	private:
		float m_Time = 0.0f;
	};
}
