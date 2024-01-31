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

	//任意ボタンを押されているとき
	bool PushKey(BYTE keyNumber);
	//任意ボタンを押された瞬間
	bool TriggerKey(BYTE keyNumber);

private://メンバ変数
	// キーボードデバイスの生成
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	// 全キーの入力状態を取得する
	BYTE key[256] = {};
	//前回のキー
	BYTE keyPre[256] = {};
};

