#pragma once
#include <functional>
#include <list>
using namespace std;

namespace EZEvent{
    template<typename EventParam> class Event;

    template<typename EventParam> class EventListener{
    public:
        EventListener(void(*listener)(const EventParam&, void*), void* user_data = NULL);
    private:
        friend Event<EventParam>;
        void Invoke(const EventParam& param);
        void(*listener)(const EventParam&, void*);
        void* user_data = NULL;
    };

    template<typename EventParam> class EventTrigger{
    public:
        friend Event<EventParam>;
        void Invoke(const EventParam& param);
    private:
        Event<EventParam>* binding_event = NULL;
    };

    template<typename EventParam> class Event{
    public:
        typedef EventListener<EventParam> Listener;
        friend EventTrigger<EventParam>;
        void BindTrigger(EventTrigger<EventParam>* trigger);
        void ClearListeners();
        void AddListener(const EventListener<EventParam>& listener);
        void RemoveListener(const EventListener<EventParam>& listener);
        Event<EventParam>& operator += (const EventListener<EventParam>& listener);
        Event<EventParam>& operator -= (const EventListener<EventParam>& listener);
        Event<EventParam>& operator = (const Event<EventParam>& event) = delete;
    private:
        bool trigger_binded = false;
        void InnerInvoke(const EventParam& param);
        list<EventListener<EventParam>> listeners;
    };

    template<typename EventParam> EventListener<EventParam>::EventListener(void(*listener)(const EventParam&, void*), void* user_data){
        this->listener = listener;
        this->user_data = user_data;
    }

    template<typename EventParam> void EventListener<EventParam>::Invoke(const EventParam& param){
        listener(param, user_data);
    }

    template<typename EventParam> void EventTrigger<EventParam>::Invoke(const EventParam& param){
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

    template<typename EventParam> void Event<EventParam>::InnerInvoke(const EventParam& param){
        for(auto& listener : listeners)
            listener.Invoke(param);
    }

    template<typename EventParam> void Event<EventParam>::AddListener(const EventListener<EventParam>& listener){
        listeners.push_back(listener);
    }

    template<typename EventParam> void Event<EventParam>::RemoveListener(const EventListener<EventParam>& listener){
        listeners.erase(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator +=(const EventListener<EventParam>& listener){
        AddListener(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator -=(const EventListener<EventParam>& listener){
        RemoveListener(listener);
    }

}