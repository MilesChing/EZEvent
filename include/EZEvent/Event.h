#pragma once
#include <functional>
#include <list>
using namespace std;

namespace EZEvent{
    template<typename EventParam> class Event;

    template<typename EventParam> class EventTrigger{
    public:
        friend Event<EventParam>;
        void Invoke(const EventParam& param);
    private:
        Event<EventParam>* binding_event = NULL;
    };

    template<typename EventParam> class Event{
    public:
        friend EventTrigger<EventParam>;
        Event(EventTrigger<EventParam>* trigger);
        void ClearListeners();
        void AddListener(function<void(const EventParam&)>& listener);
        void AddListener(void(*listener)(const EventParam&));
        void RemoveListener(function<void(const EventParam&)>& listener);
        void RemoveListener(void(*listener)(const EventParam&));
        Event<EventParam>& operator +=(function<void(const EventParam&)>& listener);
        Event<EventParam>& operator -=(function<void(const EventParam&)>& listener);
        Event<EventParam>& operator +=(void(*listener)(const EventParam&));
        Event<EventParam>& operator -=(void(*listener)(const EventParam&));
        Event<EventParam>& operator =(const Event<EventParam>& event) = delete;
    private:
        void InnerInvoke(const EventParam& param);
        list<function<void(const EventParam&)>> lambda_listeners;
        list<void(*)(const EventParam&)> func_listeners;
    };

    template<typename EventParam> void EventTrigger<EventParam>::Invoke(const EventParam& param){
        if(binding_event) binding_event->InnerInvoke(param);
    }

    template<typename EventParam> Event<EventParam>::Event(EventTrigger<EventParam>* trigger){
        trigger->binding_event = this;
    }

    template<typename EventParam> void Event<EventParam>::ClearListeners(){
        lambda_listeners.clear();
        func_listeners.clear();
    }

    template<typename EventParam> void Event<EventParam>::InnerInvoke(const EventParam& param){
        for(auto& listener : lambda_listeners)
            listener(param);
        for(auto& listener : func_listeners)
            listener(param);
    }

    template<typename EventParam> void Event<EventParam>::AddListener(function<void(const EventParam&)>& listener){
        lambda_listeners.push_back(listener);
    }

    template<typename EventParam> void Event<EventParam>::AddListener(void(*listener)(const EventParam&)){
        func_listeners.push_back(listener);
    }

    template<typename EventParam> void Event<EventParam>::RemoveListener(function<void(const EventParam&)>& listener){
        lambda_listeners.erase(listener);
    }

    template<typename EventParam> void Event<EventParam>::RemoveListener(void(*listener)(const EventParam&)){
        func_listeners.erase(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator +=(function<void(const EventParam&)>& listener){
        AddListener(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator -=(function<void(const EventParam&)>& listener){
        RemoveListener(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator +=(void(*listener)(const EventParam&)){
        AddListener(listener);
    }

    template<typename EventParam> Event<EventParam>& Event<EventParam>::operator -=(void(*listener)(const EventParam&)){
        RemoveListener(listener);
    }

}