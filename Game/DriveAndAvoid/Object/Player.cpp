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

//����������
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

	//�摜�̓Ǎ���
	image = LoadGraph("Resource/images/car1pol.bmp");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	//����s�\��Ԃł���΁A���g����]������
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

	//�R���̏���
	fuel -= speed;

	if (player_state != STATE::OUTOFCONTROLL) {
		//�ړ�����
		Movement();
	}
	

	//����������
	Accleretion();


	//�o���A����
	if (InputControl::GetButtonDown(mypad, XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
			player_state = STATE::GARD;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//
		count++;
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
			count = 0;
		}
	}

}

//�`�揈��
void Player::Draw()
{	

	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//�o���A����������Ă�����A�`����s��
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


//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation()const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed()const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}


//�o���A�����擾����
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}


//�o���A�͗L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	////////////////////////////////////////////////////////

	//move_vector = InputControl::GetLeftStick();
	move_data[1].first = InputControl::GetLeftStick(mypad);

	if (move_data[1].first.x != 0.0f && move_data[1].first.y != 0.0f) {
 		move_data[0] = move_data[1];
	}

	//���͖����Ȃ猸��
	if (move_data[1].first.x == 0.0f && move_data[1].first.y == 0.0f)
	{
		if (move_direction != Vector2D(0.0f, 0.0f)) {
			//�ړ��ʂ�0.1����Ȃ�
			if (1.0f < std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f))) {
				//�t�x�N�g�����Ƃ�
				Vector2D Deceleration = move_data[0].first * -1;
				//�ړ��ʂɉ��Z����
				move_direction += Deceleration * ACCELERATION;
			}
			else {
				move_direction = Vector2D(0.0f, 0.0f);
			}
		}
		

	}
	//���͗L��Ȃ����
	else 
	{

		//float lerp_x = std::lerp(move_data[2].first, move_data)

		//���͒��̂ݎԑ̂̌����𔽉f������B(��atan2�̓��W�A���A180/�΂��|����Ɠx���@�ɕϊ��ł���
		radt = atan2(move_data[1].first.y, move_data[1].first.x);/*  (180/ DX_PI_F)*/;
		//�����ɉ����x��������
		move_direction += move_data[1].first * ACCELERATION;
	}
	sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
	//���W�A����float�L���X�g
	angle = static_cast<float>(radt);

	//���ݒn+�ړ���
	location += move_direction;

	/////////////////////////////////////////////////////

	//�摜�O�ɍs���Ȃ��悤�ɐ�������
	/*if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}*/

}

//����������
void Player::Accleretion()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(mypad,XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(mypad,XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}


