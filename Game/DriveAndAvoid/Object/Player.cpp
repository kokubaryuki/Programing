#include"Player.h"
#include"../Utility/InputControl.h"
#include"math.h"
#include "DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),barrier(nullptr)
{

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

	//�ړ�����
	Movement();

	//����������
	Accleretion();


	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}

}

//�`�揈��
void Player::Draw()
{
	//��łȂ���Δz��̐擪��`��
	//if (!v.empty()) {
	//	DrawRotaGraphF(v[0].first.x, v[0].first.y, 1.0, v[0].second, image, TRUE);
	//	//�擪�v�f���폜
	//	v.erase(v.begin());
	//}
	//else {
	//	
	//}
	

	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//�o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
	DrawFormatString(0.0, 0.0, 0xffffff, "radt = %f", radt);
	DrawFormatString(0.0, 12.0, 0xffffff, "x = %f y = %f", direction.x, direction.y);
	DrawFormatString(0.0, 24.0, 0xffffff, "acce = %f", acceleration);
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
	direction = InputControl::GetLeftStick();
	
	//���͖����Ȃ猸��
	if (direction.x == 0.0f && direction.y == 0.0f) 
	{
		acceleration -= ACCELERATION;
		if (acceleration < 0.0f) 
		{
			acceleration = 0.0f;
		}

	}
	//���͗L��Ȃ����
	else 
	{
		acceleration += ACCELERATION;
		if (acceleration >= 12.0f) 
		{
			acceleration = 12.0f;
		}
		//���͒��̂ݎԑ̂̌����𔽉f������B(��atan2�̓��W�A���A180/�΂��|����Ɠx���@�ɕϊ��ł���
		radt = atan2(direction.y, direction.x);/*  (180/ DX_PI_F)*/;
		
		//if (v.empty()) {
		//	//�P�ڂ̗v�f�Ȃ�delay�J�n
		//	start_delay = true;

		//	v.push_back(old_move);
		//}
		//else {
		//	
		//}
		//location += direction;

		//���t���[���x�ꂳ���鏈��
		/*std::pair<Vector2D, float>move_data = { location,angle };
		v.push_back(move_data);*/
	}
	//�����ɉ����x��������
	direction *= acceleration;

	//���W�A����float�L���X�g
	angle = static_cast<float>(radt);

	//���ݒn+�ړ���
	location += direction;
	
	/////////////////////////////////////////////////////

	//�摜�O�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}

}

//�z��ɗv�f������n�߂���delay�X�^�[�g
void Player::DelayDrive(std::vector<std::pair<Vector2D, float>> vec)
{
	//if (start_delay == true) {
	//	delay_count++;

	//}
	//else 
	//{
	//	if (!vec.empty()) {
	//		location = v.begin()->first;
	//		angle = v.begin()->second;
	//		old_move = { location, angle };
	//		v.erase(v.begin());
	//	}
	//	else {

	//	}
	//}
}

//����������
void Player::Accleretion()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}


