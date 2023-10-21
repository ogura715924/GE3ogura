#pragma once
#include<Windows.h>
#include<wrl.h>

#define DIRECTINPUT_VESION 0x0800//DirectInputのバージョン指定
#include <dinput.h>

class Input
{public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();

	//任意のボタンを押されている
	bool PushKey(BYTE keyNumber);
	//任意のボタンが押された瞬間
	bool TriggerKey(BYTE keyNumber);

private://メンバ変数
	Microsoft::WRL::ComPtr<IDirectInput8>driectInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8>keyboard;
	// キーボードデバイスの生成
	
	//全キーの状態
	BYTE key[256] = {};
	//前回のキーの状態
	BYTE keyPre[256] = {};
};

