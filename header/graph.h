/*--------------------------------
 | グラフィッククラス(抽象クラス) |
  --------------------------------*/
class GraphClass{
	protected:
		virtual void Load()=0;		//画像ロード
		virtual void SetPoint()=0;	//描画座標セット

	public:			
		virtual void Draw()=0;		//画像描画
		AnimeClass Anime;			//アニメインスタンス(集約-分解構造)
};

 
/*----------------------------
 | タイトルグラフィッククラス |
  ----------------------------*/
class TitleGraphClass : public GraphClass{
	private:
		//画像ハンドル
		int  TitleBackHandle;	//背景画像
		
		//描画座標
		int  TitleBackPoint[2];	//背景画像描画座標
		
		//メソッド
		void Load();			//画像ロード
		void SetPoint();		//描画座標セット

	public:
		TitleGraphClass();		//初期化
		void Draw();			//画像描画
};

/*--------------------------
 | セーブグラフィッククラス |
  --------------------------*/
class SaveGraphClass : public GraphClass{
	private:
		//画像ハンドル
		int BackgroundHandle;	//背景画像

		//描画座標
		int BackgroundPoint[2];	//背景画像

		//メソッド　
		void Load();			//画像ロード
		void SetPoint();		//画像座標セット
	
	public:
		SaveGraphClass();		//初期化
		void Draw();			//画像描画

};

/*----------------------------
 | テキストグラフィッククラス |
  ----------------------------*/
class TextGraphClass : public GraphClass{
	private:
		//画像ハンドル
		vector<int> GameBackHandle;		//背景画像
		int CharacterHandle;			//キャラクタ画像
		int TextBoxHandle;				//テキストボックス
		int SelectBoxHandle;			//セレクトボックス

		//描画座標
		int GameBackPoint[2];			//背景画像
		int CharacterPoint[2];			//キャラクタ画像
		int TextBoxPoint[2];			//テキストボックス
		int SelectBoxPoint[2];			//セレクトボックス

		//メソッド
		void Load();					//画像ロード
		void SetPoint();				//画像座標セット


	public:
		TextGraphClass();				//初期化
		void Draw();					//一応ね、あとで消したい
		void DrawBack(UserClass &User);	//背景描画
		void DrawChar(UserClass &User);	//キャラクタ描画
		void DrawWindow();				//テキストウィンドウ描画
};
		
/*------------------------------
 | コンフィググラフィッククラス |
  ------------------------------*/
class ConfigGraphClass : public GraphClass{
	private:
		//定数
		enum{TEXTSPEED,AUTOSPEED,ALLVOL,BGMVOL,SEVOL};

		int SelectNo;									//選択番号
		
		//画像ハンドル
		int BackgroundHandle;							//背景画像

		//描画座標
		int BackgroundPoint[2];								//背景画像

		struct ConfigData_rec ConfigData;				//コンフィグコピー情報
		struct ConfigArg_rec  ConfigParam[6];			//コンフィグパラメータに渡す値セット
		struct MenuArg_rec    MenuParam;				//保存とかタイトルに戻るとかのメニューパラメータ

		//メソッド
		void Load();
		void SetPoint();

	public:
		ConfigGraphClass();								//初期化

		void SetMenuParam();							//メニューパラメータセット

		void Draw();									//画面描画
		int  GetSelectNo();								//選択されたメニューのナンバーを返す
		void SetConfigData(ConfigData_rec &ConfigData);	//現在設定されている項目を貰う
		ConfigData_rec GetConfigData();					//現在設定された項目を返す
};

/*--------------------------------
 | シークレットグラフィッククラス |
  --------------------------------*/
class SecretGraphClass :public GraphClass{
	private:
		//画像ハンドル
		int BackgroundHandle;	//背景画像
		int PlayButtonHandle;			//再生ボタン

		//描画座標
		int BackgroundPoint[2];	//背景画像
		int PlayButtonPoint[2];	//再生ボタン

		//メソッド　
		void Load();			//画像ロード
		void SetPoint();		//画像座標セット
	
	public:
		SecretGraphClass();		//初期化
		void Draw();			//画像描画
		void DrawBack();		//背景描画
		void DrawButton();		//ボタン描画

};