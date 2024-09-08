#ifndef NODE_H
#define NODE_H

#include <raylib.h>

class Node
{
private:
    Vector2 position;
    bool paused;
public:
    Node();
    ~Node();
    bool isPaused();
    void togglePause();
    void setPosition(Vector2 v2);
    Vector2 getPosition();
    //Should be overwridden by the nodes.
    virtual void update(bool paused) {};
};

#endif