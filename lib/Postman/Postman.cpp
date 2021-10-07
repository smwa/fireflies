#include <Postman.hpp>

using namespace std;
#include <list>

#include <Clock.hpp>
#include <Message.hpp>
#include <Node.hpp>
#include <QueuedMessage.hpp>
#include <LED.hpp>
#include <Accelerometer6DoF.hpp>

void Postman::enqueue(Message* message, Node* source, Node* destination) {
    QueuedMessage* queued_message = new QueuedMessage();
    queued_message->arrival_time = this->clock->get_time();
    queued_message->message = message;
    queued_message->source = source;
    queued_message->destination = destination;
    this->messages->push_back(queued_message);
    this->garbage_tracker->insert(message);
    if (this->garbage_tracker->size() > 5000) {
        Message* to_delete = *next(this->garbage_tracker->begin(), 0);
        this->garbage_tracker->erase(0);
        delete to_delete;
    }
};

void Postman::process() {
    std::list<QueuedMessage*>::iterator it;
    for (it = this->messages->begin(); it != this->messages->end(); it++) {
        QueuedMessage* message = *it;
        if (this->clock->get_time() >= message->arrival_time + this->message_delay) {
            LED* led_destination = dynamic_cast<LED*>(message->destination);
            Accelerometer6DoF* acc_destination = dynamic_cast<Accelerometer6DoF*>(message->destination);
            if (led_destination != nullptr) {
                led_destination->send_message(message->message, message->source);
            }
            else if (acc_destination != nullptr) {
                acc_destination->send_message(message->message, message->source);
            }
            else {
                message->destination->send_message(message->message, message->source);
            }
            it = this->messages->erase(it);
            delete message;
        }
    }
};

void Postman::set_message_delay(int message_delay) {
    this->message_delay = message_delay;
};