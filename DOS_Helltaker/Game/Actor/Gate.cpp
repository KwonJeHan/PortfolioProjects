#include "Gate.h"

Gate::Gate(const Vector2& position)
	: DrawableActor("��")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Blue;
}
