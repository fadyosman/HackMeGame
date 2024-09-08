#include <raylib.h>
#include "game.h"
int main(int argc, char **argv)
{
    Game game(1024,1024,"The Hack Me Game",60);
    game.run();
    
    return 0;
}
