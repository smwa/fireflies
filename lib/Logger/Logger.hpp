using namespace std;
#include <string>
#include <list>

class LogMessage;
class Clock;

enum LOG_LEVEL { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };
static const string LOG_LEVEL_LABELS[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };

class Logger
{
    public:
        Logger(Clock* clock, LOG_LEVEL log_level) {
            this->clock = clock;
            this->log_level = log_level;
        };
        void log(string component, string message, LOG_LEVEL log_level);
        void log(string component, string message, double attribute, LOG_LEVEL log_level);
        void log(string component, string message, int attribute, LOG_LEVEL log_level);
        bool has_message();
        string get_message();
        static Logger* get_instance();
        static void set_instance(Logger* logger);
    private:
        LOG_LEVEL log_level;
        list<string> messages = list<string>();
        Clock* clock;
        static Logger* instance;
};
