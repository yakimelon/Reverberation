#include"../header/define.h"

/*メニューパラメータセット　―タイトル画面―*/
void SetMenuParam_Title(MenuArg_rec &MenuArg,bool SecretFlag){
	char TmpText[5][32] = {
		"最初から始める","続きから始める","？？？","設定","ばいばい"
	};
	
	if( SecretFlag == TRUE ) strcpy(TmpText[2],"おまけ");

	MenuArg.DrawX			= 950;
	MenuArg.DrawY			= 125;
	MenuArg.Interval		= 70;
	MenuArg.Width			= 30;
	MenuArg.Height			= 30;
	MenuArg.ListMin			= 1;
	MenuArg.ListMax			= 6;
	MenuArg.AtherNo			= 0;
	MenuArg.AlphaNo			= 50;
	MenuArg.DrawFlag		= MENU::TEXT;
	MenuArg.DirectionFlag	= MENU::COL;
	
	for( int i=0 ; i<5 ; i++ ) {
		strcpy(MenuArg.DrawText[i],TmpText[i]);
	}

	MenuArg.TextColor  = GetColor(0,0,0);
	MenuArg.FontFamily = MENU::GOSIC;

}

/*メニューパラメータセット　―ゲーム画面―*/
void SetMenuParam_GameRight(MenuArg_rec &MenuArg){
	char TmpText[6][32] = {
		"Save","Load","Auto","Backlog","Config"
	};
	
	MenuArg.DrawX			= windowX-100;
	MenuArg.DrawY			= windowY-200;
	MenuArg.Interval		= 5;
	MenuArg.Width			= 28;
	MenuArg.Height			= 28;
	MenuArg.ListMin			= 0;
	MenuArg.ListMax			= 6;
	MenuArg.AtherNo			= 6;
	MenuArg.AlphaNo			= 100;
	MenuArg.DrawFlag		= MENU::TEXT;
	MenuArg.DirectionFlag	= MENU::COL;
	
	for( int i=0 ; i<6 ; i++ ) {
		strcpy(MenuArg.DrawText[i],TmpText[i]);
	}

	MenuArg.TextColor  = GetColor(255,255,255);
	MenuArg.FontFamily = MENU::GOSIC;

}
