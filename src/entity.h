#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
    Entity();
    Entity(std::string fileName, int movementState = 0);
    Entity(std::string fileName, sf::IntRect rect);
    void Load(std::string fileName);
    void Load(std::string fileName, sf::IntRect rect);
    bool Collision(Entity *entity);
    void SetActive(int active);
    int Active();
    int Group();
    virtual void Update();
    void UpdateTexture(std::string filePath);
    ~Entity();
    
    sf::Vector2f velocity;
    bool status;
    bool isPlayer;
protected:
    int active, groupId, movementState;

private:
    sf::Texture* texture;
};

#endif // ENTITY_H
