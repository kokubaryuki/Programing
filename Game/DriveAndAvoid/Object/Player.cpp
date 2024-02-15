#include"Player.h"
#include"../Utility/InputControl.h"
#include"cmath"
#include "DxLib.h"

Player::Player(int pad,float x,float y) :image(NULL), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),barrier(nullptr)
{
	mypad = pad;
	location.x = x;
	location.y = y;
}

Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 10;
	fuel = 20000;
	barrier_count = 3;

	switch (mypad)
	{
		case 0:
			dspos = Vector2D(50, 50);
			break;
		case 1:
			dspos = Vector2D(1100, 50);
			break;
		case 2:
			dspos = Vector2D(50, 670);
			break;
		case 3:
			dspos = Vector2D(1100, 670);
			break;
		default:
			break;
	}

	//画像の読込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
	for (int i = 0; i < 20; i++) {
		effect[i] = nullptr;
	}
	driftse = LoadSoundMem("Resource/SE/drift.wav");
}

//更新処理
void Player::Update()
{

	//吹っ飛ばされ状態じゃなければ、スマッシュ可能
	if (player_state != STATE::OUTOFCONTROLL) {
		Smash();
	}
	if (smash_available == false)
	{
		smash_cool_count++;
		if (smash_cool_count >= 420) {
			smash_available = true;
			smash_cool_count = 0;
		}
	}

	//スマッシュ攻撃状態じゃなければ、ドリフト可能
	if (player_state != STATE::SMASH && 0 < stamina) 
	{
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
		count++;
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
			count = 0;
		}
	}


	//残像を表示(エフェクト描画)
	if (player_state == STATE::DRIFT || player_state == STATE::SMASH)
	{
		if (drawing_count % DRAWING_INTERVAL == 0)
		{
			if (effect[drawing_num] == nullptr) {
				effect[drawing_num] = new Effect(location.x, location.y, 1.0f, angle, image);
				drawing_num++;
				if (19 < drawing_num) {
					drawing_num = 0;
				}
			}
		}
		drawing_count++;
	}
	//ドリフト状態じゃなければ
	else
	{
		//生成中の残像を削除
		if (drawing_count != 0)
		{
			drawing_count = 0;
		}
	}
	//エフェクトが生成されていたら、更新を行う
	for (int i = 0; i < 20; i++)
	{
		if (effect[i] != nullptr)
		{
			effect[i]->Update();
			if (effect[i]->IsFinished()) {
				delete effect[i]; // Effect インスタンスを削除する
				effect[i] = nullptr;
			}
		}
	}
	if (player_state == STATE::DRIFT) {
		if (!CheckSoundMem(driftse)) {
			PlaySoundMem(driftse, DX_PLAYTYPE_BACK);
		}
		stamina--;
		if (stamina <= 0) 
		{
			stamina = 0;
			can_drift = false;
		}
	}
	else 
	{
		StopSoundMem(driftse);
		stamina++;
		if (MAX_STAMINA <= stamina)
		{
			stamina = MAX_STAMINA;
			can_drift = true;
		}
	}
	stamina_ratio = (stamina / MAX_STAMINA) * 100.0f;
}

//描画処理
void Player::Draw()
{
	for (int i = 0; i < 20; i++) {
		if (effect[i] != nullptr) {
			effect[i]->Draw();
		}
	}
	//スタミナバー(仮)
	if (can_drift == true) {
		DrawBox(dspos.x - 3, dspos.y - 3, dspos.x + 100 + 3, dspos.y + 50 + 3, 0xffffff, false);
		DrawBox(dspos.x, dspos.y, dspos.x + stamina_ratio, dspos.y + 50, 0xff0000, true);
	}
	else {
		DrawBox(dspos.x - 3, dspos.y - 3, dspos.x + 100 + 3, dspos.y + 50 + 3, 0xffffff, false);
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawBox(dspos.x, dspos.y, dspos.x + stamina_ratio, dspos.y + 50, 0xff0000, true);
		//設定を元に戻す。
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (smash_available) {
		DrawCircle(dspos.x - 3, dspos.y - 3 - 10, 15, 0xffffff, FALSE,2);
		DrawCircle(dspos.x - 3, dspos.y - 3 - 10, 14, 0x1000ff, TRUE);
	}
	else {
		DrawCircle(dspos.x - 3, dspos.y - 3 - 10, 15, 0xffffff, FALSE, 2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawCircle(dspos.x - 3, dspos.y - 3 - 10, 14, 0x1000ff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
	DrawCircle(location.x, location.y, myrad, 0xffffff, false,3);
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

float Player::GetRad() const
{
	return myrad;
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
	//RBボタンが押されている間、加速する
	if (InputControl::GetButton(mypad,XINPUT_BUTTON_RIGHT_SHOULDER) && can_drift == true)
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
	if (InputControl::GetButtonDown(mypad, XINPUT_BUTTON_A) && smash_available == true)
	{
		player_state = STATE::SMASH;
		smash_available = false;
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
		
		//移動する前に速度ベクトルを出す
		//Vector2D old_md = move_direction;
		move_direction = Vector2D(lerp_posx, lerp_posy) - location;
		move_direction = move_direction / 8.0f;
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

Vector2D Player::GetDirection() const
{
	return move_direction;
}

float Player::GetMass() const
{
	return mass;
}

void Player::AddMoveDirection(Vector2D add)
{
	move_direction = add;
}

void Player::SetLocation(Vector2D loco)
{
	location = loco;
}


