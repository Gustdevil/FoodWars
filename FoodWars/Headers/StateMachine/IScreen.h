#include <utility>

#ifndef PROJECT_SWA_ISCREEN_H
#define PROJECT_SWA_ISCREEN_H

#include "memory"
#include "../../../TonicEngine/Headers/Input/WindowClosedObserver.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"

class ScreenStateManager;

class IScreen : IObserver<WindowEvent>{
protected:
    std::shared_ptr<ScreenStateManager> _context;
    std::shared_ptr<InputFacade> _inputFacade;
    bool _isClosed;
public:

    IScreen(std::shared_ptr<ScreenStateManager> context) : _context(std::move(context)), _inputFacade(std::make_shared<InputFacade>()), _isClosed(false) {
        _inputFacade->getWindowEventObservable()->registerObserver(this);
    }

    ~IScreen() {

    }
    virtual void update(double deltaTime) {

    }

    void update(std::shared_ptr<WindowEvent> event) {
        if (event->GetWindowEventType() == WindowEventType::Quit) {
            _isClosed = true;
        }
    }
    bool isWindowClosed() const {
        return _isClosed;
    }
};
#endif //PROJECT_SWA_ISCREEN_H