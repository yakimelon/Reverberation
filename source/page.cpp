#include"../header/define.h" 


/*--------------------------
 | ページクラス(抽象クラス) |
  --------------------------*/
/*ページ遷移処理*/
void PageClass::MovePage(int Select,int FadeFlag,UserClass &User){
	//クリックされたらページ移動
	if( FadeFlag == TRUE ) User.SetPage( Select );
}

/*モードセット*/
void PageClass::SetMode(int Mode,int FadeFlag){
	if( FadeFlag == TRUE ) ModeFlag = Mode;
}

/*モード取得*/
int PageClass::GetMode(){
	return ModeFlag;
}


/*----------------------
 | タイトルページクラス |
  ----------------------*/
/*初期化*/
TitlePageClass::TitlePageClass(){
	//初期動作モード設定
	ModeFlag = MODE::MAIN;
}

/*タイトルメイン*/
void TitlePageClass::Main(UserClass &User){

	//BGM再生
	Sound.SetVol(User);
	Sound.PlayMusic(User);

	//モード分岐
	switch( ModeFlag ){

		//メインモード(トップ画面)
		case MODE::MAIN:
			Title.Main(ChangeFlag,User);	
			Title.ModeChange(ModeFlag,ChangeFlag,User);
		break;

		//ロード画面
		case MODE::LOAD:
			Save.Main(ChangeFlag);
			Save.Load(ModeFlag,User);
			Save.Delete(User);
			Save.ModeChange(ModeFlag,ChangeFlag,User);
		break;

		//おまけ
		case MODE::SECRET:

		break;

		//コンフィグ画面
		case MODE::CONFIG:
			Conf.Main(User,ChangeFlag);
			Conf.ModeChange(ModeFlag,ChangeFlag,User);
		break;

	}

	//ページが変わるとき、BGMを止める
	if( ModeFlag == MODE::OTHER ){
		Sound.StopBGM();		//音楽を停止
		ModeFlag = MODE::MAIN;	//モードフラグを初期化
		ChangeFlag = TRUE;		//チェンジフラグを立てる
	}

}


/*--------------------
 | ゲームページクラス |
  --------------------*/
/*初期化*/
GamePageClass::GamePageClass(){
	//初期動作モード設定
	ModeFlag = MODE::MAIN;
}

/*ゲームメイン*/
void GamePageClass::Main(UserClass &User){

	Sound.SetVol(User);		//音量
	Sound.PlayMusic(User);	//音楽再生
	
	//モード取得
	switch( ModeFlag ){
		//ゲームメイン
		case MODE::MAIN:
			Text.Main(User);
			Text.ModeChange(ModeFlag,ChangeFlag,User);
		break;		

		//セーブ画面
		case MODE::SAVE:
			Save.Main(ChangeFlag);
			Save.Save(User);
			Save.Delete(User);
			Save.ModeChange(ModeFlag,ChangeFlag,User);
		break;

		//ロード画面
		case MODE::LOAD:
			Save.Main(ChangeFlag);
			Save.Load(ModeFlag,User);
			Save.Delete(User);
			Save.ModeChange(ModeFlag,ChangeFlag,User);
		break;

		//エンディング
		case MODE::END:
			Sound.StopBGM();
			Ending.Main(User,ModeFlag);
		break;

		//コンフィグ画面
		case MODE::CONFIG:
			Conf.Main(User,ChangeFlag);
			Conf.ModeChange(ModeFlag,ChangeFlag,User);
		break;
	}

	//ページが変わるとき、後処理をする
	if( ModeFlag == MODE::OTHER ){
		Sound.StopBGM();			//音楽を停止	
		ModeFlag   = MODE::MAIN;	//モードフラグを初期化
		ChangeFlag = TRUE;			//チェンジフラグを立てる
	}

}
			

/*--------------------------
 | シークレットページクラス |
  --------------------------*/
/*メイン関数*/
void SecretPageClass::Main(UserClass &User){
	Secret.Main(User,ChangeFlag);

}