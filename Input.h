#pragma once
#include<Windows.h>
#include<wrl.h>

#define DIRECTINPUT_VESION 0x0800//DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

class Input
{public:
	//namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//������
	void Initialize(WinApp*winApp);
	//�X�V
	void Update();

	//�C�Ӄ{�^����������Ă���Ƃ�
	bool PushKey(BYTE keyNumber);
	//�C�Ӄ{�^���������ꂽ�u��
	bool TriggerKey(BYTE keyNumber);

private://�����o�ϐ�

	// �L�[�{�[�h�f�o�C�X�̐���
	WinApp* WinApp_ = nullptr;

	Microsoft::WRL::ComPtr<IDirectInput8>directInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	// �S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};
	//�O��̃L�[
	BYTE keyPre[256] = {};
};

