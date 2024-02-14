#include "EndScene.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

EndScene::EndScene() :back_ground(NULL)
{

}

EndScene::~EndScene()
{

}

//初期化処理
void EndScene::Initialize()
{
	y = 720;
	back_ground = LoadGraph("Resource/images/End.bmp");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/End.bmpがありません\n");
	}
}

//更新処理
eSceneType EndScene::Update()
{

	y--;
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(1, XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void EndScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);

	//引用先表示
	SetFontSize(20);
	DrawString(540, y, "BGM   musmus.main.jp", GetColor(204, 0, 0));
	SetFontSize(20);
	DrawString(500, y+30, "SE        soundeffect-lab.info", GetColor(0, 0, 0));
}

//終了時処理
void EndScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
}

//現在のシーン情報を取得する
eSceneType EndScene::GetNowScene() const
{
	
	return eSceneType::E_END;
}