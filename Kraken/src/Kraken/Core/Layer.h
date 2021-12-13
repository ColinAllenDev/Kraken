/* Layer.h - Implementation of engine layers. These layers are used on the LayerStack to process events, handle rendering, etc. */
#pragma once

#include "Kraken/Core/Base.h"
#include "Kraken/Events/Event.h"

namespace Kraken {
	class KRAKEN_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		
		/// Called upon when attaching layer to the LayerStack
		virtual void OnAttach() {}
		/// Called upon when detaching layer to the LayerStack
		virtual void OnDetach() {}
		/// Called during update loop
		virtual void OnUpdate() {}
		
		virtual void OnImGuiRender() {}
		
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}