#pragma once
#include "IEventData.h"
#include "IEventManage.h"
#include <list>
#include <map>

namespace AwesomeEngine
{
	const unsigned int EVENTMANAGER_NUM_QUEUES = 2;
	class EventManager : IEventManager
	{
		//static EventManager Instance;

	public:
		explicit EventManager(const char* pName, bool setAsGlobal);
		virtual ~EventManager() {}


		typedef std::list<SimpleFunctionDelegate> EventListenerList;
		typedef std::map<EventType, EventListenerList> EventListenerMap;
		typedef std::list<IEventDataPtr> EventQueue;
		EventListenerMap m_eventListeners;
		EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
		int m_activeQueue; // index of actively processing queue; events
		// enque to the opposing queue 

	public:
		virtual bool VAddListener(const SimpleFunctionDelegate& eventDelegate, const EventType& type);
		virtual bool VRemoveListener(const SimpleFunctionDelegate& eventDelegate, const EventType& type);
		virtual bool VTriggerEvent(const IEventDataPtr& pEvent)const;
		virtual bool VQueueEvent(const IEventDataPtr& pEvent);
		virtual bool VAbortEvent(const EventType& type, bool allOfType = false);
		virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE);

	};
}