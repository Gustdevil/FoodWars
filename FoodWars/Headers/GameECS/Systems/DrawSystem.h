#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"

class DrawSystem : public IBaseSystem {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    Renderlist _renderList;
    int _updateCallCount;
    double _deltaTimeTotal;
    std::string _fpsString;
public:
    DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade);
    ~DrawSystem();
    void generateTerrain();
    void generateTerrainDrawables(int x, int y);
    void update(double dt) override;
};


#endif //PROJECT_SWA_DRAWSYSTEM_H