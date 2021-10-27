#include <Human.hpp>

#include <math.h>

#include <Message.hpp>

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

void Human::send_message(Message message, Node* source) {
    Node::send_message(message, source);
    energy *= 5;
    energy += message.energy;
    energy /= 6;

    // tone += message.direction * message.energy / 4.0;
    // tone = ((int)(tone * 100000) % 100000) / 100000.0;
    if (message.accelerometer_index == 1) {
        tone += message.energy / 8.0;
    }
    else if (message.accelerometer_index == 2) {
        tone -= message.energy / 8.0;
    }

    double min_energy = energy;
    double max_energy = energy;
    for (int i = 0; i < ENERGY_OVER_TIME_LENGTH; i++) {
        min_energy = min(min_energy, energy_over_time[i]);
        max_energy = max(max_energy, energy_over_time[i]);
    }
    chaos = max_energy - min_energy;

    if (message_energies_times[message_energies_index - 1 % MESSAGE_ENERGIES_LENGTH] != last_tick) {
        message_energies[message_energies_index] = message.energy;
        message_energies_times[message_energies_index] = last_tick;
        message_energies_index += 1;
        if (message_energies_index >= MESSAGE_ENERGIES_LENGTH) {
            message_energies_index -= MESSAGE_ENERGIES_LENGTH;
        }
    }

    double max_energy_from_message = message.energy;
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
        while (pulse < 10.0) {
            pulse *= 2.0;
        }
        while (pulse > 60.0) {
            pulse /= 2.0;
        }
    }
};

void Human::tick(int time) {
    Node::tick(time);
    double dropoff_rate = 5000.0;
    double drift_percentage = time_since_last_tick / dropoff_rate;
    energy -= energy * drift_percentage;
    chaos -= chaos * drift_percentage;
    tone = (tone * (1.0 - drift_percentage / 8.0)) + (0.5 * drift_percentage / 8.0);

    energy_over_time[energy_over_time_index++] = energy;
    if (energy_over_time_index >= ENERGY_OVER_TIME_LENGTH) {
        energy_over_time_index -= ENERGY_OVER_TIME_LENGTH;
    }
};
