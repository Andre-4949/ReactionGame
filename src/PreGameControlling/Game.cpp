#include "../../include/PreGameControlling/Game.h"
#include "../../include/PreGameControlling/Menu.h"


void Game::start() {
    //Set up game with programm parameters if all are specified
    if(argc==5){
        parseGameSession();
    }
    //Otherwise get them through user command line inputs
    else {
        setupGameSession();
    }
    Game::session.loop();
    Menu::printResults(Game::session.getGameMode()->getResultsHandler());
}

Game::Game(const int argc, const char* argv[]) {
    this->argc = argc;
    for (int i = 0; i < argc; ++i) {
        this->argv.emplace_back(argv[i]);
    }
}

void Game::setupGameSession() const {
    Menu menu;
    Game::session = menu.readOptions();
}

void Game::parseGameSession() const{
    std::string name = argv[1];
    std::string gamemodeAsStr = argv[2];
    std::string sequenceAsStr = argv[3];
    std::string frameNumAsStr = argv[4];
    int gamemode=0, sequence=0, frameNum=0;
    try {
        gamemode = std::stoi(gamemodeAsStr);
        sequence = std::stoi(sequenceAsStr);
        frameNum = std::stoi(frameNumAsStr);
    }catch (std::invalid_argument::exception e){
        std::cout << "\n\n\n" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Provided Arguments couldn't be parsed." << std::endl;
        exit(0);
    }
    GameMode* scene = Menu::getGameModeByUserInput(gamemode,frameNum,sequence);
    const GameSession session(scene, name);
    Game::session = session;
}