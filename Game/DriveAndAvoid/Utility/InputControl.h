#pragma once

#include"Vector2D.h"
#include"math.h"

#define DEEDZOON 10000.0f

//入力管理機能
class InputControl
{
private:

	static bool now_button[4][16];//現在フレーム入力値
	static bool old_button[4][16];//過去フレーム入力値
	static float trigger[4][2];   //左右トリガー入力値
	static Vector2D stick[4][2];//左右スティック入力値

public:
	static void Update(int pad); //更新処理

	//ボタン入力取得処理
	static bool GetButton(int pad,int button);    //押し続けている間
	static bool GetButtonDown(int pad,int button);//押した瞬間
	static bool GetButtonUp(int pad,int button);  //離した瞬間


	//トリガー入力取得処理
	static float GetLeftTrigger(int pad);        //左トリガー
	static float GetRightTrigger(int pad);       //右トリガー

	//スティック入力取得処理
	static Vector2D GetLeftStick(int pad);
	static Vector2D GetRightStick(int pad);

private:
    //ボタン配列範囲チェック
	static bool CheckButtonRange(int pad,int button);

};
