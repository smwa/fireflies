#include <Accelerometer6DoF.hpp>

#include <stdlib.h>
#include <math.h>

#include <Message.hpp>
#include <Color.hpp>
#include <Human.hpp>

void Accelerometer6DoF::set_values(double x, double y, double z, double a, double b, double c) {
    trace("X", x);
    trace("Y", y);
    trace("Z", z);
    trace("A", a);
    trace("B", b);
    trace("C", c);
    stats[stats_index][0] = x;
    stats[stats_index][0] = y;
    stats[stats_index][2] = z;
    stats[stats_index][3] = a;
    stats[stats_index][4] = b;
    stats[stats_index][5] = c;
    stats_index += 1;
    if (stats_index >= READINGS_PER_DIRECTION_CHANGE) {
        stats_index -= READINGS_PER_DIRECTION_CHANGE;
    }
    int direction = -1;
    double energy = 0.0;
    for (int i = stats_index - READINGS_PER_DIRECTION_CHANGE; i < stats_index; i++) {
        int index = (i + READINGS_PER_DIRECTION_CHANGE) % READINGS_PER_DIRECTION_CHANGE;
        
        int local_direction = 1;
        for (int degree = 0; degree < 3; degree++) {
            energy += fabs(stats[index][degree]);
            if (stats[index][degree] < -0.2) {
                local_direction += 1;
            }
        }
        local_direction = local_direction % 2;
        if (direction == -1) {
            direction = local_direction;
        }
        else {
            if (local_direction != direction) {
                return;
            }
        }
    }
    energy /= READINGS_PER_DIRECTION_CHANGE * 3;
    if (direction == 0) {
        direction = -1;
    }
    if (energy < 0.16) {
        return;
    }
    if (direction == last_direction_sent) {
        return;
    }
    debug("direction", direction);
    debug("energy", energy);
    Message* message = new Message();
    message->direction = direction;
    message->energy = energy;
    // Copied to heart
    double hue = human->get_tone();
    double saturation = 1.0;
    double luminosity = human->get_energy() * 0.2 + energy * 0.5;
    message->color = Color::get(hue, saturation, luminosity);
    send_message(message, this);
    last_direction_sent = direction;
    human->send_message(message, this);
};
