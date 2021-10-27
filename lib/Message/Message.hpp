#include <Color.hpp>

#ifndef CLASS_MESSAGE
#define CLASS_MESSAGE
class Message
{
    public:
        double energy = 0.0;
        int direction = 0.0;
        int accelerometer_index = 0;
        Color color = Color::get(0.0, 0.0, 0.0);
};
#endif
