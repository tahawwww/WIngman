#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Bullet
{
    private:
        Texture *texture;
        Sprite sprite;

        Vector2f currentVelocity;
        float maxVelocity;
        float acceleration;
        Vector2f direction;


    public:
        Bullet(Texture *texture,Vector2f position, Vector2f scale,
               Vector2f direction,float initialVelocity,
               float maxVelocity,float acceleration);
        virtual ~Bullet();

        //Accessors
        inline FloatRect getGlobalBounds() const
        {
            return this->sprite.getGlobalBounds();
        }
        inline const Vector2f& getPosition() const
        {
            return this->sprite.getPosition();
        }



        // Functions
        void Movement();
        void Update();
        void Draw(RenderTarget &target);

    protected:


};

#endif // BULLET_H
