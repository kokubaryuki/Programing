#include "EndScene.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

EndScene::EndScene() :back_ground(NULL)
{

}

EndScene::~EndScene()
{

}

//����������
void EndScene::Initialize()
{
	y = 720;
	back_ground = LoadGraph("Resource/images/End.bmp");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/End.bmp������܂���\n");
	}
}

//�X�V����
eSceneType EndScene::Update()
{

	y--;
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(1, XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void EndScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);

	//���p��\��
	SetFontSize(20);
	DrawString(540, y, "BGM   musmus.main.jp", GetColor(204, 0, 0));
	SetFontSize(20);
	DrawString(500, y+30, "SE        soundeffect-lab.info", GetColor(0, 0, 0));
}

//�I��������
void EndScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
}

//���݂̃V�[�������擾����
eSceneType EndScene::GetNowScene() const
{
	
	return eSceneType::E_END;
}