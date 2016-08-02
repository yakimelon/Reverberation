#include"../header/define.h" 

/*------------------
 | コンフィグクラス |
  ------------------*/
/*初期化*/
ConfigClass::ConfigClass(){
	Select = -1;
}

/*メイン関数*/
void ConfigClass::Main(UserClass& User,int &ChangeFlag){

	//定数宣言
	const int Speed = 60;	//フェードイン速度

	//モードチェンジしたとき、初期化
	if( ChangeFlag == TRUE ){
		ConfigData = User.GetConfigData(); //ユーザークラスのコンフィグ情報をコピー
		
		//テスト用
		BackConfigData = ConfigData;

		ChangeFlag = FALSE;					//モードチェンジフラグを折る
		FadeFlag   = FALSE;					//フェード完了フラグを折る
		Graph.Anime.Reset();				//アニメーションリセット
	}

	//フェードイン
	FadeFlag = Graph.Anime.FadeIn(Speed);

	//グラフィッククラスにコンフィグ情報を渡す
	Graph.SetConfigData(ConfigData);
	
	//画面描画
	Graph.Draw();

	//グラフィッククラスから変更されたコンフィグ情報を受け取る
	ConfigData = Graph.GetConfigData();

	//決定とかのメニュー選択番号受け取り
	Select = Graph.GetSelectNo();

	//コンフィグデータをユーザークラスに反映させる。
	User.SetConfigData(ConfigData);
}


/*モードチェンジクラス*/
void ConfigClass::ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User){
	//インスタンス化
	MouseClass *Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;
	
	//定数定義
	enum{INIT,SAVE,BACK,TITLEBACK};

	//左クリックされて、フェードも終わってる
	if( Mouse->GetState(MOUSE::LEFT) == TRUE && FadeFlag == TRUE && Dialog.GetDrawFlag() == FALSE){
		switch( Select ){
			//セーブ
			case SAVE:
				Dialog.SetSelectNo( Select , "変更を保存していいですか？" );
			break;

			//バック
			case BACK:
				Dialog.SetSelectNo( Select , "変更を保存しないで戻りますか？" );
			break;

			//タイトルバック
			case TITLEBACK:
				Dialog.SetSelectNo( Select , "タイトルに戻りますか？" );
			break;

			//初期化
			case INIT:
				Dialog.SetSelectNo( Select ,"設定を初期化しますか？" );
			break;
		}
	}

	//ダイアログが表示されているなら
	if( Dialog.GetDrawFlag() == TRUE ){

		//ダイアログ描画
		Dialog.Draw(User);

		//「はい」をクリック
		if( Dialog.GetSelectFlag() == DIALOG::YES ){
			switch( Dialog.GetSelectNo() ){
				//設定保存
				case SAVE:
					ModeFlag = MODE::MAIN;
					ChangeFlag = TRUE;
				break;

				//戻る
				case BACK:
					User.SetConfigData(BackConfigData);
					ModeFlag = MODE::MAIN;
					ChangeFlag = TRUE;	
				break;

				//タイトルに戻る
				case TITLEBACK:
					User.SetConfigData(BackConfigData);
					ModeFlag = MODE::OTHER;
					User.SetPage( PAGE::TITLE );
				break;

				//設定初期化
				case INIT:
					ConfigData.TextSpeed = 2;
					ConfigData.AutoSpeed = 2;
					ConfigData.SkipFlag  = 0;
					ConfigData.AllBolume = 3;
					ConfigData.BGMBolume = 2;
					ConfigData.SEBolume  = 2;
				break;
			}
			//ダイアログ削除
			Dialog.Clear();
		}

		//「いいえ」をクリック
		if( Dialog.GetSelectFlag() == DIALOG::NO ){
			//ダイアログ削除
			Dialog.Clear();
		}
	}
}