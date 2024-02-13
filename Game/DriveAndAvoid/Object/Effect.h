#pragma once
#include "DxLib.h"

#define HARF_RATE	200

class Effect 
{
private:
	int my_x;
	int my_y;
	float my_exrate;
	float my_angle;
	float my_image;
	int TranceRate;

	bool finish;
public:
	Effect(int locoX,int locoY,float exrate,float angle, int image);
	~Effect();

	void Update();     //XVˆ—
	void Draw();       //•`‰æˆ—
	bool IsFinished() const;
};
