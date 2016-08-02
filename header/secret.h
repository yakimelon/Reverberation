/*--------------------
 | シークレットクラス |
  --------------------*/
class SecretClass{
	private:
		int Select;									//選択番号受け取り
		int FadeFlag;								//フェードフラグ
		int SetNo;									//再生中ナンバー
		Dvector_s ShowText;							//描画テキスト

		MenuArg_rec MusicListParam;					//曲一覧パラメータ

	public:
		SecretClass();								//初期化
		void SetMenuParam();						//メニューパラメータセット
		void SetText();								//テキストセット
		void Main(UserClass& User,int &ChangeFlag);	//メイン
		SecretGraphClass Graph;						//グラフィック
		SecretSoundClass Sound;						//サウンド

};
