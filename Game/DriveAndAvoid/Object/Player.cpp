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

	//�R���̏���
	//fuel -= speed;

	//������΂����Ԃ���Ȃ���΁A�X�}�b�V���\
	if (player_state != STATE::OUTOFCONTROLL) {
		Smash();
	}

	//�X�}�b�V���U����Ԃ���Ȃ���΁A�h���t�g�\
	if (player_state != STATE::SMASH) {
		Drift();
	}

	//�ړ������̓X�}�b�V���U���Ɛ�����΂����ԈȊO�Ȃ�
	if (player_state != STATE::SMASH && player_state != STATE::OUTOFCONTROLL) 
	{
		Movement();
	}
	
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
	move_data[2].first = InputControl::GetLeftStick(mypad);

	//���͖����Ȃ猸��
	if (move_data[2].first.x == 0.0f && move_data[2].first.y == 0.0f)
	{
		//�ړ��x�N�g���̒���(����)�𑪂�
		float length = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
		if (length != 0.0f)
		{
			//����(����)��0.1����Ȃ�
			if (ACCELERATION < length)
			{
				//���݂̈ړ��x�N�g���𐳋K��
				Vector2D NormalVector = Vector2D(move_direction.x / length, move_direction.y / length);
				//�t�x�N�g�����Ƃ�
				Vector2D Deceleration = NormalVector * -1;
				//�ړ��ʂɉ��Z����
				move_direction += Deceleration * ACCELERATION;
			}
			else 
			{
				move_direction = Vector2D(0.0f, 0.0f);
				//���S�Ɏ~�܂�����A�C�h��
				player_state = STATE::IDLE;
			}
		}
	}
	//���͗L��Ȃ����
	else 
	{
		//���݂̃x�N�g���ƐV�����x�N�g����x������y��������`��Ԃ��ď������x�N�g����ς���
		float lerp_x = std::lerp(move_data[1].first.x, move_data[2].first.x, Interpolation_rate);
		float lerp_y = std::lerp(move_data[1].first.y, move_data[2].first.y, Interpolation_rate);
		move_data[1].first = Vector2D(lerp_x, lerp_y);

		//���͒��̂ݎԑ̂̌����𔽉f������B(��atan2�̓��W�A���A180/�΂��|����Ɠx���@�ɕϊ��ł���
		move_data[1].second = atan2(move_data[1].first.y, move_data[1].first.x);/*  (180/ DX_PI_F)*/;

		//�����ɉ����x��������
		move_direction += move_data[1].first * ACCELERATION;
		sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
		if (MAXSPEED < sqrt_val) 
		{
			move_direction = move_data[1].first * MAXSPEED;
		}
	}

	sqrt_val = std::sqrtf(std::powf(move_direction.x, 2.0f) + std::powf(move_direction.y, 2.0f));
	angle = move_data[1].second;
	//���ݒn+�ړ���
	location += move_direction;
}

//����������
void Player::Drift()
{
	//RB�{�^���������ꂽ��A��������
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
	//A�{�^���ŃX�}�b�V���U�����X�}�b�V���U����ԂɑJ��
	if (InputControl::GetButtonDown(mypad, XINPUT_BUTTON_A)) 
	{
		player_state = STATE::SMASH;
		//��ԃ��[�g��������
		smash_rate = 0.0f;
		//
		smash_start_point = location;
		Vector2D fowerd_vector = Vector2D(std::cosf(move_data[1].second), std::sinf(move_data[1].second));
		//�X�^�[�g�ʒu����ԑ̂̑O�x�N�g�������Ɂ~100�����|�C���g���擾
		smash_target_point = smash_start_point + fowerd_vector * SMASH_POWER;
	}

	if (player_state == STATE::SMASH) {
		//��ԃ��[�g��10%�����₷
		smash_rate += 0.1f;

		//�X�^�[�g�ʒu����^�[�Q�b�g�ʒu�܂ł̐��`��Ԃ����l���擾��location�ɃZ�b�g
		float lerp_posx = std::lerp(smash_start_point.x, smash_target_point.x, smash_rate);
		float lerp_posy = std::lerp(smash_start_point.y, smash_target_point.y, smash_rate);
		location = Vector2D(lerp_posx, lerp_posy);

		//�^�[�Q�b�g�|�C���g�܂�100%���B������
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


