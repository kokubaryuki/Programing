#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"

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
	

	/// //////////////////////////////////////////////////
	Vector2D Setlocation[3][4] = { { {275,380},{1000,380},{0,0}     ,{0,0}      },
								   { {637,50} ,{275,670} ,{1000,670},{0,0}      },
								   { {275,50} ,{1000,50} ,{275,670} ,{1000,670} } };
	int Number_of_connections = 0;
	int combination3[3][2] = { {0,1}, {0,2}, {1,2} };
	int combination4[6][2] = { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} };
	int tmp = 4;
	Mphase phase = Mphase::READY;
	int readycount = 0;
	int readysound = 0;
	Vector2D n;
	int DownCount = 0;
	int back_image;
	int readyimage[4];
	int rinum = 0;
	int deathse;
	int winner;
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
	//‰~‚Æ‰~‚Ì“–‚½‚è”»’è
	bool IsHitCheck(Player* p1, Player* p2);
	//“àÏ
	float Dot(Vector2D& a, Vector2D& b);
	//”½”­ƒxƒNƒgƒ‹‚ğZo
	void CalcRepulsionVector(Player* p1, Player* p2);
	
};


