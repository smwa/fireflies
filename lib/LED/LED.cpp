#include <LED.hpp>

#include <stdlib.h>

#include <Color.hpp>
#include <Human.hpp>
#include <Message.hpp>
#include <Postman.hpp>

double lerp(double a, double b, double t) {
    return b * t + a * (1.0 - t);
};

LED::LED(Postman* postman, Human* human, int led_index) : Node(postman) {
    this->human = human;
    this->led_index = led_index;
};

int LED::get_led_index() {
    return led_index;
};

void LED::send_message(Message message, Node* source) {
    Node::send_message(message, source);

    double random_percent = (double)rand() / (double)RAND_MAX;

    // Chance of creating new message with tweaked color
    if (random_percent < human->get_chaos() * 0.008) {
        double rand_hue = (double)rand() / (double)RAND_MAX;
        double rand_saturation = 0.5 + ((double)rand() / (double)RAND_MAX) / 2.0;
        double rand_luminosity = human->get_energy() * 0.25 + 0.75 * (double)rand() / (double)RAND_MAX;
        Color new_color = Color::get(rand_hue, rand_saturation, rand_luminosity);
        Message new_message = Message();
        new_message.direction = 0;
        new_message.energy = human->get_energy();
        new_message.color = new_color;
        postman->enqueue(new_message, this, this);
    }
    
    random_percent = (double)rand() / (double)RAND_MAX;
    
    // if not chaotic, use what you're given
    if (random_percent > human->get_chaos()) {
        target_color = message.color;
        return;
    }

    random_percent = (double)rand() / (double)RAND_MAX;
    
    target_color = Color::get(
        lerp(message.color.get_hue(), target_color.get_hue(), random_percent),
        lerp(message.color.get_saturation(), target_color.get_saturation(), random_percent),
        lerp(message.color.get_luminosity(), target_color.get_luminosity(), random_percent)
    );
};

void LED::tick(int time) {
    Node::tick(time);
    double min_time_total_dropoff = 600.0; // lower is faster
    double new_luminosity = target_color.get_luminosity() - (human->get_chaos() + 0.1) * (double)time_since_last_tick / min_time_total_dropoff;
    target_color = Color::get(target_color.get_hue(), target_color.get_saturation(), new_luminosity);
    double lerp_amount = (double)time_since_last_tick / 200.0; // higher divider means slower fade
    if (lerp_amount > 1.0) lerp_amount = 1.0;

    color = Color::get(
        target_color.get_hue(),
        lerp(color.get_saturation(), target_color.get_saturation(), lerp_amount),
        lerp(color.get_luminosity(), target_color.get_luminosity(), lerp_amount)
    );
};
