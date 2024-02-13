#pragma once

#include"Vector2D.h"
#include"math.h"

#define DEEDZOON 4500.0f

//入力管理機能
class InputControl
{
private:

	int Pad1;
	int SetUseJoypadFlag;

	static bool now_button[16];//現在フレーム入力値
	static bool old_button[16];//過去フレーム入力値
	static float trigger[2];   //左右トリガー入力値
	static Vector2D stick[2];//左右スティック入力値

public:
	static void Update(); //更新処理

	//ボタン入力取得処理
	static bool GetButton(int button);    //押し続けている間
	static bool GetButtonDown(int button);//押した瞬間
	static bool GetButtonUp(int button);  //離した瞬間


	//トリガー入力取得処理
	static float GetLeftTrigger();        //左トリガー
	static float GetRightTrigger();       //右トリガー

	//スティック入力取得処理
	static Vector2D GetLeftStick();
	static Vector2D GetRightStick();

private:
    //ボタン配列範囲チェック
	static bool CheckButtonRange(int button);

};
