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
    target_color = Color::get(
        lerp(message.color.get_hue(), target_color.get_hue(), target_color.get_luminosity() / (message.color.get_luminosity() + target_color.get_luminosity())),
        max(message.color.get_saturation(), target_color.get_saturation()),
        max(message.color.get_luminosity(), target_color.get_luminosity())
    );

    message.color = target_color;

    Node::send_message(message, source);

    // Chance of creating new message with tweaked color
    if ((double)rand() / (double)RAND_MAX < human->get_chaos() * 0.06) {
        double rand_hue = (double)rand() / (double)RAND_MAX;
        double rand_saturation = 0.5 + ((double)rand() / (double)RAND_MAX) / 2.0;
        double rand_luminosity = human->get_energy() * 0.25 + 0.75 * (double)rand() / (double)RAND_MAX;
        Color new_color = Color::get(rand_hue, rand_saturation, rand_luminosity);
        Message new_message = Message();
        new_message.direction = (rand() % 3) - 1;
        new_message.energy = human->get_energy();
        new_message.color = new_color;
        postman->enqueue(new_message, this, this);
    }
};

void LED::tick(int time) {
    Node::tick(time);
    double min_time_total_dropoff = 200.0; // lower is faster
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
