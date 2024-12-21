#include "Explosion.h"
#include "Enemy.h"
#include "Game.h"

using namespace sf;

Explosion::Explosion(Texture& texture, Vector2f position,Vector2f scale,float duration = 0.5f,float speed = 0.3f)// Set the duration of the explosion
{

    // Explosion
    this->explosionSprite.setTexture(texture);
    this->explosionSprite.setPosition(position);
    this->explosionSprite.setScale(scale);
    this->duration = duration;
    this->speed = speed;


}

void Explosion::Update()
{
     float elapsedTime = this->clock.getElapsedTime().asSeconds();
        if (elapsedTime < duration)
        {
            float scale = 0.1f + (elapsedTime / duration) * speed; // Grow explosion slightly
            this->explosionSprite.setScale(scale, scale);
        }
}

void Explosion::Draw(RenderTarget &window)
{
    window.draw(this->explosionSprite);
}

bool Explosion::isFinished() const
{
    return clock.getElapsedTime().asSeconds() >= duration;
}
Explosion::~Explosion()
{

}
