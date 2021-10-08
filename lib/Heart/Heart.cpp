#include <Heart.hpp>

#include <math.h>

#include <Message.hpp>
#include <Human.hpp>

Heart::Heart(Postman* postman, Human* human) : Node(postman) {
    this->human = human;
};

void Heart::send_message(Message message, Node* source) {
    Node::send_message(message, source);
    last_message_received = last_tick;
};

void Heart::tick(int time) {
    Node::tick(time);
    if (time - last_message_received > human->get_pulse() * 50.0) {
        info("Heartbeat");
        Message message = Message();
        message.direction = 0;
        message.energy = human->get_energy();
        // Copied from accelerometer
        double hue = human->get_tone();
        double saturation = 1.0;
        double luminosity = human->get_energy() * 0.75;
        message.color = Color::get(hue, saturation, luminosity);
        
        send_message(message, this);
    }
};
