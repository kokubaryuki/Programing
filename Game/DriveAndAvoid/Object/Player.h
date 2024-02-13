#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"vector"
#include "utility"//std::pair

#define ACCELERATION 0.3f
#define DELAY_FLAME	 30

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
	int barrier_Time; //バリアの時間
	
	/******************/
	double radt;
	Vector2D direction;
	float acceleration = 0.0f;
	
	//??フレーム遅れて動く
	std::vector<std::pair<Vector2D, float>> v;
	std::pair<Vector2D, float> old_move = { Vector2D(0.0f,0.0f),0.0f };
	
	//ディレイカウント
	int delay_count = 0;
	//カウント後描画開始
	bool start_delay = false;

	
	/******************/
public:
	Player();
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
	int GetbarrierTime()const;     //バリアの時間取得
	
private:

	void Movement();   //移動処理
	void DelayDrive(std::vector<std::pair<Vector2D, float>> vec); //
	void Accleretion();//加速処理

};
	