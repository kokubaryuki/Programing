#pragma once

#include "SceneBase.h"

enum class PHASE 
{
	OPENING,
	MENU,
	ENDING
};

class TitleScene:public SceneBase
{
private:

	int background_image;//�w�i�摜
	int menu_image;      //���j���[�摜
	int cursor_image;    //�J�[�\���摜
	int menu_cursor;     //���j���[�J�[�\���ԍ�
	int TitleBGM;        //�^�C�g����BGM�p�ϐ�]
	int SHandle;
	int openingse;
	int selectSe;
	int decideSe;
	int anim_x = 0;
	int name;
	int menu_start;
	int menu_help;
	int menu_end;
	int TranceRate = 0;
	int count = 0;
	int jumppower = 25;


	//////////////////////////
	PHASE phase = PHASE::OPENING;
public:
	TitleScene();
	virtual~TitleScene();;

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};

