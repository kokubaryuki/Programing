#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"cmath"
#include"math.h"
#include "utility"//std::pair

#define ACCELERATION 0.08f
#define MAXSPEED	 5.0f

enum class STATE {
	IDLE,			//�A�C�h��
	DRIFT,			//�h���t�g
	DAMAGED,		//
	OUTOFCONTROLL
};

class Player
{
private:

	bool is_active;   //�L����Ԃ��H
	int image;        //�摜�f�[�^
	Vector2D location;//�ʒu���W
	Vector2D box_size;//�����蔻��
	float angle;      //�p�x
	float speed;      //����
	float hp;         //�̗�
	float fuel;       //�R��
	int barrier_count;//�o���A�̖���
	Barrier* barrier; //�o���A
	
	/******************/
	double radt;
	Vector2D move_vector;
	Vector2D move_direction;
	float acceleration = 0.0f;
	//�p�x�͕⊮���Ă݂� : [0] = Old,  [1] = Now,  [2] = New
	std::pair<Vector2D, float> move_data[3] = { std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
									       std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f),
										   std::pair<Vector2D,float>(Vector2D(0.0f,0.0f),0.0f) };
	int pad;
	/******************/
public:
	Player(int input_type);
	~Player();
	
	void Initialize(); //����������
	void Update();     //�X�V����
	void Draw();       //�`�揈��
	void Finalize();   //�I������

public:

	void SetActive(bool flg);      //�L���t���O�ݒ�
	void DecreaseHp(float velue);  //�̗͌�������
	Vector2D GetLocation()const;   //�ʒu���W�擾
	Vector2D GetBoxSize()const;    //�����蔻��̑傫���擾
	float GetSpeed() const;        //�����擾����
	float GetFuel()const;          //�R���擾
	float GetHp()const;            //�̗͎擾
	int GetBarriarCount()const;    //�o���A�̖����擾
	bool IsBarrier()const;         //�o���A�͗L�����H���擾
	void Playerdie() const;        // �v���C���[����

private:

	void Movement();   //�ړ�����
	void Accleretion();//��������

};
	