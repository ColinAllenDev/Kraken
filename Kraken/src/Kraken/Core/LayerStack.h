/* LayerStack.h - Implements a wrapper for a vector of layers to represent a stack structure.
 * Layers will be pushed to and popped from the first half (start) of the vector.
 * Overlays will be pushed to and popped from second half (end) of the vector.
 * The LayerStack is processed from end to front in order to process overlays last.
 */
#pragma once

#include "Kraken/Core/Base.h"
#include "Layer.h"

#include <vector>

namespace Kraken {
	class KRAKEN_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin();  }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:	
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
