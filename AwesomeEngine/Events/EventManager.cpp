#include "EventManager.h"

namespace AwesomeEngine
{
	EventManager::EventManager(const char * pName, bool setAsGlobal)
	{
	}

	bool EventManager::VAddListener(const SimpleFunctionDelegate & eventDelegate, const EventType & type)
	{
		return false;
	}
	bool EventManager::VRemoveListener(const SimpleFunctionDelegate & eventDelegate, const EventType & type)
	{
		return false;
	}
	bool EventManager::VTriggerEvent(const IEventDataPtr & pEvent) const
	{
		for (auto& listener : m_eventListeners)
		{
			
		}
		return false;
	}
	bool EventManager::VQueueEvent(const IEventDataPtr & pEvent)
	{
		return false;
	}
	bool EventManager::VAbortEvent(const EventType & type, bool allOfType)
	{
		return false;
	}
	bool EventManager::VTickVUpdate(unsigned long maxMillis)
	{
		return false;
	}
}