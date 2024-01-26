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

	bool PushKey(BYTE keyNumber);

private://メンバ変数
	// キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard;
};

