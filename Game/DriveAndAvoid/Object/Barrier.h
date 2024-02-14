#pragma once

#include"../Utility/Vector2D.h"



class Barrier
{
private:
	int image;      //バリア画像
	float life_span;//バリアの寿命
	double Barrier_angle = 0.0;

public:

	Barrier();
	~Barrier();
	
	void Draw(const Vector2D& location);  //描画処理
	bool IsFinished(float speed);         //寿命が尽きたか？
	
	void Set_Angle(double a) {
		Barrier_angle = a;
	}
};
