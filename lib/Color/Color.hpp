using namespace std;
#include <list>

#ifndef CLASS_COLOR
#define CLASS_COLOR
class Color {
    public:
        static Color get(double hue, double saturation, double luminosity);
        double get_hue();
        double get_saturation();
        double get_luminosity();
        double get_red();
        double get_green();
        double get_blue();
    protected:
        Color(double hue, double saturation, double luminosity) {
            this->hue = hue;
            this->saturation = saturation;
            this->luminosity = luminosity;
        };
        double hue; // from 0.0 to 1.0
        double saturation;
        double luminosity;
};
#endif
