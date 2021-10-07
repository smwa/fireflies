#include <Human.hpp>

#include <math.h>

#include <Message.hpp>
#include <Color.hpp>

double Human::get_chaos() {
    return chaos;
};

double Human::get_energy() {
    return energy;
};

double Human::get_tone() {
    return tone;
};

double Human::get_pulse() {
    return pulse;
};

void Human::send_message(Message* message, Node* source) {
    Node::send_message(message, source);
    energy *= 5;
    energy += message->energy;
    energy /= 6;

    tone += message->direction * message->energy / 16.0;
    tone = ((int)(tone * 100000) % 100000) / 100000.0;

    double min_energy = energy;
    double max_energy = energy;
    for (int i = 0; i < ENERGY_OVER_TIME_LENGTH; i++) {
        min_energy = min(min_energy, energy_over_time[i]);
        max_energy = max(max_energy, energy_over_time[i]);
    }
    chaos = max_energy - min_energy;

    if (message_energies_times[message_energies_index - 1 % MESSAGE_ENERGIES_LENGTH] != last_tick) {
        message_energies[message_energies_index] = message->energy;
        message_energies_times[message_energies_index] = last_tick;
        message_energies_index += 1;
        if (message_energies_index >= MESSAGE_ENERGIES_LENGTH) {
            message_energies_index -= MESSAGE_ENERGIES_LENGTH;
        }
    }

    double max_energy_from_message = message->energy;
    for (int i = 0; i < MESSAGE_ENERGIES_LENGTH; i++) {
        max_energy_from_message = max(max_energy_from_message, message_energies[i]);
    }
    int pulse_length = 0;

    int last_measured_pulse = -1;
    for (int i = MESSAGE_ENERGIES_LENGTH - 1; i >= 0; i--) {
        if (message_energies[i] > max_energy_from_message * 0.8) {
            if (last_measured_pulse >= 0) {
                pulse_length = last_measured_pulse - message_energies_times[i];
                break;
            }
            last_measured_pulse = message_energies_times[i];
        }
    }
    if (pulse_length > 0) {
        pulse = pulse_length; // ms per pulse
        while (pulse < 20.0) {
            pulse *= 2.0;
        }
        while (pulse > 200.0) {
            pulse /= 2.0;
        }
    }
};

void Human::tick(int time) {
    Node::tick(time);
    double drift_percentage = 1.0 - pow(9, time_since_last_tick / 2000.0) / pow(10, time_since_last_tick / 2000.0);
    energy -= energy * drift_percentage;
    chaos -= chaos * drift_percentage;
    tone = (tone * (1.0 - drift_percentage / 4.0)) + (0.5 * drift_percentage / 4.0);

    energy_over_time[energy_over_time_index++] = energy;
    if (energy_over_time_index >= ENERGY_OVER_TIME_LENGTH) {
        energy_over_time_index -= ENERGY_OVER_TIME_LENGTH;
    }

    if (time - message_energies_times[(message_energies_index - 1) + MESSAGE_ENERGIES_LENGTH % MESSAGE_ENERGIES_LENGTH] > pulse * 50.0) {
        info("Heartbeat");
        Message* message = new Message();
        message->direction = 0;
        message->energy = energy;
        // Copied from accelerometer
        double hue = get_tone();
        double saturation = 1.0;
        double luminosity = get_energy() * 0.75;
        message->color = Color::get(hue, saturation, luminosity);
        
        send_message(message, this);
    }
};