/* Kraken::Event - Core event handler class, defines event types and categories as well as 
 * functionality for receiving information about events as well as dispatching them.
 * Currently uses 'blocking' events. Buffer events and event bus to be implemented in the future.
 */

#pragma once
#include "kepch.h"
#include "Kraken/Core/Base.h"

namespace Kraken {

	/* Events in Kraken are blocking (events are dispatched as they occur)
	   TODO: Buffer events in an event bus and process them during the
	   'event' part of the update stage. */

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// BIT(x) bit-shift macro used so a single event can belong to multiple categories.
	// This allows for bitwise or operator usage: EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryWindow			= BIT(1),
		EventCategoryInput			= BIT(2),
		EventCategoryKeyboard		= BIT(3),
		EventCategoryMouse			= BIT(4),
		EventCategoryMouseButton	= BIT(5)
	};

	// Implements EventType information using single macro rather than implementing name, non-member type, and virtual override 'getter'.
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								   									virtual EventType GetEventType() const override { return GetStaticType(); }\
								   									virtual const char* GetName() const override { return #type; }
	
	// Implements EventCategoryType information using single macro.
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	
	class KRAKEN_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsHandled() { return m_Handled; }
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		// Has an event been handled or not?
		bool m_Handled = false; 
	};

	class EventDispatcher {
		// Standard event function returns a bool representing if
		// the type of function matches the event function type.
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		// Create instance of dispatcher with received event
		EventDispatcher(Event& event) : m_Event(event) {}

		// Call dispatch function with EventFn
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			// Check if the type of incoming event = the static type of the template used in definition
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// Sets m_Handled to output of m_Event and returns true
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			} 
			return false;
		}
	private:
		Event& m_Event;
	};

	// Operator Overload [<<] in Event Class for logging
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}