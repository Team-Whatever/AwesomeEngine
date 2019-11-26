#pragma once
#include "IEventData.h"

namespace AwesomeEngine
{
	class IEventManager {
	public:
		enum eConstants { kINFINITE = 0xffffffff };

		// Registers a delegate function that will get called when the
		// event type is triggered. Returns true if successful, false if not.
		virtual bool VAddListener(const SimpleVoidFunctionDelegate& eventDelegate, const EventType& type) = 0;

		// Removes a delegate/event type pairing from the internal tables.
		// Returns false if the pairing was not found.
		virtual bool VRemoveListener(const SimpleVoidFunctionDelegate& eventDelegate, const EventType& type) = 0;

		// Fires off event NOW. This bypasses the queue entirely and
		// immediately calls all delegate functions registered for the event.
		virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;

		// Fires off event. This uses the queue and will call the
		// delegate function on the next call to VTickVUpdate(), assuming there's enough time.
		virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;

		// Finds the next-available instance of the named event type and
		// remove it from the processing queue.This may be done up to the
		// point that it is actively being processed ... e.g.: is safe to
		// happen during event processing itself.
		// If allOfType is true, then all events of that type are
		// cleared from the input queue. Returns true if the event was found
		// and removed, false otherwise
		virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;

		// Allows for processing of any queued messages, optionally
		// specify a processing time limit so that the event processing does
		// not take too long.Note the danger of using this artificial
		// limiter is that all messages may not in fact get processed.
		// returns true if all messages ready for processing were completed, false otherwise(e.g.timeout).
		virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE) = 0;

		// Getter for the main global event manager. This is the event
		// manager that is used by the majority of the engine, though you
		// are free to define your own as long as you instantiate it with
		// setAsGlobal set to false.It is not valid to have more than one global event manager.
		static IEventManager* Get(void);
	};
}