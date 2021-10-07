#include <CanLog.hpp>

#include <Logger.hpp>

// only message
void CanLog::trace(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::TRACE);
};

void CanLog::debug(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::DEBUG);
};

void CanLog::info(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::INFO);
};

void CanLog::warn(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::WARN);
};

void CanLog::error(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::ERROR);
};

void CanLog::fatal(string message) {
    Logger::get_instance()->log(this->_logger_component_name, message, LOG_LEVEL::FATAL);
};

// double attribute
void CanLog::trace(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::TRACE);
};

void CanLog::debug(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::DEBUG);
};

void CanLog::info(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::INFO);
};

void CanLog::warn(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::WARN);
};

void CanLog::error(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::ERROR);
};

void CanLog::fatal(string message, double attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::FATAL);
};

// int attribute
void CanLog::trace(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::TRACE);
};

void CanLog::debug(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::DEBUG);
};

void CanLog::info(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::INFO);
};

void CanLog::warn(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::WARN);
};

void CanLog::error(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::ERROR);
};

void CanLog::fatal(string message, int attribute) {
    Logger::get_instance()->log(this->_logger_component_name, message, attribute, LOG_LEVEL::FATAL);
};
