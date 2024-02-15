#pragma once
#include<wrl.h>
#include <string>
#include<dxcapi.h>
#include <d3dx12.h>

#include"DirectXCommon.h"
#include<DirectXTex.h>

//共通
class SpriteCommon
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initialize(DirectXCommon*dxCommon);
	void SpritePreDraw();

	// Getter
	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
	DirectXCommon* GetDirectXCommon() { return dxCommon_; }

	//画像読み込み
	DirectX::ScratchImage LoadTexture(const std::wstring& filePath);
	//読み込んだ画像をGPU(シェーダーに送る)
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private:
	static IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);
private:
	DirectXCommon* dxCommon_=nullptr;
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
};

