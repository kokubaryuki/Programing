#include"Barrier.h"
#include"DxLib.h"
#include"Player.h"

//float Player::angle;

Barrier::Barrier() : life_span(1000)
{
	//画像の読込み
	image = LoadGraph("Resource/images/barrier.png");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}

}


Barrier::~Barrier()
{
	//読みこんだ画像を削除
	DeleteGraph(image);
}


//描画処理
void Barrier::Draw(const Vector2D& location)
{
	DrawRotaGraphF(location.x, location.y, 1.0, Barrier_angle, image, TRUE);
}

//寿命は尽きたか？
bool Barrier::IsFinished(float speed)
{
		life_span -= speed;
		return(life_span <= 0);
}











