#include"../header/define.h" 

/*--------------------
 | シークレットクラス |
  --------------------*/
/*初期化*/
SecretClass::SecretClass(){
	Select = -1;
	SetNo  = 5;

	//パラメータセット
	SetMenuParam();
}

/*メニューパラメータセット*/
void SecretClass::SetMenuParam(){
	char TmpText[6][32] = {
		"タイトルの曲","回想の曲","出会いの曲","別れの曲","エンディング","戻る"
	};
	
	MusicListParam.DrawX			= 150;
	MusicListParam.DrawY			= 95;
	MusicListParam.Interval			= 70;
	MusicListParam.Width			= 30;
	MusicListParam.Height			= 30;
	MusicListParam.ListMin			= 0;
	MusicListParam.ListMax			= 6;
	MusicListParam.AtherNo			= -1;
	MusicListParam.AlphaNo			= 50;
	MusicListParam.DrawFlag			= MENU::TEXT;
	MusicListParam.DirectionFlag	= MENU::COL;
	
	for( int i=0 ; i<6 ; i++ ) {
		strcpy(MusicListParam.DrawText[i],TmpText[i]);
	}

	MusicListParam.TextColor  = GetColor(255,255,255);
	MusicListParam.FontFamily = MENU::GOSIC;
}

/*描画テキストセット*/
void SecretClass::SetText(){	
	int  FileHandle;
	int  TitleCount = 0;
	int  TextCount  = 0;
	char TmpBuf[256];
	
	const int TitleMax       = 6;
	const int TextMax        = 19;
	const int LoadTextLength = 256;

	//配列領域確保
	ShowText.resize(TitleMax);
	for( int i=0 ; i<TitleMax ; i++ ) ShowText[i].resize(TextMax);
	
	//ファイル読み込み
	FileHandle = FileRead_open("./resource/story/omake.txt");

	//テキスト取得
	while( FileRead_eof(FileHandle) == 0 ){
		FileRead_gets(TmpBuf,LoadTextLength,FileHandle);
 		ShowText[TitleCount][TextCount] = TmpBuf;
		
		//カウントアップ
		TextCount++;
		if( TextCount > TextMax-1 ){
			TitleCount++;
			TextCount = 0;
		}
	}

}

/*メイン関数*/
void SecretClass::Main(UserClass& User,int &ChangeFlag){
	auto *Mouse = MouseClass::GetInstance();
	static SecretMenuClass MusicList(MusicListParam);

	int TitleDrawY = 0;

	const int DrawStringX = 520;
	const int DrawStringY = 150;
	const int LineHeight  = 30;
	const int FontSize    = 22;

	//描画テキストセット
	SetText();

	//モードチェンジしたとき、初期化
	if( ChangeFlag == TRUE ){
		ChangeFlag = FALSE;					//モードチェンジフラグを折る
		FadeFlag   = FALSE;					//フェード完了フラグを折る
		Graph.Anime.Reset();				//アニメーションリセット
	}

	//背景描画
	Graph.DrawBack();

	//曲一覧描画
	MusicList.Select();
	MusicList.Draw(SetNo);


	//選択番号取得
	Select = MusicList.GetSelectNo();

	SetFontSize(22);

	//説明文描画
	for( int i=0 ; i<19 ; i++ ){
		if( i == 0 ) TitleDrawY = -50;
		else		 TitleDrawY = 0;

		DrawStringShadow(DrawStringX,DrawStringY+LineHeight*i+TitleDrawY,ShowText[SetNo][i],GetColor(255,255,255),GetColor(0,0,0));
	}

	//クリックされたら音楽再生
	if( Mouse->GetState(MOUSE::LEFT) > 0  ){
		Sound.SetVol( User );
		Sound.PlayMusic( Select );
		SetNo = Select;

		if( Select == 5 ) User.SetPage( PAGE::TITLE );
	}

	if( SetNo < 0 ) SetNo = 5;
	//DrawStringShadow(DrawStringX,DrawStringY+200,"１２３４５６７８９０１２３４５６７８９０１２３４５６７８９０",GetColor(255,255,255),GetColor(0,0,0));

	//DrawStringShadow(10,10,"シークレットモードへようこそ ―",GetColor(0,0,0),GetColor(150,150,150));
}

