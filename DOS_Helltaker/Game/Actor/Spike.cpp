#include "Spike.h"

Spike::Spike(const Vector2& position)
	: DrawableActor("��")//��
{
	// ��ġ ����
	this->position = position;
	
	// ���� ����
	color = Color::Red;
}
