using namespace std;
#include <list>

#include "../CanLog/CanLog.hpp"

class Postman;
class Message;

#ifndef CLASS_NODE
#define CLASS_NODE
class Node : public CanLog
{
    public:
        Node(Postman* postman) {
            this->postman = postman;
            this->nodes = new list<Node*>();
        };
        void add_node(Node* node);
        virtual void send_message(Message* message, Node* source);
        virtual void tick(int time);
        Postman* postman;
    protected:
        int time_since_last_tick = 0;
        int last_tick = 0;
    private:
        list<int>* message_arrival_times;
        list<Message*>* messages;
        list<Node*>* nodes = {};
};
#endif
