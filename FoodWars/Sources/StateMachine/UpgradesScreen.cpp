#include "../../Headers/StateMachine/UpgradesScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

UpgradesScreen::UpgradesScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
    _renderList._shapes[1].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenUpgrades.png"));

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [c = _context, &p = _previousScreen]() {  c->setActiveScreen(p); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _sprites.push_back(quitButton);
}

UpgradesScreen::~UpgradesScreen() = default;

void UpgradesScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void UpgradesScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void UpgradesScreen::setPreviousScreen(const std::string& screen){
    _previousScreen = screen;
}