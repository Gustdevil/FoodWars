#ifndef PROJECT_SWA_LEVELBUILDER_H
#define PROJECT_SWA_LEVELBUILDER_H


#include "../../GameECS/Entities/EntityManager.h"
#include "EntityMomento.h"
#include "../../../../TonicEngine/Headers/Visual/Renderlist.h"

const int MINIMAL_SHAPE_DIM = 32;
const int MAXIMAL_SHAPE_DIM = 32;
const int COLOR_INCREMENT = 5;

class LevelBuilder {
public:
    LevelBuilder();
    ~LevelBuilder() = default;
private:
    EntityManager* _entityManager = nullptr;
    std::vector<EntityMomento*> _momentoList;
    Renderlist _renderList;
    bool _buildCollidable;
    bool _buildDamageable;

    int _shapeDimension = MINIMAL_SHAPE_DIM;

    int _colorRed = 0; //Between 0 and 255
    int _colorGreen = 0; //Between 0 and 255
    int _colorBlue = 0; //Between 0 and 255
public:
    void resetEntityManager();

    void incrementShapeSize();
    void decrementShapeSize();

    void incrementColorRed();
    void incrementColorGreen();
    void incrementColorBlue();

    void decrementColorRed();
    void decrementColorGreen();
    void decrementColorBlue();

    void placeBlock(int x, int y);
    void undoPlaceBlock();

    Renderlist drawCurrentScene();
};


#endif //PROJECT_SWA_LEVELBUILDER_H
