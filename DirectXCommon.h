#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

#include"WinApp.h"

class DirectXCommon
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initilize(WinApp* winApp);

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
	WinApp* winApp_ = nullptr;

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;

	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ComPtr<IDXGISwapChain4> swapChain;

	ComPtr<ID3D12DescriptorHeap> rtvHeap;
};

