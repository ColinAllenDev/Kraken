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

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnImGuiRender();

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
