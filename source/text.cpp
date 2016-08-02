#include"../header/define.h" 

/*----------------
 | テキストクラス |
  ----------------*/
/*初期化処理*/
TextClass::TextClass(){
	InitVar();		//変数初期化
	LoadStory();	//ストーリ読み込み
}

/*変数初期化*/
void TextClass::InitVar(){
	//メンバ変数初期化
	SelectFlag = 1;
	Select = -1;
	AutoFlag = -1;
	TextCount = 0;
	SceneCount = 0;
	SerifCount = 0;
	SelectFlag = 0;
	WriteMode  = NORMAL;
	TextGraphEndFlag=0;
	memset(LineMax,0,sizeof(LineMax));
	memset(LineNo,0,sizeof(LineNo));
	memset(Text,'\0',sizeof(Text));
	memset(Name,'\0',sizeof(Name));
}

/*ストーリーロード*/
void TextClass::LoadStory(){
	//真の変数
	int							FileHandle;			//ファイルハンドル
	char						TmpBuf[128];		//テキスト取得用一時変数
	char						FileName[64];		//ファイル名格納
	std::string					TmpText;			//テキスト取得後操作用一時オブジェクト 
	std::vector<std::string>	SplitTextArray;		//分割された文字を格納する配列

	//カウンタ
	int	Count = 0;									//カウンタ
	int	Scene = 0;									//シーンカウンタ

	//行数管理
	int SerifNo = -1;								//セリフのナンバーを格納(最初は必ず加算されるので、初期値は負の数にしておく)

	//定数
	const int LoadTextLen = 128;					//読み込むテキストの文字数
	const int NAME		  = 0;						//分割された文字列を格納する配列に関するもの
	const int TEXT		  = 1;						//分割された文字列を格納する配列に関するもの


	//SceneMax(定数)までロード
	while( Scene <= SceneMax ){ 

		//ファイル名を取得
		sprintf(FileName,"./resource/story/zankyo scene%d.txt",Scene);
		
		//ファイルオープン
		FileHandle = FileRead_open(FileName);

		//ファイル終端までループ
		while( FileRead_eof(FileHandle) == 0 ){
			//ファイルから一行取得
			FileRead_gets(TmpBuf,LoadTextLen,FileHandle);
			
			//一文字目が '\0' なら空行と判断しスキップ
			if( TmpBuf[0] == '\0'  ) continue;

			//char型配列のTmpBufをStringオブジェクトのTmpTextに変換
			TmpText = TmpBuf;
				
			//TmpTextの一文字目が'\0'ならば空行と判断しスキップ
			if( TmpText[0] == NULL ) continue;

			//全角･半角スペースを除去
			CutSpace(TmpText);

			//TmpTextの一文字目が'\0'ならば空行と判断しスキップ
			if( TmpText[0] == '\0' ) continue;

			//TmpTextをNameとTextに分割
			SplitTextArray = StringSplit(TmpText,':');

			//分割された文字列をNameとTextに代入
			Name[Scene][Count] = SplitTextArray[NAME];
			Text[Scene][Count] = SplitTextArray[TEXT];

			//Nameが"コメント"ならコメントと判断しスキップ
			if( Name[Scene][Count] == "コメント" ) continue;

			//一時処理、Nameが"背景"ならとりまスキップ
			//if( Name[Scene][Count] == "背景" ) continue;

			//Textが'\0'なら前のテキストの続きと判断し、Nameに続きと代入し、TextにName(一行全て入ってる)の内容をコピー ＆ 行数加算
			//それ以外ならば次のテキストと判断し、SerifNoを加算し、行数加算
			if( Text[Scene][Count] == "\0" ){
				Text[Scene][Count] = Name[Scene][Count];
				Name[Scene][Count] = "続き";
				LineNo[Scene][SerifNo]++;
			}else{
				SerifNo++;
				LineNo[Scene][SerifNo]++;
			}

			//最大行数加算
			LineMax[Scene]++;

			//カウントを進める
			Count++;
		}

		//シーンカウントを進める
		Scene++;

		//カウント初期化
		Count=0;
		SerifNo=-1;

	}
	
}

/*文字列分割*/
std::vector<std::string> TextClass::StringSplit(const std::string &Str,char Sep){
	//いろいろ宣言
	std::vector<std::string> V;
	std::stringstream Ss(Str);
	std::string Buffer;

	const std::string EndOfText = "\0";

	//文字列分割
	while( std::getline(Ss,Buffer,Sep) ) V.push_back(Buffer);

	//終端文字 '\0' を挿入
	V.push_back(EndOfText);

	return V;
}

/*テキストからスペースを取り除く*/
int TextClass::CutSpace(std::string &TmpText){
	//変数宣言
	int  i = 0;				//空白除去処理に使うカウンタ
	char TmpStr[3];		   	//空白除去処理につかう一時変数

	const int BigSpaceSize = 2; //全角スペースのサイズ

	//全角空白を取り除く処理
	if( TmpText.length() >= BigSpaceSize ){
		do{
			if( TmpText.length() <= i ){
				TmpText[0] = '\0';
				return 0;
			}
			TmpStr[0] = TmpText[i];
			TmpStr[1] = TmpText[i+1];
			TmpStr[2] = '\0';
			i+=2;
		}while( strcmp(TmpStr,"　") == 0 );
		TmpText = &TmpText[i-2];
	}
	
	//半角スペースを取り除く処理
	i=0;
	while( TmpText[i] == ' ' ){
		//文字数を超えないようなコーディングをしろ(上参照)

		i++;
		if( TmpText.length() <= i ){
			TmpText[0] = '\0';
			return 0;
		}
	}
	TmpText = &TmpText[i];

}

/*メイン関数*/
void TextClass::Main(UserClass &User){
	//メニューパラメータセット
	static struct MenuArg_rec MenuRightParam;
	SetMenuParam_GameRight(MenuRightParam);
	static MenuClass GameRightMenu(MenuRightParam);

	//定数
	const int OtherSelect = 6;


	//ゲームカウントの初期化
	InitGameCount(User);

	//テキストチェック
	CheckText(User);	

	//制御コードチェック
	if( WriteMode != EYECATCH ) CheckCotrolCode(User);

	//背景描画
	Graph.DrawBack(User);

	//キャラクタ描画
	Graph.DrawChar(User);

	//テキストボックス描画
	if( WriteMode != NOTWINDOW ) Graph.DrawWindow();

	//描画モード取得
	//WriteMode = GetWriteMode();

	//コンフィグで未読スキップ許可設定
	ReadUpdate(User);

	//既読チェック
	CheckRead();
	
	//デバッグ用既読操作
	ControlRead();

	//メニュー設置･処理
	if( WriteMode == NORMAL ){
		GameRightMenu.Create();
		Select = GameRightMenu.GetSelectNo();
	}
	
	//テキスト描画
	if( WriteMode == NORMAL    ) NormalWrite(User);	//通常テキスト描画
	if( WriteMode == EYECATCH  ) EyeCatching(User);	//アイキャッチ
	if( WriteMode == BACKLOG   ) BackLogMain(User);	//バックログ
	if( WriteMode == NOTWINDOW ) NotWindow();		//ウィンドウ非表示
	if( WriteMode == END	   ) GameEnd(User);		//ゲーム終了

	//メニューを選択していなければ、テキストを進める･スキップ･オート
	if( Select == OtherSelect && WriteMode == NORMAL){
		PutNextLine(User);
		//SkipFunction(User);
		AutoFunction(User);
	}
	
	//現在のカウントをセット
	SetGameData(User);
}

/*モードチェンジ*/
void TextClass::ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User){
	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();
	AnimeClass Anime;

	static int Count = 0;

	const int AtherSelect = -1;

	//タイマー
	static int Timer = 0;
	if( WriteMode != NOTWINDOW ) Timer++;

	//モードチェンジ
	if( Mouse->GetState(MOUSE::LEFT) == TRUE ){
		if( Select == GAME_MENU::SAVE )    ModeFlag  = MODE::SAVE;
		if( Select == GAME_MENU::LOAD )    ModeFlag  = MODE::LOAD;
		if( Select == GAME_MENU::BACKLOG ) WriteMode = BACKLOG;
		if( Select == GAME_MENU::CONFIG  ) ModeFlag  = MODE::CONFIG;
		if( Select == GAME_MENU::AUTO )    AutoFlag *= -1;
		ChangeFlag = TRUE;
	}

	//ウィンドウ非表示
	/*
	if( Mouse->GetState( MOUSE::RIGHT) > 0 && WriteMode == NORMAL && Timer > 20 ){
		WriteMode = NOTWINDOW;
		Timer = 0;
	}
	*/

	//バックログ
	if( Mouse->GetWheel() > 0 && WriteMode == NORMAL ) WriteMode = BACKLOG;

	//エンディングモードへ
	if( WriteMode == END ){ //&& Mouse->GetState(MOUSE::LEFT) > 10 ){
		Select    = AtherSelect;
		WriteMode = NORMAL;
		ModeFlag = MODE::END;
		//ModeFlag = MODE::OTHER;
		//User.SetPage( PAGE::TITLE );
	}

	//タイトル画面へ
	if( WriteMode == TITLE ){
		Count++;
		DrawBox(0,0,windowX,windowY,GetColor(0,0,0),TRUE);
		SetFontSize(100);
		ChangeFont("ＭＳ 明朝");
		DrawString(windowX/3,windowY/3,"- FIN - ",GetColor(255,255,255));
		User.SetBGMCode( GAME_BGM::STOP );
		if( Count > 200 ){
			WriteMode = NORMAL;
			ModeFlag = MODE::OTHER;
			User.SetPage( PAGE::TITLE );
			Count = 0;
		}
		
	}
}

/*ゲームカウント初期化*/
void TextClass::InitGameCount(UserClass& User){
	//ゲームカウント取得
	SaveData   = User.GetSaveData();
	SceneCount = SaveData.SceneCount;
	TextCount  = SaveData.TextCount;
	SerifCount = SaveData.SerifCount;
	User.SetBGMCode ( SaveData.BGMCode  );
	User.SetBackCode( SaveData.BackCode );
	User.SetCharacterCode( SaveData.CharCode );
}

/*様々なテキストチェック*/
void TextClass::CheckText(UserClass &User){
	//メニュー決定フラグを折っておく
	MenuEnterFlag = 0;

	const int AtherSelect = -1;

	//一回目フラグ
	static bool FirstFlag = FALSE;

	//シーンの終わりなら、次のシーンへ(カウント更新)
	if( TextCount >= LineMax[SceneCount] ){
		SceneCount++;
		TextCount  = 0;
		SerifCount = 0;

		//ユーザークラスに渡す
		SaveData.SceneCount = SceneCount;
		SaveData.TextCount  = TextCount;
		SaveData.SerifCount = SerifCount;
		User.SetSaveData(SaveData);
		
		//アイキャッチを動作させる
		WriteMode = EYECATCH;
	}

	//シーンのはじめにアイキャッチを動作させる
	if( SceneCount == 0 && TextCount == 0 && FirstFlag == FALSE ){
		Select    = AtherSelect;
		WriteMode = EYECATCH;
		FirstFlag = TRUE;
	}
	if( TextCount > 0 ) FirstFlag = FALSE;
	

}

/*テキスト通常描画*/
void TextClass::NormalWrite(UserClass &User){
	//インスタンス取得
	KeyClass* Key = KeyClass::GetInstance();
	MouseClass* Mouse = MouseClass::GetInstance();

	//テキスト描画
	WriteText(User);	

	//名前描画
	WriteName();

 	//ゲームカウント更新
	//User.SetSaveData(SceneCount,TextCount,SerifCount);
}

/*テキスト描画*/
void TextClass::WriteText(UserClass &User){
	//変数宣言
	static int  WriteCount  = 0;					//書き込み時カウント
	static int  WriteIndex[3] = {0,0,0};			//現在何文字目か
	static int  WriteX = 0;							//書き込みX軸座標
	static int  WriteY = 0;							//書き込みY座標
	static int  OldTextCount;						//前のテキストカウントを取得
	static int  WriteLine;							//描画する行
	int  Length;									//文字数
	int  TmpCount  = 0;								//一時カウンタ
	int  LoopCount = 0;								//ループ用カウンタ
	char WriteText[3];								//書き込み文字

	//定数定義	
	const int DrawX		= 250;							//描画基準Ｘ座標						
	const int DrawY		= windowY - windowY / 3 + 50;	//描画基準Ｙ座標
	const int TextSpace = 14;							//文字と文字の間隔
	const int LineSpace = 40;							//行と行の間隔
	const int FontSize  = 28;							//フォントサイズ
	int DrawSpeed;										//文字の描画速度
	

	//文字の描画速度を取得
	if( AutoFlag == 1 ) DrawSpeed = User.GetAutoTextSpeed();
	else				DrawSpeed = User.GetTextSpeed();


	//テキストが進んだら変数初期化
	if( TextCount != OldTextCount ){
		memset(WriteIndex,0,sizeof(WriteIndex));
		WriteCount = 0;
		WriteX     = 0;
		WriteY     = 0;
		WriteLine   = 0;
	}
	//前のテキストカウントを取得(上の初期化のため)
	OldTextCount = TextCount;

	//フォントサイズ
	//SetFontSize(FontSize);

	//現在表示されている文字数だけ表示する(Lineは行数を示し、最大行数分ループする)
	for( int Line=0 ; Line<LineNo[SceneCount][SerifCount] ; Line++ ){

		//描画が完了している行まで描画
		if( Line <= WriteLine ){
			LoopCount = 0;																								//ループカウンタ初期化
			while( LoopCount <= WriteIndex[Line] ){																		//書き込み可能文字数以下なら
				WriteX = LoopCount * TextSpace;																			//描画X座標更新
				WriteText[0] = Text[SceneCount][TextCount+Line][LoopCount];												//1byte目代入
				WriteText[1] = Text[SceneCount][TextCount+Line][LoopCount+1];											//2byte目代入
				WriteText[2] = '\0';																					//ヌル文字を代入
				//DrawStringToHandle(DrawX+WriteX,DrawY + ( LineSpace * Line ),WriteText,GetColor(200,200,200),TextFontHandle);	//一文字描画
				DrawStringShadow(DrawX+WriteX,DrawY + ( LineSpace * Line ),WriteText,GetColor(233,233,233),GetColor(5,5,5));
				LoopCount+=2;																							//一文字分カウントアップ
			}

			Length = Text[SceneCount][TextCount+Line].length()-2;

			//文字列の終端ならば、書き込み行数を更新
			if( Length <= WriteIndex[Line] ){
				WriteLine = Line+1;					//文字列の終端ならば、書き込み行数を更新
			}else if( WriteCount % DrawSpeed == 0 ) WriteIndex[Line]+=2;


			//もしも全文描画終了フラグが立っているならば,描画カウントを最大にする(文字数を代入)
			if( TextGraphEndFlag == 1 ){
				WriteIndex[Line] = Length;
			}
		}
	}
	
	//描画タイミング動機用
	WriteCount++;
	
	//テキストが全て描画されたら、全文描画終了フラグを立てる
	if( WriteLine == LineNo[SceneCount][SerifCount] ) TextGraphEndFlag = 1;

}

/*名前描画*/
void TextClass::WriteName(){
	//定数定義
	const int DrawX = 200;
	const int DrawY = windowY - windowY / 3 + 10;

	//Nameが主人公なら、空文字を代入(地の文なので名前を表示させない)
	if( Name[SceneCount][TextCount] == "主人公" ){
		Name[SceneCount][TextCount][0] = '\0';
	}

	//名前描画
	DrawStringShadow(DrawX,DrawY,Name[SceneCount][TextCount].c_str(),GetColor(233,233,233),GetColor(5,5,5));
}

/*次の行へ進める*/
void TextClass::PutNextLine(UserClass &User){
	//インスタンス取得
	KeyClass*   Key    = KeyClass::GetInstance();
	MouseClass* Mouse = MouseClass::GetInstance();

	//エンターが押されて、テキストが表示し終わって、メニューを選択していないなら、カウントを進める
	if( ( Key->GetState(KEY_INPUT_RETURN) == 1 || Mouse->GetState(MOUSE::LEFT) == 1 || Mouse->GetWheel() < 0 ) && MenuEnterFlag != 1){
		//テキスト表示完了フラグが立っていればカウントを進める
		if( TextGraphEndFlag == 1 ){

			//テキストカウントを現在の行数分進める
			//TextCount        += RowNo;
			TextCount += LineNo[SceneCount][SerifCount];

			//Graph.Draw();

			//セリフカウントを進める
			SerifCount++;

			//テキスト表示完了フラグをﾊﾞｯｷﾊﾞｷ
			TextGraphEndFlag =  0;
			
			//現在カウントを更新
			//User.SetSaveData(SceneCount,TextCount,SerifCount);

		}else{
			TextGraphEndFlag = 1;
		}
	}
}

/*スキップ処理*/
void TextClass::SkipFunction(UserClass &User){
	//キークラスインスタンス取得
	KeyClass* Key = KeyClass::GetInstance();

	//変数宣言
	static int SkipCount = 0;

	//スキップチェック
	if( ( Key->GetState(KEY_INPUT_LCONTROL) > 0 || Key->GetState(KEY_INPUT_RCONTROL) >0 ) && SkipPermitFlag == 1){
		TextGraphEndFlag =  1;
		if( SkipCount % 3 == 0 ){
			TextCount += LineNo[SceneCount][SerifCount];
			SerifCount++;
			TextGraphEndFlag =  0;
			//User.SetSaveData(SceneCount,TextCount,SerifCount);
		}
		SkipCount++;
	}
}

/*既読チェック*/
void TextClass::CheckRead(){
	short int ReadData[2];
	FILE *fp;

	//定数
	enum{SCENE,TEXT,SERIF};

	//既読データ読み込み
	fp = fopen("./resource/data/read.dat","rb+");
	fseek(fp,0L,SEEK_SET);
	fread(ReadData,2,sizeof(short int),fp);
	fclose(fp);
	
	//既読チェック
	if( SceneCount < ReadData[SCENE] ){
		SkipPermitFlag = 1;
	}else if( SceneCount == ReadData[SCENE] ){
		if( TextCount < ReadData[TEXT] ) SkipPermitFlag = 1;
	}else{
		//スキップ禁止
		SkipPermitFlag = 0;
		ReadData[SCENE] = SceneCount;
		ReadData[TEXT]  = TextCount;
		fp = fopen("./resource/data/read.dat","wb+");
		fwrite(ReadData,2,sizeof(short int),fp);
		fclose(fp);
	}

}

/*オート処理*/
void TextClass::AutoFunction(UserClass &User){
	//キークラスインスタンス取得
	KeyClass* Key = KeyClass::GetInstance();

	//変数宣言
	static int AutoCount = 0;
	const  int StopSpeed = 120;

	//オートチェック
	if( Key->GetState(KEY_INPUT_A) == 1 )	AutoFlag *= -1;
	if( AutoFlag == 1 ) DrawStringShadow(10,windowY-50,"AutoMode...",GetColor(255,255,255),GetColor(5,5,5));
	if( AutoFlag == 1 && TextGraphEndFlag == 1 ){
		if( AutoCount % StopSpeed == 0 ){
			TextCount += LineNo[SceneCount][SerifCount];
			SerifCount++;
			TextGraphEndFlag =  0;
			//User.SetSaveData(SceneCount,TextCount,SerifCount);
		}
		AutoCount++;
	}
}

/*アイキャッチ*/
 void TextClass::EyeCatching(UserClass &User){
	MouseClass* Mouse = MouseClass::GetInstance();

	const int MinVol    = 9000;
	const int FadeSpeed = 7;

	//static bool SoundBack  = FALSE;
	static bool FirstFlag  = FALSE;
	static bool PlayFlag   = FALSE;
	static bool FadeFlag1  = FALSE;
	static bool FadeFlag2  = TRUE;
	static int FadeCount   = 255;
	static int MovieVol;
	static int MovieHandle;
	static int TmpSoundCode;


	//音量取得
	MovieVol = User.GetBGMVol() * 4;

	//現在のサウンドコードのバックアップ
	//if( SoundBack == FALSE ){
	//	TmpSoundCode = User.GetBGMCode();
	//	SoundBack = TRUE;
	//}

	//音楽停止 
	User.SetBGMCode( GAME_BGM::STOP );

	//フェードアウト処理
	if( FadeFlag1 == FALSE && FadeFlag2 == TRUE ){
		SetDrawBright(FadeCount,FadeCount,FadeCount);
		FadeCount -= FadeSpeed;
		if( FadeCount <= 0 ) FadeFlag1 = TRUE;
	}

	//再生前の初期化
	if( FirstFlag == FALSE && FadeFlag1 == TRUE ){
		SetDrawBright(255,255,255);
		MovieHandle = LoadGraph("./resource/movie/eyecatch.ogv");
		SetMovieVolumeToGraph( MinVol + MovieVol , MovieHandle );
		PlayMovieToGraph( MovieHandle );
		FirstFlag = TRUE;
		PlayFlag  = TRUE;
	}

	//動画再生
	if( PlayFlag == TRUE ){
		DrawGraph(0,0,MovieHandle,TRUE);
		WaitTimer(17);
	}

	//再生中か判断
	if( GetMovieStateToGraph(MovieHandle) != 1 && FadeFlag1 == TRUE ){
		PlayFlag  = FALSE;
		FirstFlag = FALSE;
		FadeFlag1 = FALSE;
		FadeFlag2 = FALSE;
	}

	//フェードイン
	if( FadeFlag2 == FALSE ){
		SetDrawBright(FadeCount,FadeCount,FadeCount);
		FadeCount += FadeSpeed;
		if( FadeCount >= 255 ){
			FadeFlag2 = TRUE;
			//SoundBack = FALSE;
			//User.SetBGMCode( TmpSoundCode );
			WriteMode = NORMAL;
		}
	}


	//メッセージ描画
	//DrawString(300,windowY - windowY / 3 + 50,"アイキャッチだよ、クリックで進むよっ！",GetColor(0,0,0));

	//if( Mouse->GetState(MOUSE::LEFT) == 1 ){
	//	WriteMode = NORMAL;
	//}
}

/*バックログ*/
void TextClass::BackLogMain(UserClass &User){
	MouseClass* Mouse = MouseClass::GetInstance();
	static BackLogClass BackLog;
	
	//いろいろ宣言
	static int Count = 0;
	static int Flag  = 0;
	static int End1  = 0;
	static int End2  = 0;
	const  int Stop  = 10;
	const  int END_FLAG = -100000000;
	
	//10フレーム停止する
	if( Count > Stop ){
		if( Flag == 0 ){
			BackLog.Update(LineNo[SceneCount],SerifCount);
			Flag = 1;
		}
		End1 = BackLog.DrawLog(Name[SceneCount],Text[SceneCount]);
		//前のシーンにジャンプ
		End2 = BackLog.Jump(TextCount,SerifCount,User);
	}
	Count++;

	//バックログから戻る
	if( End1 == END_FLAG || End2 == END_FLAG ){
		if( End2 == END_FLAG ) BackCheckControlCode(User);
		WriteMode = NORMAL;
		Flag      = 0;
	}


}

/*デバッグ用既読操作*/
void TextClass::ControlRead(){
	/*
	MouseClass* Mouse = MouseClass::GetInstance();
	FILE *fp;
	short int WriteData[2] = {10,10};

	//デバッグ用既読データ削除処理
	if( Mouse->GetState(MOUSE::LEFT) ){

		//削除
		if( Select == 3 ){
			fp = fopen("./resource/data/read.dat","wb+");
			WriteData[0] = SceneCount;
			WriteData[1] = TextCount;
			fwrite(WriteData,2,sizeof(short int),fp);
			fclose(fp);
		}

		//埋める
		if( Select == 4 ){
			fp = fopen("./resource/data/read.dat","wb+");
			fwrite(WriteData,2,sizeof(short int),fp);
			fclose(fp);
		}
	}*/
}
			
/*コンフィグの未読スキップ許可設定*/
void TextClass::ReadUpdate(UserClass &User){
	short int WriteData[2];
	FILE *fp;

	int SkipFlag;

	//スキップフラグを取得
	SkipFlag = User.GetSkipFlag();

	//許可
	if( SkipFlag == 0 ){
		SkipPermitFlag = 1;
		//fp = fopen("./resource/data/read.dat","wb+");
		//WriteData[0] = 999;
		//WriteData[1] = 999;
		//fwrite(WriteData,2,sizeof(short int),fp);
		//fclose(fp);
	}


	//禁止
	if( SkipFlag == 1 ){
		SkipPermitFlag = 0;
	/*	fp = fopen("./resource/data/read.dat","wb+");
		WriteData[0] = SceneCount;
		WriteData[1] = TextCount;
		fwrite(WriteData,2,sizeof(short int),fp);
		fclose(fp);*/
	}
}

/*ウィンドウ非表示*/
void TextClass::NotWindow(){
	auto Mouse = MouseClass::GetInstance();

	//タイマー
	static int Timer = 0;

	Timer++;

	if( Mouse->GetState( MOUSE::RIGHT ) > 0 && Timer > 20 ){
		WriteMode = NORMAL;
		Timer = 0;
	}
}

/*時間が経ったように見せる*/
void TextClass::OverTime(UserClass &User){

	//各種変数宣言
	static int TmpMode;					//前回のモード
	static int FirstFlag;				//初めの一回だけ実行するためのフラグ
	std::string EventCode;				//イベントコードを格納

	static int  Count		= 255;		//明るさを変えるカウンタ
	static int  Timer		= 0;		//タイマー
	static bool BlackFlag	= FALSE;	//暗くなったら立つ
	static bool WhiteFlag	= FALSE;	//明るくなったら立つ
	static bool StopFlag    = FALSE;	//停止するフラグ
			
	//初回のみ実行
	if( FirstFlag == FALSE ){
		TmpMode   = WriteMode;
		FirstFlag = TRUE;
		WriteMode = CHANGE;
	}

	//イベントコード受け取り
	EventCode = Text[SceneCount][TextCount];

	//コードが「経過」なら
	if( EventCode == "経過" ){
			
			//画面の明るさを変更
			SetDrawBright(Count,Count,Count);

			//明るいならカウント下げ、暗いならカウント上げ
			if( BlackFlag == FALSE ) Count-=5;
			else					 Count+=5;

			//限界まで達したら各種フラグを立てる
			if( Count < 0   )		 StopFlag  = TRUE;
			if( Count > 255 )		 WhiteFlag = TRUE;

			//停止フラグが立ってるならタイマー加算
			if( StopFlag == TRUE ) Timer++;

			//30フレーム以上なら
			if( Timer > 30 ){
				Timer	  = 0;
				StopFlag  = FALSE;
				BlackFlag = TRUE;
			}

			//全ての処理が終わったらなら、各変数初期化
			if( WhiteFlag == TRUE ){
				Count = 255;
				Timer = 0;
				BlackFlag = FALSE;
				WhiteFlag = FALSE;
				StopFlag  = FALSE;
				FirstFlag = FALSE;

				TextCount++;
				SerifCount++;
				WriteMode = TmpMode;
			}
		
		}
}

/*ゲームオーバー*/
void TextClass::GameEnd(UserClass &User){
	//定数
	const int DrawX = 250;
	const int DrawY = windowY - windowY / 3 + 10;
	


	//DrawStringToHandle(DrawX,DrawY,"ゲームオーバーだじょ、長め左クリックでタイトル戻るよ！",GetColor(0,0,0),TextFontHandle);
}

/*現在のデータをセット*/
void TextClass::SetGameData(UserClass &User){
	//時間関係
	time_t now;
	struct tm *Date;

	time(&now);
	Date = localtime(&now);
	
	SaveData.SceneCount = SceneCount;
	SaveData.TextCount  = TextCount;
	SaveData.SerifCount = SerifCount;
	SaveData.BGMCode    = User.GetBGMCode();
	SaveData.BackCode   = User.GetBackCode();
	SaveData.CharCode	= User.GetCharacterCode();
	SaveData.Year		= Date->tm_year+1900;
	SaveData.Mon		= Date->tm_mon+1;
	SaveData.Day		= Date->tm_mday;
	SaveData.TextLength = Text[SceneCount][TextCount].size();
	strcpy(SaveData.Text,Text[SceneCount][TextCount].c_str());

	//現在カウントを更新
	User.SetSaveData(SaveData);
}
	
/*制御コードチェック*/
void TextClass::CheckCotrolCode(UserClass &User){
	//各種コード受け取り変数
	std::string BGMCode;
	std::string BackCode;
	std::string EventCode;
	std::string CharacterCode;

	bool EventFlag = FALSE;

	do{
	
		EventFlag = FALSE;


		//音楽制御
		if( Name[SceneCount][TextCount] == "音楽" ){
			//BGMコード受け取り
			BGMCode = Text[SceneCount][TextCount];
			if( BGMCode == "回想" )   User.SetBGMCode( GAME_BGM::KAISOU1 );
			if( BGMCode == "出会い" ) User.SetBGMCode( GAME_BGM::DEAI );
			if( BGMCode == "別れ" )   User.SetBGMCode( GAME_BGM::WAKARE );
			if( BGMCode == "無音" )   User.SetBGMCode( GAME_BGM::STOP );
			if( BGMCode == "残響" )	  User.SetBGMCode( GAME_BGM::TITLE);
			TextCount++;
			SerifCount++;
			EventFlag = TRUE;
		}

	
		//背景画像制御
		if( Name[SceneCount][TextCount] == "背景" ){
			//背景コード受け取り
			BackCode = Text[SceneCount][TextCount];
			if( BackCode == "暗闇" ) User.SetBackCode( GAME_BACK::BLACK  );
			if( BackCode == "川原" ) User.SetBackCode( GAME_BACK::KAWARA );
			if( BackCode == "夜空" ) User.SetBackCode( GAME_BACK::YOZORA );
			TextCount++;
			SerifCount++;
			EventFlag = TRUE;
		}
		
		//キャラクタ画像制御
		if( Name[SceneCount][TextCount] == "キャラ" ){
			//キャラクタコード受け取り
			CharacterCode = Text[SceneCount][TextCount];
			if( CharacterCode == "藍"     ) User.SetCharacterCode( GAME_CHAR::AI );
			if( CharacterCode == "非表示" )	User.SetCharacterCode( GAME_CHAR::NOT );
			TextCount++;
			SerifCount++;
			EventFlag = TRUE;
		}

		//時間経過
		if( Name[SceneCount][TextCount] == "イベント" ){
			EventCode = Text[SceneCount][TextCount];
			if( EventCode == "経過"       ) OverTime(User);
			if( EventCode == "タイトルへ" ) WriteMode = TITLE;
		}
	
		//エンド
		if( Name[SceneCount][TextCount] == "エンド" ){
			TextCount++;
			SerifCount++;
			WriteMode = END;
		}

	}while( EventFlag == TRUE );
}

/*バックログから戻ったときに前の制御コードを取得*/
void TextClass::BackCheckControlCode(UserClass &User){
	int TmpSceneCount,TmpTextCount;
	bool BGMFlag  = FALSE;
	bool BackFlag = FALSE;
	bool CharFlag = FALSE;
	std::string BGMCode;
	std::string BackCode;
	std::string CharacterCode;

	TmpSceneCount = SceneCount;
	TmpTextCount  = TextCount;
	
	//曲をいったん停止
	User.SetBGMCode( GAME_BGM::STOP );
	User.SetCharacterCode( GAME_CHAR::NOT );

	while( TmpTextCount >= 0 ){
		//音楽制御
		if( Name[TmpSceneCount][TmpTextCount] == "音楽" && BGMFlag == FALSE){
			//BGMコード受け取り
			BGMCode = Text[TmpSceneCount][TmpTextCount];
			if( BGMCode == "回想" )   User.SetBGMCode( GAME_BGM::KAISOU1 );
			if( BGMCode == "出会い" ) User.SetBGMCode( GAME_BGM::DEAI );
			if( BGMCode == "別れ" )   User.SetBGMCode( GAME_BGM::WAKARE );
			if( BGMCode == "無音" )   User.SetBGMCode( GAME_BGM::STOP );
			if( BGMCode == "残響" )	  User.SetBGMCode( GAME_BGM::TITLE);
			BGMFlag = TRUE;
		}
	
		//背景画像制御
		if( Name[TmpSceneCount][TmpTextCount] == "背景" && BackFlag == FALSE ){
			//背景コード受け取り
			BackCode = Text[TmpSceneCount][TmpTextCount];
			if( BackCode == "暗闇" ) User.SetBackCode( GAME_BACK::BLACK  );
			if( BackCode == "川原" ) User.SetBackCode( GAME_BACK::KAWARA );
			BackFlag = TRUE;
		}
		
		//キャラクタ画像制御
		if( Name[TmpSceneCount][TmpTextCount] == "キャラ"  && CharFlag == FALSE ){
			//キャラクタコード受け取り
			CharacterCode = Text[TmpSceneCount][TmpTextCount];
			if( CharacterCode == "藍"     ) User.SetCharacterCode( GAME_CHAR::AI );
			if( CharacterCode == "非表示" )	User.SetCharacterCode( GAME_CHAR::NOT );
			CharFlag = TRUE;
		}
		
		//カウントを下げる
		TmpTextCount--;
		
		//もしテキストカウントが0を下回ったら各コードを初期化
		if( TmpTextCount < 0 ){
			if( BGMFlag  == FALSE ) User.SetBGMCode( GAME_BGM::STOP );
			if( BackFlag == FALSE ) User.SetBackCode( GAME_BACK::BLACK );
			if( CharFlag == FALSE ) User.SetCharacterCode( GAME_CHAR::NOT );
		}
		
		//全てのコードが確認されたら処理を抜ける
		if( BGMFlag == TRUE && BackFlag == TRUE && CharFlag == TRUE  ) break;

	}
}