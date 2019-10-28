#pragma once
#include <functional>
#include <list>
using namespace std;

namespace EZEvent{
    template<typename EventParam> class Event;

    template<typename EventParam> class EventTrigger{
    public:
        friend Event<EventParam>;
        void Invoke(const EventParam& param) const;
    private:
        Event<EventParam>* binding_event = NULL;
    };

    template<typename EventParam> class Event{
    public:
        //typedef void(*Listener)(const EventParam&);
        typedef std::function<void(const EventParam&)> Listener;
        friend EventTrigger<EventParam>;
        void BindTrigger(EventTrigger<EventParam>* trigger);
        void ClearListeners();
        void AddListener(const Listener& listener);
        void RemoveListener(const Listener& listener);
        Event<EventParam>& operator += (const Listener& listener);
        Event<EventParam>& operator -= (const Listener& listener);
        Event<EventParam>& operator = (const Event<EventParam>& event) = delete;
    private:
        bool trigger_binded = false;
        void InnerInvoke(const EventParam& param) const;
        list<Event<EventParam>::Listener> listeners;
    };

    template<typename EventParam> void EventTrigger<EventParam>::Invoke(const EventParam& param) const{
        if(binding_event) binding_event->InnerInvoke(param);
    }

    template<typename EventParam> void Event<EventParam>::BindTrigger(EventTrigger<EventParam>* trigger){
        if(trigger_binded) return;
        trigger->binding_event = this;
        trigger_binded = true;
    }

    template<typename EventParam> void Event<EventParam>::ClearListeners(){
        listeners.clear();
    }

    template<typename EventParam> void Event<EventParam>::InnerInvoke(const EventParam& param) const{
        for(auto& listener : listeners)
            listener(param);
    }

    template<typename EventParam> void Event<EventParam>::AddListener(const Event<EventParam>::Listener& listener){
        listeners.push_back(listener);
    }

    template<typename EventParam> void Event<EventParam>::RemoveListener(const Event<EventParam>::Listener& listener){
        listeners.erase(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator +=(const Event<EventParam>::Listener& listener){
        AddListener(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator -=(const Event<EventParam>::Listener& listener){
        RemoveListener(listener);
    }

}