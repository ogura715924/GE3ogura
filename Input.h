#pragma once
#include<Windows.h>

#define DIRECTINPUT_VESION 0x0800//DirectInputのバージョン指定
#include <dinput.h>

//#pragma comment(lib. "dinput8.lib")
//#pragma comment(lib. "dxguid.lib")

#include<wrl.h>
#include "WinApp.h"

class Input
{public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//初期化
	void Initialize(WinApp*winApp);
	//更新
	void Update();

	//任意のボタンを押されている
	bool PushKey(BYTE keyNumber);
	//任意のボタンが押された瞬間
	bool TriggerKey(BYTE keyNumber);

private://メンバ変数
	WinApp* winApp_ = nullptr;

	Microsoft::WRL::ComPtr<IDirectInput8>directInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8>keyboard;
	// キーボードデバイスの生成
	
	//全キーの状態
	BYTE key[256] = {};
	//前回のキーの状態
	BYTE keyPre[256] = {};
};

