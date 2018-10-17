//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_MAINMENUSCREEN_H
#define PROJECT_SWA_MAINMENUSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"

class MainMenuScreen : public IScreen {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
public:
    MainMenuScreen(std::shared_ptr<ScreenStateManager> context);
    ~MainMenuScreen();
    void update(double deltaTime) const override;
};

#endif //PROJECT_SWA_MAINMENUSCREEN_H
