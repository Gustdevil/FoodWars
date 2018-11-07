#include "../../Headers/StateMachine/LevelCreationScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelCreationScreen::LevelCreationScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);
    _inputFacade->getMouseEventObservable()->registerObserver(this);
    _windowResCalc = _context->getWindowResolutionCalculator();
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    //_renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaper.png"});

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);
}

LevelCreationScreen::~LevelCreationScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void LevelCreationScreen::update(double deltaTime) {
    Renderlist renderlist = _levelBuilder.drawCurrentScene();
    _renderList.mergeShapeRectangles(renderlist.rectangleList);
    _renderList.mergeShapeSprites(renderlist.spriteList);
    _renderList.mergeShapeText(renderlist.textList);
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelCreationScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void LevelCreationScreen::update(std::shared_ptr<MouseEvent> event) {
    if(event->getMouseEventType() == MouseEventType::Down){
        _levelBuilder.placeBlock(event->getXPosition(), event->getYPosition());
    }
}