#include <iostream>
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Level/MainLevel.h"

int main()
{
	// �޸� ���� Ȯ��
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new MainLevel());
	game.Run();
}