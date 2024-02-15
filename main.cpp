#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

#include"SpriteCommon.h"
#include"Sprite.h"

#include"ImGuiManager.h"


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

    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp_->GetHwnd(), dxCommon_);

    // スプライトコモン
    SpriteCommon* Common = new SpriteCommon();
    Common->Initialize(dxCommon_);

    // スプライト
    Sprite* sp = new Sprite();
    sp->Initialize(Common);


    // ゲームループ
    while (true) {
        //更新
        if (winApp_->Update() == true) {
            //ゲームループを抜ける
            break;
        }

        ImGuiManager::NewFrame();
        imgui->ShowDemo();
      
        //入力の更新
        input_->Update();

        //更新前処理
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();
        Common->SpritePreDraw();
        
        //スプライト
        sp->Draw();

        //更新後処理
        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();
    }

    //deleteデリート置き場
    delete sp;
    delete Common;
    delete imgui;
    delete input_;
    delete dxCommon_;
    winApp_->Finalize();
    delete winApp_;



    return 0;
}
