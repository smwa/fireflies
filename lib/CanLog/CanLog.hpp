using namespace std;
#include <string>

class Logger;

#ifndef CLASS_CANLOG
#define CLASS_CANLOG
class CanLog
{
    public:
        string _logger_component_name;
    protected:
        void trace(string message);
        void trace(string message, double attribute);
        void trace(string message, int attribute);
        void debug(string message);
        void debug(string message, double attribute);
        void debug(string message, int attribute);
        void info(string message);
        void info(string message, double attribute);
        void info(string message, int attribute);
        void warn(string message);
        void warn(string message, double attribute);
        void warn(string message, int attribute);
        void error(string message);
        void error(string message, double attribute);
        void error(string message, int attribute);
        void fatal(string message);
        void fatal(string message, double attribute);
        void fatal(string message, int attribute);
};
#endif
