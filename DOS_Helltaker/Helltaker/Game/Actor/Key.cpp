#include "Key.h"

Key::Key(const Vector2& position)
	: DrawableActor("��")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Blue;
}
