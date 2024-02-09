#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

#include <vector>
#include<chrono>

#include"WinApp.h"

class DirectXCommon
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initilize(WinApp* winApp);

	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	//Getter
	ID3D12Device* GetDevice()const { return device.Get(); };
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); };


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

	// ディスクリプタヒープ作成
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripots, bool shaderVisible);

	//FPS固定初期化処理
	void InitilizeFixFPS();

	//FPS固定更新処理
	void UpdateFixFPS();
	
private:
	WinApp* winApp_ = nullptr;

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;

	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ComPtr<IDXGISwapChain4> swapChain;

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<ComPtr<ID3D12Resource>>backBuffers;

	ComPtr<ID3D12Resource> depthBuff;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;


	D3D12_RESOURCE_BARRIER barrierDesc{};

	// ディスクリプタヒープ
	// RTV(ゲーム画面を保存しておく)
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	// SRV(画像などを保存しておくもの)
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;

	//記録用時間計測の変数
	std::chrono::steady_clock::time_point reference_;
};

