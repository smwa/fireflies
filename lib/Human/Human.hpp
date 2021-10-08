#include <Node.hpp>

class Message;

class Human : public Node
{
    public:
        Human(Postman* postman) : Node(postman) {
            for (int i = 0; i < ENERGY_OVER_TIME_LENGTH; i++) {
                energy_over_time[i] = 0.0;
            }
            for (int i = 0; i < MESSAGE_ENERGIES_LENGTH; i++) {
                message_energies[i] = 0.0;
                message_energies_times[i] = i - MESSAGE_ENERGIES_LENGTH;
            }
        };
        double get_energy();
        double get_chaos();
        double get_tone();
        double get_pulse();
        void send_message(Message message, Node* source);
        void tick(int time);
    private:
        static const int ENERGY_OVER_TIME_LENGTH = 10;
        int energy_over_time_index = 0;
        double energy_over_time[ENERGY_OVER_TIME_LENGTH];

        static const int MESSAGE_ENERGIES_LENGTH = 100;
        int message_energies_index = 0;
        double message_energies[MESSAGE_ENERGIES_LENGTH];
        int message_energies_times[MESSAGE_ENERGIES_LENGTH];

        double energy = 0.0;
        double chaos = 0.0;
        double tone = 0.5;
        double pulse = 200.0;
};
