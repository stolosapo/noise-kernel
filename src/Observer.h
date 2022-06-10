#ifndef Observer_h__
#define Observer_h__

#include <vector>
#include <map>
#include <string>
#include <signal.h>

using namespace std;

namespace NoiseKernel
{
    class Event;

    class EventArgs
    {
    public:
        EventArgs();
        virtual ~EventArgs();
    };

    typedef void (*EventDelegate)(void* sender, EventArgs* e);

    class EventHandler
    {
    public:
        EventHandler();
        virtual ~EventHandler();

        virtual void onEvent(void* sender, EventArgs* e) = 0;
    };

    class Event
    {
    public:
        Event();
        virtual ~Event();

        virtual void addEventHandler(EventHandler* eventHandler);
        virtual void addEventHandler(EventDelegate delegate);

        virtual void removeEventHandler(EventHandler* eventHandler);
        virtual void removeEventHandler(EventDelegate delegate);

        virtual void raise(void* sender, EventArgs* e);

        Event& operator+=(EventHandler* eventHandler);
        Event& operator+=(EventDelegate delegate);

        Event& operator-=(EventHandler* eventHandler);
        Event& operator-=(EventDelegate delegate);

    private:
        vector<EventHandler*> eventHandlers;
        vector<EventDelegate> delegates;
    };
}

#endif // Observer_h__
