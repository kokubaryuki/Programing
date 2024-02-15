#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"cmath"
#include"math.h"
#include"vector"
#include"Effect.h"
#include "utility"//std::pair

#define ACCELERATION		0.1f		//加速度
#define MAXSPEED			5.0f		//最大スピード
#define DRIFT_RATE			0.075f		//ドリフト状態
#define DRIVE_RATE			0.010f		//ドライブ状態
#define SMASH_POWER			300.0f		//スマッシュパワー
#define DRAWING_INTERVAL	2			//エフェクト描画間隔
#define MAX_STAMINA			300.0f		//スタミナ最大値(60*7 -> 7秒)

enum class STATE {
	IDLE = 0,		//アイドル
	DRIVE,			//ドライブ
	DRIFT,			//ドリフト
	SMASH,			//スマッシュ攻撃
	DAMAGED,		//ダメージを食らった
	GARD,			//ガード状態
	OUTOFCONTROLL	//確定死
};

class Player
{
private:
	int image;        //画像データ
	Vector2D location;//位置座標
	Vector2D box_size;//当たり判定
	float angle;      //角度
	float speed;      //速さ
	float hp;         //体力
	float fuel;       //燃料
	int barrier_count;//バリアの枚数
	Barrier* barrier; //バリア
	
	bool smash_available = true;
	int smash_cool_count = 0;

	//float smash_draw_rate = 600.0f - smash_cool_count
	/******************/
	float myrad = 40.0f;					//半径
	int mass = DX_PI * myrad * myrad;	//質量(面積)
	Vector2D move_direction;		//速度ベクトル

	STATE player_state;
	double radt;
	Vector2D move_vector;
	
	float acceleration = 0.0f;
	float sqrt_val = 0.0f;
	bool a = false;
	//角度は補間してみる : [0] = Old,  [1] = Now,  [2] = New
	std::pair<Vector2D, float> move_data[3] = { std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
												std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
												std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f) };
	int count = 0;
	int mypad;
	float smash_rate = 0.1;
	//補間する割合
	float Interpolation_rate = DRIVE_RATE;
	Vector2D smash_start_point;
	Vector2D smash_target_point;

	Effect* effect[20];
	int drawing_count = 0;
	int drawing_num = 0;
	int stamina = 300;
	float stamina_ratio = (stamina / MAX_STAMINA) * 100.0f;
	bool can_drift = true;
	int driftse;
	Vector2D dspos;
	/******************/
public:
	Player(int pad,float x, float y);
	~Player();
	
	void Initialize(); //初期化処理
	void Update();     //更新処理
	void Draw();       //描画処理
	void Finalize();   //終了処理

public:
	void DecreaseHp(float velue);  //体力減少処理
	Vector2D GetLocation()const;   //位置座標取得
	float GetRad()const;		   //半径取得
	Vector2D GetBoxSize()const;    //当たり判定の大きさ取得
	float GetSpeed() const;        //速さ取得処理
	float GetFuel()const;          //燃料取得
	float GetHp()const;            //体力取得
	int GetBarriarCount()const;    //バリアの枚数取得
	bool IsBarrier()const;         //バリアは有効か？を取得
	//void Playerdie() const;        // プレイヤー死ぬ
	Vector2D GetDirection()const;
	float GetMass()const;
	void AddMoveDirection(Vector2D add);
	void SetLocation(Vector2D loco);
private:

	void Movement();   //移動処理
	void Drift();	   //ドリフト処理
	void Smash();	   //スマッシュ攻撃

};
	