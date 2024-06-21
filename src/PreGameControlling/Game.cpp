//
// Created by andre on 15.06.2024.
//

#include "../../include/PreGameControlling/Game.h"
#include "../../include/PreGameControlling/Menu.h"

void Game::start(){
  Menu menu;
  session = menu.getOptions();
  session.loop();
  menu.printResults(session.getScene()->getResultsHandler());
}