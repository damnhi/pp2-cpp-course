#include <algorithm>
#include "engine.h"
#include "player.h"
#include "stage.h"
#include "shoot.h"
#include "enemy.h"


namespace {
inline auto signum(int x)
{
    return (x > 0) - (x < 0);
}

Direction randDirection()
{
    auto randEdge = rand() % static_cast<uint8_t>(Direction::UPPER_LEFT);
    return static_cast<Direction>(randEdge);
}
} // namespace


Position generateNewEnemyPosition(int width, int height)
{
    Position position2Generate = Position(rand() % width, rand() % height);

    switch (randDirection()) {
        case Direction::UP:
            position2Generate.y_ = height-1;
            break;
        case Direction::DOWN:
            position2Generate.y_ = 0;
            break;
        case Direction::LEFT:
            position2Generate.x_ = 0;
            break;
        case Direction::RIGHT:
            position2Generate.x_ = width-1;
            break;
        default:
            break;
    }
    return position2Generate;
}


Engine::~Engine() = default;



Engine::Engine(std::size_t stageWidth, std::size_t stageHeight):
    player_(new Player(ObjectType::OBJECT_PLAYER,Position(10,5),Direction::RIGHT)), stage_(new Stage(stageWidth, stageHeight))
{
    // TODO...
}

void Engine::update()
{
    updateBullets();
    updateEnemies();
    randEnemies();
}

void Engine::updateBullets()
{
    // TODO...
}

void Engine::updateEnemies()
{
    // TODO...
}

void Engine::movePlayerUp()
{
    // TODO...
    return player_->moveUp();
}

void Engine::movePlayerDown()
{
    // TODO...
    return player_->moveDown();
}

void Engine::movePlayerLeft()
{
    // TODO...
    return player_->moveLeft();
}
void Engine::movePlayerRight()
{
    // TODO...
    return player_->moveRight();
}

void Engine::playerShoots()
{
    // TODO...
    movePlayerRight();
    const Shoot this_shoot=Shoot( playerDirection(),playerPosition());
    shoots_.push_back(this_shoot);
}

Position Engine::playerPosition() const
{
    // TODO...
    return player_->position();
}

Direction Engine::playerDirection() const
{
    // TODO...
    return player_->direction();
}

bool Engine::isPlayerAlieve() const
{
    // TODO...
    return player_->isAlieve();
}

std::size_t Engine::stageWidthCells() const
{
    // TODO...

    return stage_->width();
}
std::size_t Engine::stageHeightCells() const
{
    // TODO...
    return stage_->height();
}

void Engine::randEnemies(Position (*positionGenerator)(int,int))
{
    if (enemies_.size() < maxEnemies_)
    {
        // TODO...
    }
}
