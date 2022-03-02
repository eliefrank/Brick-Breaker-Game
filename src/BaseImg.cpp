#include "BaseImg.h"

BaseImg::BaseImg(const sf::Vector2f& position, const sf::Vector2f& size, const Type t)
    :m_position(position), m_sprite(*ResourceManager::instance().getTexture(t))
{
    m_sprite.setOrigin(getSize().x / 2, getSize().y / 2);
    setPosition(m_position);
    setSize(size);
}

void BaseImg::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

void BaseImg::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

sf::Vector2f BaseImg::getPosition() const
{
    return m_sprite.getPosition();
}

void BaseImg::setTransparent(bool trans)
{
    if(trans)
        m_sprite.setColor(sf::Color(255, 255, 255, 120));
    else
        m_sprite.setColor(sf::Color(255, 255, 255, 255));
}

void BaseImg::setTexture(Type t)
{
    m_sprite.setTexture(*ResourceManager::instance().getTexture(t));
}

void BaseImg::setSize(const sf::Vector2f& size)
{
    m_sprite.scale((size.x / getSize().x), (size.y / getSize().y));

}

sf::Vector2f BaseImg::getSize() const
{
    return sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}
