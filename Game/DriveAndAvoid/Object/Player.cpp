#include"Player.h"
#include"../Utility/InputControl.h"
#include"cmath"
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
	/*if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}*/

	//燃料の消費
	//fuel -= speed;

	//吹っ飛ばされ状態じゃなければ、スマッシュ可能
	if (player_state != STATE::OUTOFCONTROLL) {
		Smash();
	}

	//スマッシュ攻撃状態じゃなければ、ドリフト可能
	if (player_state != STATE::SMASH) {
		Drift();
	}

	//移動処理はスマッシュ攻撃と吹っ飛ばされ状態以外なら
	if (player_state != STATE::SMASH && player_state != STATE::OUTOFCONTROLL) 
	{
		Movement();
	}
	
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
	DrawFormatString(700, 12, 0xffffff, " move_data[1].x = %f", move_data[1].first.x);
	DrawFormatString(700, 36, 0xffffff, " move_data[1].y = %f", move_data[1].first.y);
	//DrawFormatString(700, 36, 0xffffff, "move_direction.x = %f, y = %f", move_direction.x, move_direction.y);
	//DrawFormatString(700, 78, 0xffffff, "sqrt_val = %f", sqrt_val);
	if (Interpolation_rate == DRIFT_RATE) {
		DrawFormatString(700, 90, 0xffffff, "DRIFT!!!!");
	}
	else 
	{
		DrawFormatString(700, 90, 0xffffff, "DRIVE");
	}
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
	move_data[2].first = InputControl::GetLeftStick(mypad);

	//入力無しなら減速
	if (move_data[2].first.x == 0.0f && move_data[2].first.y == 0.0f)
	{
		//移動ベクトルの長さ(速さ)を測る
		float length = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
		if (length != 0.0f)
		{
			//長さ(速さ)が0.1より上なら
			if (ACCELERATION < length)
			{
				//現在の移動ベクトルを正規化
				Vector2D NormalVector = Vector2D(move_direction.x / length, move_direction.y / length);
				//逆ベクトルをとる
				Vector2D Deceleration = NormalVector * -1;
				//移動量に加算する
				move_direction += Deceleration * ACCELERATION;
			}
			else 
			{
				move_direction = Vector2D(0.0f, 0.0f);
				//完全に止まったらアイドル
				player_state = STATE::IDLE;
			}
		}
	}
	//入力有りなら加速
	else 
	{
		//現在のベクトルと新しいベクトルのx成分とy成分を線形補間して少しずつベクトルを変える
		float lerp_x = std::lerp(move_data[1].first.x, move_data[2].first.x, Interpolation_rate);
		float lerp_y = std::lerp(move_data[1].first.y, move_data[2].first.y, Interpolation_rate);
		move_data[1].first = Vector2D(lerp_x, lerp_y);

		//入力中のみ車体の向きを反映させる。(※atan2はラジアン、180/πを掛けると度数法に変換できる
		move_data[1].second = atan2(move_data[1].first.y, move_data[1].first.x);/*  (180/ DX_PI_F)*/;

		//方向に加速度をかける
		move_direction += move_data[1].first * ACCELERATION;
		sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
		if (MAXSPEED < sqrt_val) 
		{
			move_direction = move_data[1].first * MAXSPEED;
		}
	}

	sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
	angle = move_data[1].second;
	//現在地+移動量
	location += move_direction;
}

//加減速処理
void Player::Drift()
{
	//RBボタンが押されたら、加速する
	if (InputControl::GetButton(mypad,XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		Interpolation_rate = DRIFT_RATE;
		player_state = STATE::DRIFT;
	}
	else 
	{
		Interpolation_rate = DRIVE_RATE;
		player_state = STATE::DRIVE;
	}
}

void Player::Smash()
{
	//Aボタンでスマッシュ攻撃＆スマッシュ攻撃状態に遷移
	if (InputControl::GetButtonDown(mypad, XINPUT_BUTTON_A)) 
	{
		player_state = STATE::SMASH;
		//補間レートを初期化
		smash_rate = 0.0f;
		//
		smash_start_point = location;
		Vector2D fowerd_vector = Vector2D(std::cosf(move_data[1].second), std::sinf(move_data[1].second));
		//スタート位置から車体の前ベクトル向けに×100したポイントを取得
		smash_target_point = smash_start_point + fowerd_vector * SMASH_POWER;
	}

	if (player_state == STATE::SMASH) {
		//補間レートを10%ずつ増やす
		smash_rate += 0.1f;

		//スタート位置からターゲット位置までの線形補間した値を取得＆locationにセット
		float lerp_posx = std::lerp(smash_start_point.x, smash_target_point.x, smash_rate);
		float lerp_posy = std::lerp(smash_start_point.y, smash_target_point.y, smash_rate);
		location = Vector2D(lerp_posx, lerp_posy);

		//ターゲットポイントまで100%到達したら
		if (1.0f <= smash_rate) {
			smash_rate = 0.0f;
			if (InputControl::GetButton(mypad, XINPUT_BUTTON_RIGHT_SHOULDER)) {
				player_state = STATE::DRIFT;
			}
			else {
				player_state = STATE::DRIVE;
			}			
		}
	}
}


