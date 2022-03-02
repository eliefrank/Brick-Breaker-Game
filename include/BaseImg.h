#pragma once
#include "ResourceManager.h"

class BaseImg
{
public:
    BaseImg(const sf::Vector2f& position, const sf::Vector2f& size, const Type t);
    virtual ~BaseImg() = default;
    virtual void draw(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setTransparent(bool trans);
    void setTexture(Type t);
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
   
private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
};
