#include "TileMap.h"
#include "Constants.h"

void drawTileMap(sf::RenderWindow& window, sf::Texture& tileSet) {
    sf::Sprite tile(tileSet);

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            if (TileMap[currentLevel][i][j] == 'P') tile.setTextureRect(sf::IntRect(143 - 16 * 3, 112, 16, 16));
            if (TileMap[currentLevel][i][j] == 'k') tile.setTextureRect(sf::IntRect(143, 112, 16, 16));
            if (TileMap[currentLevel][i][j] == 'c') tile.setTextureRect(sf::IntRect(143 - 16, 112, 16, 16));
            if (TileMap[currentLevel][i][j] == 't') tile.setTextureRect(sf::IntRect(0, 47, 32, 95 - 47));
            if (TileMap[currentLevel][i][j] == 'g') tile.setTextureRect(sf::IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));
            if (TileMap[currentLevel][i][j] == 'G') tile.setTextureRect(sf::IntRect(145, 222, 222 - 145, 255 - 222));
            if (TileMap[currentLevel][i][j] == 'd') tile.setTextureRect(sf::IntRect(0, 106, 74, 127 - 106));
            if (TileMap[currentLevel][i][j] == 'w') tile.setTextureRect(sf::IntRect(99, 224, 140 - 99, 255 - 224));
            if (TileMap[currentLevel][i][j] == 'r') tile.setTextureRect(sf::IntRect(143 - 32, 112, 16, 16));
            if ((TileMap[currentLevel][i][j] == ' ') || (TileMap[currentLevel][i][j] == '0')) continue;

            tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
            window.draw(tile);
        }
}
