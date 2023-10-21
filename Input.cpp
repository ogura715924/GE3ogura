#include "Input.h"

#include <cassert>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
    HRESULT result;

    // DirectInput�̏�����(�L�[�{�[�h�̏���)
    result = DirectInput8Create(
        hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

  
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
 //�O��̃L�[���͂�ۑ�
    memcpy(keyPre, key, sizeof(key));
      // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
    // �S�L�[�̓��͏�Ԃ��擾����
       keyboard->GetDeviceState(sizeof(key), key);

   
}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;

    }

    //�C�ӂ̃{�^����������Ă��Ȃ�������
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]!=0&& keyPre[keyNumber]==0) {
        return true;

    }
    return false;
}
