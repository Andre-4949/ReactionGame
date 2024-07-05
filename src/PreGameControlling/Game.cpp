#include "../../include/PreGameControlling/Game.h"
#include "../../include/PreGameControlling/Menu.h"

void Game::start() {
    Menu menu;
    Game::session = menu.getOptions();
    Game::session.loop();
    menu.printResults(Game::session.getScene()->getResultsHandler());
}