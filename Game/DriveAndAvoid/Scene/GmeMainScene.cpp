#include"GameMainScene.h"
#include"../Object/RankingDate.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL), mileage(0) /*,player(nullptr)*/ 
{

}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	Number_of_connections = GetJoypadNum();
	readysound = LoadSoundMem("Resource/SE/ready.wav");

	//高得点値を読み込む
	ReadHighScore();
	SHandle = LoadSoundMem("Resource/BGM/戦闘bgm.wav");
	//画像の読込み
	back_ground = LoadGraph("Resource/images/Stage.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);


	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}

	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}

	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}
	//, 275:50, 1000:50, 275:670  1000:670
	//オブジェクトの生成
	/*for (int i = 0; i < Number_of_connections + 1; i++) {
		player[i] = new Player(i,);
	}*/
	player[0] = new Player(0, 275, 50);
	player[1] = new Player(1, 1000, 50);
	player[2] = new Player(2, 275, 670);
	player[3] = new Player(3, 1000, 670);
	//player = new Player();
	//enemy = new Enemy* [10];

	//オブジェクトの初期化
	/*for (int i = 0; i < 4; i++) {
		player[i]->Initialize();
	}*/
	for (int i = 0; i < 4; i++) {
		player[i]->Initialize();
	}
	//player->Initialize();

	/*for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}*/
	
}

//更新処理
eSceneType GameMainScene::Update()
{
	switch (phase) 
	{
	case Mphase::READY:
		if (readycount == 0) {
			PlaySoundMem(readysound, DX_PLAYTYPE_LOOP);
		}
		readycount++;
		if (3 <= readycount / 60) 
		{
			readycount = 0;
			StopSoundMem(readysound);
			phase = Mphase::GO;
		}
		break;
	case Mphase::GO:
		//プレイヤーの更新
		for (int i = 0; i < 4; i++) {
			player[i]->Update();
		}
		//コントローラーの接続数次第で当たり判定を行う数を変える
		switch (tmp/*Number_of_connections*/)
		{
		case 2:
			if (IsHitCheck(player[0], player[1]))
			{

			}
			break;
		case 3:
			for (int i = 0; i < 3; i++) {
				if (IsHitCheck(player[combination3[i][0]], player[combination3[i][1]]))
				{

				}
			}
			break;
		case 4:
			for (int i = 0; i < 6; i++) {
				if (IsHitCheck(player[combination4[i][0]], player[combination4[i][1]]))
				{

				}
			}
			break;
		default:
			break;
		}


		break;
	case Mphase::FINISH:
		break;
	default:
		break;
	}


	//移動距離の更新
	//mileage += (int)player->GetSpeed() + 5;

	////敵生成処理
	//if (mileage / 20 % 100 == 0)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		if (enemy[i] == nullptr)
	//		{
	//			int type = GetRand(3) % 3;
	//			enemy[i] = new Enemy(type, enemy_image[type]);
	//			enemy[i]->Initialize();
	//			break;
	//		}
	//	}
	//}

	//敵の更新と当たり判定チェック
	//for (int i = 0; i < 10; i++)
	//{
	//	if (enemy[i] != nullptr)
	//	{
	//		enemy[i]->Update(player->GetSpeed());

	//		//画面外に行ったら、敵を削除そてスコア加算
	//		if (enemy[i]->GetLocation().y >= 640.0f)
	//		{
	//			enemy_count[enemy[i]->GetType()]++;
	//			enemy[i]->Finalize();
	//			delete enemy[i];
	//			enemy[i] = nullptr;
	//		}

	//		//当たり判定の確認
	//		if (IsHitCheck(player, enemy[i]))
	//		{
	//			player->SetActive(false);
	//			player->DecreaseHp(-50.0);
	//			enemy[i]->Finalize();
	//			delete enemy[i];
	//			enemy[i] = nullptr;
	//		}
	//	}
	//}
	//////////////////////////////////////////
	//bool check[4] = { 0,1,0,0 };
	////プレイヤーの燃料か体力が０未満なら、リザルトに遷移する
	//
	//for (int i = 0; i < 4; i++) {
	//	if (player[i]->GetFuel() < 0.0f || player[i]->GetHp() < 0.0f)
	//	{
	//		check[i] = true;
	//	}
	//}
	//int a = 0;
	//for (int i = 0; i < 4; i++) {
	//	if (check[i] == true) {
	//		a++;
	//	}
	//}
	//if (a == 3) {
	//	return eSceneType::E_RESULT;
	//}

	/////////////////////////////////////

	return GetNowScene();
}




//描画処理
void GameMainScene::Draw() const
{
	//背景画像の画像
	//DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(225, mileage % 480, back_ground, TRUE);

	//プレイヤーの描画
	for (int i = 0; i < 4; i++) {
		player[i]->Draw();
	}
	float a = 4.0f - static_cast<float>(readycount / 60.0f);
	switch (phase)
	{
	case Mphase::READY:
		
		SetFontSize(30);
		DrawFormatString(640, 360, 0x000000, "%f", a);
		break;
	case Mphase::GO:
		break;
	case Mphase::FINISH:
		break;
	default:
		break;
	}



	////燃料ゲージの描画
	//float fx = 510.0f;
	//float fy = 390.0;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy +
	//	40.0f, GetColor(0, 102, 204), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	////体力ゲージの描画
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000),
	//	fy + 40.0f, GetColor(255, 0, 0), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}



//終了時処理
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);

	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	//リザルトデータの書き込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開きません\n");
	}

	//スコアを保存
	fprintf(fp, "%d,\n", score);

	//避けた数と得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	for (int i = 0; i < 4; i++) {
		player[i]->Finalize();
	}
	//player->Finalize();
	for (int i = 0; i < 4; i++) {
		delete player[i];
	}
	

	/*for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;*/

}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//当たり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p1, Player* p2)
{
	//プレイヤー同士の距離を測る
	Vector2D ab = p1->GetLocation() - p2->GetLocation();
	//長さを図る
	float length = std::sqrtf(std::powf(ab.x, 2.0f) + std::powf(ab.y, 2.0f));
	
	float hit = length - p1->GetRad() - p2->GetRad();
	/*if (hit<0.0f) {
		return true;
	}*/
	//正規化する
	Vector2D n = Vector2D(ab.x / length, ab.y / length);

	//プレイヤーがバリアを貼っていたら、当たり判定を無視する
	if (p1->IsBarrier())
	{
		return false;
	}
	
	//敵の情報が無ければ、当たり判定を無視する
	if (p2 == nullptr)
	{
		return false;
	}

	//位置情報の差分を取得
	Vector2D diff_location = p1->GetLocation() - p2->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p1->GetBoxSize() + p2->GetBoxSize();


	//コリジョンデータより位置情報の差が小さいなら、ヒットする
	//return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < (box_ex.y)));
}


