#include <Postman.hpp>

using namespace std;
#include <list>

#include <Clock.hpp>
#include <Message.hpp>
#include <Heart.hpp>
#include <Node.hpp>
#include <LED.hpp>
#include <Accelerometer6DoF.hpp>

void Postman::enqueue(Message message, Node* source, Node* destination) {
    QueuedMessage queued_message = QueuedMessage();
    queued_message.arrival_time = this->clock->get_time();
    queued_message.message = message;
    queued_message.source = source;
    queued_message.destination = destination;
    this->messages.push_back(queued_message);
};

void Postman::process() {
    std::list<QueuedMessage>::iterator message;
    for (message = this->messages.begin(); message != this->messages.end(); message++) {
        if (this->clock->get_time() >= message->arrival_time + this->message_delay) {
            LED* led_destination = dynamic_cast<LED*>(message->destination);
            Accelerometer6DoF* acc_destination = dynamic_cast<Accelerometer6DoF*>(message->destination);
            Heart* heart_destination = dynamic_cast<Heart*>(message->destination);
            if (led_destination != nullptr) {
                led_destination->send_message(message->message, message->source);
            }
            else if (acc_destination != nullptr) {
                acc_destination->send_message(message->message, message->source);
            }
            else if (heart_destination != nullptr) {
                heart_destination->send_message(message->message, message->source);
            }
            else {
                message->destination->send_message(message->message, message->source);
            }
            message = this->messages.erase(message);
            --message;
        }
    }
};

void Postman::set_message_delay(int message_delay) {
    this->message_delay = message_delay;
};
