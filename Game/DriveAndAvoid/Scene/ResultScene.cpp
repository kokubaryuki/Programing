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

//初期化処理
void ResultScene::Initialize()
{
	resultimage[0] = LoadGraph("Resource/images/PLAYER1.png");
	resultimage[1] = LoadGraph("Resource/images/PLAYER2.png");
	resultimage[2] = LoadGraph("Resource/images/PLAYER3.png");
	resultimage[3] = LoadGraph("Resource/images/PLAYER4.png");
	winnerimage = LoadGraph("Resource/images/WINNER.png");
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
	switch (mode) {
	case MODE::ANNOUNCEMENT:
		count++;

		break;
	case MODE::FREE:
		//Bボタンでランキングに移動する
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

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, -66, back_ground, TRUE);
	DrawGraph(378, 200, winnerimage, TRUE);
	DrawGraph(350, 350, resultimage[score], TRUE);

}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	DeleteGraph(winnerimage);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(resultimage[i]);
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


	////避けた数と得点を取得
	//for(int i=0;i<3;i++)
	//{
	//	fscanf_s(fp, "%d,\n", &enemy_count[i]);
	//}

	//ファイルクローズ
	fclose(fp);

}












