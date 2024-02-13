#include"Effect.h"

Effect::Effect(int locoX, int locoY, float exrate, float angle, int image)
{
    my_x = locoX;
    my_y = locoY;
    my_exrate = exrate;
    my_angle = angle;
    my_image = LoadGraph("Resource/images/car1pol.bmp");
    TranceRate = HARF_RATE;
    finish = false;
}

Effect::~Effect()
{
    //読みこんだ画像を削除
    DeleteGraph(my_image);
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
    
    DrawRotaGraph(my_x, my_y, my_exrate, my_angle, my_image, TRUE);
    
    //設定を元に戻す。
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
          
}

bool Effect::IsFinished() const
{
    return finish;
}

