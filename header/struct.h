/*メニュークラスに渡すパラメータ*/
struct MenuArg_rec{
	//パラメータ
	int  DrawX,DrawY;		//描画オブジェクト左上座標
	int  Interval;			//描画オブジェクト同士の間隔
	int  Width,Height;		//描画オブジェクトの幅と高さ(Width,heightはテキストの場合フォントサイズになる)
	int  ListMin;			//描画オブジェクトの最小ナンバー
	int  ListMax;			//描画オブジェクトの最大ナンバー
	int  AtherNo;			//描画オブジェクトを選択していなときに返すナンバー
	int  AlphaNo;			//選択中オブジェクトの透明度
	int  DrawFlag;			//描画するオブジェクトの種類(0==画像描画 1==テキスト描画)
	int  DirectionFlag;		//描画方向(0==縦 1==横)

	//描画フラグが０ならば画像
	int  DrawHandle[32];	//描画オブジェクト

	//描画フラグが１ならばテキスト
	char DrawText[32][32];	//描画テキスト
	unsigned int  TextColor;			//描画テキストカラー
	int  FontFamily;		//フォントファミリー

};

/*コンフィグメニューに渡すパラメータ*/
struct ConfigArg_rec{
	//パラメータ
	std::string Title;	//タイトル
	int			DrawX;	//描画X座標
	int			DrawY;	//描画Y座標
	int			Width;	//メニューの横幅
	int			Height;	//メニューの高さ
	int			ListNo;	//項目の数
	int			SetNo;	//設定されている値
};

/*セーブデータ構造体*/
struct SaveData_rec{
	short int   SceneCount;	//シーンカウント
	short int   TextCount;	//テキストカウント
	short int   SerifCount;	//セリフカウント
	int         BGMCode;	//BGMコード
	int         BackCode;	//背景コード
	int			CharCode;	//キャラクターコード
	int			Year;		//年
	int			Mon;		//月
	int			Day;		//日
	int         TextLength;	//テキストの文字数(バイト数)
	char		Text[61];	//テキスト1行(これは100%ﾊﾞｯﾌｧｵｰﾊﾞｰﾌﾛｰの元になるから、std::stringにしておくこと！)
};

/*コンフィグデータ構造体*/
struct ConfigData_rec{
	//テキスト関連
	int  TextSpeed;
	int  AutoSpeed;
	int  SkipFlag;

	//音量関連
	int  AllBolume;
	int  BGMBolume;
	int  SEBolume;
};
