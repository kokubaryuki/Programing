/***************************
*�Ԕ����Q�[��������Ă݂悤!
****************************/
#include"DxLib.h"
#include"Scene/SceneManager.h"

//���C���֐�(�v���O�����͂�������n�܂�܂�)
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)

{
	//��O����(�ُ킪����������Acatch���ɔ�т܂�)
	try
	{
		double dNextTime = GetNowCount();

		SetMainWindowText("�N���u��");

		ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

		SetAlwaysRunFlag(true);		//��ɃA�N�e�B�u�ɂ���

		SetGraphMode(1280, 720, 32);	//��ʃT�C�Y�̐ݒ�

		if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

		SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

		//�V�[���}�l�[�W���[�@�\�̐���
		SceneManager manager;

		//�V�[���}�l�[�W���[�@�\�̏���������
		manager.Initialize();

	    //�V�[���}�l�[�W���[�̍X�V����
		manager.Update();

		//�V�[���}�l�[�W���[�@�\�̏I��������
		manager.Finalize();
	}
	catch (const char* err_log)
	{
		//�G���[�������e�̏o��
		OutputDebugString(err_log);

		//�G���[�I����ʒm
		return-1;
	}

	//����I����ʒm
	return 0;
}