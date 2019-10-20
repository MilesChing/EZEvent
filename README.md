# EZEvent

A C++ toolkit for implementing an event mechanism similar to C#.

## Install Lib

This toolkit contains only header files.

~~~shell
git clone https://github.com/MilesChing/EZEvent
cd EZEvent
mkdir build
cd build
# cmake required
cmake ..
make -j
# install header files to include/
sudo make install
~~~

## Usage

~~~cpp
#include "EZEvent/Event.h"
using namespace EZEvent;
~~~

An event operation are completed with two instances: Event & EventTrigger. Declare a public Event member to support the Event subscription, and a private EventTrigger member to trigger the event internally.

~~~cpp
class MessageSolver{
private:
    EZEvent::EventTrigger<string> MessageReceivedTrigger;
public:
    MessageSolver(){
        // Bind a trigger with an event.
        // Triggers and events can only be bound once.
        MessageReceived.BindTrigger(&MessageReceivedTrigger);
    }
    EZEvent::Event<string> MessageReceived;

    void SendMessage(string message){
        //Invoke the event through the specific trigger
        MessageReceivedTrigger.Invoke(message);
    }
};
~~~

Call `AddListener` or operator `+=` to register a listener. `RemoveListener` and operator `-=` is used to deregister a listener. Both Lambda expressions and function Pointers are supported:

~~~cpp
message_solver.MessageReceived += [](const string& message){
    cout << "listener #1 Receive message \"" << message << "\"" << endl;
};  //Lambda Expression Listener

message_solver.MessageReceived += test_receiver;    //Function Listener
~~~

