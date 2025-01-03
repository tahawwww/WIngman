#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"
#include "Bullet.h"

using namespace sf;

class Player
{
    private:
        unsigned playerNr;

        Vector2f playerCenter;

        int shootTimerMax;
        int shootTimer;
        int damageTimer;
        int damageTimerMax;

        Sprite sprite;
        RectangleShape hitbox;

        // Audio
        SoundBuffer laserSound;
        Sound laser;

        // Accessories
        Sprite mainGunSprite;
        std::vector<Bullet> bullets;
        Texture *laserTexture;
        Texture *bulletTexture;
        Texture *missile01Texture;
        Texture *missile02Texture;

        int controls[5];
        Vector2f currentVelocity;
        float maxVelocity;
        float acceleration;
        Vector2f direction;
        float stabilizerForce;

        int level;
        int exp;
        int expNext;

        int hp;
        int hpMax;

        int damage;
        int damageMax;
        int currentWeapon;

        // Upgrades
        bool dualMissiles01;
        bool dualMissiles02;
        int mainGunLevel;

        int score;

    public:

        Player(std::vector<Texture> &textures,
               int UP=22,int DOWN=18,
                int LEFT=0,int RIGHT=3,
                int SHOOT=57);
        virtual ~Player();

        // Accessors
        inline std::vector<Bullet>& getBullets()
        {
            return this->bullets;
        }
        inline Vector2f getPosition() const
        {
            return this->sprite.getPosition();
        }
        void setPosition(float x, float y)
        {
            return this->sprite.setPosition(x,y);
        }
        inline const String getHpAsString() const
        {
            return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
        }
        inline const int getDamage() const
        {
            return rand() % this->damageMax + this->damage;
        }
        inline FloatRect getGlobalBounds() const
        {
            return this->sprite.getGlobalBounds();
        }
        inline const int& getHP() const
        {
            return this->hp;
        }
        inline const int& getHPMax() const
        {
            return this->hpMax;
        }
        inline void takeDamage(int damage)
        {
            this->hp-=damage;
        }
        inline bool isAlive() const
        {
            return this-> hp > 0;
        }
        inline const int& getPlayerNr() const
        {
            return this->playerNr;
        }


        // Functions
        void UpdateAccessories();
        void Combat();
        void Movement();
        void Update(Vector2u WindowBounds);
        void Draw(RenderTarget &target);

        //Statics
        static unsigned players;

    protected:


};

#endif // PLAYER_H
