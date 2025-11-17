#include "player.h"

Player::Player(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;

    this->Load("data/gfx/rat.png");
    this->setPosition(x, y);
    this->setScale(-2.5, 2);
    this->setOrigin(0, 0);
    this->speed = 0.00015f;
}

void Player::Update(sf::RenderWindow* window, InputManager inputManager, int timeElapsed) {
    float speed = this->speed * timeElapsed;
    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * speed -
                       inputManager.IsPressed(InputManager::Left) * speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * speed -
                       inputManager.IsPressed(InputManager::Up) * speed;

    if(this->velocity.x > 0) {
        this->setScale(-2.5, 2);
        this->setOrigin(0, 0);
    } else if(this->velocity.x < 0) {
        this->setScale(2.5, 2);
        this->setOrigin(40, 0);
    };
    
    // .x = (this->velocity.x > 0) ? -1 : (this->velocity.x < 0) ? 1 : this->scale.x;

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
