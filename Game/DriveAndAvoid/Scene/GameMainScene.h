#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"

class GameMainScene : public SceneBase
{
private:
	int high_score;
	int back_ground;
	int barrier_image;
	int mileage;
	int enemy_image[3];
	int enemy_count[3];
	Player* player[4] = {};
	Enemy** enemy;

	int combination2[1][2] = { { 0,1 } };
	int combination3[3][2] = { { 0,1 }, { 0,2 }, { 1,2 } };
	int combination4[6][2] = { { 0,1 }, { 0,2 }, { 0,3 }, { 1,2 }, { 1,3 }, { 2,3 } };

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
	bool IsHitCheck(Player* p, Enemy* e);

};


