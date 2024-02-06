#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

    // WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();

    // DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initilize(winApp_);

    //Inputの生成、初期化
    input_=new Input();
    input_->Initialize(winApp_);

    // スプライトコモン
    SpriteCommon* spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon_);

    Sprite* sprite_ = new Sprite();
    sprite_->Initialize(dxCommon_, spriteCommon_);
  
    // ゲームループ
    while (true) {
        //更新
        if (winApp_->Update() == true) {
            //ゲームループを抜ける
            break;
        }
      
        //入力の更新
        input_->Update();

        // 描画前処理
        dxCommon_->PreDraw();

        sprite_->Draw();

        // 描画後処理
        dxCommon_->PostDraw();


    }

    //deleteデリート置き場
    delete spriteCommon_;
    delete sprite_;
    delete input_;
    delete dxCommon_;
    winApp_->Finalize();
    delete winApp_;



    return 0;
}
