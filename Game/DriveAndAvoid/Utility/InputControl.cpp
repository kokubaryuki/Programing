#include"InputControl.h"
#include"DxLib.h"

bool InputControl::now_button[4][16] = {};
bool InputControl::old_button[4][16] = {};
float InputControl::trigger[4][2] = {};
Vector2D InputControl::stick[4][2] = {};

//���͋@�\:�X�V����
void  InputControl::Update(int pad)
{

	//XInput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state[4] = {};
	GetJoypadXInputState(DX_INPUT_PAD1+pad, &input_state[pad]);


	//�{�^�����͒l�̍X�V
	for (int i = 0; i < 16; i++)
	{
		old_button[pad][i] = now_button[pad][i];
		now_button[pad][i] = (bool)input_state[pad].Buttons[i];
	}

	//�g���K�[���͒l�̍X�V�i0.0f�`1.0f�ɔ͈͂𐧌�����j
	trigger[pad][0] = (float)input_state[pad].LeftTrigger / (float)UCHAR_MAX;
	trigger[pad][1] = (float)input_state[pad].RightTrigger / (float)UCHAR_MAX;


	//���X�e�B�b�N���͒l�̍X�V�i-1.0f�`1.0f�ɔ͈͂𐧌�����)
	if (fabs((double)input_state[pad].ThumbLX) > DEEDZOON)
	{
		stick[pad][0].x = (float)input_state[pad].ThumbLX / (float)SHRT_MAX;
	}

	else
	{
		//stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
		stick[pad][0].x = 0.0f;
	}


	if (fabs((double)input_state[pad].ThumbLY) > DEEDZOON)
	{
		stick[pad][0].y = -(float)input_state[pad].ThumbLY / (float)SHRT_MAX;
	}

	else
	{
		//stick[0].y = ((float)input_state.ThumbLY / (float)SHRT_MIN);
		stick[pad][0].y = 0.0f;
	}



	//�E�X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����j
	if (input_state[pad].ThumbRX > 0.0f)
	{
		stick[pad][1].x=(float)input_state[pad].ThumbRX / (float)SHRT_MAX;
	}
	
	else
	{
		stick[pad][1].x= -((float)input_state[pad].ThumbRX / (float)SHRT_MIN);
	}

	if (input_state[pad].ThumbRY > 0.0f)
	{
		stick[pad][1].y = (float)input_state[pad].ThumbRY / (float)SHRT_MAX;
	}

	else
	{
		stick[pad][1].y = -((float)input_state[pad].ThumbRY / (float)SHRT_MIN);
	}

}
//

//�{�^���擾:�����Ă��
bool InputControl::GetButton(int pad,int button)
{
	return CheckButtonRange(pad,button) && (now_button[pad][button] &&
		old_button[pad][button]);
}

//�{�^�����������u��
bool InputControl::GetButtonDown(int pad,int button)
{
	return CheckButtonRange(pad,button) && (now_button[pad][button] &&
		!old_button[pad][button]);
}

//�{�^���擾:�������u��
bool InputControl::GetButtonUp(int pad,int button)
{
	return CheckButtonRange(pad,button) && (!now_button[pad][button] &&
		old_button[pad][button]);
}

//���g���K�[�擾
float InputControl::GetLeftTrigger(int pad)
{
	return trigger[pad][0];
}


//�E�g���K�[�擾
float InputControl::GetRightTrigger(int pad)
{
	return trigger[pad][1];
}


//���X�e�B�b�N
Vector2D InputControl::GetLeftStick(int pad)
{
	return stick[pad][0];
}

//�E�X�e�B�b�N
Vector2D InputControl::GetRightStick(int pad)
{
	return stick[pad][1];
}

//�{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange(int pad,int button)
{
	return(0 <= now_button[pad][button] && now_button[pad][button] < 16);
}


