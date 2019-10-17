#include "EZEvent/Event.h"
#include <string>
#include <iostream>
using namespace std;
class MessageSolver{
private:
    EZEvent::EventTrigger<string> MessageReceivedTrigger;
public:
    MessageSolver() : MessageReceivedTrigger(),
        MessageReceived(&MessageReceivedTrigger){}
    EZEvent::Event<string> MessageReceived;
    void SendMessage(string message){
        MessageReceivedTrigger.Invoke(message);
    }
}message_solver;

int main(){
    message_solver.MessageReceived += [](const string& message){
        cout << "listener #1 Receive message \"" << message << "\"" << endl;
    };

    message_solver.MessageReceived += [](const string& message){
        cout << "listener #2 Receive message \"" << message << "\"" << endl;
    };

    while(true){
        cout << "Send a message ([Q]Quit): ";
        string mes;
        cin >> mes;
        if(mes == "Q") return 0;
        else message_solver.SendMessage(mes);
    }
}