#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"

using namespace std;
using namespace sf;


enum textures {player = 0, laser01 ,missile01, mainGun01, enemy01, bigEnemy, fastEnemy, meme01,meme02};

Game::Game(RenderWindow *window)
{
    this->window = window;
    this->window->setFramerateLimit(60);

    // Initialize Fonts
    this->font.loadFromFile("Textures/font_1.otf");

    // Wallpaper
    this->wallpaperTexture.loadFromFile("Textures/wallpaper.jpg");
    this->wallpaperSprite.setTexture(this->wallpaperTexture);
    Vector2u windowSize = this->window->getSize();
    Vector2u textureSize = this->wallpaperTexture.getSize();
        this->wallpaperSprite.setScale(
            static_cast<float>(windowSize.x) / textureSize.x,
            static_cast<float>(windowSize.y) / textureSize.y
            );

    // Audio
    this->backgroundMusic.openFromFile("Textures/bg_music.wav");
    this->backgroundMusic.setLoop(true);
    this->backgroundMusic.setVolume(10);
    this->backgroundMusic.play();

    this->gameOverAudio.openFromFile("Textures/game_over.wav");
    this->gameOverAudio.setVolume(70);

    Texture enemyExplosionTexture;
    if (enemyExplosionTexture.loadFromFile("Textures/explosion_1.png"))
    {
        this->explosionTextures.push_back(enemyExplosionTexture); // Texture for enemy explosions
    }
    else { std::cerr << "Failed to load enemy explosion texture!" << std::endl; }

    Texture playerExplosionTexture;
    if (playerExplosionTexture.loadFromFile("Textures/explosion_4.png"))
    {
        this->explosionTextures.push_back(playerExplosionTexture); // Texture for player explosions
    }
    else { std::cerr << "Failed to load player explosion texture!" << std::endl; }

    // Initialize textures
    this->textures.push_back(Texture());
    this->textures[player].loadFromFile("Textures/ship_3.png");
    this->textures.push_back(Texture());
    this->textures[laser01].loadFromFile("Textures/bullet_6.png");
    this->textures.push_back(Texture());
    this->textures[missile01].loadFromFile("Textures/gun_3.png");
    this->textures.push_back(Texture());
    this->textures[mainGun01].loadFromFile("Textures/gun_4.png");
    this->textures.push_back(Texture());
    this->textures[enemy01].loadFromFile("Textures/enemy.png");
    this->textures.push_back(Texture());
    this->textures[bigEnemy].loadFromFile("Textures/enemy_2.png");
    this->textures.push_back(Texture());
    this->textures[fastEnemy].loadFromFile("Textures/enemy_4.png");
    this->textures.push_back(Texture());
    this->textures[meme01].loadFromFile("Textures/Anss.png");
    this->textures.push_back(Texture());
    this->textures[meme02].loadFromFile("Textures/Ali.png");

    // Initialize player
    this->players.push_back(Player(this->textures));
    this->players.push_back(Player(this->textures,Keyboard::I,Keyboard::K,Keyboard::J,Keyboard::L,Keyboard::RShift));
    this->playersAlive = this->players.size();

    // Initialize Enemies
    Enemy e1(&this->textures[enemy01], this->window->getSize(),
                            Vector2f(0.f,0.f), Vector2f(-1.f,0.f), Vector2f(0.1f,0.1f),
                            0, rand()%3 +1 , 2, 1);

    this->enemiesSaved.push_back(Enemy(e1));
    this-> enemySpawnTimerMax =45;
    this-> enemySpawnTimer = this-> enemySpawnTimerMax;

    this->InitUI();
}
Game::~Game()
{
    cout<<"game stooped";
}
void Game:: InitUI()
{
    Text tempText;

    for(size_t i=0; i< this->players.size(); i++)
    {
        //Follow Text Init
        tempText.setFont(font);
        tempText.setCharacterSize(25);
        tempText.setFillColor(Color::White);
        tempText.setString(to_string(i));

        this->followPlayerTexts.push_back(Text (tempText));


        // Static Text Init
        tempText.setFont(font);
        tempText.setCharacterSize(25);
        tempText.setFillColor(Color::White);
        tempText.setString("");

        this->staticPlayerTexts.push_back(Text (tempText));
    }
        // Enemy Text
        this->enemyText.setFont(this->font);
        this->enemyText.setCharacterSize(30);
        this->enemyText.setFillColor(Color::White);

        this->gameOverText.setFont(this->font);
        this->gameOverText.setFillColor(Color::Red);
        this->gameOverText.setCharacterSize(200);
        this->gameOverText.setString("GAME OVER!");
        this->gameOverText.setPosition(this->window->getSize().x/2 - 450.f,
                                       this->window->getSize().y/2 -100.f);
}
void Game::UpdateUI()
{
    for(size_t i=0; i< this->followPlayerTexts.size(); i++)
    {
        this->followPlayerTexts[i].setPosition(this->players[i].getPosition().x,this->players[i].getPosition().y-20.f);
        this->followPlayerTexts[i].setString(to_string(i)+ "            -       " + this->players[i].getHpAsString());
    }
    for(size_t i=0; i< this->staticPlayerTexts.size(); i++)
    {

    }
}
void Game::Update()
{
    if(this->players.size() > 0)
    {

        // Update Timers
        if(this->enemySpawnTimer < this->enemySpawnTimerMax)
        {
            this->enemySpawnTimer++;
        }

        // Spawn Enemies
        if(this->enemySpawnTimer >= this-> enemySpawnTimerMax)
        {
            int spawnChance = rand() % 100;

            if(spawnChance<10)
            {
                std::cout << "Spawning big enemy" << std::endl;
                // Spawn a big enemy
                this->enemies.push_back(Enemy(&this->textures[bigEnemy], this->window->getSize(),Vector2f(0.f, 0.f),
                                              Vector2f(-0.5f, 0.f), Vector2f(0.4f, 0.4f),0, 7, 7, 5));
            }
            else if (spawnChance >= 10 && spawnChance < 40)
            {
                std::cout << "Spawning fast enemy" << std::endl;
                // Spawn a fast enemy
                this->enemies.push_back(Enemy(&this->textures[fastEnemy], this->window->getSize(),Vector2f(0.f, 0.f),
                                              Vector2f(-1.5f, 0.f), Vector2f(0.2f, 0.2f),0, 1, 1, 1));
            }
            else if (spawnChance <=43 &&  spawnChance >= 41 )
            {
                this->enemies.push_back(Enemy(&this->textures[meme01], this->window->getSize(),Vector2f(0.f, 0.f),
                                              Vector2f(-0.5f, 0.f), Vector2f(0.8f, 0.8f),0, 100, 10, 10));
            }
            else if (spawnChance <=46 &&  spawnChance >= 44 )
            {
                this->enemies.push_back(Enemy(&this->textures[meme02], this->window->getSize(),Vector2f(0.f, 0.f),
                                              Vector2f(-0.4f, 0.f), Vector2f(0.8f,0.8f),0, 100, 10, 10));
            }
            else
            {
                std::cout << "Spawning regular enemy" << std::endl;
                 this->enemies.push_back(Enemy(&this->textures[enemy01], this->window->getSize(),Vector2f(0.f,0.f),
                                                Vector2f(-1.f,0.f), Vector2f(0.4f,0.4f),0,rand()%3+1, 2, 1));
            }


            this-> enemySpawnTimer = 0; // Reset Timer
        }

        for(size_t i=0; i< this->players.size(); i++)
        {
            //Update Players
            this->players[i].Update(this->window->getSize());


            // Bullets update
            for(size_t k=0; k < this->players[i].getBullets().size() ;k++)
            {
                this->players[i].getBullets()[k].Update();

                // Enemy Collision Check
                for(size_t j=0; j < this->enemies.size(); j++)
                {

                    if(this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
                    {
                        this->players[i].getBullets().erase(this->players[i].getBullets().begin() +k);

                        if(this->enemies[j].getHP() > 0)
                        {
                            this->enemies[j].takeDamage(this->players[i].getDamage());
                        }
                        if(this->enemies[j].getHP() <= 0)
                        {
                            // Create an explosion at the enemy's position
                            this->enemyExplosions.emplace_back(this->explosionTextures[0], this->enemies[j].getPosition(),Vector2f(0.06f,0.06f),0.2f,0.2f);
                            this->enemies.erase(this->enemies.begin() + j);
                        }

                    }

                    else if(this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
                    {
                        this->enemies.erase(this->enemies.begin() + i);

                    }
                }
                // Window Bounds Check
                if( this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
                {
                    this->players[i].getBullets().erase(this->players[i].getBullets().begin() +k);

                }
            }
        }
        //Update Player Explosion
        for (size_t i = 0; i < this->playerExplosions.size();i++)
        {
            this->playerExplosions[i].Update();
            if (this->playerExplosions[i].isFinished())
            {
                this->playerExplosions.erase(playerExplosions.begin() + i); // Remove player Explosion
            }
             else
            {
                ++i; // Only increment if we didn't erase
            }
        }
        // Update enemy explosions
        for (size_t i = 0; i < this->enemyExplosions.size();)
        {
            this->enemyExplosions[i].Update();
            if (this->enemyExplosions[i].isFinished())
            {
                this->enemyExplosions.erase(enemyExplosions.begin() + i); // Remove finished explosions
            }
            else
            {
                ++i; // Only increment if we didn't erase
            }
        }
        // Update Enemies
        for(size_t i=0; i < this->enemies.size(); i++)
        {
                this->enemies[i].Update();

                for(size_t k=0; k < this->players.size(); k++)
                {
                    if(this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
                    {
                        this->players[k].takeDamage(this->enemies[i].getDamage());

                        if(!this->players[k].isAlive())
                        {
                            if(this->players[k].getHP() <= 0)
                            {
                                this->playerExplosions.emplace_back(this->explosionTextures[1],this->players[k].getPosition(),Vector2f(0.1f,0.1f), 0.4f,1.f);
                            }
                            this->players.erase(this->players.begin() + k);
                            this->followPlayerTexts.erase(this->followPlayerTexts.begin() + k);
                            this->playersAlive--;
                            if(playersAlive==0)
                            {
                                this->backgroundMusic.stop();
                                this->gameOverAudio.play();
                                break;
                            }
                            return;
                        }

                        this->enemies.erase(this->enemies.begin() + i);
                        return;
                    }
                }

                if(this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
                {
                    this->enemies.erase(this->enemies.begin() + i);
                    return;
                }
            }
        //Update UI
        this->UpdateUI();
    }
}

void Game::DrawUI()
{
    for(size_t i=0; i< this->followPlayerTexts.size(); i++)
    {
        this->window->draw(this->followPlayerTexts[i]);
    }
    for(size_t i=0; i< this->staticPlayerTexts.size(); i++)
    {
        this->window->draw(this->staticPlayerTexts[i]);
    }
    if(this->playersAlive <= 0)
    {
        this->window->draw(this->gameOverText);
    }
}
void Game::Draw()
{
    this->window->clear();
    // Wallpaper
    this->window->draw(this->wallpaperSprite);

    for(size_t i=0; i< this->players.size(); i++)
    {
        this->players[i].Draw(*this->window);
    }
    for(size_t i=0; i< this->enemies.size(); i++)
    {
        this->enemyText.setPosition(this->enemies[i].getPosition().x,this->enemies[i].getPosition().y -25.f);
        this->enemyText.setString(to_string(this->enemies[i].getHP())
                                                +"/"+
                                  to_string(this->enemies[i].getHPMax()));

        this->enemies[i].Draw(*this->window);
        this->window->draw(this->enemyText);
    }
    // Draw player explosions
    for (size_t i = 0; i < this->playerExplosions.size(); ++i)
    {
        this->playerExplosions[i].Draw(*this->window);
    }
    // Draw explosions
    for (size_t i = 0; i < this->enemyExplosions.size(); ++i)
    {
        this->enemyExplosions[i].Draw(*this->window);
    }

    this-> DrawUI();
    this->window->display();
}
