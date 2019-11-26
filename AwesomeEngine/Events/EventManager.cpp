#include "EventManager.h"
#include "Timer.h"

namespace AwesomeEngine
{
	bool EventManager::VAddListener(const EventListenerDelegate & eventDelegate, const EnumEventType & type)
	{
		return VAddListener(eventDelegate, (EventType)type);
	}

	bool EventManager::VAddListener(const EventListenerDelegate & eventDelegate, const EventType & type)
	{
		// this will find or create the entry
		EventListenerList& eventListenerList = m_eventListeners[type];
		for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it) {
			if (eventDelegate == (*it)) {
				return false;
			}
		}
		eventListenerList.push_back(eventDelegate);
		return true;
	}

	bool EventManager::VRemoveListener(const EventListenerDelegate & eventDelegate, const EnumEventType & type)
	{
		return VRemoveListener(eventDelegate, (EventType)type);
	}

	bool EventManager::VRemoveListener(const EventListenerDelegate & eventDelegate, const EventType & type)
	{
		bool success = false;
		auto findIt = m_eventListeners.find(type);
		if (findIt != m_eventListeners.end()) {
			EventListenerList& listeners = findIt->second;
			for (auto it = listeners.begin(); it != listeners.end(); ++it) {
				if (eventDelegate == (*it)) {
					listeners.erase(it);
					success = true;
					// We don¡¯t need to continue because it should be impossible
					// for the same delegate function to be registered for the same
					// event more than once.
					break;
				}
			}
		}
		return success;
	}

	//bool EventManager::VTriggerEvent(const IEventDataPtr & pEvent) const
	bool EventManager::VTriggerEvent(const EnumEventType pEvent, const EventParam param)
	{
		auto findIt = m_eventListeners.find(pEvent);
		if (findIt != m_eventListeners.end()) {
			EventListenerList& listeners = findIt->second;
			for (auto it = listeners.begin(); it != listeners.end(); ++it) {
				(*it)(param);
			}

		}

		return false;
	}

	bool EventManager::VQueueEvent(const IEventDataPtr & pEvent)
	{
		auto findIt = m_eventListeners.find(pEvent->VGetEventType());
		if (findIt != m_eventListeners.end()) {
			m_queues[m_activeQueue].push_back(pEvent);
			return true;
		}
		else {
			return false;
		}
	}

	bool EventManager::VAbortEvent(const EventType & inType, bool allOfType)
	{
		bool success = false;
		EventListenerMap::iterator findIt = m_eventListeners.find(inType);
		if (findIt != m_eventListeners.end()) {
			EventQueue& eventQueue = m_queues[m_activeQueue];
			auto it = eventQueue.begin();
			while (it != eventQueue.end()) {
				// Removing an item from the queue will invalidate the iterator, so
				// have it point to the next member.All work inside this loop will be
				// done using thisIt.
					auto thisIt = it;
				++it;
				if ((*thisIt)->VGetEventType() == inType) {
					eventQueue.erase(thisIt);
					success = true;
					if (!allOfType)
						break;
				}
			}
		}
		return success;
	}
	bool EventManager::VTickVUpdate(unsigned long maxMillis)
	{
		//unsigned long currMs = GetTickCount();
		//unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ?
		//	(IEventManager::kINFINITE) : (currMs + maxMillis));
		//// swap active queues and clear the new queue after the swap
		//int queueToProcess = m_activeQueue;
		//m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
		//m_queues[m_activeQueue].clear();
		//// Process the queue
		//while (!m_queues[queueToProcess].empty()) {
		//	// pop the front of the queue
		//	IEventDataPtr pEvent = m_queues[queueToProcess].front();
		//	m_queues[queueToProcess].pop_front();
		//	const EventType& eventType = pEvent->VGetEventType();

		//	// find all the delegate functions registered for this event
		//	auto findIt = m_eventListeners.find(eventType);
		//	if (findIt != m_eventListeners.end()) {
		//		const EventListenerList& eventListeners = findIt->second;
		//		// call each listener
		//		for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it) {
		//			EventListenerDelegate listener = (*it);
		//			listener(pEvent);
		//		}
		//	}

		//	// check to see if time ran out
		//	currMs = GetTickCount();
		//	if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs) {
		//		break;
		//	}
		//	// If we couldn¡¯t process all of the events, push the remaining
		//	// events to the new active queue.Note: To preserve sequencing, go
		//	// back - to - front, inserting them at the head of the active queue.
		//	bool queueFlushed = (m_queues[queueToProcess].empty());
		//	if (!queueFlushed) {
		//		while (!m_queues[queueToProcess].empty()) {
		//			IEventDataPtr pEvent = m_queues[queueToProcess].back();
		//			m_queues[queueToProcess].pop_back();
		//			m_queues[m_activeQueue].push_front(pEvent);
		//		}
		//	}
		//	return queueFlushed;
		//}
		return false;
	}
}