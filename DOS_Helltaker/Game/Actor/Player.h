#pragma once

#include <Actor/DrawableActor.h>

// ���� ���� ���� ����
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

	// �̵� Ƚ��
	int moveCount = 0;

	// ������ ���� ����
	int hasKey = 0;

private:
	// ���� ������ �����ϴ� ����
	GameLevel* refLevel = nullptr;
};