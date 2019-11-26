#pragma once
#include <list>
#include <map>
#include <memory>
#include "IEventData.h"
#include "IEventManage.h"

namespace AwesomeEngine
{
	const unsigned int EVENTMANAGER_NUM_QUEUES = 2;
	class EventManager //: IEventManager
	{
	public:
		static EventManager& GetInstance()
		{
			static EventManager Instance;
			return Instance;
		}

	public:
		virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
		virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EnumEventType& type);
		
		virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
		virtual bool VRemoveListener(const EventListenerDelegate & eventDelegate, const EnumEventType & type);

		//virtual bool VTriggerEvent(const IEventDataPtr& pEvent)const;
		virtual bool VTriggerEvent(const EnumEventType pEvent, const EventParam param);

		virtual bool VQueueEvent(const IEventDataPtr& pEvent);
		virtual bool VAbortEvent(const EventType& type, bool allOfType = false);
		virtual bool VTickVUpdate(unsigned long maxMillis = IEventManager::kINFINITE);

	private:
		typedef std::list<EventListenerDelegate> EventListenerList;
		typedef std::map<EventType, EventListenerList> EventListenerMap;
		typedef std::list<IEventDataPtr> EventQueue;
		EventListenerMap m_eventListeners;
		EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
		int m_activeQueue; // index of actively processing queue; events
		// enque to the opposing queue 

	};
}