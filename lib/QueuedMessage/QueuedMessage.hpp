#include <Message.hpp>

class Node;

class QueuedMessage
{
    public:
        Message message = Message();
        Node* source;
        Node* destination;
        int arrival_time;
};
