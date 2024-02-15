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
	Number_of_connections = 0;
	Number_of_connections = GetJoypadNum();
	readysound = LoadSoundMem("Resource/SE/READY.mp3");

	//高得点値を読み込む
	ReadHighScore();
	SHandle = LoadSoundMem("Resource/BGM/戦闘bgm.wav");
	//画像の読込み
	back_ground = LoadGraph("Resource/images/Stage.png");
	back_image = LoadGraph("Resource/images/STAGEBACK.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	//int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);


	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}

	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}
	//, 275:50, 1000:50, 275:670  1000:670
	switch (Number_of_connections) {
	case 2:
		for (int i = 0; i < Number_of_connections; i++) {
			player[i] = new Player(i, Setlocation[Number_of_connections - 2][i].x, Setlocation[Number_of_connections - 2][i].y);
		}
		break;
	case 3:
		for (int i = 0; i < Number_of_connections; i++) {
			player[i] = new Player(i, Setlocation[Number_of_connections - 2][i].x, Setlocation[Number_of_connections - 2][i].y);
		}
		break;
	case 4:
		for (int i = 0; i < Number_of_connections; i++) {
			player[i] = new Player(i, Setlocation[Number_of_connections - 2][i].x, Setlocation[Number_of_connections - 2][i].y);
		}
		break;
	default:
		break;
	}
	/*player[0] = new Player(0, 275, 50);
	player[1] = new Player(1, 1000, 50);
	player[2] = new Player(2, 275, 670);
	player[3] = new Player(3, 1000, 670);*/
	//enemy = new Enemy* [10];

	//オブジェクトの初期化
	/*for (int i = 0; i < 4; i++) {
		player[i]->Initialize();
	}*/
	for (int i = 0; i < Number_of_connections; i++) {
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
		for (int i = 0; i < Number_of_connections; i++) {
			if (player[i] != nullptr) {
				player[i]->Update();
				//画面外に行ったら死ぬ
				if (player[i]->GetLocation().x < 215 || 1065 < player[i]->GetLocation().x ||
					player[i]->GetLocation().y < 0 || 720 < player[i]->GetLocation().y)
				{
					player[i]->Finalize();
					delete player[i];
					player[i] = nullptr;
					DownCount++;
				}
			}
		}
		if (Number_of_connections - 1 <= DownCount) {
			phase = Mphase::FINISH;
			DownCount = 0;
			break;
		}
		//コントローラーの接続数次第で当たり判定を行う数を変える
		switch (Number_of_connections)
		{
		case 2:
			if (player[0] == nullptr || player[1] == nullptr) 
			{
				break;
			}
			if (IsHitCheck(player[0], player[1]))
			{
				CalcRepulsionVector(player[0], player[1]);
			}
			break;
		case 3:
			for (int i = 0; i < 3; i++) 
			{
				//死んでいるキャラの当たり判定は飛ばす
				if (player[combination3[i][0]] == nullptr || player[combination3[i][1]] == nullptr) 
				{
					break;
				}
				if (IsHitCheck(player[combination3[i][0]], player[combination3[i][1]]))
				{
					CalcRepulsionVector(player[combination3[i][0]], player[combination3[i][1]]);
				}
			}
			break;
		case 4:
			for (int i = 0; i < 6; i++) 
			{
				//死んでいるキャラの当たり判定は飛ばす
				if (player[combination4[i][0]] == nullptr || player[combination4[i][1]] == nullptr) 
				{
					break;
				}
				if (IsHitCheck(player[combination4[i][0]], player[combination4[i][1]]))
				{
					CalcRepulsionVector(player[combination4[i][0]], player[combination4[i][1]]);
				}
			}
			break;
		default:
			break;
		}

		break;
	case Mphase::FINISH:

		return eSceneType::E_RESULT;
		break;
	default:
		break;
	}

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の画像
	//DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);

	DrawRotaGraph(640, 360, 1.0, 0, back_image, false);
	DrawGraph(225, mileage % 480, back_ground, TRUE);
	//プレイヤーの描画
	for (int i = 0; i < Number_of_connections; i++) {
		if (player[i] != nullptr) {
			player[i]->Draw();
		}
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

}

//終了時処理
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);

	for (int i = 0; i < 3; i++)
	{
		score = i;
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
	for (int i = 0; i < Number_of_connections; i++) {
		if(player[i] != nullptr)
		player[i]->Finalize();
	}
	//player->Finalize();
	for (int i = 0; i < Number_of_connections; i++) {
		delete player[i];
	}
	
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
	//プレイヤー同士の距離を測る(軸)
	Vector2D a = p1->GetLocation();
	Vector2D b = p2->GetLocation();
	Vector2D ab = a - b;
	//長さを図る
	float length = std::sqrtf(std::powf(ab.x, 2.0f) + std::powf(ab.y, 2.0f));
	
	//正規化する
	n = Vector2D(ab.x / length, ab.y / length);
	
	float hit = length - p1->GetRad() - p2->GetRad();
	
	if (hit<0.0f) {
		//めり込みを外す
		float overlap_length = -1.0f + hit;
		float am = p1->GetMass();
		float bm = p2->GetMass();
		Vector2D edit_location_a = a + n * (overlap_length * -bm / (am + bm));
		Vector2D edit_location_b = b + n * (overlap_length *  am / (am + bm));
		p1->SetLocation(edit_location_a);
		p2->SetLocation(edit_location_b);
		return true;
	}
	return false;
}

float GameMainScene::Dot(Vector2D& a, Vector2D& b)
{
	return a.x * b.x + a.y * b.y;
}

void GameMainScene::CalcRepulsionVector(Player* p1,Player* p2)
{
	//正射影の長さを求める（相手の円に対する当たりの強さ）
	Vector2D amd = p1->GetDirection();
	Vector2D bmd = p2->GetDirection();
	//p1(a)がp2(b)に対する当たりの強さ
	float apower = Dot(amd, n);
	//p2(b)がp1(a)に対する当たりの強さ
	float bpower = Dot(bmd, n);

	//それぞれの垂直ベクトル,水平ベクトルを求める
	Vector2D avx = n * apower;	//の垂直
	Vector2D avy = amd - avx;	//水平

	Vector2D bvx = n * bpower;
	Vector2D bvy = bmd - bvx;

	//反発係数
	float e = 0.8f;
	float am = p1->GetMass();
	float bm = p2->GetMass();

	//反発後の速度を求める
	float as2 = (am * apower + bm * bpower - (e * bm * (apower - bpower))) / (am + bm);
	float bs2 = (am * apower + bm * bpower + (e * am * (apower - bpower))) / (am + bm);

	//速度を直線状のベクトルに変換
	Vector2D avx2 = n * as2;
	Vector2D bvx2 = n * bs2;

	Vector2D av2 = avy + avx2;
	Vector2D bv2 = bvy + bvx2;

	//移動ベクトルに反発する速度ベクトルを足す
	p1->AddMoveDirection(av2);
	p2->AddMoveDirection(bv2);
}


