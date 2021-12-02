#pragma once

#include "Event.h"

namespace Kraken {
	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMovedEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)
	private:
		float m_XOffset, m_YOffset;
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(float xSize, float ySize) : m_Width(xSize), m_Height(ySize) {}

		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		float m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent(bool closed) : m_Closed(closed) {}

		inline bool GetIsClosed() const { return m_Closed; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent: " << m_Closed;
			return ss.str();
		}

	private:
		bool m_Closed;
	};

	// TODO: Implement WindowFocusEvent and WindowLostFocusEvent
}
