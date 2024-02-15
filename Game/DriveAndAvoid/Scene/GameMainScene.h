#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"

enum class Mphase
{
	READY = 0,
	GO,
	FINISH
};

class GameMainScene : public SceneBase
{
private:
	int high_score;
	int back_ground;
	int barrier_image;
	int mileage;
	int enemy_image[3];
	int enemy_count[3];
	int SHandle;
	Player* player[4];
	int UI;

	/// //////////////////////////////////////////////////
	int Number_of_connections;
	int combination3[3][2] = { {0,1}, {0,2}, {1,2} };
	int combination4[6][2] = { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} };
	int tmp = 4;
	Mphase phase = Mphase::READY;
	int readycount = 0;
	int readysound = 0;
	Vector2D n;
	/////////////////////////////////////////////////////
public:
	GameMainScene();
	virtual~ GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;

	virtual eSceneType GetNowScene()const override;

private:
	//ハイスコア読込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p1, Player* p2);
	float Dot(Vector2D& a, Vector2D& b);
	void CalcRepulsionVector(Player* p1, Player* p2);
	
};


