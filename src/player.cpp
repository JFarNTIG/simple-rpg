#include "player.h"

Player::Player(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;
    this->isPlayer = true;

    this->Load("data/gfx/player.png");
    this->setPosition(x, y);
    this->speed = 0.00015f;;
    this->stamina = 4;
}

void Player::Update(sf::RenderWindow* window, InputManager inputManager, int timeElapsed) {
    float speed = this->speed * timeElapsed;
    // Sprint ability
    float sprintMultiplier;
    if(inputManager.IsPressed(InputManager::SprintAbility) && stamina>-1){
        sprintMultiplier = 3.0f;
        stamina -= 1.0f/60.0f;
    } else{
        sprintMultiplier = 1.0f;
        stamina += 1.0f/60.0f;
    }
    speed = speed * sprintMultiplier;
    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * speed -
                       inputManager.IsPressed(InputManager::Left) * speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * speed -
                       inputManager.IsPressed(InputManager::Up) * speed;

    // Set correct speed on diagonal movement
    if((this->velocity.x == speed || this->velocity.x == -speed)
    && (this->velocity.y == speed || this->velocity.y == -speed)) {
        this->velocity.x *= .75;
        this->velocity.y *= .75;
    }
    
}

float Player::GetSpeed() {
    return this->speed;
}

Player::~Player()
{

}
