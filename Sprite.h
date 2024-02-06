#pragma once
#include "DirectXCommon.h"
#include <d3d12.h>
#include <wrl.h>
#include "SpriteCommon.h"

//íPëÃ
class Sprite
{
public:
	//èâä˙âª
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);
	void Draw();
private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
};

