#pragma once
#include"DirectXCommon.h"
#include"SpriteCommon.h"
#include<DirectXMath.h>

#include<d3d12.h>
#include<wrl.h>

//�P��
class Sprite
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	struct Transform {
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT3 translate;
	};

	struct VertexData {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcord;
	};

public:
	void Initialize(SpriteCommon*common);
void Draw();

//���_���쐬
void CreateVertex();
//�C���f�b�N�X���쐬
void CreateIndex();
//�}�e���A�����쐬
void CreateMaterial();
//�s����쐬
void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	//���_���
	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	//�}�e���A�����
	ComPtr<ID3D12Resource> materialResource;

	//�s����
	ComPtr<ID3D12Resource> wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	//�摜�̕ۑ���̃A�h���X
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	//�p�����[�^
	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	//                   Scale   Rotate  Translate
	Transform transform = { {1,1,1}, {0,0,0},{0,0,0} };

	// �J����
	Transform cameraTransform{ {1,1,1},{0,0,0},{0,0,-5} };
};

