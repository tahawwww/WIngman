#include "Player.h"
#include "Game.h"
using namespace std;

enum controls{UP=0, DOWN,LEFT,RIGHT,SHOOT};
enum weapons {LASER=0,MISSILE01,MISSILE02};
unsigned Player :: players =0;

Player::Player(std::vector<Texture> &textures,
                int UP,int DOWN,
                int LEFT,int RIGHT,
                int SHOOT)
    :level(1),exp(0),expNext(100),hp(10),hpMax(10),
    damage(1),damageMax(2),score(0)
{
    // Update Position
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height/2;

    // Textures and Sprites
    this-> sprite.setTexture(textures[0]);
    this-> sprite.setScale(0.3f,0.3f);

    this-> laserTexture = &textures[1];
    this-> missile01Texture = &textures[2];

    this-> mainGunSprite.setTexture(textures[3]);
    this-> mainGunSprite.setOrigin(this->mainGunSprite.getGlobalBounds().width/2,
                                   this->mainGunSprite.getGlobalBounds().height/2);
    this->mainGunSprite.setScale(0.3f,0.3f);
    this->mainGunSprite.setPosition(this->playerCenter.x +20.f,this->playerCenter.y);

    // Timers
    this->shootTimerMax = 25;
    this->shootTimer = this->shootTimerMax;
    this->damageTimer = 10;
    this->damageTimer = this->damageTimer;

    // Controls
    this-> controls[controls::UP] = UP;
    this-> controls[controls::DOWN] = DOWN;
    this-> controls[controls::LEFT] = LEFT;
    this-> controls[controls::RIGHT] = RIGHT;
    this-> controls[controls::SHOOT] = SHOOT;

    // Velocity and accelerations
    this-> maxVelocity = 15.f;
    this-> acceleration = 0.8f;
    this-> stabilizerForce = 0.4f;

    // Guns
    this-> currentWeapon = LASER;

    // Upgrades
    this-> mainGunLevel =0;
    this-> dualMissiles01=false;
    this-> dualMissiles02=false;

    // Add number of player for co-op
    this->playerNr=Player::players;
    Player::players++;


}

void Player::UpdateAccessories()
{
    // Set the gun position so that it follows player
    this->mainGunSprite.setPosition(this->mainGunSprite.getPosition().x,
                                    this->playerCenter.y);

    // Animate the main Gun and correct it after firing
    if(this->mainGunSprite.getPosition().x < this->playerCenter.x + 20.f)
    {
        this->mainGunSprite.move(2.f + this->currentVelocity.x,0.f);
    }

    if(this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f)
    {
        this->mainGunSprite.setPosition(this->playerCenter.x +20.f,this->playerCenter.y);
    }

}
Player::~Player()
{

}
void Player ::Movement()
{
    // UP
    if(Keyboard::isKeyPressed(Keyboard::Key(this-> controls[controls::UP])))
    {
        this->direction.x = 0.f;
        this->direction.y = -1.f;

        if(this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }

    // DOWN
    if(Keyboard::isKeyPressed(Keyboard::Key(this-> controls[controls::DOWN])))
    {
        this->direction.x = 0.f;
        this->direction.y = 1.f;

        if(this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
            this->currentVelocity.x += this->direction.x * this->acceleration;

        if(this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }

    // LEFT
    if(Keyboard::isKeyPressed(Keyboard::Key(this-> controls[controls::LEFT])))
    {
        this->direction.x = -1.f;
        this->direction.y = 0.f;

        if(this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
            this->currentVelocity.x += this->direction.x * this->acceleration;

    }

    // RIGHT
    if(Keyboard::isKeyPressed(Keyboard::Key(this-> controls[controls::RIGHT])))
    {
        this->direction.x = 1.f;
        this->direction.y = 0.f;

        if(this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
            this->currentVelocity.x += this->direction.x * this->acceleration;

    }

    // Drag force
    if(this->currentVelocity.x > 0)
    {
        this->currentVelocity.x -= this->stabilizerForce;
        if(this->currentVelocity.x < 0)
            this->currentVelocity.x =0;
    }
    else if(this->currentVelocity.x < 0)
    {
        this->currentVelocity.x += this->stabilizerForce;
        if(this->currentVelocity.x > 0)
            this->currentVelocity.x =0;
    }

    if(this->currentVelocity.y > 0)
    {
        this->currentVelocity.y -= this->stabilizerForce;
        if(this->currentVelocity.y < 0)
            this->currentVelocity.y =0;
    }
    else if(this->currentVelocity.y < 0)
    {
        this->currentVelocity.y += this->stabilizerForce;
        if(this->currentVelocity.y > 0)
            this->currentVelocity.y = 0;
    }

    // Final Move
    this->sprite.move(this->currentVelocity);

    // Update Position
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height/2;
}
void Player::Combat()
{
    // SHOOT
    if(Keyboard::isKeyPressed(Keyboard::Key(this-> controls[controls::SHOOT]))
       && this->shootTimer >= this->shootTimerMax)
    {
        if(this->currentWeapon==LASER)
        {
            // Create Bullet
            if(this->mainGunLevel==0)
            {
                this->bullets.push_back(Bullet(laserTexture,
                                    Vector2f(this->playerCenter.x + 35.f ,this->playerCenter.y),
                                    Vector2f(0.12f,0.12f),
                                    Vector2f(1.f,0.f),
                                    20.f, 60.f, 3.f));
            }
            else if(this->mainGunLevel==1)
            {
                this->bullets.push_back(Bullet(laserTexture,
                                    Vector2f(this->playerCenter.x + 35.f ,this->playerCenter.y),
                                    Vector2f(0.12f,0.12f),
                                    Vector2f(1.f,0.f),
                                    20.f, 60.f, 3.f));
            }
            else if(this->mainGunLevel==2)
            {
                this->bullets.push_back(Bullet(laserTexture,
                                    Vector2f(this->playerCenter.x + 35.f ,this->playerCenter.y),
                                    Vector2f(0.12f,0.12f),
                                    Vector2f(1.f,0.f),
                                    20.f, 60.f, 3.f));
            }
            // Animate gun
            this->mainGunSprite.move(-30.f,0.f);
        }
        else if(this->currentWeapon==MISSILE01)
        {
            // Create Bullet
            this->bullets.push_back(Bullet(missile01Texture,
                                    Vector2f(this->playerCenter.x + 35.f ,this->playerCenter.y -25.f),
                                    Vector2f(0.12f,0.12f),
                                    Vector2f(1.f,0.f),
                                    2.f, 50.f, 1.f));
            if(this->dualMissiles01)
            {
                this->bullets.push_back(Bullet(missile01Texture,
                                    Vector2f(this->playerCenter.x + 35.f ,this->playerCenter.y +25.f),
                                    Vector2f(0.12f,0.12f),
                                    Vector2f(1.f,0.f),
                                    2.f, 50.f, 1.f));
            }
            // Animate gun
            this->mainGunSprite.move(-30.f,0.f);
        }
        else if(this->currentWeapon==MISSILE02)
        {
            if(this->dualMissiles02)
            {

            }
        }


        this-> shootTimer = 0; //Reset Timer
    }
}
void Player::Update(Vector2u WindowBounds)
{
    //Update Timers
    if(this->shootTimer < this->shootTimerMax)
    {
        this->shootTimer++;
    }
    if(this->damageTimer < this->damageTimerMax)
    {
        this->damageTimer++;
    }

    this->Movement();
    this-> UpdateAccessories();
    this->Combat();
}
void Player::Draw(RenderTarget &target)
{
    for(size_t i=0; i< this->bullets.size();i++)
    {
        this->bullets[i].Draw(target);
    }
    target.draw(this->mainGunSprite);
    target.draw(this->sprite);
}
