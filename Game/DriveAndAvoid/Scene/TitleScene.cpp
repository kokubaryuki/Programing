#include"TileScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓Ǎ���
	background_image = LoadGraph("Resource/images/Title2.png");
	menu_image= LoadGraph("Resource/images/Title1.png");
	cursor_image= LoadGraph("Resource/images/cone.bmp");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title2.pig������܂���\n");
	}

	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}

	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}

}

//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;

		//��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}
	
	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}


	//�J�[�\������i���肵����ʂɈړ�����)
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:
			return eSceneType::E_HELP;

		default:
			return eSceneType::E_END;

		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void TitleScene::Draw()const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//���j���[�摜�̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 58, 0.7, DX_PI / 2.0, cursor_image, TRUE);

}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene()const
{
	return eSceneType::E_TITLE;
}








