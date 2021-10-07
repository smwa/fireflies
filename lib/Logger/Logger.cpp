#include <Logger.hpp>

using namespace std;
#include <string>
#include <list>
#include <sstream>
#include <iomanip>

#include <Clock.hpp>

void Logger::log(string component, string message, LOG_LEVEL log_level) {
    if (!this->clock) {
        return;
    }
    if (log_level >= this->log_level) {
        ostringstream sout;
        sout << setfill('0') << setw(7) << clock->get_time() << " " << LOG_LEVEL_LABELS[log_level] << " " << component << ": " << message;
        messages->push_back(sout.str());
    }
};

void Logger::log(string component, string message, double attribute, LOG_LEVEL log_level) {
    if (!this->clock) {
        return;
    }
    if (log_level >= this->log_level) {
        ostringstream sout;
        sout << setfill('0') << setw(7) << setprecision(3) << fixed << clock->get_time() << " " << LOG_LEVEL_LABELS[log_level] << " " << component << ": " << message << " = " << attribute;
        messages->push_back(sout.str());
    }
};

void Logger::log(string component, string message, int attribute, LOG_LEVEL log_level) {
    if (!this->clock) {
        return;
    }
    if (log_level >= this->log_level) {
        ostringstream sout;
        sout << setfill('0') << setw(7) << clock->get_time() << " " << LOG_LEVEL_LABELS[log_level] << " " << component << ": " << message << " = " << attribute;
        messages->push_back(sout.str());
    }
};

bool Logger::has_message() {
    return !this->messages->empty();
};

string Logger::get_message() {
    string m = this->messages->front();
    this->messages->pop_front();
    return m;
};

Logger* Logger::instance = 0;

Logger* Logger::get_instance() {
    return Logger::instance;
};

void Logger::set_instance(Logger* logger) {
    instance = logger;
};
