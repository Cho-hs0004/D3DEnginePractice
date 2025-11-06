

#include "Default.h"
#include "GameObject.h"

UINT GameObject::g_ObjCount = 0;

GameObject::GameObject()
{
	m_id = g_ObjCount++;
}

GameObject::~GameObject()
{

}

void GameObject::Create(RenderInfo* rf)
{
	m_RF = *rf;
}
