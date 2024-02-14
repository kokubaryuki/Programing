#include"TileScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読込み
	background_image = LoadGraph("Resource/images/Title2.png");
	menu_image= LoadGraph("Resource/images/Title1.png");
	cursor_image= LoadGraph("Resource/images/cone.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title2.pigがありません\n");
	}

	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}

	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}

}

//更新処理
eSceneType TitleScene::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;

		//一番下に到達したら、一番上にする
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}
	
	//カーソル上移動
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}


	//カーソル決定（決定した画面に移動する)
	if (InputControl::GetButtonDown(0,XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:
			return eSceneType::E_HELP;

		default:
			return eSceneType::E_END;

		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}


//描画処理
void TitleScene::Draw()const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	DrawGraph(120, 200, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 58, 0.7, DX_PI / 2.0, cursor_image, TRUE);

}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene()const
{
	return eSceneType::E_TITLE;
}








