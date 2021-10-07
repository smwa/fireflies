#include <Node.hpp>

using namespace std;
#include <list>

#include <Message.hpp>
#include <Postman.hpp>
#include <Color.hpp>

void Node::add_node(Node* node) {
    this->nodes->push_back(node);
};

void Node::send_message(Message* message, Node* source) {
    this->debug("Received message");
    this->trace("Direction", message->direction);
    this->trace("Energy", message->energy);
    this->trace("Hue", message->color.get_hue());
    this->trace("Saturation", message->color.get_saturation());
    this->trace("Luminosity", message->color.get_luminosity());
    std::list<Node*>::iterator it;
    for (it = this->nodes->begin(); it != this->nodes->end(); it++) {
        if ((*it) != source) {
            this->postman->enqueue(message, this, (*it));
        }
    }
};

void Node::tick(int time) {
    time_since_last_tick = time - last_tick;
    last_tick = time;
};
