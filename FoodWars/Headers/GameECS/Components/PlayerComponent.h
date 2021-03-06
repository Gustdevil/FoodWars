#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H

#include <memory>
#include <vector>
#include <string>
#include "Component.h"
#include "../../../Headers/StateMachine/Misc/Weapon.h"
#include "../../StateMachine/Misc/FactionEnum.h"

class PlayerComponent : public Component {
public:
    PlayerComponent();
    explicit PlayerComponent(int id, Faction faction);
public:
    void setPlayerID(int id);

    void setSelectedWeapon(const std::string &selectionType);
    void addScore(int score);
    void setFaction(Faction faction);
    void setIsAlive(bool alive);

    int getPlayerID() const;
    int getScore() const;
    Weapon* getSelectedWeapon() const;
    int getSelectedWeaponAvailability() const;
    int getAmountOFWeapons() const;

    Faction getFaction() const;
    bool isAlive() const;

    void addToWeaponType(const std::string &weaponType, int increaseBy);

    int getTotalAmmoCount() const;

    void accept(SerializationVisitor &visitor) override;

    void accept(DeserializationVisitor &visitor) override;

    std::string getName() const override;
protected:
    int _playerID;
    int _score;
    int _selectedWeaponAvailability;
    int _selectedWeaponIndex;
    bool _isAlive;
    std::vector<std::unique_ptr<Weapon>> _weapons{};
    Faction _faction;
    void initWeapon(int ammo, int ammo1, int ammo2);
    template<typename T, typename... Args>
    Weapon *createWeapon(Args &&... args) {
        std::unique_ptr<T> weapon = std::make_unique<T>(std::forward<Args>(args)...);
        _weapons.push_back(std::move(weapon));
        return weapon.get();
    }
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H
