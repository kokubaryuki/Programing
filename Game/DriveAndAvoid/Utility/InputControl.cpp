#include"InputControl.h"
#include"DxLib.h"

bool InputControl::now_button[4][16] = {};
bool InputControl::old_button[4][16] = {};
float InputControl::trigger[4][2] = {};
Vector2D InputControl::stick[4][2] = {};

//入力機能:更新処理
void  InputControl::Update(int pad)
{

	//XInputコントローラーの入力値を取得する
	XINPUT_STATE input_state[4] = {};
	GetJoypadXInputState(DX_INPUT_PAD1+pad, &input_state[pad]);


	//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button[pad][i] = now_button[pad][i];
		now_button[pad][i] = (bool)input_state[pad].Buttons[i];
	}

	//トリガー入力値の更新（0.0f～1.0fに範囲を制限する）
	trigger[pad][0] = (float)input_state[pad].LeftTrigger / (float)UCHAR_MAX;
	trigger[pad][1] = (float)input_state[pad].RightTrigger / (float)UCHAR_MAX;


	//左スティック入力値の更新（-1.0f～1.0fに範囲を制限する)
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



	//右スティック入力値の更新(-1.0f～1.0fに範囲を制限する）
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

//ボタン取得:押してる間
bool InputControl::GetButton(int pad,int button)
{
	return CheckButtonRange(pad,button) && (now_button[pad][button] &&
		old_button[pad][button]);
}

//ボタンを押した瞬間
bool InputControl::GetButtonDown(int pad,int button)
{
	return CheckButtonRange(pad,button) && (now_button[pad][button] &&
		!old_button[pad][button]);
}

//ボタン取得:離した瞬間
bool InputControl::GetButtonUp(int pad,int button)
{
	return CheckButtonRange(pad,button) && (!now_button[pad][button] &&
		old_button[pad][button]);
}

//左トリガー取得
float InputControl::GetLeftTrigger(int pad)
{
	return trigger[pad][0];
}


//右トリガー取得
float InputControl::GetRightTrigger(int pad)
{
	return trigger[pad][1];
}


//左スティック
Vector2D InputControl::GetLeftStick(int pad)
{
	return stick[pad][0];
}

//右スティック
Vector2D InputControl::GetRightStick(int pad)
{
	return stick[pad][1];
}

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int pad,int button)
{
	return(0 <= now_button[pad][button] && now_button[pad][button] < 16);
}


