#include "Stone.h"

Stone::Stone(const Vector2& position)
	: DrawableActor("��")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
