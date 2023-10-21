#pragma once
#include<Windows.h>
#include<wrl.h>

#define DIRECTINPUT_VESION 0x0800//DirectInput�̃o�[�W�����w��
#include <dinput.h>

class Input
{public:
	//namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//������
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//�X�V
	void Update();

	//�C�ӂ̃{�^����������Ă���
	bool PushKey(BYTE keyNumber);
	//�C�ӂ̃{�^���������ꂽ�u��
	bool TriggerKey(BYTE keyNumber);

private://�����o�ϐ�
	Microsoft::WRL::ComPtr<IDirectInput8>driectInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8>keyboard;
	// �L�[�{�[�h�f�o�C�X�̐���
	
	//�S�L�[�̏��
	BYTE key[256] = {};
	//�O��̃L�[�̏��
	BYTE keyPre[256] = {};
};

