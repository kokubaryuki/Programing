#include"ResultScene.h"
#include"../Object/RankingDate.h"
#include"../Utility/InputControl.h"
#include"GameMainScene.h"
#include"DxLib.h"

ResultScene::ResultScene() :back_ground(NULL), score(0)
{

}

ResultScene::~ResultScene()
{

}

//����������
void ResultScene::Initialize()
{
	resultimage[0] = LoadGraph("Resource/images/PLAYER1.png");
	resultimage[1] = LoadGraph("Resource/images/PLAYER2.png");
	resultimage[2] = LoadGraph("Resource/images/PLAYER3.png");
	resultimage[3] = LoadGraph("Resource/images/PLAYER4.png");
	winnerimage = LoadGraph("Resource/images/WINNER.png");
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
	switch (mode) {
	case MODE::ANNOUNCEMENT:
		count++;

		break;
	case MODE::FREE:
		//B�{�^���Ń����L���O�Ɉړ�����
		if (InputControl::GetButtonDown(0, XINPUT_BUTTON_B))
		{
			return eSceneType::E_TITLE;
		}
		break;
	case MODE::FINISH:

		break;
	default:
		break;
	}
	
	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, -66, back_ground, TRUE);
	DrawGraph(378, 200, winnerimage, TRUE);
	DrawGraph(350, 350, resultimage[score], TRUE);

}

//�I��������
void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	DeleteGraph(winnerimage);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(resultimage[i]);
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


	////���������Ɠ��_���擾
	//for(int i=0;i<3;i++)
	//{
	//	fscanf_s(fp, "%d,\n", &enemy_count[i]);
	//}

	//�t�@�C���N���[�Y
	fclose(fp);

}












