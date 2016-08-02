#include"../header/define.h" 

/*--------------
 | セーブクラス |
  --------------*/
/*初期化*/
SaveClass::SaveClass(){
	ClickFlag      = 0;
	Page           = 0;
	Select		   = 0;
	MenuDialogFlag = FALSE;
	SaveDialogFlag = FALSE;
	LoadFlag	   = TRUE;

	//パラメータセット
	SetMenuParam();
}

/*メニューパラメータセット*/
void SaveClass::SetMenuParam(){
	//左データ
	SaveLeftParam.DrawX			= 0;
	SaveLeftParam.DrawY			= 60;
	SaveLeftParam.Interval		= 0;
	SaveLeftParam.Width			= 639;
	SaveLeftParam.Height		= 119;
	SaveLeftParam.ListMin		= 0;
	SaveLeftParam.ListMax		= 5;
	SaveLeftParam.AtherNo		= -1;
	SaveLeftParam.AlphaNo		= 100;
	SaveLeftParam.DrawFlag		= MENU::DATA;
	SaveLeftParam.DirectionFlag	= MENU::COL;

	//右データ
	SaveRightParam.DrawX			= 640;
	SaveRightParam.DrawY			= 60;
	SaveRightParam.Interval			= 0;
	SaveRightParam.Width			= 640;
	SaveRightParam.Height			= 119;
	SaveRightParam.ListMin			= 5;
	SaveRightParam.ListMax			= 10;
	SaveRightParam.AtherNo			= -1;
	SaveRightParam.AlphaNo			= 100;
	SaveRightParam.DrawFlag			= MENU::DATA;
	SaveRightParam.DirectionFlag	= MENU::COL;

	//ナビゲーション
	SaveNaviParam.DrawX			= 0;
	SaveNaviParam.DrawY			= 660;
	SaveNaviParam.Interval		= 0;
	SaveNaviParam.Width			= 320;
	SaveNaviParam.Height		= 60;
	SaveNaviParam.ListMin		= 10;
	SaveNaviParam.ListMax		= 14;
	SaveNaviParam.AtherNo		= -1;
	SaveNaviParam.AlphaNo		= 200;
	SaveNaviParam.DrawFlag		= MENU::IMAGE;
	SaveNaviParam.DirectionFlag	= MENU::ROW;
	SaveNaviParam.DrawHandle[0]	= LoadGraph("./resource/graph/BackGo.png");
	SaveNaviParam.DrawHandle[1]	= LoadGraph("./resource/graph/TitleBackGo.png");
	SaveNaviParam.DrawHandle[2]	= LoadGraph("./resource/graph/BackPage.png");
	SaveNaviParam.DrawHandle[3]	= LoadGraph("./resource/graph/FrontPage.jpg");

}

/*セーブメイン関数*/
void SaveClass::Main(int &ChangeFlag){
	//スピード定数
	const int Speed = 30;
	enum{SCENE,TEXT,SERIF};
	enum{BGM,BACK,CHAR};
	enum{YEAR,MON,DAY};

	//モードチェンジして一回目,アニメーションを初期化
	if( ChangeFlag == TRUE ){
		Page       = 0;
		LoadFlag   = TRUE;
		ChangeFlag = FALSE;			//モードチェンジフラグを折る
		FadeFlag   = FALSE;			//フェード完了フラグを折る
		Graph.Anime.Reset();		//アニメクラス初期化
	}


	//フェードイン
	FadeFlag = Graph.Anime.FadeIn(Speed);

	//セーブデータ取得
	GetSaveData();

	//セーブデータ描画
	Draw(Select);

	//セーブデータロード
	LoadData.SceneCount = SaveCount[Page][Select][SCENE];
	LoadData.TextCount  = SaveCount[Page][Select][TEXT];
	LoadData.SerifCount = SaveCount[Page][Select][SERIF];
	LoadData.BGMCode    = SaveCode[Page][Select][BGM];
	LoadData.BackCode   = SaveCode[Page][Select][BACK];
	LoadData.CharCode   = SaveCode[Page][Select][CHAR];
	LoadData.Year       = SaveDate[Page][Select][YEAR];
	LoadData.Mon		= SaveDate[Page][Select][MON];
	LoadData.Day		= SaveDate[Page][Select][DAY];
	LoadData.TextLength = SaveTextLength[Page][Select][0];
	strcpy(LoadData.Text,SaveText[Page][Select]);

}

/*セーブ画面からモードチェンジ*/
void SaveClass::ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User){
	//インスタンス化
	MouseClass *Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;

	//定数定義
	enum{BACK=10,TITLEBACK};

	//ダイアログ描画フラグを取得
	MenuDialogFlag = Dialog.GetDrawFlag();

	//左クリックされて、フェードも終わってる
	if( Mouse->GetState(MOUSE::LEFT) == TRUE && FadeFlag == TRUE && MenuDialogFlag == FALSE ){
		switch( Select ){
			//前に戻る
			case BACK:
				ModeFlag   = MODE::MAIN;
				ChangeFlag = TRUE;
			break;

			//タイトルに戻る
			case TITLEBACK:
				Dialog.SetSelectNo( Select , "タイトルに戻りますか？");
			break;
		}
	}

	if( MenuDialogFlag == TRUE ){
		//ダイアログ描画
		Dialog.Draw(User);

		//Yesなら処理
		if( Dialog.GetSelectFlag() == DIALOG::YES ){
			
			//選択番号受け取り
			Select = Dialog.GetSelectNo();

			//タイトルならば
			if( Select == TITLEBACK ){
				ModeFlag = MODE::OTHER;
				User.SetPage( PAGE::TITLE );
				Dialog.Clear();
			}
		}
		
		//Noならダイアログ削除
		if( Dialog.GetSelectFlag() == DIALOG::NO ) 	Dialog.Clear();
	}
}

/*セーブデータ描画*/
void SaveClass::Draw(int &Select){
	//セーブデータの数
	const int SaveNo	  = 5;
	const int AtherSelect = -1;
	const int PageNo      = 3;
	enum{YEAR,MON,DAY};

	//各種メニュー宣言
	static SaveMenuClass LeftMenu(SaveLeftParam);
	static SaveMenuClass RightMenu(SaveRightParam);
	static MenuClass NaviMenu(SaveNaviParam);

	//引数として渡すセーブデータ	
	Dvector_i	RightData_Date( 5 , vector<int>(3) );
	Dvector_i	LeftData_Date( 5 , vector<int>(3) );
	std::vector<char*> RightData_Text(5);
	std::vector<char*> LeftData_Text(5);

	//データ代入
	for(int i=0 ; i<SaveNo ; i++ ){
		//日付
		LeftData_Date[i][YEAR]  = SaveDate[Page][i][YEAR];
		LeftData_Date[i][MON]   = SaveDate[Page][i][MON];
		LeftData_Date[i][DAY]   = SaveDate[Page][i][DAY];
		RightData_Date[i][YEAR] = SaveDate[Page][i+SaveNo][YEAR];
		RightData_Date[i][MON]  = SaveDate[Page][i+SaveNo][MON];
		RightData_Date[i][DAY]  = SaveDate[Page][i+SaveNo][DAY];
						
		//一行テキスト
		LeftData_Text[i]  = SaveText[Page][i];
		RightData_Text[i] = SaveText[Page][i+SaveNo];
		
	}

	/*セーブデータ更新*/
	LeftMenu.UpdateData(LeftData_Date,LeftData_Text);
	RightMenu.UpdateData(RightData_Date,RightData_Text);

	/*メニューの選択番号取得*/
	if( MenuDialogFlag == FALSE && SaveDialogFlag == FALSE ){
		LeftMenu.Select();		
		RightMenu.Select();		
		NaviMenu.Select();
	}

	/*背景描画*/
	Graph.Draw();

	/*メニュー描画*/
	LeftMenu.Draw(Page);		
	RightMenu.Draw(Page);		
	NaviMenu.Draw();

	/*選択中番号を取得*/
	Select = NaviMenu.GetSelectNo();
	if( Select == AtherSelect ) Select = RightMenu.GetSelectNo();
	if( Select == AtherSelect ) Select = LeftMenu.GetSelectNo();

	//ページ切り替え
	ChangePage();

}

/*セーブデータの取得*/
void SaveClass::GetSaveData(){
	//ファイルポインタ宣言
	FILE *fp;
	int TmpHash = 0;

	const int Key = 7;

	//読み込みフラグが立ってるなら
	if( LoadFlag == TRUE ){
		//変数初期化
		Hash = 0;
		memset(SaveCount,0,sizeof(SaveCount));
		memset(SaveCode,0,sizeof(SaveCode));
		memset(SaveDate,0,sizeof(SaveDate));
		memset(SaveTextLength,0,sizeof(SaveTextLength));
		memset(SaveText,0,sizeof(SaveText));

		//ファイルオープン
		fp = fopen("./resource/data/save.dat","rb+");
	
		//データ受け取り
		fseek(fp,0L,SEEK_SET);
		for( int j=0 ; j<3  ; j++ ){
			for( int i=0 ; i<10 ; i++ ){
				fread(&Hash,1,sizeof(int),fp);
				fread(SaveCount[j][i],3,sizeof(short int),fp);
				fread(SaveCode[j][i],3,sizeof(int),fp);
				fread(SaveDate[j][i],3,sizeof(int),fp);
				fread(SaveTextLength[j][i],1,sizeof(int),fp);
				TextSize = (size_t)SaveTextLength[j][i][0];
				fread(SaveText[j][i],1,sizeof(SaveText[j][i]),fp);

				//ハッシュ値計算
				for( int h=0 ; h<3 ; h++ ) TmpHash += SaveCount[j][i][h];
				TmpHash = Hash^Key;
				TmpHash = Hash%Key;
				if( Hash != TmpHash ){
					//強制終了
					MessageBox(NULL,"どうしてデータの改竄なんてしたのっ！\n(プログラムの不具合の場合は開発者まで連絡ください。)","焼きそばメロンパン",MB_OK);
					exit(0);
				}
				TmpHash = 0;
			}
		}
		//ファイルクローズ
		fclose(fp);
		
		//読み込みフラグをﾊﾞｯｷﾊﾞｷ
		LoadFlag = FALSE;
	}
}

/*データセーブ*/
void SaveClass::Save(UserClass &User){
	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;

	//いろいろ宣言
	FILE *fp;
	static int  TrueSelect = 12;

	//変数達
	short int SceneCount = 0;
	short int TextCount  = 0;
	short int SerifCount = 0;
	SaveData_rec SaveData;

	//定数
	enum{SCENE,TEXT,SERIF};
	enum{BGM,BACK,CHAR};
	enum{YEAR,MON,DAY};
	const int SaveDataMin = 0;
	const int SaveDataMax = 10;
	const int Key		  = 7;

	//タイトル描画
	SetFontSize(40);
	DrawString(20,20,"― セーブ画面 ―",GetColor(255,255,255));

	//ダイアログ描画フラグを取得
	SaveDialogFlag = Dialog.GetDrawFlag();

	//左クリックされたら
	if( Mouse->GetState(MOUSE::LEFT) == TRUE && FadeFlag == TRUE && SaveDialogFlag == FALSE && DeleteDialogFlag == FALSE ){
		if( SaveDataMin <= Select && Select < SaveDataMax ){
			Dialog.SetSelectNo( Select , "セーブしていいですか？" );
		}
	}

	if( SaveDialogFlag == TRUE ){
		
		//ダイアログ描画
		Dialog.Draw(User);

		//Yesの場合
		if( Dialog.GetSelectFlag() == DIALOG::YES ){
			
			//選択番号受け取り
			Select = Dialog.GetSelectNo();

			//ファイルオープン
			fp = fopen("./resource/data/save.dat","wb+");

			//現在のデータ読み込み
			SaveData = User.GetSaveData();
		
			SaveCount[Page][Select][SCENE]  = SaveData.SceneCount ; 
			SaveCount[Page][Select][TEXT]   = SaveData.TextCount  ; 
			SaveCount[Page][Select][SERIF]  = SaveData.SerifCount ;
			SaveCode[Page][Select][BGM]     = SaveData.BGMCode    ;
			SaveCode[Page][Select][BACK]    = SaveData.BackCode   ;
			SaveCode[Page][Select][CHAR]    = SaveData.CharCode	  ;
			SaveDate[Page][Select][YEAR]    = SaveData.Year       ;
			SaveDate[Page][Select][MON]     = SaveData.Mon	      ;
			SaveDate[Page][Select][DAY]     = SaveData.Day		  ;
			SaveTextLength[Page][Select][0] = SaveData.TextLength ; 
			strcpy(SaveText[Page][Select],SaveData.Text);


			//セーブデータ書き込み
			for( int j=0 ; j<3 ; j++ ){
				for( int i=0 ; i<10 ; i++ ){
					
					//ハッシュ値計算
					for( int h=0 ; h<3 ; h++ ) Hash += SaveCount[j][i][h];
					Hash = Hash^Key;
					Hash = Hash%Key;

					fwrite(&Hash,1,sizeof(int),fp);
					fwrite(SaveCount[j][i],3,sizeof(short int),fp);
					fwrite(SaveCode[j][i],3,sizeof(int),fp);
					fwrite(SaveDate[j][i],3,sizeof(int),fp);
					fwrite(SaveTextLength[j][i],1,sizeof(int),fp);
					TextSize = (size_t)SaveTextLength[j][i][0];
					fwrite(SaveText[j][i],1,sizeof(SaveText[j][i]),fp);
				}
			}

			//ファイルクローズ
			fclose(fp);
			Dialog.Clear();
		}

		//Noの場合
		if( Dialog.GetSelectFlag() == DIALOG::NO ){
			//ダイアログ削除
			Dialog.Clear();
		}	
	}
}
	
/*セーブデータロード*/
void SaveClass::Load(int &ModeFlag,UserClass& User){
	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;

	//定数定義
	const int SaveDataMin = 0;
	const int SaveDataMax = 10;

	//タイトル描画
	SetFontSize(40);
	DrawString(20,20,"― ロード画面 ―",GetColor(255,255,255));

	//ダイアログ描画フラグを取得
	SaveDialogFlag = Dialog.GetDrawFlag();

	//左クリックされて、フェードが完了している
	if( Mouse->GetState(MOUSE::LEFT) == TRUE && FadeFlag == TRUE && SaveDialogFlag == FALSE && DeleteDialogFlag == FALSE ){
		if( SaveDataMin <= Select && Select < SaveDataMax && SaveDate[Page][Select][0] != 0 ){
			Dialog.SetSelectNo( Select , "ロードしてよろしいですか？" );
		}
	}


	//ダイアログが描画されているならば
	if( SaveDialogFlag == TRUE ){
		
		//ダイアログ描画
		Dialog.Draw(User);

		//Yesなら
		if( Dialog.GetSelectFlag() == DIALOG::YES ){

			//選択番号を受け取る
			Select = Dialog.GetSelectNo();

			//読み込み処理
			User.SetSaveData(LoadData);
			ModeFlag = MODE::OTHER;
			User.SetPage( PAGE::GAME );

			//ダイアログ削除
			Dialog.Clear();
		}

		//Noなら
		if( Dialog.GetSelectFlag() == DIALOG::NO ){
			Dialog.Clear();
		}
	}

}

/*ページ切り替え*/
void SaveClass::ChangePage(){
	auto *Mouse = MouseClass::GetInstance();

	static int  Timer     = 0;
	static bool ClickOk   = TRUE;
	static bool ClickFlag = 0;

	if( Mouse->GetState(MOUSE::LEFT) == 1 && ClickFlag == FALSE ){

		ClickFlag = TRUE;
		
		if( Select == 12 ) Page = ( Page + 2 ) % 3;
		if( Select == 13 ) Page = ( Page + 1 ) % 3;

	}

	if( ClickFlag == TRUE ) Timer++;
	if( Timer > 10       ){
		ClickFlag = FALSE;
		Timer = 0;
	}

}

/*セーブデータ削除*/
void SaveClass::Delete(UserClass &User){
	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;

	//いろいろ宣言
	FILE *fp;
	static int  TrueSelect = 12;
	static int  Timer      = 0;

	//変数達
	short int SceneCount = 0;
	short int TextCount  = 0;
	short int SerifCount = 0;
	SaveData_rec SaveData;
	int Hash = 0;

	//定数
	enum{SCENE,TEXT,SERIF};
	enum{BGM,BACK,CHAR};
	enum{YEAR,MON,DAY};
	const int SaveDataMin = 0;
	const int SaveDataMax = 10;
	const int Key = 7;

	//ダイアログ描画フラグを取得
	DeleteDialogFlag = Dialog.GetDrawFlag();

	//左クリックされたら
	if( Mouse->GetState(MOUSE::RIGHT) == TRUE && FadeFlag == TRUE && SaveDialogFlag == FALSE && DeleteDialogFlag == FALSE ){
		if( SaveDataMin <= Select && Select < SaveDataMax && SaveDate[Page][Select][YEAR] != 0){
			Dialog.SetSelectNo( Select , "削除しますよ？" );
			Timer = 0;
		}
	}

	if( DeleteDialogFlag == TRUE ){
		
		//ダイアログ描画
		Dialog.Draw(User);

		//Yesの場合
		if( Dialog.GetSelectFlag() == DIALOG::YES ){
			
			//選択番号受け取り
			Select = Dialog.GetSelectNo();

			//ファイルオープン
			fp = fopen("./resource/data/save.dat","wb+");
			
			//空データ生成
			//Hash							= 0;
			SaveCount[Page][Select][SCENE]  = 0;
			SaveCount[Page][Select][TEXT]   = 0; 
			SaveCount[Page][Select][SERIF]  = 0;
			SaveCode[Page][Select][BGM]     = 0;
			SaveCode[Page][Select][BACK]    = 0; 
			SaveCode[Page][Select][CHAR]	= 0;
			SaveDate[Page][Select][YEAR]    = 0;
			SaveDate[Page][Select][MON]     = 0;
			SaveDate[Page][Select][DAY]     = 0;
			SaveTextLength[Page][Select][0] = 0; 
			//strcpy(SaveText[Page][Select],"\0");
			memset(SaveText[Page][Select],'\0',sizeof(SaveText[Page][Select]));


			//セーブデータ書き込み
			for( int j=0 ; j<3 ; j++ ){
				for( int i=0 ; i<10 ; i++ ){
					//ハッシュ値計算
					for( int h=0 ; h<3 ; h++ ) Hash += SaveCount[j][i][h];
					Hash = Hash^Key;
					Hash = Hash%Key;

					fwrite(&Hash,1,sizeof(int),fp);
					fwrite(SaveCount[j][i],3,sizeof(short int),fp);
					fwrite(SaveCode[j][i],3,sizeof(int),fp);
					fwrite(SaveDate[j][i],3,sizeof(int),fp);
					fwrite(SaveTextLength[j][i],1,sizeof(int),fp);
					TextSize = (size_t)SaveTextLength[j][i][0];
					fwrite(SaveText[j][i],1,sizeof(SaveText[j][i]),fp);
				}
			}

			//ファイルクローズ
			fclose(fp);
			//Timer++;
			Dialog.Clear();
		}

		//Noの場合
		if( Dialog.GetSelectFlag() == DIALOG::NO ){
			//ダイアログ削除
			Dialog.Clear();
			
		}	
	}
}
	