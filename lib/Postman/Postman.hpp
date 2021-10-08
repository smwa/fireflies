using namespace std;
#include <list>
#include <set>

#include <QueuedMessage.hpp>

class Clock;
class Message;
class Node;

class Postman
{
    public:
        Postman(Clock* clock) {
            this->clock = clock;
            this->message_delay = 0;
        };
        void enqueue(Message* message, Node* source, Node* destination);
        void process();
        void set_message_delay(int message_delay);
    private:
        Clock* clock;
        list<QueuedMessage> messages = list<QueuedMessage>();
        set<Message*> garbage_tracker = set<Message*>();
        int message_delay;
};
