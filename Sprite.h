#pragma once
#include"DirectXCommon.h"
#include"SpriteCommon.h"

#include<d3d12.h>
#include<wrl.h>

//単体
class Sprite
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initialize(DirectXCommon*dxCommon,SpriteCommon*common);
void Draw();

// 頂点情報作成
void CreateVertex();
// インデックス情報作成
void CreateIndex();
// マテリアル情報作成
void CreateMaterial();
// 行列情報作成
void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	//頂点情報
	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	//マテリアル情報
	ComPtr<ID3D12Resource> materialResource;
};

