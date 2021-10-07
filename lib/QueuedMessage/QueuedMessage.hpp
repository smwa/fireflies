class Message;
class Node;

class QueuedMessage
{
    public:
        Message *message;
        Node *source;
        Node *destination;
        int arrival_time;
};
