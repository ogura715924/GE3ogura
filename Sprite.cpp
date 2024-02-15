#include "Sprite.h"

#include <DirectXMath.h>

#include "BufferResorce.h"

#include "External/imgui/imgui.h"

#include"TextureManager.h"


using namespace Microsoft::WRL;
using namespace DirectX;


void Sprite::Initialize( SpriteCommon* common, std::wstring textureFilePath)
{
	common_ = common;
	dxCommon_ = common_->GetDirectXCommon();

	textureIndex_ = TextureManager::Getinstance()->GetTextureIndexFilePath(textureFilePath);

	//���_���
	CreateVertex();
	//�C���f�b�N�X���
	CreateIndex();
	//�F
	CreateMaterial();
	//�s��
	CreateWVP();

	//�摜�̃T�C�Y�𐮗�����
	AdjustTextureSize();
}

void Sprite::Update()
{
	//�X�V����
	transform.translate ={position.x, position.y, 0};
	transform.rotate = { 0,0,rotation };
	materialData->color = color_;
	transform.scale = { size.x,size.y,1.0f };


	//�A���J�[�|�C���g�X�V
	float left = 0.0f - anchorPoint.x;
	float right = 1.0f - anchorPoint.x;
	float top = 0.0f - anchorPoint.y;
	float bottom = 1.0f - anchorPoint.y;

	//�t���b�v
	if (isFlipX == true) {
		//���E���]
		left = -left;
		right = -right;
	}
	if (isFlipY == true) {
		//�㉺���]
		top = -top;
		bottom = -bottom;
	}


	//���_���
	vertexData[0].position = { left, bottom, 0.0f, 1.0f };
	vertexData[1].position = { left, top, 0.0f, 1.0f };
	vertexData[2].position = { right, bottom, 0.0f, 1.0f };
	vertexData[3].position = { right, top, 0.0f, 1.0f };

	//���_���
	vertexData[0].position = { left, bottom, 0.0f, 1.0f };
	vertexData[1].position = { left, top, 0.0f, 1.0f };
	vertexData[2].position = { right, bottom, 0.0f, 1.0f };
	vertexData[3].position = { right, top, 0.0f, 1.0f };


	const DirectX::TexMetadata& metaData = TextureManager::Getinstance()->GetMetaData(textureIndex_);
	float tex_left = textureLeftTop.x / metaData.width;
	float tex_right = (textureLeftTop.x + textureSize.x) / metaData.width;
	float tex_top = textureLeftTop.y / metaData.height;
	float tex_bottom = (textureLeftTop.y + textureSize.y) / metaData.height;


	//UV���W
	vertexData[0].texcord = { tex_left ,tex_bottom };
	vertexData[1].texcord = { tex_left,tex_top };
	vertexData[2].texcord = { tex_right,tex_bottom };
	vertexData[3].texcord = { tex_right,tex_top };


	ImGui::Begin("Texture");
	ImGui::DragFloat3("Pos", &transform.translate.x, 0.1f);

	ImGui::DragFloat3("UV-Pos", &uvTransform.translate.x, 0.01f, -10.f, 10.f);
	ImGui::SliderAngle("UV-Rot", &uvTransform.rotate.z);
	ImGui::DragFloat3("UV-Scale", &uvTransform.scale.x, 0.01f, -10.f, 10.f);

	ImGui::End();
}

void Sprite::Draw()
{
	//Y���𒆐S�ɉ�]
	//transform.rotate.y += 0.03f;
	//���[���h
	XMMATRIX scaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&transform.scale));
	XMMATRIX rotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&transform.rotate));
	XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&transform.translate));
	//��]�s��ƃX�P�[���s��̊|���Z
	XMMATRIX rotationAndScaleMatrix = XMMatrixMultiply(rotateMatrix, scaleMatrix);
	//�ŏI�I�ȍs��ϊ�
	XMMATRIX worldMatrix = XMMatrixMultiply(rotationAndScaleMatrix, translationMatrix);

	//�J����
	XMMATRIX cameraScaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&cameraTransform.scale));
	XMMATRIX cameraRotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&cameraTransform.rotate));
	XMMATRIX cameraTranslationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&cameraTransform.translate));
	//��]�s��ƃX�P�[���s��̊|���Z
	XMMATRIX cameraRotationAndScaleMatrix = XMMatrixMultiply(cameraRotateMatrix, cameraScaleMatrix);
	//�ŏI�I�ȍs��ϊ�
	XMMATRIX cameraMatrix = XMMatrixMultiply(cameraRotationAndScaleMatrix, cameraTranslationMatrix);

	//View
	XMMATRIX view = XMMatrixInverse(nullptr, cameraMatrix);
	//Proj
	XMMATRIX proj = XMMatrixOrthographicOffCenterLH(0, WinApp::window_width, WinApp::window_height, 0, 0.1f, 100.0f);
	// WVP
	XMMATRIX worldViewProjectionMatrix = worldMatrix * (view * proj);

	// �s��̑��
	*wvpData = worldViewProjectionMatrix;


	//UV���W
	XMMATRIX uvscaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&uvTransform.scale));
	XMMATRIX uvrotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&uvTransform.rotate));
	XMMATRIX uvtranslationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&uvTransform.translate));
	//��]�s��ƃX�P�[���s��̊|���Z
	XMMATRIX uvrotationAndScaleMatrix = XMMatrixMultiply(uvrotateMatrix, uvscaleMatrix);
	//�ŏI�I�ȍs��ϊ�
	XMMATRIX uvworldMatrix = XMMatrixMultiply(uvrotationAndScaleMatrix, uvtranslationMatrix);
	materialData->uvTransform = uvworldMatrix;


	//���_���
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//�C���f�b�N�X���
	dxCommon_->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	//�F���
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//�s��
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	//�摜
	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2,TextureManager::Getinstance()->GetSrvHandleGPU(textureIndex_));

	//���_���̂ݕ`��
	//dxCommon_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
	//�C���f�b�N�X��񂪂���ꍇ�̕`��
	dxCommon_->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0,0);

}

void Sprite::SetTexture(std::wstring textureFilePath)
{
	textureIndex_ = TextureManager::Getinstance()->GetTextureIndexFilePath(textureFilePath);
}


void Sprite::CreateVertex()
{
	//VertexResource
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(VertexData) * 4);

	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 4;
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	//���_���
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	vertexData[0].position = { 0.0f, 1.0f, 0.0f, 1.0f };
	vertexData[0].texcord = { 0.0f,1.0f };

	vertexData[1].position = { 0.0f, 0.0f, 0.0f, 1.0f };
	vertexData[1].texcord = { 0.0f,0.0f };

	vertexData[2].position = { 1.0f, 1.0f, 0.0f, 1.0f };
	vertexData[2].texcord = { 1.0f,1.0f };

	vertexData[3].position = { 1.0f, 0.0f, 0.0f, 1.0f };
	vertexData[3].texcord = { 1.0f,0.0f };

}

void Sprite::CreateIndex()
{
	indexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(uint32_t) * 6);

	indexBufferView.BufferLocation = indexResource->GetGPUVirtualAddress();
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;

	uint32_t* indexData = nullptr;
	indexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	//VertexData[0,1,2]�̒��_�ŎO�p�`���ꖇ�쐬
	indexData[0] = 0;   indexData[1] = 1; indexData[2] = 2;

	//VertexData[1,3,2]�̒��_�ŎO�p�`���ꖇ�쐬
	indexData[3] = 1;   indexData[4] = 3; indexData[5] = 2;
}

void Sprite::CreateMaterial()
{
	materialResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(MaterialData));

	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	materialData->color = color_;
	materialData->uvTransform = XMMatrixIdentity();
}

void Sprite::CreateWVP()
{
	wvpResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMMATRIX));
    
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));

	*wvpData = XMMatrixIdentity();
}

void Sprite::AdjustTextureSize()
{
	const DirectX::TexMetadata& metaData = TextureManager::Getinstance()->GetMetaData(textureIndex_);

	textureSize.x = static_cast<float>(metaData.width);
	textureSize.y = static_cast<float>(metaData.height);

	size = textureSize;
}
