using namespace std;
#include <list>
#include <set>

class Clock;
class Message;
class Node;
class QueuedMessage;

class Postman
{
    public:
        Postman(Clock* clock) {
            this->clock = clock;
            this->message_delay = 0;
            messages = new list<QueuedMessage*>();
            garbage_tracker = new set<Message*>();
        };
        void enqueue(Message* message, Node* source, Node* destination);
        void process();
        void set_message_delay(int message_delay);
    private:
        Clock* clock;
        list<QueuedMessage*>* messages;
        set<Message*>* garbage_tracker;
        int message_delay;
};
