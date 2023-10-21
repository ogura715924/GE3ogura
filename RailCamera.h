#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
class RailCamera
{
public:

	void Initialize();

	void Update();

private:
		//ワールド変換データ
		WorldTransform worldTransform_;
		//ビュープロジェクション
		ViewProjection viewProjection_;
};

