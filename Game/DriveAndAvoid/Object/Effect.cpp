#include"Effect.h"

Effect::Effect(int locoX, int locoY, float exrate, float angle, int imagenum)
{
    my_x = locoX;
    my_y = locoY;
    my_exrate = exrate;
    my_angle = angle;
    num = imagenum;
    carimage[0] = LoadGraph("Resource/images/car1.png");
    carimage[1] = LoadGraph("Resource/images/car2.png");
    carimage[2] = LoadGraph("Resource/images/car3.png");
    carimage[3] = LoadGraph("Resource/images/car4.png");
    TranceRate = HARF_RATE;
    finish = false;
}

Effect::~Effect()
{
    //読みこんだ画像を削除
    for (int i = 0; i < 4; i++) {
        DeleteGraph(carimage[i]);
    }
}

void Effect::Update()
{
    TranceRate -= 5;
    if (TranceRate <= 0) {
        finish = true;
    }
}

void Effect::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, TranceRate);
    //透過して描画
    
    DrawRotaGraph(my_x, my_y, my_exrate, my_angle, carimage[num], TRUE);
    
    //設定を元に戻す。
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
          
}

bool Effect::IsFinished() const
{
    return finish;
}

