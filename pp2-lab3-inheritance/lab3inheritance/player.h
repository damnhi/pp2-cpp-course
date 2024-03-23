#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "direction.h"

/**
 * Proszę o utworzenie klasy `Player`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_playerIsObject`
 * - Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter. Domyślna wartość to `Direction::RIGHT`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerHasDirection`
 * - Klasa powinna mieć składową oznaczającą czy gracz żyje, oraz getter i setter: `isAlieve()`, `setIsAlieve()`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerCanDie`
 */

//#define UNIMPLEMENTED_playerIsObject
//#define UNIMPLEMENTED_playerHasDirection
//#define UNIMPLEMENTED_playerCanDie

class Player:public Object
{
private:
        Direction direction_;
        bool isAlive_ = true;
// TODO...
public:
    Direction direction()
    {
        return direction_;
    }

    void setDirection(Direction newDirection_)
    {
        direction_= newDirection_;
    }
    explicit Player(ObjectType objectType=ObjectType::OBJECT_PLAYER, Position pos=Position(), Direction direction=Direction::RIGHT): Object(objectType, pos), direction_(direction){};

    bool isAlieve()
    {
        return isAlive_;
    }
    void setIsAlieve(bool newAliveStatus)
    {
        isAlive_ = newAliveStatus;
    }

};

#endif // PLAYER_H
