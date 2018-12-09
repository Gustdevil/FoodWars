//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"

TurnSystem::TurnSystem(EntityManager &entityManager) : _entityManager(&entityManager), _defaultTimePerTurn(30),
                                                       _timePerTurn(_defaultTimePerTurn)
{
}

TurnSystem::~TurnSystem() = default;

// Lower remaining time of 'active' TurnComponent
// If remainingTime <= 0, end turn.
void TurnSystem::update(double deltaTime) {
    std::map<int, TurnComponent *> turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    for(const auto &iterator: turnComponents) {
        if(iterator.second->isMyTurn()) {
            iterator.second->lowerRemainingTime(deltaTime);
            if(iterator.second->getRemainingTime() <= 0) {
                iterator.second->setRemainingTime(0);
                iterator.second->setEnergy(0);
            }
            break;
        }
    }
}

void TurnSystem::switchTurn() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if(iterator.second->isMyTurn()) {
            if((_entityManager->getComponentFromEntity<AIComponent>(iterator.first) && (iterator.second->getEnergy() <= 0.0 || iterator.second->getRemainingTime() <= 0))
            || _entityManager->getComponentFromEntity<PlayerComponent>(iterator.first)) {
                iterator.second->switchTurn(false);
                iterator.second->setEnergy(100);
                for (const auto &iterator2: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
                    if (iterator.first != iterator2.first) {
                        iterator2.second->switchTurn(true);
                        iterator2.second->setRemainingTime(30);
                    }
                }
                break;
            }
        }
    }
}

void TurnSystem::resetCurrentTime() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            iterator.second->setRemainingTime(30);
            break;
        }
    }
}

int TurnSystem::getCurrentPlayerID() const {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            return iterator.first;
        }
    }
}

void TurnSystem::resetCurrentEnergy() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            iterator.second->setEnergy(100);
            break;
        }
    }
}

double TurnSystem::getCurrentPlayerEnergy() const {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>())
        if (iterator.second->isMyTurn()) return iterator.second->getEnergy();
}



