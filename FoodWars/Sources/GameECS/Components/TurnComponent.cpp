//
// Created by pietb on 15-Oct-18.
//

#include "../../../Headers/GameECS/Components/TurnComponent.h"

// Pure default initialization
TurnComponent::TurnComponent() {
    _energy = 100;
    _remainingTime = 0;
}

// Alternative amount of energy
TurnComponent::TurnComponent(double energy): _energy(energy) {

}

TurnComponent::~TurnComponent() = default;

void TurnComponent::switchTurn(bool change) {
    _myTurn = change;
}

void TurnComponent::setRemainingTime(double t) {
    _remainingTime = t;
}

void TurnComponent::lowerRemainingTime(double t) {
    _remainingTime -= t;
}

double TurnComponent::getRemainingTime() const {
    return _remainingTime;
}

bool TurnComponent::isMyTurn() const {
    return _myTurn;
}

void TurnComponent::lowerEnergy(double delta) {
    _energy -= delta;
}

double TurnComponent::getEnergy() const {
    return _energy;
}

void TurnComponent::setEnergy(double energy) {
    _energy = energy;
}

void TurnComponent::setEnergy(int energy) {
    _energy = energy;
}

void TurnComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("energy", _energy);
    visitor.visit("remainingTime", _remainingTime);
    visitor.visit("myTurn", _myTurn);
}

std::string TurnComponent::getName() const {
    return "TurnComponent";
}

bool TurnComponent::getIsShooting() const {
    return _isShooting;
}

void TurnComponent::setIsShooting(bool change) {
    _isShooting = change;
}

void TurnComponent::changeIsShooting() {
    _isShooting = !_isShooting;
}