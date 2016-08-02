#define GLOBAL_INSTANCE
#include"../header/define.h"
 
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	//変数宣言
	bool EndFlag = 0;
	
	//ウィンドウ設定
	SetOutApplicationLogValidFlag(FALSE);			//ログを出力しない
	ChangeWindowMode(TRUE);							//ウィンドウモード変更
	SetGraphMode(1280,720,32);						//ウィンドウサイズ指定
	SetWindowText("夜空の贈り物 ver1.01");			//ウィンドウタイトル変更
	DxLib_Init();									//DXライブラリ初期化

	//初期設定
	SetUseDXArchiveFlag( TRUE );					//アーカイブファイル使用
	SetDXArchiveExtension("kws");					//拡張子変更
	SetDrawScreen( DX_SCREEN_BACK );				//裏画面設定
	GetClientRect(GetMainWindowHandle(),&rect);		//ウィンドウサイズ取得
	//SetAlwaysRunFlag(TRUE);							//非アクティブでも実行
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);	//きれいなフォント
	SetBackgroundColor(255,255,255);

	//フォントサイズ設定
	MenuFontHandle = CreateFontToHandle( NULL , 36 , -1 , DX_FONTTYPE_ANTIALIASING );
	TextFontHandle = CreateFontToHandle( NULL , 28 , -1 , DX_FONTTYPE_ANTIALIASING );

	//インスタンス化
	UserClass		 User;							//ユーザ情報クラス
	TitlePageClass*	 TitlePage  = new TitlePageClass;	//タイトルページクラス
	GamePageClass*   GamePage   = new GamePageClass;	//ゲームページクラス
	SecretPageClass* SecretPage = new SecretPageClass;	//おまけページクラス

	//コンフィグ情報をロード
	User.LoadConfigData();

	//メインループ
	while( ProcessLoop() == 0 && EndFlag != TRUE ){

		switch( User.GetPage() ){
			//タイトルページ
			case PAGE::TITLE:
				TitlePage->Main(User);
			break;

			//ゲームページ
			case PAGE::GAME:
				GamePage->Main(User);
			break;

			//おまけモード
			case PAGE::SECRET:
				SecretPage->Main(User);
			break;

			//ゲーム終了
			case PAGE::END:
				EndFlag = TRUE;
			break;
		}

	}

	//コンフィグデータセーブ
	User.SaveConfigData();

	delete TitlePage;
	delete GamePage;
	delete SecretPage;

	DxLib_End();

	return 0;
}