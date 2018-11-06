#include "../../../Headers/GameECS/Systems/DamageableSystem.h"

DamageableSystem::DamageableSystem(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {
    _damageableComponents = _entityManager->getAllEntitiesWithComponent<DamageableComponent>();
    for(auto x : _damageableComponents)
    {
        if(!x.second->IsAlive())
        {
            _entityManager->removeEntity(x.first);
        }
    }
}