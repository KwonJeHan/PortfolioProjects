#include "Skeleton.h"

Skeleton::Skeleton(const Vector2& position)
	: DrawableActor("��")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
