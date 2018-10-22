//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/MainMenuScreen.h"

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void MainMenuScreen::update(std::shared_ptr<MouseEvent> event){
    if((event->getXPosition() >= 100 && event->getXPosition() <= 540)
    && (event->getYPosition() >= 100 && event->getYPosition() <= 140))
    {
        _context->setActiveScreen<GameScreen>();
    }
}

MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getMouseEventObservable()->registerObserver(this);

    _renderList.rectangleList.emplace_back(ShapeRectangle{640, 480, 0, 0, Colour { 0, 0, 0, 100}});
    _renderList.rectangleList.emplace_back(ShapeRectangle{440, 40, 100, 100, Colour { 200, 200, 200, 100}});
    //TODO: Startgame text - requires visual facade update
}

MainMenuScreen::~MainMenuScreen() {

}