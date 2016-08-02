/*----------------------
 | 確認ダイアログクラス |
  ----------------------*/
class DialogClass{
	private:
		int  DrawX,DrawY;										//描画座標X
		int  Width,Height;										//描画座標Y
		std::string Message;									//ダイアログメッセージ
		int  MessageFontSize;									//メッセージフォントサイズ
		int  SelectFlag;										//選択フラグ
		bool DrawFlag;											//描画フラグ
		int  SelectNo;											//選択番号
		int  Timer;												//タイマカウンタ
		bool FirstFlag;											//一回だけ実行する処理のフラグ

		struct MenuArg_rec MenuParam;							//メニューのパラメータ

	public:
		DialogClass();											//初期化
		void SetPoint();										//座標初期化
		void SetMenuParam();									//メニューパラメータ設定
		
		void SetSelectNo(int SelectNo,std::string Message);		//選択番号セット
		void Draw(UserClass &User);								//ダイアログ描画
		bool GetDrawFlag();										//描画フラグ取得
		int  GetSelectFlag();									//選択フラグ取得
		int  GetSelectNo();										//選択番号取得
		void Clear();											//ダイアログ削除

		//SEに関するクラス
		SESoundClass SE;
};