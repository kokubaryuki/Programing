#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"iostream"
#include"vector"
#include "utility"//std::pair

#define ACCELERATION 0.3f
#define DELAY_FLAME	 30

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
	int barrier_Time; //�o���A�̎���
	
	/******************/
	double radt;
	Vector2D direction;
	float acceleration = 0.0f;
	
	//??�t���[���x��ē���
	std::vector<std::pair<Vector2D, float>> v;
	std::pair<Vector2D, float> old_move = { Vector2D(0.0f,0.0f),0.0f };
	
	//�f�B���C�J�E���g
	int delay_count = 0;
	//�J�E���g��`��J�n
	bool start_delay = false;

	
	/******************/
public:
	Player();
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
	int GetbarrierTime()const;     //�o���A�̎��Ԏ擾
	
private:

	void Movement();   //�ړ�����
	void DelayDrive(std::vector<std::pair<Vector2D, float>> vec); //
	void Accleretion();//��������

};
	