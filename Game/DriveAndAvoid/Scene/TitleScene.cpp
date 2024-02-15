#include"TileScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_start(NULL), menu_help(NULL), menu_end(NULL),
cursor_image(NULL), menu_cursor(0)
{
	
}

TitleScene::~TitleScene()
{
	
}

//����������
void TitleScene::Initialize()
{
	SHandle = LoadSoundMem("Resource/BGM/Titlebgm.wav");
	selectSe = LoadSoundMem("Resource/SE/�I�����̌��ʉ�.mp3");
	decideSe = LoadSoundMem("Resource/SE/DECIDE.mp3");
	openingse = LoadSoundMem("Resource/SE/OPENING.mp3");
	//�摜�̓Ǎ���
	name = LoadGraph("Resource/images/TITLENAME.png");
	background_image = LoadGraph("Resource/images/TITLE.png");
	menu_start = LoadGraph("Resource/images/TITLESTART.png");
	menu_help = LoadGraph("Resource/images/TITLEHELP.png");
	menu_end = LoadGraph("Resource/images/TITLEEND.png");
	cursor_image= LoadGraph("Resource/images/SELECTBER2.png");
	
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
	ChangeVolumeSoundMem(255, SHandle);
	//PlaySoundMem(SHandle, DX_PLAYTYPE_LOOP, TRUE);
}

//�X�V����
eSceneType TitleScene::Update()
{
	switch (phase) 
	{
	case PHASE::OPENING:
		if (!CheckSoundMem(openingse)) 
		{
			PlaySoundMem(openingse, DX_PLAYTYPE_BACK, TRUE);
		}
		count++;
		if (240 <= count) {
			count = 0;
			phase = PHASE::MENU;
		}
		break;
	case PHASE::MENU:
		if (!CheckSoundMem(SHandle)) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_LOOP, TRUE);
		}
		TranceRate++;
		if (255 <= TranceRate) {
			TranceRate = 255;
		}
		//�J�[�\�����ړ�
		if (InputControl::GetButtonDown(0, XINPUT_BUTTON_DPAD_DOWN))
		{
			PlaySoundMem(selectSe, DX_PLAYTYPE_BACK, TRUE);
			menu_cursor++;

			//��ԉ��ɓ��B������A��ԏ�ɂ���
			if (menu_cursor > 2)
			{
				menu_cursor = 0;
			}
		}

		//�J�[�\����ړ�
		if (InputControl::GetButtonDown(0, XINPUT_BUTTON_DPAD_UP))
		{
			PlaySoundMem(selectSe, DX_PLAYTYPE_BACK, TRUE);
			menu_cursor--;
			//��ԏ�ɓ��B������A��ԉ��ɂ���
			if (menu_cursor < 0)
			{
				menu_cursor = 2;
			}
		}

		if (InputControl::GetButtonDown(0, XINPUT_BUTTON_B))
		{
			//PlaySoundMem(decideSe, DX_PLAYTYPE_BACK, TRUE);
			StopSoundMem(SHandle);
			phase = PHASE::ENDING;
		}
		break;
	case PHASE::ENDING:
		if (!CheckSoundMem(decideSe)) {
			PlaySoundMem(decideSe, DX_PLAYTYPE_BACK, TRUE);
		}
		TranceRate--;
		if (TranceRate <= 0) {
			TranceRate = 0;
		}
		count++;
		if (count < 50) {
			anim_x -= 3;
		}
		else {
			anim_x += 14;
		}
		if (300 <= count) {
			count = 0;
			anim_x = 0;
			switch (menu_cursor)
			{
			case 0:
				return eSceneType::E_MAIN;
			case 1:
				return eSceneType::E_HELP;
			default:
				return eSceneType::E_CREDIT;
			}
		}
		break;
	default:
		break;
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void TitleScene::Draw()const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TranceRate);
	//���߂��ĕ`��
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
	DrawGraph(25, 25, name, TRUE);
	DrawRotaGraph(1100, 300,1.0f,0, menu_start, TRUE);
	DrawRotaGraph(1090, 360, 1.0f, 0, menu_help, TRUE);
	DrawRotaGraph(1070, 420, 1.0f, 0, menu_end, TRUE);
	//DrawGraph()
	//���j���[�摜�̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(950 + anim_x, 300 + menu_cursor * 60, 1.0f, 0, cursor_image, TRUE);
	//�ݒ�����ɖ߂��B
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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








