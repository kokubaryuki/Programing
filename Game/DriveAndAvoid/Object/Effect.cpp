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
    //�ǂ݂��񂾉摜���폜
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
    //���߂��ĕ`��
    
    DrawRotaGraph(my_x, my_y, my_exrate, my_angle, my_image, TRUE);
    
    //�ݒ�����ɖ߂��B
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
          
}

bool Effect::IsFinished() const
{
    return finish;
}

