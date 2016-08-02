#include"../header/define.h" 

/*----------------
 | タイトルクラス |
  ----------------*/
/*タイトルメインモード*/
void TitleClass::Main(int &ChangeFlag,UserClass &User){
	bool SecretFlag;
	
	User.SetSecretFlag();
	SecretFlag = User.GetSecretFlag();

	//メニューパラメータセット
	static struct MenuArg_rec MenuParam;
	SetMenuParam_Title(MenuParam,SecretFlag);
	TitleMenuClass Menu(MenuParam);

	//定数宣言
	const int Speed = 10;	//フェードイン速度

	//モードチェンジして一回目
	if( ChangeFlag == TRUE ){
		ChangeFlag = FALSE;			//モードチェンジフラグを折る
		FadeFlag   = FALSE;			//フェード完了フラグを折る
		Graph.Anime.Reset();		//アニメーションリセット
	}

	//フェードイン
	FadeFlag = Graph.Anime.FadeIn(Speed);

	//背景描画
	Graph.Draw();

	//タイトルメニュー設置
	Menu.Create();

	//セーブデータ初期化
	InitSaveData(User);

	//現在選択中のメニューを取得
	Select = Menu.GetSelectNo();
}

/*動作モードチェンジ*/
void TitleClass::ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User){
	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();

	//セーブ構造体宣言
 	struct SaveData_rec SaveData;

	//左クリックされた
	if( Mouse->GetState(MOUSE::LEFT) == TRUE && FadeFlag == TRUE ){
		//コンティニュー
		if( Select == TITLE::LOAD ){
			ModeFlag   = MODE::LOAD;
			ChangeFlag = TRUE;
		}

		//コンフィグ
		if( Select == TITLE::CONFIG ){
			ModeFlag   = MODE::CONFIG;
			ChangeFlag = TRUE;
		}

		//ゲームスタート
		if( Select == TITLE::START ){
			ModeFlag = MODE::OTHER;
			User.SetPage( PAGE::GAME );

			//ゲームカウント初期化
			InitSaveData(User);
			//User.SetSaveData(SaveData);	
		}

		//おまけ
		if( Select == TITLE::SECRET && User.GetSecretFlag() == TRUE ){
			ModeFlag   = MODE::OTHER;
			User.SetPage( PAGE::SECRET );
		}

		//ゲーム終了
		if( Select == TITLE::END ){
			ModeFlag = MODE::OTHER;
			User.SetPage( PAGE::END );
		}
	}

}

/*タイトルクラス*/
void TitleClass::InitSaveData(UserClass &User){
	SaveData_rec SaveData;
	
	SaveData.SceneCount = 0;
	SaveData.TextCount  = 0;
	SaveData.SerifCount = 0;
	SaveData.BGMCode    = GAME_BGM::STOP;
	SaveData.BackCode   = GAME_BACK::BLACK;
	SaveData.CharCode   = GAME_CHAR::NOT;
	SaveData.Year		= 0;
	SaveData.Mon		= 0;
	SaveData.Day		= 0;
	SaveData.TextLength = 0;
	memset(SaveData.Text,'\0',sizeof(SaveData.Text));

	User.SetSaveData( SaveData );
}