#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"cmath"
#include"math.h"
#include"vector"
#include"Effect.h"
#include "utility"//std::pair

#define ACCELERATION		0.1f		//�����x
#define MAXSPEED			5.0f		//�ő�X�s�[�h
#define DRIFT_RATE			0.075f		//�h���t�g���
#define DRIVE_RATE			0.010f		//�h���C�u���
#define SMASH_POWER			300.0f		//�X�}�b�V���p���[
#define DRAWING_INTERVAL	2			//�G�t�F�N�g�`��Ԋu
#define MAX_STAMINA			300.0f		//�X�^�~�i�ő�l(60*7 -> 7�b)

enum class STATE {
	IDLE = 0,		//�A�C�h��
	DRIVE,			//�h���C�u
	DRIFT,			//�h���t�g
	SMASH,			//�X�}�b�V���U��
	DAMAGED,		//�_���[�W��H�����
	GARD,			//�K�[�h���
	OUTOFCONTROLL	//�m�莀
};

class Player
{
private:
	int image;        //�摜�f�[�^
	Vector2D location;//�ʒu���W
	Vector2D box_size;//�����蔻��
	float angle;      //�p�x
	float speed;      //����
	float hp;         //�̗�
	float fuel;       //�R��
	int barrier_count;//�o���A�̖���
	Barrier* barrier; //�o���A
	
	bool smash_available = true;
	int smash_cool_count = 0;

	//float smash_draw_rate = 600.0f - smash_cool_count
	/******************/
	float myrad = 40.0f;					//���a
	int mass = DX_PI * myrad * myrad;	//����(�ʐ�)
	Vector2D move_direction;		//���x�x�N�g��

	STATE player_state;
	double radt;
	Vector2D move_vector;
	
	float acceleration = 0.0f;
	float sqrt_val = 0.0f;
	bool a = false;
	//�p�x�͕�Ԃ��Ă݂� : [0] = Old,  [1] = Now,  [2] = New
	std::pair<Vector2D, float> move_data[3] = { std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
												std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
												std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f) };
	int count = 0;
	int mypad;
	float smash_rate = 0.1;
	//��Ԃ��銄��
	float Interpolation_rate = DRIVE_RATE;
	Vector2D smash_start_point;
	Vector2D smash_target_point;

	Effect* effect[20];
	int drawing_count = 0;
	int drawing_num = 0;
	int stamina = 300;
	float stamina_ratio = (stamina / MAX_STAMINA) * 100.0f;
	bool can_drift = true;
	int driftse;
	Vector2D dspos;
	/******************/
public:
	Player(int pad,float x, float y);
	~Player();
	
	void Initialize(); //����������
	void Update();     //�X�V����
	void Draw();       //�`�揈��
	void Finalize();   //�I������

public:
	void DecreaseHp(float velue);  //�̗͌�������
	Vector2D GetLocation()const;   //�ʒu���W�擾
	float GetRad()const;		   //���a�擾
	Vector2D GetBoxSize()const;    //�����蔻��̑傫���擾
	float GetSpeed() const;        //�����擾����
	float GetFuel()const;          //�R���擾
	float GetHp()const;            //�̗͎擾
	int GetBarriarCount()const;    //�o���A�̖����擾
	bool IsBarrier()const;         //�o���A�͗L�����H���擾
	//void Playerdie() const;        // �v���C���[����
	Vector2D GetDirection()const;
	float GetMass()const;
	void AddMoveDirection(Vector2D add);
	void SetLocation(Vector2D loco);
private:

	void Movement();   //�ړ�����
	void Drift();	   //�h���t�g����
	void Smash();	   //�X�}�b�V���U��

};
	