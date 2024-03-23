#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

/**
 * Proszę o utworzenie klasy `Enemy`, która będzie dziedziczyć po klasie `Object`
 * - Klasa ta powinna mieć mieć składową odpowiadającą ilości punktów życia, oraz getter: `lifePercent()`
 * - Klasa powinna mieć konstruktor przyjmujący aktualną pozycje oraz maksymalne życie z wartością domyślną.
 * - Klasa powinna mieć metodę `isAlieve()` która zwraca prawdę jeśli wróg ma życie powyżej zera
 * - Klasa powinna mieć metodę `decreaseLife()` przyjmującą jako argument liczbę obrażeń
 * - Po zaimplementowaniu powyższego proszę zakomentować makro `UNIMPLEMENTED_enemy`
 */

//#define UNIMPLEMENTED_enemy

class Enemy: public Object
{
private:
    int maxlifePoints_;
    int currentlifePoints_;
public:
    bool isAlieve() const;
    int lifePercent() const;
    void decreaseLife(int damage_);
    explicit Enemy(Position pos=Position(), int maxlifePoints = 100): Object(ObjectType::OBJECT_ENEMY, pos), maxlifePoints_(maxlifePoints), currentlifePoints_(maxlifePoints){};
    // TODO:
};

#endif // ENEMY_H
