#include <Arduino.h>

#include <Wire.h>
#include <FastLED.h>

#include <sstream>

#define NUMBER_OF_LEDS 192

#define GY521_LEFT 0x68
#define GY521_RIGHT 0x69

#include <Accelerometer6DoF.hpp>
#include <Human.hpp>
#include <Heart.hpp>
#include <Message.hpp>
#include <Clock.hpp>
#include <Color.hpp>
#include <Postman.hpp>
#include <Logger.hpp>
#include <LED.hpp>

double normalize (int16_t value) {
  return value < 0
    ? -static_cast<double>(value) / std::numeric_limits<int16_t>::min()
    :  static_cast<double>(value) / std::numeric_limits<int16_t>::max()
    ;
}

CRGB leds[NUMBER_OF_LEDS];

TwoWire GY521 = Wire;

Logger* logger;

Clock* clk = new Clock();
Postman* postman = new Postman(clk);

Human* human_node = new Human(postman);
Heart* heart_node = new Heart(postman, human_node);
Accelerometer6DoF* gy521_left = new Accelerometer6DoF(postman, human_node, 0);
Accelerometer6DoF* gy521_right = new Accelerometer6DoF(postman, human_node, 191);
LED* led_nodes[NUMBER_OF_LEDS - 2];

// X, Y, Z, temperature, A, B, C
double GY521_left_readings[7];
double GY521_right_readings[7];

void setup() {
    Serial.begin(115200);
    
    logger = new Logger(clk, LOG_LEVEL::INFO);
    Logger::set_instance(logger);
    clk->set_time(millis());

    FastLED.addLeds<WS2812, 23, EOrder::GRB>(leds, NUMBER_OF_LEDS);
    for (int i = 1; i < NUMBER_OF_LEDS - 1; i++) {
        ostringstream sout;
        led_nodes[i-1] = new LED(postman, human_node, i);
        sout << "LED " << i - 1;
        led_nodes[i-1]->_logger_component_name = sout.str();
    }

    // length one
    int length_one_top = 64;
    gy521_left->add_node(led_nodes[0]);
    led_nodes[0]->add_node(gy521_left);
    for (int i = 0 + 1; i < length_one_top; i++) {
        led_nodes[i]->add_node(led_nodes[i-1]);
        led_nodes[i-1]->add_node(led_nodes[i]);
    }
    heart_node->add_node(led_nodes[length_one_top - 1]);
    led_nodes[length_one_top - 1]->add_node(heart_node);

    // length two
    int length_two_top = length_one_top + 31;
    heart_node->add_node(led_nodes[length_one_top]);
    led_nodes[length_one_top]->add_node(heart_node);
    for (int i = length_one_top + 1; i < length_two_top; i++) {
        led_nodes[i]->add_node(led_nodes[i-1]);
        led_nodes[i-1]->add_node(led_nodes[i]);
    }

    // length three
    int length_three_top = length_two_top + 31;
    for (int i = length_two_top + 1; i < length_three_top; i++) {
        led_nodes[i]->add_node(led_nodes[i-1]);
        led_nodes[i-1]->add_node(led_nodes[i]);
    }
    heart_node->add_node(led_nodes[length_three_top - 1]);
    led_nodes[length_three_top - 1]->add_node(heart_node);

    // length four
    int length_four_top = length_three_top + 64;
    heart_node->add_node(led_nodes[length_three_top]);
    led_nodes[length_three_top]->add_node(heart_node);
    for (int i = length_three_top + 1; i < length_four_top; i++) {
        led_nodes[i]->add_node(led_nodes[i-1]);
        led_nodes[i-1]->add_node(led_nodes[i]);
    }
    gy521_right->add_node(led_nodes[length_four_top - 1]);
    led_nodes[length_four_top - 1]->add_node(gy521_right);

    GY521.begin();

    GY521.beginTransmission(GY521_LEFT);
    GY521.write(0x6B); // PWR_MGMT_1 register
    GY521.write(0b00001000); // set to zero (wakes up the MPU-6050), 4th bit disables temperature sensor
    GY521.endTransmission(true);

    GY521.beginTransmission(GY521_RIGHT);
    GY521.write(0x6B); // PWR_MGMT_1 register
    GY521.write(0); // set to zero (wakes up the MPU-6050)
    GY521.endTransmission(true);

    gy521_left->_logger_component_name = "Left Sensor";
    gy521_right->_logger_component_name = "Right Sensor";
    human_node->_logger_component_name = "Human Node";
    heart_node->_logger_component_name = "Heart Node";
}

void loop() {
    delay(1);

    // leds[190].setRGB(255, 255, 255);
    // FastLED.show();

    GY521.beginTransmission(GY521_LEFT);
    GY521.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    GY521.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    GY521.requestFrom(GY521_LEFT, 7*2, 1); // request a total of 7*2=14 registers
    // "GY521.read()<<8 | GY521.read();" means two registers are read and stored in the same variable
    for (int i = 0; i < 7; i++) {
        GY521_left_readings[i] = normalize(GY521.read()<<8 | GY521.read());
    }
    gy521_left->set_values(
        GY521_left_readings[0],
        GY521_left_readings[1],
        GY521_left_readings[2],
        GY521_left_readings[4],
        GY521_left_readings[5],
        GY521_left_readings[6]
    );

    GY521.beginTransmission(GY521_RIGHT);
    GY521.write(0x3B);
    GY521.endTransmission(false);
    GY521.requestFrom(GY521_RIGHT, 7*2, 1);
    for (int i = 0; i < 7; i++) {
        GY521_right_readings[i] = normalize(GY521.read()<<8 | GY521.read());
    }
    gy521_right->set_values(
        GY521_right_readings[0],
        GY521_right_readings[1],
        GY521_right_readings[2],
        GY521_right_readings[4],
        GY521_right_readings[5],
        GY521_right_readings[6]
    );

    clk->set_time(millis());
    postman->process();
    postman->set_message_delay(human_node->get_pulse());
    human_node->tick(clk->get_time());
    heart_node->tick(clk->get_time());
    gy521_left->tick(clk->get_time());
    gy521_right->tick(clk->get_time());
    for (int i = 0; i < NUMBER_OF_LEDS - 2; i++) {
        led_nodes[i]->tick(clk->get_time());
        leds[led_nodes[i]->get_led_index()].setRGB((int)(led_nodes[i]->color.get_red() * 255.0), (int)(led_nodes[i]->color.get_green() * 255.0), (int)(led_nodes[i]->color.get_blue() * 255.0));
    }
    FastLED.show();
    while (logger->has_message()) {
        Serial.println(logger->get_message().c_str());
    }
}
// TODO Move more members to the heap
