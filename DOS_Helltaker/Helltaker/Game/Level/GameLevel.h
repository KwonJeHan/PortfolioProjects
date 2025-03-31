#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// ���ڹ� ���� ����.
class DrawableActor;
class Player;
class Stone;
class Skeleton;
class Target;
class Spike;
class Gate;
class Key;
class Demon;
class GameLevel : public Level
{
    RTTI_DECLARATIONS(GameLevel, Level)

public:
    GameLevel();

    // ������Ʈ �Լ�
    virtual void Update(float deltaTime) override;

    // ������ �׸��� �Լ�
    virtual void Draw() override;

    // �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�
    bool CanPlayerMove(const Vector2& position);

    // �������� ����
    void SelectStage();

    // �ؽ�Ʈ ���� �б�
    void TextFileRead(const char* filename);

    // ���� �ε���
    int fileIndex = 0;

private:
    // ���� ���������� Ŭ���� �ߴ��� Ȯ���ϴ� �Լ�
    bool CheckStageClear();

    // ��� ���������� Ŭ���� �ߴ��� Ȯ���ϴ� �Լ�
    bool CheckGameClear();

    // �̵� Ƚ���� �̵� ���� Ƚ���� �Ѿ�� ���� ���� �ƴ��� Ȯ���ϴ� �Լ�
    bool CheckGameOver();

private:
    // ��/�� ���� �迭.
    List<DrawableActor*> map;

    // �ڽ� ����
    List<Stone*> stones;

    // Ÿ�� ����
    List<Target*> targets;

    // �ذ� ����
    List<Skeleton*> skeletons;

    // ���� ���� ����
    List<Spike*> spikes;

    // �� ����
    List<Gate*> gates;

    // ���� ����
    List<Key*> keys;

    // �Ǹ� ����
    Demon* demon = nullptr;

    // �÷��̾� ����
    Player* player = nullptr;

    // �������� Ŭ���� ����
    bool isStageClear = false;

    // ���� Ŭ���� ����
    bool isGameClear = false;
    bool lastStage = false;

    // ���� ���� ����
    bool isGameOver = false;

    // �̵� ���� Ƚ��
    int moveLimit;

};