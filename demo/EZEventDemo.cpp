#include "EZEvent/Event.h"
#include <string>
#include <iostream>
#include <tuple>
using namespace std;
class MessageSolver{
private:
    EZEvent::EventTrigger<string> MessageReceivedTrigger;
public:
    MessageSolver(){
        MessageReceived.BindTrigger(&MessageReceivedTrigger);
    }
    EZEvent::Event<string> MessageReceived;
    void SendMessage(string message){
        MessageReceivedTrigger.Invoke(message);
    }
}message_solver;

void test_receiver(const string& message){
    cout << "listener #2 Receive message \"" << message << "\"" << endl;
}

int main(){
    message_solver.MessageReceived += [](const string& message){
        cout << "listener #1 Receive message \"" << message << "\"" << endl;
    };  //Lambda Expression Listener

    message_solver.MessageReceived += test_receiver;    //Function Listener

    while(true){
        cout << "Send a message ([Q]Quit): ";
        string mes;
        cin >> mes;
        if(mes == "Q") return 0;
        else message_solver.SendMessage(mes);
    }
}