#pragma once

#include"SceneBase.h"

class EndScene :public SceneBase
{
private:

	int back_ground;    //”wŒi‰æ‘œ
	int y;              //yŽ²
	//int Timestop = 0;   //ŽžŠÔ’âŽ~

public:
	EndScene();
	virtual~EndScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize()override;

	virtual eSceneType GetNowScene() const override;

};

