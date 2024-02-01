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

private:
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
};

