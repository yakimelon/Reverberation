/*--------------------------
 | ページクラス(抽象クラス) |
  --------------------------*/
class PageClass{
	protected:
		int ModeFlag;											//動作モード(Main･Load･Confの三種類)
		int ChangeFlag;											//モードが変わったときに立つ

	public:
		void MovePage(int select,int FadeFlag,UserClass &User);	//ページ遷移処理
		void SetMode(int Mode,int FadeFlag);					//モードセット
		int  GetMode();											//現在モード取得
		SaveClass		Save;									//セーブクラスインスタンス(集約-分解構造)
		ConfigClass		Conf;									//コンフィグクラスインスタンス
};


/*----------------------
 | タイトルページクラス |
  ----------------------*/
class TitlePageClass : public PageClass{
	public:
		TitlePageClass();					//初期化
		void Main(UserClass &User);			//タイトルページの入り口
		TitleClass      Title;				//タイトルクラスインスタンス(集約-分解構造)
		TitleSoundClass Sound;				//タイトルサウンドクラス
};

/*--------------------
 | ゲームページクラス |
  --------------------*/
class GamePageClass : public PageClass{
	public:
		GamePageClass();					//初期化
		void Main(UserClass &User);			//ゲームページの入り口
		TextClass		Text;				//テキストクラス(集約-分解構造)	
		GameSoundClass  Sound;				//ゲームサウンドクラス			
		EndingClass     Ending;				//エンディングクラス
};

/*--------------------------
 | シークレットページクラス |
  --------------------------*/
class SecretPageClass : public PageClass{
	public:
		void Main(UserClass &User);	//メイン関数
		SecretClass Secret;
};
