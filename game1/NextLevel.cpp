#include "NextLevel.h"
#include "Constants.h"

void loadNextLevel() {
    if (currentLevel + 1 < TileMap.size()) {
        currentLevel++;
    }
    else {
        // ��������� ����� ���� �����...
        currentLevel--; // ��������� � ���������� ������, ���� ������� ������ ���
    }
}
