
#include <Node.hpp>
#include <Color.hpp>

class Color;
class Human;
class Message;

#ifndef CLASS_LED
#define CLASS_LED
class LED : public Node
{
    public:
        LED(Postman* postman, Human* human, int led_index);
        void send_message(Message message, Node* source);
        void tick(int time);
        int get_led_index();
        Color color = Color::get(0.0, 0.0, 0.0);
        Color target_color = Color::get(0.0, 0.0, 0.0);
    protected:
        Human* human;
    private:
        int led_index;
};
#endif
