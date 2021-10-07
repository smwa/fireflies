#include <Color.hpp>

using namespace std;

Color Color::get(double hue, double saturation, double luminosity) {
    if (hue > 1.0) hue = 1.0;
    if (hue < 0.0) hue = 0.0;
    if (saturation > 1.0) saturation = 1.0;
    if (saturation < 0.0) saturation = 0.0;
    if (luminosity > 1.0) luminosity = 1.0;
    if (luminosity < 0.0) luminosity = 0.0;
    
    return Color(hue, saturation, luminosity);
};

double Color::get_hue() {
    return hue;
};

double Color::get_saturation() {
    return saturation;
};

double Color::get_luminosity() {
    return luminosity;
};

double Color::get_red() {
    double a = get_saturation() * min(get_luminosity(), 1.0 - get_luminosity());
    int k = (int)(get_hue() * 360.0 / 30.0) % 12;
    return get_luminosity() - a * (double)max(-1, min(min(k - 3, 9 - k), 1));
};

double Color::get_green() {
    double a = get_saturation() * min(get_luminosity(), 1.0 - get_luminosity());
    int k = (int)(8.0 + get_hue() * 360.0 / 30.0) % 12;
    return get_luminosity() - a * (double)max(-1, min(min(k - 3, 9 - k), 1));
};

double Color::get_blue() {
    double a = get_saturation() * min(get_luminosity(), 1.0 - get_luminosity());
    int k = (int)(4.0 + get_hue() * 360.0 / 30.0) % 12;
    return get_luminosity() - a * (double)max(-1, min(min(k - 3, 9 - k), 1));
};
