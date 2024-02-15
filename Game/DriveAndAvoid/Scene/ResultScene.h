#pragma once

#include"SceneBase.h"
enum class PHASE {
	ANNOUNCEMENT,
	FREE,
	FINISH
};
class ResultScene:public SceneBase
{
private:
	int back_ground;    //�w�i�摜
	int score;          //�X�R�A
	int enemy_count[3]; //�G�̃J�E���g
	int enemy_image[3]; //�G�摜
	int resultimage[4];
	int winnerimage;
	PHASE phase = PHASE::ANNOUNCEMENT;
	int count = 0;
public:
	ResultScene();
	virtual~ResultScene();


	virtual void Initialize()override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;

	virtual eSceneType GetNowScene()const override;

private:
	void ReadResultData();
};

