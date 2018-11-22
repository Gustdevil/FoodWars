#include <utility>
#include "../../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include <math.h>

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> entityManager) : _entityManager(std::move(entityManager)) {

}

void CollisionSystem::update(double dt) {
    std::map<int, std::shared_ptr<BoxCollider>> entitiesWithCollider = _entityManager->getAllEntitiesWithComponent<BoxCollider>();

    for(auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        int entity = iterator.first;
        std::shared_ptr<BoxCollider> collider = entitiesWithCollider[entity];
        if(!collider) continue;
        std::shared_ptr<MoveComponent> moveComponent = iterator.second;
        std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(entity);
        if(positionComponent && (std::abs(moveComponent->xVelocity) > 0 || std::abs(moveComponent->yVelocity) > 0)) {
            for (auto const &collideAbleIterator : entitiesWithCollider) {
                int otherEntity = collideAbleIterator.first;
                if (otherEntity == entity) continue;
                std::shared_ptr<BoxCollider> otherCollider = collideAbleIterator.second;
                std::shared_ptr<PositionComponent> otherPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
                if (positionComponent) {
                    bool collisionOccured = positionComponent->X < otherPosition->X + otherCollider->width &&
                                  positionComponent->X + collider->width > otherPosition->X &&
                                  positionComponent->Y < otherPosition->Y + otherCollider->height &&
                                  positionComponent->Y + collider->height > otherPosition->Y;
                    if(collisionOccured) {
                        double centerX = positionComponent->X + (collider->width / 2.0);
                        double centerY = positionComponent->Y + (collider->height / 2.0);
                        double otherCenterX = otherPosition->X + otherCollider->width / 2.0;
                        double otherCenterY = otherPosition->Y + otherCollider->height / 2.0;
                        double angle = (std::atan2(otherCenterX - centerX, otherCenterY - centerY)) * 360 / (2 * M_PI);
                        if(angle < 0) angle += 360;
                        notify(std::make_shared<CollisionEvent>(CollisionEvent{entity, otherEntity, angle}));
                        if(angle > 315 || angle <= 45) positionComponent->Y = otherPosition->Y - collider->height; // moving entity on top of other
                        if(angle >= 45 && angle <= 135 && moveComponent->xVelocity > 0) positionComponent->X = otherPosition->X - collider->width - 1; // moving entity left of other
                        if(angle > 135 && angle < 225 && moveComponent->yVelocity < 0)  positionComponent->Y = otherPosition->Y + otherCollider->height; // moving entity below other
                        if(angle >= 225 && angle <= 315 && moveComponent->xVelocity < 0) positionComponent->X = otherPosition->X + otherCollider->width; // moving entity right of other
                    }
                }
            }
        }
    }
}
