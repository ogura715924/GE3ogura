#include "Input.h"

#include <cassert>

using namespace Microsoft::WRL;

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(WinApp* winApp)
{
    WinApp_ = winApp;

    HRESULT result;

    // DirectInput�̏�����(�L�[�{�[�h�̏���)
    ComPtr<IDirectInput8> directInput;
    result = DirectInput8Create(
       WinApp_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

  
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        WinApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
    for (int i = 0; i < 256; i++) {
        keyPre[i] = key[i];
    }
    //��Ɠ����@�\
    //keyPre�̒���key�̏����R�s�[����
    memcpy(keyPre, key, sizeof(key));

    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
   
    keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����
    if (key[keyNumber]) {
        return true;
    }
    //�����łȂ����false��Ԃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����
    if (key[keyNumber] != 0 && keyPre[keyNumber] == 0) {
        return true;
    }
    return false;
}
