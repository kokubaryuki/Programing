#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene() :background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読込み
	background_image = LoadGraph("Resource/images/help (3).png");
	backSe = LoadSoundMem("Resource/SE/選択時の効果音.mp3");
	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/help (3).pngがありません\n");
	}
}


//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_B))
	{
		PlaySoundMem(backSe, DX_PLAYTYPE_BACK);
		return eSceneType::E_TITLE;
	}
	return GetNowScene();

}


//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0,0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(20);
	/*DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);
	DrawString(20, 160, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 180, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 200, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 220, "数回当たるとゲームオーバーです", 0xffffff, 0);*/

	DrawString(430, 650, "----　Bボタンを押してタイトルへ戻る ----", 0xffffff, 0);
}


//終了時処理
void HelpScene::Finalize()
{
	//読み込んだ画像の処理
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene()const
{
	return eSceneType::E_HELP;
}

