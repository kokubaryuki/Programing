#pragma once

#include"Vector2D.h"
#include"math.h"

#define DEEDZOON 10000.0f

//���͊Ǘ��@�\
class InputControl
{
private:

	static bool now_button[4][16];//���݃t���[�����͒l
	static bool old_button[4][16];//�ߋ��t���[�����͒l
	static float trigger[4][2];   //���E�g���K�[���͒l
	static Vector2D stick[4][2];//���E�X�e�B�b�N���͒l

public:
	static void Update(int pad); //�X�V����

	//�{�^�����͎擾����
	static bool GetButton(int pad,int button);    //���������Ă����
	static bool GetButtonDown(int pad,int button);//�������u��
	static bool GetButtonUp(int pad,int button);  //�������u��


	//�g���K�[���͎擾����
	static float GetLeftTrigger(int pad);        //���g���K�[
	static float GetRightTrigger(int pad);       //�E�g���K�[

	//�X�e�B�b�N���͎擾����
	static Vector2D GetLeftStick(int pad);
	static Vector2D GetRightStick(int pad);

private:
    //�{�^���z��͈̓`�F�b�N
	static bool CheckButtonRange(int pad,int button);

};
