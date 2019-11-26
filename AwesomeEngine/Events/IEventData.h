#pragma once
#include <memory>
#include <functional>
#include <strstream>
#include "FastDelegate.h"

typedef unsigned long EventType;

enum EnumEventType
{
	Event_Mouse_Moved,
	Event_Mouse_Clicked,
	Event_CharKey_Pressed,
};

//const EventType EvtData_MouseClicked::sk_EventType("84B73E90-176A-4948-80D6-2437246BFADD");

class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPtr; // smart ptr to IEventData
class IEventData
{
public:
	virtual const EventType& VGetEventType(void) const = 0;
	virtual float VGetTimeStamp(void) const = 0;
	virtual void VSerialize(std::ostrstream& out) const = 0;
	virtual IEventDataPtr VCopy(void) const = 0;
	virtual const char* GetName(void) const = 0;

};

struct EventParam
{
	int param1;
	int param2;
};


typedef std::function<void()> SimpleVoidFunctionDelegate;
typedef std::function<void(int)> SimpleVoidFunctionDelegate1;
typedef std::function<void(int, int)> SimpleVoidFunctionDelegate2;
typedef std::function<void(int, int, int)> SimpleVoidFunctionDelegate3;

typedef fastdelegate::FastDelegate1<EventParam> EventListenerDelegate;

class MouseEvent
{
	//Register()
	//{
	//	EventManager.Instance.AddListender(this, EventType::MouseClicked, &MouseEvent::MouseClicked);
	//}

	//void MouseClicked( bool isLeft, int x, int y)
	//{

	//}
};