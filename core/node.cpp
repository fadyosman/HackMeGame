#include "node.h"

Node::Node() {
    paused = false;
}

void Node::togglePause() {
    paused = !paused;
}

bool Node::isPaused() {
    return paused;
}

void Node::setPosition(Vector2 p) {
    position = p;
}

Vector2 Node::getPosition() {
    return position;
}

Node::~Node() {

}