﻿#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

//WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();

//DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initilize(winApp_);

    //Inputの生成、初期化
    input_=new Input();
    input_->Initialize(winApp_);

    // ゲームループ
    while (true) {
        //更新
        if (winApp_->Update() == true) {
            //ゲームループを抜ける
            break;
        }
      
        //入力の更新
        input_->Update();

        //更新前処理
        dxCommon_->PreDraw();
        
        //更新後処理
        dxCommon_->PostDraw();
    }

    //deleteデリート置き場
    delete input_;

    delete dxCommon_;

    winApp_->Finalize();
    delete winApp_;



    return 0;
}
