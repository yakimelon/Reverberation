/*----------------------
 | セーブ画面制御クラス |
  ----------------------*/
class SaveClass{
	protected:
		//セーブデータ一覧(構造体にできそう？)
		int		   SaveHash[3][10];				//ハッシュ
		short int  SaveCount[3][10][3];			//データ受け取り配列(シーンカウント、ゲームカウント)
		int        SaveCode[3][10][3];			//データ受け取り配列(BGM,Back)								
		int		   SaveDate[3][10][3];			//日付配列(年,月,日)
		int		   SaveTextLength[3][10][1];	//一行テキスト文字数
		size_t	   TextSize;					//テキストサイズをsize_t型にキャストする
		char       SaveText[3][10][101];		//一行テキスト	
		int		   Hash;						//ハッシュ値

		int  Select;							//選択番号
		int  Page;								//ページ番号
		int  FadeFlag;							//フェードフラグ
		int  ClickFlag;							//セーブデータクリックフラグ

		bool LoadFlag;							//セーブデータ読み込みフラグ


		//ダイアログ関係
		bool SaveDialogFlag;
		bool MenuDialogFlag;
		bool DeleteDialogFlag;

		//ロードデータ
		struct SaveData_rec LoadData;

		//メニューパラメータ
		struct MenuArg_rec SaveLeftParam;		//左側のセーブデータ
		struct MenuArg_rec SaveRightParam;		//右側のセーブデータ
		struct MenuArg_rec SaveNaviParam;		//ナビゲーション
		
		//メソッド
		void SetMenuParam();					//メニューパラメータセット

	public:	
		SaveClass();													//初期化
		void Draw(int &Select);											//データ描画処理
		void Save(UserClass &User);										//データセーブ
		void Load(int &ModeFlag,UserClass &User);						//データロード
		void Delete(UserClass &User);									//データ削除
		int  YesNoBox(int ModeFlag);									//確認ボックス

		void Main(int &ChangeFlag);										//メイン関数
		void ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User);	//モードチェンジ
		void GetSaveData();												//セーブデータ取得
		void ChangePage();												//セーブのページ変更
		
		SaveGraphClass Graph;											//セーブグラフィック制御
};