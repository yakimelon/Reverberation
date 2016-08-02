/*----------------
 | テキストクラス |
  ----------------*/
class TextClass{
	private:
		//定数
		enum{SceneMax=8,RowMax=1024};						//シーン最大数、行数最大
		enum{NORMAL,EYECATCH,BACKLOG,NOTWINDOW,CHANGE,END,TITLE}; //描画モード定数

		int  Select;										//選択メニュー
		int  MenuEnterFlag;									//メニュー決定フラグ 
		int  WriteMode;									    //描画モード格納

		short int  TextCount;								//テキストカウンタ
		short int  SceneCount;								//シーンカウンタ
		short int  SerifCount;								//セリフカウンタ

		int  SelectFlag;									//選択肢出現フラグ
		int  SkipPermitFlag;								//スキップ許可フラグ
		int  AutoFlag;										//オートフラグ　
		int  TextGraphEndFlag;								//テキスト全文描画完了フラグ

		int LineNo[64][1024];								//各セリフの行数を取得
		int LineMax[100];									//1シーンごとのテキストの総行数
		std::string Name[64][1024];							//キャラネーム変数
		std::string Text[64][1024];							//セリフテキスト変数

		//テキストメソッド
		void InitGameCount(UserClass &User);				//ゲームカウントの初期化

		//セーブデータ
		struct SaveData_rec SaveData;	

	public:
		//初期化･チェック
		TextClass();										//初期化
		void InitVar();										//変数初期化
		void LoadStory();									//ストーリーロード
		int  CutSpace(std::string &TmpText);				//テキストから全角空白を取り除く
		void CheckText(UserClass &User);					//テキストチェック
		std::vector<std::string> StringSplit(const std::string &Str,char Sep);		 //文字列分割

		//メイン関数
		void Main(UserClass &User);													//メイン関数
		void ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User);				//モードチェンジ

		//通常描画関連
		void NormalWrite(UserClass &User);					//テキスト通常描画
		void WriteText(UserClass &User);					//テキスト描画
		void WriteName();									//名前描画
		void WriteSkip();									//スキップ機能
		
		//次の行へ進める
		void PutNextLine(UserClass &User);					//次の行へ進める		
		
		//描画モード取得
		int  GetWriteMode();								//セレクトフラグ取得

		//アイキャッチ関連
		void EyeCatching(UserClass &User);					//アイキャッチ処理

		//スキップ・オート
		void SkipFunction(UserClass &User);					//スキップ処理
		void CheckRead();									//既読チェック
		void ControlRead();									//デバッグ用既読操作
		void AutoFunction(UserClass &User);					//オート処理

		//バックログ描画
		void BackLogMain(UserClass &User);					//バックログ描画

		//ウィンドウ非表示
		void NotWindow();									//ウィンドウ非表示

		//コンフィグの未読スキップ許可設定
		void ReadUpdate(UserClass &User);					//そのまま

		//時間が経過したように見せる
		void OverTime(UserClass &User);						//時間が経ったように見せる

		//ゲーム終了
		void GameEnd(UserClass &User);						//終了

		//現在のデータをセット
		void SetGameData(UserClass &User);

		//制御コードチェック
		void CheckCotrolCode(UserClass &User);	
		void BackCheckControlCode(UserClass &User);


		//ゲームグラフィック
		TextGraphClass		Graph;
				
};