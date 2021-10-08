#include <Node.hpp>

class Postman;
class Human;

class Heart : public Node
{
    public:
        Heart(Postman* postman, Human* human);
        void send_message(Message* message, Node* source);
        void tick(int time);
    protected:
        Human* human;
        int last_message_received = 0;
};
