#pragma once

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class GameObject
{
public:
	struct RenderInfo {
		Matrix m_World;

		ComPtr<ID3D11Buffer>             m_VB;
		ComPtr<ID3D11Buffer>             m_IB;

		UINT												m_IndexCnt;

		ComPtr<ID3D11VertexShader> m_VS;
		ComPtr<ID3D11PixelShader>    m_PS;

		ComPtr<ID3D11InputLayout>   m_InputLayout;

		int TexID;
	};
private:
	static UINT g_ObjCount;
	UINT m_id;

	RenderInfo m_RF;
public:
	GameObject();
	virtual ~GameObject();

	void Create(RenderInfo rf);

	UINT GetID() { return m_id; }
	Matrix GetMatrix() { return m_RF.m_World; }
	const RenderInfo& GetRenderInfo() { return m_RF; }
};