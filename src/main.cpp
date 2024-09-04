#include "Game.h"

#include <spine/Debug.h>

#ifdef DEBUG
spine::DebugExtension dbgExtension(spine::SpineExtension::getInstance());
#endif

int main()
{
#ifdef DEBUG
    spine::SpineExtension::setInstance(&dbgExtension);
#endif

    Game game;
    game.startGame();
   
#ifdef DEBUG
    dbgExtension.reportLeaks();
#endif    
    
    return 0;
}