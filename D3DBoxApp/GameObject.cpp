

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




Box::Box()
{

}

Box::~Box()
{

}

/// //////////////////////////////////////////////
/// Box
void Box::Update(float dTime)
{
	if(!pathQ.empty() && !m_isMoving)
	{
		auto nextCell = pathQ.front();
		pathQ.pop();
		float cellSize = 1.0f; 
		float halfGridSize = 20 * cellSize; 
		float targetX = -halfGridSize + cellSize * nextCell.first + cellSize * 0.5f;
		float targetZ = -halfGridSize + cellSize * nextCell.second + cellSize * 0.5f;
		m_TargetPos.x = targetX;
		m_TargetPos.z = targetZ;
		
		m_vDir = m_TargetPos - m_Pos;

		m_vDir.Normalize();

		m_isMoving = true;
	}
	if (m_isMoving)
	{
		if (m_Pos.x >= m_TargetPos.x - 0.01f && m_Pos.x <= m_TargetPos.x + 0.01f
			&& m_Pos.z >= m_TargetPos.z - 0.01f && m_Pos.z <= m_TargetPos.z + 0.01f)
			m_isMoving = false;
		else
			m_Pos += m_vDir * m_Speed * dTime;
	}

	m_RF.m_World = Matrix::CreateTranslation(m_Pos);
}

void Box::SetPath(std::queue<std::pair<int, int>>* pathQ)
{
	//Astar에 미로 넣고 패스 받아서
	//업데이트에서 패스의 사이즈가 0이 아니면 그럼 que가 낫지않나?
	this->pathQ = *pathQ;
}
