#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
class RailCamera
{
public:

	void Initialize();

	void Update();

private:
		//���[���h�ϊ��f�[�^
		WorldTransform worldTransform_;
		//�r���[�v���W�F�N�V����
		ViewProjection viewProjection_;
};

