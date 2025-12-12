#include "Game.hpp"
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    Game game;
    game.run();
    
    return 0;
}