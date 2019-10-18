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
	# build an Event like this to bind an Event with a Trigger
    MessageSolver() : MessageReceivedTrigger(),
        MessageReceived(&MessageReceivedTrigger){}
    EZEvent::Event<string> MessageReceived;
    void SendMessage(string message){
        MessageReceivedTrigger.Invoke(message);
    }
};
~~~

