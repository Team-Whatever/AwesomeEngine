#pragma once
#include <memory>
#include <functional>

typedef unsigned long EventType;

//const EventType EvtData_MouseClicked::sk_EventType("84B73E90-176A-4948-80D6-2437246BFADD");

class IEventData
{
public:
	//virtual const EventType& VGetEventType(void) const = 0;
	//virtual float VGetTimeStamp(void) const = 0;
	//virtual void VSerialize(std::ostrstream& out) const = 0;
	//virtual IEventDataPtr VCopy(void) const = 0;
	//virtual const char* GetName(void) const = 0;
};

typedef std::shared_ptr<IEventData> IEventDataPtr; // smart ptr to IEventData
typedef std::function<void()> SimpleFunctionDelegate;
//typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;