/* Kraken::KeyEvent [Event] - Classes representing keyboard input events. */

#pragma once

#include "Event.h"

namespace Kraken {
	class KRAKEN_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected: // Cannot be constructed outside classes that derive this
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class KRAKEN_API KeyPressedEvent : public KeyEvent {
	public:
		// repeatCount handles the repeating of events by defining the length at which we hold a key down.
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		};

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KRAKEN_API KeyReleasedEvent : public KeyEvent {
	public:
		// repeatCount handles the repeating of events by defining the length at which we hold a key down.
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		};

		EVENT_CLASS_TYPE(KeyReleased)
	};
}