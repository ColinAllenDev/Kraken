#include "kepch.h"
#include "LayerStack.h"

namespace Kraken {
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) 
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		// Using vector::emplace to insert a new element into m_Layers directly before m_LayerInsert
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		// vector::emplace_back to insert a new element into the back of m_Layers
		// Note: Overlays will always be placed/processed after Layers in the stack
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); // probably inefficient
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}