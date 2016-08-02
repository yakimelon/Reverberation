/*--------------------------
 | コンフィグメニュークラス |
  --------------------------*/
class ConfigMenuClass{
	private:
		std::string Title;				//メニュータイトル
		int DrawX,DrawY;				//メニュー描画座標
		int Width,Height;				//メニュー縦横サイズ
		int ListNo;						//メニュー項目数
		int SetNo;						//設定されている値

		int SelectNo;					//選択された番号

		struct MenuArg_rec MenuArg;		//メニューパラメータ
		void SetMenuParam();			//メニューパラメータセット

	public:
		ConfigMenuClass(ConfigArg_rec ConfigArg);	

		void Draw();					//描画
		int  GetSelectNo();				//クリックされた値を返す
};