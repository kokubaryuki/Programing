#pragma once

#include"SceneBase.h"
#include"../Object/RankingDate.h"

class RankingDispScene:public SceneBase
{
private:

private:
	int background_image;
	RankingData* ranking;


public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};
