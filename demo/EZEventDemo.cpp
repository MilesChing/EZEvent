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

int main(){
    int i = 0;

    message_solver.MessageReceived += EZEvent::EventListener<string>([](const string& message, void* user_data){
        int i = *(int*)user_data;
        cout << "listener #1 Receive message \"" << message << "\" when i = " << i << endl;
    }, &i);

    message_solver.MessageReceived += EZEvent::EventListener<string>([](const string& message, void* user_data){
        int i = *(int*)user_data;
        cout << "listener #1 Receive message \"" << message << "\" when i = " << i << endl;
    }, &i);

    while(true){
        ++i;
        cout << "Send a message ([Q]Quit): ";
        string mes;
        cin >> mes;
        if(mes == "Q") return 0;
        else message_solver.SendMessage(mes);
    }
}