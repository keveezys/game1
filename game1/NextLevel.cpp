#include "NextLevel.h"
#include "Constants.h"

void loadNextLevel() {
    if (currentLevel + 1 < TileMap.size()) {
        currentLevel++;
    }
    else {
        // ќбработка конца игры здесь...
        currentLevel--; // ¬ернутьс€ к последнему уровню, если уровней больше нет
    }
}
