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

//初期化処理
void ResultScene::Initialize()
{
	
	//画像の読込み
	back_ground = LoadGraph("Resource/images/RESULT.png");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/RESULT.pngがありません\n");
	}
	//ゲームの結果
	ReadResultData();
}


//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに移動する
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, -66, back_ground, TRUE);

	////スコア等表示領域
	//DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	//DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(60);
	DrawString(450, 230, "ランキング表", GetColor(255,215,0));
	SetFontSize(55);
	DrawString(395, 370, "1位:", GetColor(255,215,0));
	SetFontSize(45);
	DrawString(395, 440, "2位:", GetColor(119,136,153));
	DrawString(395, 510, "3位:", GetColor(160,69,19));
	DrawString(395, 570, "4位:", GetColor(255, 255, 255));

	




	for (int i = 0; i < 3; i++)
	{
		//D/*rawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
		//DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x %4d=%6d", enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);*/
	}

	/*DrawString(180, 290, "スコア", GetColor(0, 0, 0));
	DrawFormatString(180, 290, 0xFFFFFF, "      =%6d", score);*/

	
}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}

}

//現在のシーン情報を取得する
eSceneType ResultScene::GetNowScene()const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込みません\n");
	}

	//結果を読込み
	fscanf_s(fp, "%d,\n",&score);


	//避けた数と得点を取得
	for(int i=0;i<3;i++)
	{
		fscanf_s(fp, "%d,\n", &enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

}












