#include "../../../Headers/GameECS/Systems/ShootSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include <math.h>


ShootSystem::ShootSystem(std::shared_ptr<EntityManager> entityManager,
                            std::shared_ptr<AudioFacade> audioFacade,
                            std::shared_ptr<VisualFacade> visualFacade,
                                std::shared_ptr<InputFacade> inputFacade) :
                                                _audioFacade(std::move(audioFacade)),
                                                _entityManager{std::move(entityManager)},
                                                _visualFacade{std::move(visualFacade)},
                                                _isShooting{false},
                                                _projectileFired{false},
                                                _projectile{0}
{
    inputFacade->getMouseEventObservable()->registerObserver(this);
}

ShootSystem::~ShootSystem() = default;

void ShootSystem::update(double deltaTime) {
    if (!_entityManager->exists(_projectile)) _projectileFired = false;
    if(_projectileFired)
    {
        auto projectilePos = _entityManager->getComponentFromEntity<PositionComponent>(_projectile);
        auto projectileSize = _entityManager->getComponentFromEntity<BoxCollider>(_projectile);
        auto projectileMove = _entityManager->getComponentFromEntity<MoveComponent>(_projectile);

        std::cout << projectilePos->X << ", " << projectilePos->Y << std::endl;
        if ((projectilePos->X + projectileSize->width) >= 1590 || projectilePos->X <= 1
                || (projectilePos->Y + projectileSize->height) >= 890) {
            _projectileFired = false;
            _entityManager->removeEntity(_projectile);
        }

    }
}

void ShootSystem::update(std::shared_ptr<MouseEvent> event) {
    if(_isShooting && !_projectileFired)
    {
        int currentPlayer = 0;
        auto turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const &x : turnComponents)
        {
            if (x.second->isMyTurn()) {
                currentPlayer = x.first;
                break;
            }
        }
        auto currentPlayerPos = _entityManager->getComponentFromEntity<PositionComponent>(currentPlayer);
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Left) {
            double distance = hypot(event->getXPosition() - currentPlayerPos->X, currentPlayerPos->Y - event->getYPosition());

            auto playerSize = _entityManager->getComponentFromEntity<BoxCollider>(currentPlayer);
            double angleX = event->getXPosition() - (currentPlayerPos->X);
            double angleY = event->getYPosition() - (currentPlayerPos->Y);

            generateProjectile(currentPlayerPos, angleX, angleY);
            _isShooting = false;
            _projectileFired = true;

            _entityManager->getComponentFromEntity<TurnComponent>(currentPlayer)->lowerEnergy(20);
            _audioFacade->playEffect("jump");
        }
    }
}

void ShootSystem::toggleShooting() {
    _isShooting = !_isShooting;
}

void ShootSystem::generateProjectile(std::shared_ptr<PositionComponent> pos, double velocityX, double velocityY) {
    _projectile = _entityManager->createEntity();
    int posX = pos->X + static_cast<int>(velocityX / 4);
    int posY = pos->Y + static_cast<int>(velocityY / 4);

    auto drawableComponent = new DrawableComponent;
    drawableComponent->shape = new ShapeSprite(11, 38, posX, posY, "carrot.png");

    _entityManager->addComponentToEntity(_projectile, drawableComponent);
    _entityManager->addComponentToEntity(_projectile, new PositionComponent(posX, posY));
    _entityManager->addComponentToEntity(_projectile, new BoxCollider(11, 38));
    _entityManager->addComponentToEntity(_projectile, new DamagingComponent(100));
    _entityManager->addComponentToEntity(_projectile, new DamageableComponent { 10 });
    _entityManager->addComponentToEntity(_projectile, new GravityComponent(20));

    auto moveComponent = new MoveComponent();
    moveComponent->xVelocity = velocityX;
    moveComponent->yVelocity = velocityY * 5;
    _entityManager->addComponentToEntity(_projectile, moveComponent);
}