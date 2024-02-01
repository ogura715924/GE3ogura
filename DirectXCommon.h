#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

class DirectXCommon
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initilize();

private: 
	//デバイス
	void DeviceInitilize();
	//コマンド
	void CommandInitilize();
	//スワップチェーン
	void SwapChainInitilize();
	//レンダーターゲット
	void RenderTargetInitialize();
	//深度バッファ
	void DepthBufferInitilize();
	//フェンス
	void FenceInitilize();

private:
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
};

