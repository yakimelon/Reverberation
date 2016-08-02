/*----------------
 | メニュークラス |
  ----------------*/
class MenuClass{
	protected:
		//メニューパラメータ
		int  DrawX,DrawY;		//描画オブジェクト左上座標
		int  Interval;			//描画オブジェクト同士の間隔
		int  Width[32];			//描画オブジェクトの幅
		int  Height;			//描画オブジェクトの高さ
		int  ListMin;			//描画オブジェクトの最小ナンバー
		int  ListMax;			//描画オブジェクトの最大ナンバー
		int  AtherNo;			//描画オブジェクトを選択していなときに返すナンバー
		int  AlphaNo;			//選択中オブジェクトの透明度
		int  DrawFlag;			//描画するオブジェクトの種類(0==画像描画 1==テキスト描画)
	    int  DirectionFlag;		//描画方向(0==縦 1==横)

		//画像オブジェクト	
		int  DrawHandle[32];

		//テキストオブジェクト
		char DrawText[32][32];
		unsigned int  TextColor;
		int  FontSize;
		int  FontFamily;

	 	//メニュー設置関数関連 	
		int  SelectNo;											//選択中番号

 	public:
		MenuClass(MenuArg_rec &MenuArg);						//初期化
		void Create();											//メニュー設置
		void Select();											//メニュー選択処理
		virtual void Draw();									//メニュー描画処理
		int  GetSelectNo();										//選択中番号取得
};

/*----------------------
 | セーブメニュークラス |
  ----------------------*/
class SaveMenuClass : public MenuClass{
	protected:
		Dvector_i				SaveDate;
		std::vector<char*>      SaveText;
		//short int SaveData[3][10][2];							//データ受け取り変数(シーンカウント、ゲームカウント)
	public:
		SaveMenuClass(MenuArg_rec &MenuArg);					//初期化
		void Draw(int Page);									//セーブデータを描画
		void UpdateData(Dvector_i Date,std::vector<char*> Text);
		//void UpdateData(short int ***ArgSaveData);				//セーブデータ更新							//セーブデータ更新
};

/*------------------------
 | タイトルメニュークラス |
  ------------------------*/
class TitleMenuClass : public MenuClass{
	public:
		TitleMenuClass(MenuArg_rec &MenuArg);
		void Draw();
};

/*--------------------------
 | コンフィグメニュークラス |
  --------------------------*/
class ConfigListClass : public MenuClass{
	protected:
		int SetNo;
	public:
		ConfigListClass(int SetNo,MenuArg_rec &MenuArg);
		void Draw();
};

/*----------------------------
 | シークレットメニュークラス |
  ----------------------------*/
class SecretMenuClass : public MenuClass{
	public:
		SecretMenuClass(MenuArg_rec &MenuArg);
		void Draw(int SetNo );
};