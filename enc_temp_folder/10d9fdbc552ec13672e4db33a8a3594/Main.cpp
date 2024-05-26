#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Constants.h"
#include "NextLevel.h" 
#include <iostream>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "platformer");

    Texture tileSet;
    if (!tileSet.loadFromFile("Mario_Tileset.png")) {
        std::cerr << "Error loading Mario_Tileset.png" << std::endl;
        return -1;
    }

    PLAYER Mario(tileSet);
    ENEMY enemy;
    enemy.set(tileSet, 48 * 16, 13 * 16);

    Sprite tile(tileSet);

    SoundBuffer buffer;
    if (!buffer.loadFromFile("Jump.ogg")) {
        std::cerr << "Error loading Jump.ogg" << std::endl;
        return -1;
    }
    Sound sound(buffer);

    Texture menu_texture1, menu_texture2, menu_texture3, about_texture, gameOverTexture;
    menu_texture1.loadFromFile("111.png");
    menu_texture2.loadFromFile("222.png");
    menu_texture3.loadFromFile("333.png");
    about_texture.loadFromFile("about.png");
    if (!gameOverTexture.loadFromFile("game_over.png")) {
        std::cerr << "Error loading game_over.png" << std::endl;
        return -1;
    }
    Sprite menu1(menu_texture1), menu2(menu_texture2), menu3(menu_texture3), about(about_texture), gameOver(gameOverTexture);
    gameOver.setPosition(0, 0); // Установите позицию спрайта в соответствии с вашими предпочтениями
    bool Menu = 1;
    int MenuNum = 0;

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = menu_texture1.getSize();

    // Позиция элементов меню
    float menuX = (windowSize.x - textureSize.x) / 2.f;
    float menuY1 = windowSize.y / 2.f - textureSize.y * 1.5f;
    float menuY2 = windowSize.y / 2.f - textureSize.y * 0.5f;
    float menuY3 = windowSize.y / 2.f + textureSize.y * 0.5f;
    float menuY4 = windowSize.y / 2.f + textureSize.y * 0.5f;

    menu1.setPosition(menuX, menuY1);
    menu2.setPosition(menuX, menuY2);
    menu3.setPosition(menuX, menuY3);
    about.setPosition(menuX, menuY4);


    /////меню
    while (Menu)
    {
        // Получаем позицию мыши относительно окна
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Преобразуем позицию мыши в координаты окна
        sf::Vector2f mousePositionWindow = window.mapPixelToCoords(mousePosition);

        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        MenuNum = 0;
        window.clear(sf::Color(0, 0, 0));

        if (menu1.getGlobalBounds().contains(mousePositionWindow)) { menu1.setColor(sf::Color::Yellow); MenuNum = 1; }
        if (menu2.getGlobalBounds().contains(mousePositionWindow)) { menu2.setColor(sf::Color::Yellow); MenuNum = 2; }
        if (menu3.getGlobalBounds().contains(mousePositionWindow)) { menu3.setColor(sf::Color::Yellow); MenuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (MenuNum == 1) Menu = false;
            if (MenuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
            if (MenuNum == 3) { window.close(); Menu = false; }
        }

        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }


    Music music;
    if (!music.openFromFile("Mario_Theme.ogg")) {
        return -1;
    }
    music.play();

    Clock clock;
    bool isGameOver = false;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 500;

        if (time > 20) time = 20;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!isGameOver) {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Left)) Mario.dx = -0.1;
            if (Keyboard::isKeyPressed(Keyboard::Right)) Mario.dx = 0.1;
            if (Keyboard::isKeyPressed(Keyboard::Up)) if (Mario.onGround) { Mario.dy = -0.27; Mario.onGround = false; sound.play(); }

            Mario.update(time);
            enemy.update(time);

            if (Mario.rect.intersects(enemy.rect)) {
                if (enemy.life) {
                    if (Mario.dy > 0) {
                        enemy.dx = 0;
                        Mario.dy = -0.2;
                        enemy.life = false;
                    }
                    else {
                        isGameOver = true;
                        Mario.sprite.setColor(Color::Red);
                    }
                }
            }

            // Проверка на достижение конца уровня
            for (int i = Mario.rect.top / 16; i < int( (Mario.rect.top + Mario.rect.height) / 16); i++)
                for (int j = Mario.rect.left / 16; j < int( (Mario.rect.left + Mario.rect.width) / 16); j++)
                    //std::cout << (Mario.rect.top + Mario.rect.height) / 16 << " " << size(TileMap[currentLevel]) << " " << size(TileMap[currentLevel][i]);
                    if (TileMap[currentLevel][i][j] == 'E') {
                        // Загрузка следующего уровня...
                        loadNextLevel();
                        // Сброс позиции игрока...
                        Mario.rect.left = startingPositionX;
                        Mario.rect.top = startingPositionY;
                    }

            if (Mario.rect.left > 200) offsetX = Mario.rect.left - 200;
        }

        window.clear(Color(107, 140, 255));

        drawTileMap(window, tileSet);

        if (isGameOver) {
            window.draw(gameOver);
        }
        else {
            window.draw(Mario.sprite);
            window.draw(enemy.sprite);
        }

        window.display();
    }

    return 0;
}
