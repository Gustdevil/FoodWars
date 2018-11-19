#include "../../Headers/StateMachine/HelpScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HelpScreen::HelpScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "wallpaper4.png"});

    // Backbutton
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "backbutton.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 100, 100, 9, 9, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);

    _renderList._shapes[1].push_back(new ShapeText(1040, 480, "'A'", 0, 30, 30, Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(new ShapeText(1040, 600, "'D'", 0, 30, 30, Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(new ShapeText(1040, 720, "'W'", 0, 30, 30, Colour(255, 255, 255, 0)));
}

HelpScreen::~HelpScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void HelpScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HelpScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
