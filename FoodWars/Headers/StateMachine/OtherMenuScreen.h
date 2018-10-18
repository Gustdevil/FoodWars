//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_OTHERMENUSCREEN_H
#define PROJECT_SWA_OTHERMENUSCREEN_H

//TODO: is memory needed?
//#include "memory"
#include "IScreen.h"
#include "ScreenStateManager.h"

class OtherMenuScreen : public IScreen {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
public:
    OtherMenuScreen(std::shared_ptr<ScreenStateManager> context);
    ~OtherMenuScreen();
    void update(double deltaTime) const override;
};

#endif //PROJECT_SWA_OTHERMENUSCREEN_H
