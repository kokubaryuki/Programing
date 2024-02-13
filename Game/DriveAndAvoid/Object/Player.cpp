#include"Player.h"
#include"../Utility/InputControl.h"
#include"math.h"
#include "DxLib.h"

Player::Player(int pad) :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),barrier(nullptr)
{
	mypad = pad;
}

Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 10;
	fuel = 20000;
	barrier_count = 3;

	//画像の読込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//操作不可能状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//燃料の消費
	fuel -= speed;

	if (player_state != STATE::OUTOFCONTROLL) {
		//移動処理
		Movement();
	}
	

	//加減速処理
	Accleretion();


	//バリア処理
	if (InputControl::GetButtonDown(mypad, XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
			player_state = STATE::GARD;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//
		count++;
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
			count = 0;
		}
	}

}

//描画処理
void Player::Draw()
{	

	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
	//DrawFormatString(0.0, 0.0, 0xffffff, "radt = %f", radt);
	DrawFormatString(0.0, 12.0, 0xffffff, " move_data[1].x = %f  move_data[1].y = %f", move_data[1].first.x, move_data[1].first.y);
	//DrawFormatString(0.0, 24.0, 0xffffff, "acce = %f", acceleration);
	DrawFormatString(0, 36.0, 0xffffff, "move_direction.x = %f, y = %f", move_direction.x, move_direction.y);
	DrawFormatString(0, 78.0, 0xffffff, "sqrt_val = %f", sqrt_val);
}


//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}


//バリア枚数取得処理
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}


//バリアは有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	////////////////////////////////////////////////////////

	//move_vector = InputControl::GetLeftStick();
	move_data[1].first = InputControl::GetLeftStick(mypad);

	if (move_data[1].first.x != 0.0f && move_data[1].first.y != 0.0f) {
 		move_data[0] = move_data[1];
	}

	//入力無しなら減速
	if (move_data[1].first.x == 0.0f && move_data[1].first.y == 0.0f)
	{
		if (move_direction != Vector2D(0.0f, 0.0f)) {
			//移動量が0.1より上なら
			if (1.0f < std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f))) {
				//逆ベクトルをとる
				Vector2D Deceleration = move_data[0].first * -1;
				//移動量に加算する
				move_direction += Deceleration * ACCELERATION;
			}
			else {
				move_direction = Vector2D(0.0f, 0.0f);
			}
		}
		

	}
	//入力有りなら加速
	else 
	{

		//float lerp_x = std::lerp(move_data[2].first, move_data)

		//入力中のみ車体の向きを反映させる。(※atan2はラジアン、180/πを掛けると度数法に変換できる
		radt = atan2(move_data[1].first.y, move_data[1].first.x);/*  (180/ DX_PI_F)*/;
		//方向に加速度をかける
		move_direction += move_data[1].first * ACCELERATION;
	}
	sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
	//ラジアンをfloatキャスト
	angle = static_cast<float>(radt);

	//現在地+移動量
	location += move_direction;

	/////////////////////////////////////////////////////

	//画像外に行かないように制限する
	/*if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}*/

}

//加減速処理
void Player::Accleretion()
{
	//LBボタンが押されたら、減速する
	if (InputControl::GetButtonDown(mypad,XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RBボタンが押されたら、加速する
	if (InputControl::GetButtonDown(mypad,XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}


