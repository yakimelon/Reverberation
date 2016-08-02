#include"../header/define.h" 

/*----------------------
 | 確認ダイアログクラス |
  ----------------------*/
/*初期化*/
DialogClass::DialogClass(){
	//メンバ変数初期化
	DrawFlag		= FALSE;
	SelectFlag		= -1;
	Timer			= 0;
	MessageFontSize = CreateFontToHandle( NULL , 36 , -1 , DX_FONTTYPE_ANTIALIASING );

	//描画座標初期化
	SetPoint();

	//メニューパラメータ初期化
	SetMenuParam();
}

/*座標指定*/
void DialogClass::SetPoint(){
	DrawX  = 320;
	DrawY  = 240;
	Width  = 640;
	Height = 240;
}

/*メニューパラメータ初期化*/
void DialogClass::SetMenuParam(){
	MenuParam.DrawX			= DrawX;
	MenuParam.DrawY			= DrawY + Height / 2;
	MenuParam.Interval		= 0;
	MenuParam.Width			= Width / 2;
	MenuParam.Height			= Height / 2;
	MenuParam.ListMin			= 0;
	MenuParam.ListMax			= 2;
	MenuParam.AtherNo			= -1;
	MenuParam.AlphaNo			= 100;
	MenuParam.DrawFlag		= MENU::IMAGE;
	MenuParam.DirectionFlag	= MENU::ROW;

	MenuParam.DrawHandle[0]	= LoadGraph("./resource/graph/Yes.jpg");
	MenuParam.DrawHandle[1]	= LoadGraph("./resource/graph/No.jpg");
}

/*選択番号セット*/
void DialogClass::SetSelectNo(int SelectNo,std::string Message){
	this->SelectNo = SelectNo;
	this->Message  = Message;
	DrawFlag       = TRUE;
	FirstFlag	   = FALSE;
}

/*ダイアログ描画*/
void DialogClass::Draw(UserClass &User){
	enum{DIALOG,ENTER,CANCEL};

	auto *Mouse = MouseClass::GetInstance();
	MenuClass Menu(MenuParam);

	//SE音量セット
	SE.SetVol(User);

	//表示時にSE鳴らす
	if( FirstFlag == FALSE ){
		SE.PlayMusic( DIALOG );
		FirstFlag = TRUE;
	}

	//ダイアログ描画
	DrawBox(DrawX,DrawY,DrawX+Width,DrawY+Height,GetColor(144,144,144),TRUE);
	DrawStringToHandle(DrawX,DrawY,Message.c_str(),GetColor(255,255,255),MessageFontSize);
	Menu.Create();

	//選択フラグ更新
	if( Mouse->GetState(MOUSE::LEFT) == 1 && Timer > 10 ){
		SelectFlag = Menu.GetSelectNo();
		//選択時にSE鳴らす
		if( SelectFlag == 0 ) SE.PlayMusic( ENTER );
		if( SelectFlag == 1 ) SE.PlayMusic( CANCEL );
	}

	//タイマカウント増加
	Timer++;
}

/*描画フラグを取得*/
bool DialogClass::GetDrawFlag(){
	return DrawFlag;
}

/*選択フラグ取得*/
int DialogClass::GetSelectFlag(){
	return SelectFlag;
}

/*選択番号取得*/
int DialogClass::GetSelectNo(){
	return SelectNo;
}

/*ダイアログを消す*/
void DialogClass::Clear(){
	DrawFlag   = FALSE;
	SelectFlag = -1;
	Timer      = 0;
}