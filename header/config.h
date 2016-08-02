/*------------------
 | コンフィグクラス |
  ------------------*/
class ConfigClass{
	private:
		int Select;														//選択番号受け取り
		int FadeFlag;													//フェードフラグ

		struct ConfigData_rec ConfigData;								//コンフィグコピー情報
		struct ConfigData_rec BackConfigData;							//コンフィグデータバックアップ
		struct MenuArg_rec  MenuArg;									//メニューパラメータ

	public:
		ConfigClass();													//初期化
		void Main(UserClass& User,int &ChangeFlag);						//メイン
		void ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User);	//モードチェンジ
		ConfigGraphClass Graph;											//グラフィック

};
