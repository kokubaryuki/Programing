#include"ResultScene.h"
#include"../Object/RankingDate.h"
#include"../Utility/InputControl.h"
#include"GameMainScene.h"
#include"DxLib.h"

ResultScene::ResultScene() :back_ground(NULL), score(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

ResultScene::~ResultScene()
{

}

//����������
void ResultScene::Initialize()
{
	
	//�摜�̓Ǎ���
	back_ground = LoadGraph("Resource/images/RESULT.png");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/RESULT.png������܂���\n");
	}
	//�Q�[���̌���
	ReadResultData();
}


//�X�V����
eSceneType ResultScene::Update()
{
	//B�{�^���Ń����L���O�Ɉړ�����
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, -66, back_ground, TRUE);

	////�X�R�A���\���̈�
	//DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	//DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(60);
	DrawString(450, 230, "�����L���O�\", GetColor(255,215,0));
	SetFontSize(55);
	DrawString(395, 370, "1��:", GetColor(255,215,0));
	SetFontSize(45);
	DrawString(395, 440, "2��:", GetColor(119,136,153));
	DrawString(395, 510, "3��:", GetColor(160,69,19));
	DrawString(395, 570, "4��:", GetColor(255, 255, 255));

	




	for (int i = 0; i < 3; i++)
	{
		//D/*rawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
		//DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x %4d=%6d", enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);*/
	}

	/*DrawString(180, 290, "�X�R�A", GetColor(0, 0, 0));
	DrawFormatString(180, 290, 0xFFFFFF, "      =%6d", score);*/

	
}

//�I��������
void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}

}

//���݂̃V�[�������擾����
eSceneType ResultScene::GetNowScene()const
{
	return eSceneType::E_RESULT;
}

//���U���g�f�[�^�̓Ǎ���
void ResultScene::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��݂܂���\n");
	}

	//���ʂ�Ǎ���
	fscanf_s(fp, "%d,\n",&score);


	//���������Ɠ��_���擾
	for(int i=0;i<3;i++)
	{
		fscanf_s(fp, "%d,\n", &enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

}












