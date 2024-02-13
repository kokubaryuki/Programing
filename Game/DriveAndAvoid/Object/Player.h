#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"cmath"
#include"math.h"
#include "utility"//std::pair

#define ACCELERATION 0.08f
#define MAXSPEED	 5.0f

enum class STATE {
	IDLE,			//アイドル
	DRIFT,			//ドリフト
	DAMAGED,		//
	OUTOFCONTROLL
};

class Player
{
private:

	bool is_active;   //有効状態か？
	int image;        //画像データ
	Vector2D location;//位置座標
	Vector2D box_size;//当たり判定
	float angle;      //角度
	float speed;      //速さ
	float hp;         //体力
	float fuel;       //燃料
	int barrier_count;//バリアの枚数
	Barrier* barrier; //バリア
	
	/******************/
	double radt;
	Vector2D move_vector;
	Vector2D move_direction;
	float acceleration = 0.0f;
	//角度は補完してみる : [0] = Old,  [1] = Now,  [2] = New
	std::pair<Vector2D, float> move_data[3] = { std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
									       std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
										   std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f) };
	int pad;
	/******************/
public:
	Player(int input_type);
	~Player();
	
	void Initialize(); //初期化処理
	void Update();     //更新処理
	void Draw();       //描画処理
	void Finalize();   //終了処理

public:

	void SetActive(bool flg);      //有効フラグ設定
	void DecreaseHp(float velue);  //体力減少処理
	Vector2D GetLocation()const;   //位置座標取得
	Vector2D GetBoxSize()const;    //当たり判定の大きさ取得
	float GetSpeed() const;        //速さ取得処理
	float GetFuel()const;          //燃料取得
	float GetHp()const;            //体力取得
	int GetBarriarCount()const;    //バリアの枚数取得
	bool IsBarrier()const;         //バリアは有効か？を取得
	void Playerdie() const;        // プレイヤー死ぬ

private:

	void Movement();   //移動処理
	void Accleretion();//加速処理

};
	