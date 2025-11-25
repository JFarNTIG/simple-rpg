#include "entity.h"
#include <random>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

Entity::Entity() {
    this->active = 1;
    this->texture = new sf::Texture();
    this->isPlayer = false;
    this->status = false;
}

Entity::Entity(std::string fileName, int movementState) {
    this->isPlayer = false;
    this->status = false;
    this->active = 1;
    this->texture = new sf::Texture;
    this->Load(fileName);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
    this->movementState = movementState;
}

Entity::Entity(std::string fileName, sf::IntRect rect) {
    this->active = 1;
    this->isPlayer = false;
    this->status = false;
    this->texture = new sf::Texture();
    this->Load(fileName, rect);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
}

void Entity::Load(std::string fileName) {
    this->texture->loadFromFile(fileName, sf::IntRect());
    this->setTexture(*this->texture);
}

void Entity::Load(std::string fileName, sf::IntRect rect) {
    this->texture->loadFromFile(fileName, rect);
    this->setTexture(*this->texture);
}

bool Entity::Collision(Entity *entity) {
    if(entity != NULL) {
        return this->getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    return false;
}

void Entity::SetActive(int active) {
    this->active = active;
}

void Entity::setDialogue(std::vector<std::wstring> dialogue_options) {
    this->dialogue_options = dialogue_options;
}

float Entity::calculateLength(Entity* entity) {
    float length = sqrt(pow(this->getPosition().x  - entity->getPosition().x,2) + pow(this->getPosition().y - entity->getPosition().y, 2));
    return length;
}

int Entity::Active() {
    return this->active;
}

int Entity::Group() {
    return this->groupId;
}

void Entity::Update() {
    if (this->movementState == 1) {
        // Roaming beahviour, randomised movement.
        this->velocity.x += (rand() % 3 - 1) * 0.1;
        this->velocity.y += (rand() % 3 - 1) * 0.1;
        //std::cout << "Velocity: " << this->velocity.x << ", " << this->velocity.y << std::endl;
        this->move(this->velocity);
    }
    else{
        this->move(this->velocity);
    }
}
//för att allmänt ändra textur.//
void Entity::UpdateTexture(std::string filePath){
    this->texture = new sf::Texture();
    this->Load(filePath);
}

Entity::~Entity() {
    delete this->texture;
}

// Will output a random dialogue from the dialogue_options vector
std::wstring Entity::Dialogue() {

    if (!hasSpoken) {
        std::mt19937 eng(time(0));
        std::uniform_int_distribution<int> number(0, 5);
        int random_number = number(eng);
        dialogue_option = dialogue_options[random_number];

        hasSpoken = true;
    }
    return dialogue_option;
}