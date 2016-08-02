#include"../header/define.h" 

/*----------------
 | サウンドクラス |
  ----------------*/
/*メンバ変数初期化*/
void SoundClass::VarInit(){
	PlayFlag    = STOP;
	NowPlayCode = 0;
}

/*音量セット*/
void SoundClass::SetVol(UserClass &User){
	BGMVol = User.GetBGMVol();
	SEVol  = User.GetSEVol();
}


/*------------------------
 | タイトルサウンドクラス |
  ------------------------*/
/*初期化*/
TitleSoundClass::TitleSoundClass(){
	VarInit();	//メンバ変数初期化
	Load();		//音楽データロード
}

/*音楽ロード*/
void TitleSoundClass::Load(){
	//音楽データロード
	TitleBGM  = LoadSoundMem("./resource/sound/bgm/TitleBGM.ogg");
}

/*音楽再生*/
void TitleSoundClass::PlayMusic(UserClass &User){
	ChangeVolumeSoundMem(BGMVol,TitleBGM);
	//再生フラグが立っていないならば、音楽再生
	if( PlayFlag == STOP ){
		PlayFlag = PLAY;
		//音量変更
		PlaySoundMem(TitleBGM,DX_PLAYTYPE_LOOP);
	}
}

/*音楽停止*/
void TitleSoundClass::StopBGM(){
	StopSoundMem(TitleBGM);
	PlayFlag = STOP;
}


/*----------------------
 | ゲームサウンドクラス |
  ----------------------*/
/*初期化*/
GameSoundClass::GameSoundClass(){
	VarInit();
	Load();
}

/*音楽ロード*/
void GameSoundClass::Load(){
	//音楽データロード
	GameBGM.push_back( LoadSoundMem("./resource/sound/bgm/kaisou.ogg") );
	GameBGM.push_back( LoadSoundMem("./resource/sound/bgm/kaisou2.ogg") );
	GameBGM.push_back( LoadSoundMem("./resource/sound/bgm/deai.ogg") );
	GameBGM.push_back( LoadSoundMem("./resource/sound/bgm/wakare.ogg") );	
	GameBGM.push_back( LoadSoundMem("./resource/sound/bgm/TitleBGM.ogg") );
}

/*音楽再生*/
void GameSoundClass::PlayMusic(UserClass &User){
	static bool KaisouFlag = FALSE;

	//音量設定
	for( int i=0 ; i<5 ; i++ ) ChangeVolumeSoundMem(BGMVol,GameBGM[i]);


	//曲が変わった
	if( NowPlayCode != User.GetBGMCode() ){
		for( int i=0 ; i<5 ; i++ ) StopSoundMem(GameBGM[i]);
		NowPlayCode = User.GetBGMCode();
		PlayFlag    = STOP;
		KaisouFlag  = FALSE;
	}

	//再生フラグが立っていなければ、音楽再生
	if( PlayFlag == STOP ){

		PlayFlag = PLAY;	//再生フラグを立てる

		switch( NowPlayCode ){
			//回想1ループ目
			case GAME_BGM::KAISOU1:
				PlaySoundMem(GameBGM[GAME_BGM::KAISOU1],DX_PLAYTYPE_BACK);
				KaisouFlag = TRUE;
			break;

			//回想2ループ目以降
			case GAME_BGM::KAISOU2:
				PlaySoundMem(GameBGM[GAME_BGM::KAISOU2],DX_PLAYTYPE_LOOP);
			break;

			//出会い
			case GAME_BGM::DEAI:
				PlaySoundMem(GameBGM[GAME_BGM::DEAI],DX_PLAYTYPE_LOOP);
			break;

			//別れ
			case GAME_BGM::WAKARE:
				PlaySoundMem(GameBGM[GAME_BGM::WAKARE],DX_PLAYTYPE_LOOP);
			break;

			//残響
			case GAME_BGM::TITLE:
				PlaySoundMem(GameBGM[GAME_BGM::TITLE],DX_PLAYTYPE_LOOP);
			break;

			//音楽停止
			case GAME_BGM::STOP:
			break;

		}
	}

	//回想1ループ目が終わったら2ループ目にチェンジ
	if( NowPlayCode == GAME_BGM::KAISOU1 && CheckSoundMem( GameBGM[GAME_BGM::KAISOU1] ) == 0 && KaisouFlag == TRUE ){
		PlaySoundMem(GameBGM[GAME_BGM::KAISOU2],DX_PLAYTYPE_LOOP);
		KaisouFlag = FALSE;
	}

}

/*音楽停止*/
void GameSoundClass::StopBGM(){
	for( int i=0 ; i<5 ; i++ ) StopSoundMem(GameBGM[i]);
	PlayFlag = STOP;
}

/*--------------------------
 | システムエフェクトクラス |
  --------------------------*/
/*初期化*/
SESoundClass::SESoundClass(){
	VarInit();
	Load();
}

/*音楽ロード*/
void SESoundClass::Load(){
	DialogSE  = LoadSoundMem("./resource/sound/se/dialog.ogg");
	EnterSE   = LoadSoundMem("./resource/sound/se/enter.ogg");
	CancelSE  = LoadSoundMem("./resource/sound/se/cancel.ogg");
}

/*音楽再生*/
void SESoundClass::PlayMusic(int Code){
	ChangeVolumeSoundMem(SEVol,DialogSE);
	ChangeVolumeSoundMem(SEVol,EnterSE);
	ChangeVolumeSoundMem(SEVol,CancelSE);
	if( Code == DIALOG ){
		PlaySoundMem(DialogSE,DX_PLAYTYPE_BACK);
	}
	if( Code == ENTER  ){
		PlaySoundMem(EnterSE,DX_PLAYTYPE_BACK);
	}
	if( Code == CANCEL ){
		PlaySoundMem(CancelSE,DX_PLAYTYPE_BACK);
	}
}

/*ダミー処理*/
void SESoundClass::PlayMusic(UserClass &User){
}

/*音楽停止*/
void SESoundClass::StopBGM(){
}

/*----------------------------
 | シークレットサウンドクラス |
  ----------------------------*/
/*初期化*/
SecretSoundClass::SecretSoundClass(){
	VarInit();
	Load();
}

/*音楽ロード*/
void SecretSoundClass::Load(){
	TitleBGM   = LoadSoundMem("./resource/sound/bgm/TitleBGM.ogg");
	kaisouBGM  = LoadSoundMem("./resource/sound/bgm/prologue.ogg");
	kaisou2BGM = LoadSoundMem("./resource/sound/bgm/kaisou2.ogg");
	DeaiBGM    = LoadSoundMem("./resource/sound/bgm/deai.ogg");
	WakareBGM  = LoadSoundMem("./resource/sound/bgm/wakare.ogg");
	EndingBGM  = LoadSoundMem("./resource/sound/bgm/Ending.ogg");
}

/*音楽再生(ダミー)*/
void SecretSoundClass::PlayMusic(UserClass &User){
}

/*音楽再生*/
void SecretSoundClass::PlayMusic(int Code){
	static bool KaisouFlag = TRUE;

	ChangeVolumeSoundMem(BGMVol,TitleBGM);
	ChangeVolumeSoundMem(BGMVol,kaisouBGM);
	ChangeVolumeSoundMem(BGMVol,kaisou2BGM);
	ChangeVolumeSoundMem(BGMVol,DeaiBGM);
	ChangeVolumeSoundMem(BGMVol,WakareBGM);
	ChangeVolumeSoundMem(BGMVol+50,EndingBGM);

	static int OldCode = -1;

	//曲が変わったら再生フラグを折る
	if( OldCode != Code ) PlayFlag = STOP;
	OldCode = Code;

	//曲を全て停止させる
	if( PlayFlag == STOP ) StopBGM();

	//再生フラグが立っていないならば、音楽再生
	if( PlayFlag == STOP ){
		if( Code == TITLE )  PlaySoundMem(TitleBGM,DX_PLAYTYPE_LOOP);
		if( Code == KAISOU ) PlaySoundMem(kaisouBGM,DX_PLAYTYPE_LOOP);
		if( Code == DEAI )   PlaySoundMem(DeaiBGM,DX_PLAYTYPE_LOOP);
		if( Code == WAKARE ) PlaySoundMem(WakareBGM,DX_PLAYTYPE_LOOP);
		if( Code == ENDING ) PlaySoundMem(EndingBGM,DX_PLAYTYPE_LOOP);

		PlayFlag = PLAY;
	}

	//if( CheckSoundMem( kaisouBGM ) == 0 && Code == KAISOU ){
	//	PlaySoundMem(kaisou2BGM,DX_PLAYTYPE_LOOP);
	//}

}

/*音楽停止*/
void SecretSoundClass::StopBGM(){
	StopSoundMem(TitleBGM);
	StopSoundMem(kaisouBGM);
	StopSoundMem(kaisou2BGM);
	StopSoundMem(DeaiBGM);
	StopSoundMem(WakareBGM);
	StopSoundMem(EndingBGM);
}
