#include "../../Headers/StateMachine/LevelCreationScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelCreationScreen::LevelCreationScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->getMouseEventObservable()->registerObserver(this);
    _windowResCalc = _context->getWindowResolutionCalculator();
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
    this->initButtons();
}

void LevelCreationScreen::initButtons() {

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    //Color Red Increment
    SpriteButton* RedIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorRed(); }, 50, 50, 1520, 10, Colour{0,0,0,0}};
    RedIncrementButton->addToRender(&_renderList);
    _buttons.push_back(RedIncrementButton);

    //Color Red Decrement
    SpriteButton* RedDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorRed(); }, 50, 50, 1370, 10, Colour{0,0,0,0}};
    RedDecrementButton->addToRender(&_renderList);
    _buttons.push_back(RedDecrementButton);

    //Color Green Increment
    SpriteButton* GreenIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorGreen(); }, 50, 50, 1520, 75, Colour{0,0,0,0}};
    GreenIncrementButton->addToRender(&_renderList);
    _buttons.push_back(GreenIncrementButton);

    //Color Green Decrement
    SpriteButton* GreenDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorGreen(); }, 50, 50, 1370, 75, Colour{0,0,0,0}};
    GreenDecrementButton->addToRender(&_renderList);
    _buttons.push_back(GreenDecrementButton);

    //Color Blue Increment
    SpriteButton* BlueIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorBlue(); }, 50, 50, 1520, 140, Colour{0,0,0,0}};
    BlueIncrementButton->addToRender(&_renderList);
    _buttons.push_back(BlueIncrementButton);

    //Color Blue Decrement
    SpriteButton* BlueDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorBlue(); }, 50, 50, 1370, 140, Colour{0,0,0,0}};
    BlueDecrementButton->addToRender(&_renderList);
    _buttons.push_back(BlueDecrementButton);


    //Wallpaper Next
    SpriteButton* WallpaperNext = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.setNextWallpaper(); }, 50, 50, 710, 10, Colour{0,0,0,0}};
    WallpaperNext->addToRender(&_renderList);
    _buttons.push_back(WallpaperNext);

    //Wallpaper Previous
    SpriteButton* WallpaperPrevious = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.setPreviousWallpaper(); }, 50, 50, 460, 10, Colour{0,0,0,0}};
    WallpaperPrevious->addToRender(&_renderList);
    _buttons.push_back(WallpaperPrevious);

    toggleCollidable = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOff.png", [this] {
        bool state = _levelBuilder.toggleCollidable();
        if (state) {
            toggleCollidable->changeImageURL(std::string("stateOn.png"));
        } else {
            toggleCollidable->changeImageURL(std::string("stateOff.png"));
        }
    }, 50, 50, 1030, 10, Colour{0, 0, 0, 0}};
    _buttons.push_back(toggleCollidable);

    toggleDamageable = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOff.png", [this] {
        bool state = _levelBuilder.toggleDamageable();
        if (state) {
            toggleDamageable->changeImageURL(std::string("stateOn.png"));
        } else {
            toggleDamageable->changeImageURL(std::string("stateOff.png"));
        }
    }, 50, 50, 1030, 85, Colour{0, 0, 0, 0}};
    _buttons.push_back(toggleDamageable);
}

LevelCreationScreen::~LevelCreationScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void LevelCreationScreen::update(double deltaTime) {
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelCreationScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
        this->callRender();
    }
}

void LevelCreationScreen::update(std::shared_ptr<MouseEvent> event) {
    this->callRender();
    if(event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Left){
        _levelBuilder.placeBlock(event->getXPosition(), event->getYPosition());
    }
    if(event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Right){
        _levelBuilder.removeBlock(event->getXPosition(), event->getYPosition());
    }
}

void LevelCreationScreen::callRender() {
    _renderList.clearLists();
    _levelBuilder.drawCurrentScene(_renderList);
    for(int i=0; i < _buttons.size(); i++){
        _buttons[i]->addToRender(&_renderList);
    }
    visualFacade->render(_renderList);
}