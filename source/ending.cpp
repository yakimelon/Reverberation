#include"../header/define.h"

/*--------------------
 | エンディングクラス |
  --------------------*/
/*初期化*/
EndingClass::EndingClass(){
	PlayFlag    = FALSE;
}

/*動画再生*/
void EndingClass::StartMovie(UserClass &User){
	static bool FirstFlag = FALSE;
	int MovieVol;

	const int MinVol = 9000;

	//音量取得
	MovieVol = User.GetBGMVol() * 4;

	//再生前の初期化
	if( FirstFlag == FALSE ){
		MovieHandle = LoadGraph("./resource/movie/Ending.ogv");
		SetMovieVolumeToGraph( MinVol + MovieVol,MovieHandle) ;
		PlayMovieToGraph( MovieHandle );
		FirstFlag  = TRUE;
		PlayFlag  = TRUE;
	}

	//動画再生
	if( PlayFlag == TRUE ){
		DrawGraph(0,0,MovieHandle,TRUE);
		WaitTimer(17);
	}

	//再生中か判断
	if( GetMovieStateToGraph(MovieHandle) != 1 ){
		PlayFlag  = FALSE;
		FirstFlag = FALSE;
	}
}

/*セーブエンディング*/
void EndingClass::SaveEnd(){
	FILE *fp;

	const int EndKey = 831;

	fp = fopen("./resource/data/syslog.dat","wb+");
	fwrite(&EndKey,1,sizeof(int),fp);
	fclose(fp);

}

/*タイトルに戻る*/
void EndingClass::BackTitle(UserClass &User,int &ModeFlag){
	if( PlayFlag == FALSE ){
		ModeFlag = MODE::MAIN;
		//User.SetPage(PAGE::TITLE);
	}
}

/*メイン*/
void EndingClass::Main(UserClass &User,int &ModeFlag){
	//動画再生
	StartMovie(User);
	
	//終了したことを記録
	SaveEnd();

	//エンディング後、タイトルに戻る
	BackTitle(User,ModeFlag);
}



