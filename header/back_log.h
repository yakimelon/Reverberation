/*------------------
 | バックログクラス |
  ------------------*/
class BackLogClass{
	private:
		int  DrawLine;										//描画行数
		int  DrawSize;										//テキスト描画縦サイズ
		int  LineHeight;									//一行の高さ
		int  LogDrawX;										//バックログ描画座標
		int  LogDrawY;										//バックログ描画座標
		int  DrawTextX;										//テキスト描画X
		int  DrawTextY;										//テキスト描画Y
		int  DrawNameX;										//名前描画X
		int  DrawNameY;										//名前描画Y
		int  *LineNo;										//行数リスト
		int  SerifCount;									//現在のセリフカウント
		int  DrawTextCount;									//テキストの描画カウント
		int  EventCodeSize;									//イベントコードの大きさ
		int  MoveScroll;									//スクロールバー移動量
		int  SelectNo;										//選択してるジャンプボタン
		bool EndFlag;										//エンドフラグ
		bool DialogFlag;									//ダイアログフラグ
		int  JumpLoopCount;									//ジャンプループ回数
		int  ButtonX1;										//ボタンX1座標
		int  ButtonX2;										//ボタンX2座標
		vector<int> ButtonY1;								//ボタンY1座標
		vector<int> ButtonY2;								//ボタンY2座標
		vector<int> JumpTextCount;							//テキストカウント
		vector<int> JumpSerifCount;							//セリフカウント
		int  UpButtonHandle;								//上ボタン画像ハンドル
		int  DownButtonHandle;								//下ボタン画像ハンドル

	public:
		BackLogClass();																//初期化
		void Update(int *ArgLineNo,int ArgSerifCount);								//セリフカウント更新
		void GetDrawLine();															//描画行数取得
		void GetDrawSize();															//テキスト描画縦サイズ取得
		void GetLogDrawPoint();														//描画座標取得
		int  DrawLog(std::string Name[1024],std::string Text[1024]);				//バックログ描画
		int  MouseScroll();															//マウスホイール移動量
		int  Jump(short int &TextCount,short int &SerifCount,UserClass &User);		//前のセリフに飛ぶ
		ScrollBarClass ScrollBar;													//スクロールバーインスタンス
};