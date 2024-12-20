#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Enemy.h"


using namespace sf;

class Player;
class Game
{   private:
        RenderWindow *window;

        // Wallpaper
        Texture wallpaperTexture;
        Sprite wallpaperSprite;

        // Text
        Font font;
        std::vector<Text> followPlayerTexts;
        std::vector<Text> staticPlayerTexts;
        Text enemyText;
        Text gameOverText;

        //Players
        std::vector<Player> players;
        int playersAlive;

        // Enemies
        std::vector<Enemy> enemies;
        std::vector<Enemy> enemiesSaved;
        int enemySpawnTimerMax;
        int enemySpawnTimer;

        //Textures
        std::vector<Texture> textures;

    public:
        Game(RenderWindow *window);
        virtual ~Game();

        // Accessors
        inline RenderWindow &getWindow()
        {
            return *this->window;
        }

        // Setters


        // Functions
        void InitUI();
        void DrawUI();
        void UpdateUI();

        void Update();
        void Draw();

    protected:


};

#endif // GAME_H

