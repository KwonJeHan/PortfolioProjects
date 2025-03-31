#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Stone.h"
#include "Actor/Skeleton.h"
#include "Actor/Target.h"
#include "Actor/Spike.h"
#include "Actor/Gate.h"
#include "Actor/Key.h"
#include "Actor/Demon.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"


GameLevel::GameLevel()
{
	fileIndex = Game::Get().index;
	SelectStage();
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// Ÿ�� ������ �÷��̾ �����ߴ��� Ȯ��
	isStageClear = CheckStageClear();

	// ��� ���������� Ŭ���� �ƴ��� Ȯ��
	isGameClear = CheckGameClear();

	// �÷��̾ �̵� ���� Ƚ���� �ʰ��ߴ��� Ȯ��
	isGameOver = CheckGameOver();


	// �������� Ŭ���� �� ���� ��������
	if (isStageClear)
	{
		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}
		timer.Reset();

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// �޽��� ���
		Log("Stage Clear!");

		// ������ ����
		Sleep(2000);

		system("cls");

		Game::Get().NextLevel();
	}

	// ������ Ŭ���� ������ ���� ���� ó��
	if (isGameClear)
	{
		// �뷫 �� ������ ������ �ð� ���
		/*static float elapsedTime = 0.0f;
		elapsedTime += deltaTime;
		if (elapsedTime < 0.1f)
		{
			return;
		}*/

		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// �޽��� ���
		Log("Game Clear!");

		// ������ ����
		Sleep(2000);

		// ���� ���� ó��
		Engine::Get().QuitGame();
	}

	// ���� ���� ������ ���� �����
	if (isGameOver)
	{
		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}
		timer.Reset();

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// �޽��� ���
		Log("Game Over!");

		// ������ ����
		Sleep(2000);

		system("cls");

		// �������� �ٽ� ����
		Game::Get().ReLevel();

		//// ���� ���� ó��
		//Engine::Get().QuitGame();
	}
}

void GameLevel::Draw()
{
	Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x, Engine::Get().ScreenSize().y - 1);

	// �޽��� ���
	Log("���� �̵� Ƚ�� : %dȸ, ������ �ִ� ���� ���� : %d��", (moveLimit - player->moveCount), player->hasKey);

	// �� �׸���
	for (auto* actor : map)
	{
		// �÷��̾� ��ġ Ȯ��
		if (actor->Position() == player->Position())
		{
			continue;
		}

		// �Ǹ� ��ġ Ȯ��
		if (actor->Position() == demon->Position())
		{
			continue;
		}
		
		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (actor->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (actor->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// ���� ��ġ Ȯ��
		for (auto* key : keys)
		{
			if (actor->Position() == key->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �� ��ġ Ȯ��
		for (auto* gate : gates)
		{
			if (actor->Position() == gate->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		if (shouldDraw)
		{
			actor->Draw();
		}
	}

	// Ÿ�� �׸���
	for (auto* target : targets)
	{
		// �÷��̾� ��ġ Ȯ��
		if (target->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (target->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (target->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// Ÿ�� ���� �׸���.
		if (shouldDraw)
		{
			target->Draw();
		}
	}

	// ���� ���� �׸���
	for (auto* spike : spikes)
	{
		// �÷��̾� ��ġ Ȯ��
		if (spike->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (spike->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (spike->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// ���� ���� ���� �׸���.
		if (shouldDraw)
		{
			spike->Draw();
		}
	}

	// ���� �׸���
	for (auto* key : keys)
	{
		// �÷��̾� ��ġ Ȯ��
		if (key->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (key->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (key->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// ���� ���� �׸���.
		if (shouldDraw)
		{
			if (!key->isExpired)
			{
				key->Draw();
			}
		}
	}

	// �� �׸���	
	for (auto* gate : gates)
	{
		if (!gate->isExpired)
		{
			gate->Draw();
		}
	}

	// ���� �׸���.
	for (auto* stone : stones)
	{
		if (!stone->isExpired)
		{
			stone->Draw();
		}
	}

	// �ذ� �׸���
	for (auto* skeleton : skeletons)
	{
		if (!skeleton->isExpired)
		{
			skeleton->Draw();
		}
	}

	// �Ǹ� �׸���
	demon->Draw();

	// �÷��̾� �׸���.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����
	if (isGameClear)
	{
		return false;
	}

	// ���� �˻�
	Stone* searchedStone = nullptr;
	for (auto* stone : stones)
	{
		if (stone->Position() == position)
		{
			searchedStone = stone;
			break;
		}
	}

	// �ذ� �˻�
	Skeleton* searchedSkeleton = nullptr;
	for (auto* skeleton : skeletons)
	{
		if (skeleton->Position() == position)
		{
			searchedSkeleton = skeleton;
			break;
		}
	}

	// �� �˻�
	Gate* searchedgate = nullptr;
	for (auto* gate : gates)
	{
		if (gate->Position() == position)
		{
			searchedgate = gate;
			break;
		}
	}

	// ���� �˻�
	Key* searchedkey = nullptr;
	for (auto* key : keys)
	{
		if (key->Position() == position)
		{
			searchedkey = key;
			break;
		}
	}

	// ������ ���� �� ó��
	if (searchedStone)
	{
		// �̵� ����
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// ������ �̵��� �� ��ġ
		Vector2 newPosition = searchedStone->Position() + Vector2(directionX, directionY);

		// �߰� �˻� (����)
		for (auto* stone : stones)
		{
			// ���� ó��
			if (stone == searchedStone)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� ������ �ִٸ� �̵� �Ұ�
			if (stone->Position() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻� (�ذ�)
		for (auto* skeleton : skeletons)
		{
			// ���� ó��
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// �̵��� ��ġ�� �ذ��� �ִٸ� �̵� �Ұ�
			if (skeleton->Position() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻� (��)
		for (auto* gate : gates)
		{
			// ���� ó��
			if (gate == searchedgate)
			{
				continue;
			}

			// �̵��� ��ġ�� ���� �ִٸ� �̵� �Ұ�
			if (gate->Position() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻� (����)
		for (auto* key : keys)
		{
			// ���� ó��
			if (key == searchedkey)
			{
				continue;
			}

			// �̵��� ��ġ�� ���谡 �ִٸ� �̵� ����
			if (key->Position() == newPosition)
			{
				return true;
			}
		}

		// �߰� �˻�(��)
		for (auto* actor : map)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (actor->Position() == newPosition)
			{
				// ����ȯ�� ���� ��ü�� Ÿ�� Ȯ��

				// �̵��Ϸ��� ��ġ�� ���� ������ �̵� �Ұ�
				if (actor->As<Wall>())
				{
					return false;
				}

				// �̵��Ϸ��� ��ġ�� �Ǹ��� ������ �̵� �Ұ�
				if (actor->Position() == demon->Position())
				{
					return false;
				}

				// ���̳� Ÿ��, ���� �����̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>())
				{
					// ���� �̵� ó��
					searchedStone->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					//isGameClear = CheckGameClear();

					// ������ �ذ��� �̵�, ĳ���ʹ� ���ڸ�
					return false;
				}
			}
		}
	}

	// �ذ��� ���� �� ó��
	if (searchedSkeleton)
	{
		// �̵� ����
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// �ذ��� �̵��� �� ��ġ
		Vector2 newPosition = searchedSkeleton->Position() + Vector2(directionX, directionY);

		// �߰� �˻� (�ذ�)
		for (auto* skeleton : skeletons)
		{
			// ���� ó��
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� �ذ��� �ִٸ� �ı�
			if (skeleton->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// �߰� �˻� (����)
		for (auto* stone : stones)
		{
			// ���� ó��
			if (stone == searchedStone)
			{
				continue;
			}

			// �̵��� ��ġ�� ������ �ִٸ� �ı�
			if (stone->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// �߰� �˻� (��)
		for (auto* gate : gates)
		{
			// ���� ó��
			if (gate == searchedgate)
			{
				continue;
			}

			// �̵��� ��ġ�� ���� �ִٸ� �ı�
			if (gate->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// �߰� �˻� (����)
		for (auto* key : keys)
		{
			// ���� ó��
			if (key == searchedkey)
			{
				continue;
			}

			// �̵��� ��ġ�� ���谡 �ִٸ� �̵� ����
			if (key->Position() == newPosition)
			{
				return true;
			}
		}

		// �߰� �˻�(��)
		for (auto* actor : map)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (actor->Position() == newPosition)
			{
				// ����ȯ�� ���� ��ü�� Ÿ�� Ȯ��

				// �̵��Ϸ��� ��ġ�� ���� ������ �ı�
				if (actor->As<Wall>())
				{
					Engine::Get().DestroyActor(searchedSkeleton);
					return false;
				}

				// �̵��Ϸ��� ��ġ�� �Ǹ��� ������ �ı�
				if (actor->Position() == demon->Position())
				{
					Engine::Get().DestroyActor(searchedSkeleton);
					return false;
				}

				// ���̳� Ÿ��, ���� �����̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>() || actor->As<Key>())
				{
					// �ذ� �̵� ó��
					searchedSkeleton->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					//isGameClear = CheckGameClear();

					// ������ �ذ��� �̵�, ĳ���ʹ� ���ڸ�
					return false;
				}
			}
		}
	}

	// ���� ���� �� ó��
	if (searchedgate)
	{
		if (player->hasKey > 0)
		{
			--(player->hasKey);
			Engine::Get().DestroyActor(searchedgate);
			return true;
		}
		else
		{
			return false;
		}
	}

	// ���谡 ���� �� ó��
	if (searchedkey)
	{
		++(player->hasKey);
		Engine::Get().DestroyActor(searchedkey);
		return true;
	}


	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��
	DrawableActor* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ���� ã��
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// �˻��� ���Ͱ� ������ Ȯ��
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// �˻��� ���Ͱ� �Ǹ����� Ȯ��
	if (searchedActor != nullptr)
	{
		if (searchedActor->Position() == demon->Position())
		{
			return false;
		}
	}

	// �˻��� ���Ͱ� �̵� ������ ����(��/Ÿ��)���� Ȯ��
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	// �˻��� ���Ͱ� ���� �������� Ȯ��
	if (searchedActor->As<Spike>())
	{
		++(player->moveCount);
		return true;
	}

	return false;
}

void GameLevel::SelectStage()
{
	switch (fileIndex)
	{
	case 0:
		TextFileRead("../Assets/Maps/stage1.txt");
		moveLimit = 22;
		break;
	case 1:
		TextFileRead("../Assets/Maps/stage2.txt");
		moveLimit = 25;
		break;
	case 2:
		TextFileRead("../Assets/Maps/stage3.txt");
		moveLimit = 40;
		break;
	case 3:
		TextFileRead("../Assets/Maps/stage4.txt");
		moveLimit = 15;
		lastStage = true;
		break;
	}
}

void GameLevel::TextFileRead(const char* filename)
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� ���� ����\n";
		__debugbreak();
		return;
	}

	// ���� �б�
	// �� ��ġ�� �̵�
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������
	size_t readSize = ftell(file);

	// FP ����ġ
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// ���� �о ���ۿ� ���
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���
	int index = 0;
	// ��ǥ ����� ���� ���� ����
	int xPosition = (int)(Engine::Get().ScreenSize().x + 17);
	int yPosition = (int)(Engine::Get().ScreenSize().y / 2);

	// �ؼ� (�Ľ�-Parcing)
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = (Engine::Get().ScreenSize().x + 17);
			continue;
		}

		if (mapChar == ' ')
		{
			++xPosition;
			continue;
		}

		// �� ���ڰ� 1�̸� Wall ���� ����
		if (mapChar == '1')
		{
			//std::cout << 'A';
			//AddActor(new Wall(Vector2(xPosition, yPosition)));
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// �� ���ڰ� 0�̸� �׶��� ���� ����
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		// �� ���ڰ� b�̸� ���� ���� ����
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Stone* stone = new Stone(Vector2(xPosition, yPosition));
			actors.PushBack(stone);
			stones.PushBack(stone);
		}

		// �� ���ڰ� s�̸� �ذ� ���� ����
		else if (mapChar == 's')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Skeleton* skeleton = new Skeleton(Vector2(xPosition, yPosition));
			actors.PushBack(skeleton);
			skeletons.PushBack(skeleton);
		}

		// �� ���ڰ� 2�̸� ���� ���� ����
		else if (mapChar == '2')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Key* key = new Key(Vector2(xPosition, yPosition));
			actors.PushBack(key);
			keys.PushBack(key);
		}

		// �� ���ڰ� 3�̸� �� ���� ����
		else if (mapChar == '3')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Gate* gate = new Gate(Vector2(xPosition, yPosition));
			actors.PushBack(gate);
			gates.PushBack(gate);
		}

		// �� ���ڰ� t�̸� Ÿ�� ���� ����
		else if (mapChar == 't')
		{
			Target* target = new Target(Vector2(xPosition, yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			targets.PushBack(target);
		}

		// �� ���ڰ� k�̸� ���� ���� ���� ����
		else if (mapChar == 'k')
		{
			Spike* spike = new Spike(Vector2(xPosition, yPosition));
			actors.PushBack(spike);
			map.PushBack(spike);
			spikes.PushBack(spike);
		}

		// �� ���ڰ� d�̸� �Ǹ� ���� ����
		else if (mapChar == 'd')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			demon = new Demon(Vector2(xPosition, yPosition));
			actors.PushBack(demon);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == 'p')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			player = new Player(Vector2(xPosition, yPosition), this);
			actors.PushBack(player);
		}

		++xPosition;

	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

bool GameLevel::CheckStageClear()
{
	bool stageClear = 0;
	for (auto* target : targets)
	{
		if ((player->Position() == target->Position()) && !lastStage)
		{
			++stageClear;
			continue;
		}
	}
	return stageClear;
}

bool GameLevel::CheckGameClear()
{
	bool gameClear = 0;
	for (auto* target : targets)
	{
		if ((player->Position() == target->Position()) && lastStage)
		{
			++gameClear;
			continue;
		}
	}
	return gameClear;
}

bool GameLevel::CheckGameOver()
{
	return player->moveCount >= moveLimit;
}
