#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <SFML/Graphics.hpp>
 using namespace std;
 using namespace sf;

class Explosion
{
    private:

        Vector2f position;
        Sprite explosionSprite;

        Clock clock;
        float duration; // Duration of the explosion in seconds
        float speed; // Set speed of Explosion

    public:
        Explosion(Texture& texture, Vector2f position,Vector2f scale,float duration ,float speed);
        virtual ~Explosion();
        void Update();
        void Draw(sf::RenderTarget& window);
        bool isFinished() const;


};

#endif // EXPLOSION_H
