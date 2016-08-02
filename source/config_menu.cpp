#include"../header/define.h" 

/*--------------------------
 | コンフィグメニュークラス |
  --------------------------*/
/*初期化*/
ConfigMenuClass::ConfigMenuClass(ConfigArg_rec ConfigArg){
	//メンバ変数初期化
	this->Title  = ConfigArg.Title;
	this->DrawX  = ConfigArg.DrawX;
	this->DrawY  = ConfigArg.DrawY;
	this->Width  = ConfigArg.Width;
	this->Height = ConfigArg.Height;
	this->ListNo = ConfigArg.ListNo;
	this->SetNo  = ConfigArg.SetNo;

	//コンフィグメニューパラメータセット
	SetMenuParam();
}

/*コンフィグメニューパラメータセット*/
void ConfigMenuClass::SetMenuParam(){
	int Interval;	//項目と項目の間
	int FontSize;	//フォントの大きさ

	FontSize = Height / 4;
	Interval = (Width - FontSize / 2 * ListNo ) / ( ListNo + 1 ) ;

	MenuArg.DrawX			= DrawX + Interval;
	MenuArg.DrawY			= DrawY + Height / 2;
	MenuArg.Interval		= Interval;
	MenuArg.Width			= FontSize;
	MenuArg.Height			= FontSize;
	MenuArg.ListMin			= 0;
	MenuArg.ListMax			= ListNo;
	MenuArg.AtherNo			= ListNo;
	MenuArg.AlphaNo			= 100;
	MenuArg.DrawFlag		= MENU::TEXT;
	MenuArg.DirectionFlag	= MENU::ROW;
	
	for( int i=0 ; i<ListNo ; i++ ){
		sprintf(MenuArg.DrawText[i],"%d",i+1);
	}

	//if( ListNo == 2 ){
	//	strcpy(MenuArg.DrawText[0],"Yes");
	//	strcpy(MenuArg.DrawText[1],"No");
	//}

	MenuArg.TextColor  = GetColor(255,255,255);
	MenuArg.FontFamily = MENU::GOSIC;

}

/*選択番号を取得*/
int ConfigMenuClass::GetSelectNo(){
	return SelectNo;
}

/*メニュー描画*/
void ConfigMenuClass::Draw(){
	//変数宣言
	ConfigListClass Menu(SetNo,MenuArg);

	int TitleWidth;	//タイトルの横幅
	int Interval;	//タイトル文字の左右の幅

	
	//フォントサイズ指定
	const int FontSize = Height / 4;


	//フォントサイズ変えろ
	//SetFontSize(FontSize);


	//タイトル文字の左右の幅を取得
	TitleWidth = Title.length() * FontSize / 2;
	Interval   = ( Width - TitleWidth ) / 2;

	//コンフィグメニュー描画
	DrawStringToHandle(DrawX+Interval,DrawY,Title.c_str(),GetColor(255,255,255),MenuFontHandle);
	Menu.Create();

	//選択番号を取得
	SelectNo = Menu.GetSelectNo();



}
