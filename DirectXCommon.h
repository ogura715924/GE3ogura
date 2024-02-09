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

	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//Getter
	ID3D12Device* GetDevice()const { return device.Get(); };
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); };


private: 
	//�f�o�C�X
	void DeviceInitilize();
	//�R�}���h
	void CommandInitilize();
	//�X���b�v�`�F�[��
	void SwapChainInitilize();
	//�����_�[�^�[�Q�b�g
	void RenderTargetInitialize();
	//�[�x�o�b�t�@
	void DepthBufferInitilize();
	//�t�F���X
	void FenceInitilize();

	// �f�B�X�N���v�^�q�[�v�쐬
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripots, bool shaderVisible);

	//FPS�Œ菉��������
	void InitilizeFixFPS();

	//FPS�Œ�X�V����
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

	// �f�B�X�N���v�^�q�[�v
	// RTV(�Q�[����ʂ�ۑ����Ă���)
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	// SRV(�摜�Ȃǂ�ۑ����Ă�������)
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;

	//�L�^�p���Ԍv���̕ϐ�
	std::chrono::steady_clock::time_point reference_;
};

