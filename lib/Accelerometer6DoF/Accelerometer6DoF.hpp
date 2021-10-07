#include <LED.hpp>

class Postman;
class Human;

class Accelerometer6DoF : public LED
{
    public:
        Accelerometer6DoF(Postman* postman, Human* human, int led_index) : LED(postman, human, led_index) {
            for (int i = 0; i < READINGS_PER_DIRECTION_CHANGE; i++) {
                for (int j = 0; j < 6; j++) {
                    stats[i][j] = 0.0;
                }
            }
        };
        void set_values(double x, double y, double z, double a, double b, double c);
    private:
        static const int READINGS_PER_DIRECTION_CHANGE = 5;
        int last_direction_sent = -1;
        int stats_index = 0;
        double stats[READINGS_PER_DIRECTION_CHANGE][6];
};
