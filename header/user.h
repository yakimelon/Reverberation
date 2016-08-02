/*------------------
 | ユーザ情報クラス |
  ------------------*/

/*ユーザクラス*/
 class UserClass{
	private:	
		int    PageFlag;								//現在のページ
		struct SaveData_rec   SaveData;					//セーブデータ
		struct ConfigData_rec ConfigData;				//コンフィグデータ
		int    BGMCode;									//BGMコード
		int    BackCode;								//背景画像コード
		int    CharCode;								//キャラクタコード
		bool   SecretFlag;								//シークレットフラグ
		

	public:
		UserClass();									//メンバ変数初期化
		void SetPage(int Page);							//現在ページをセット
		int  GetPage();									//現在ページを取得
		void SetSaveData(SaveData_rec &SaveData);		//セーブデータセット
		SaveData_rec GetSaveData();						//セーブデータ取得
		void LoadConfigData();							//コンフィグ情報ロード
		void SaveConfigData();							//コンフィグ情報セーブ
		void SetConfigData(ConfigData_rec &ConfigData);	//コンフィグデータセット
		ConfigData_rec GetConfigData();					//コンフィグデータ取得
		
		//各コンフィグデータを返す
		int  GetTextSpeed();		//テキストの表示速度
		int  GetAutoTextSpeed();	//オートモードの表示速度
		int  GetSkipFlag();			//未読スキップを許可するか
		int  GetBGMVol();			//BGMの音量
		int  GetSEVol();			//SEの音量
 
		//既読関係
		void ReadUpdate();			//既読関係

		//サウンドコード
		void SetBGMCode(int Code);	
		int  GetBGMCode();			

		//背景コード
		void SetBackCode(int Code);	
		int  GetBackCode();		

		//キャラクタコード
		void SetCharacterCode(int Code);
		int  GetCharacterCode();

		//シークレットフラグ
		void SetSecretFlag();
		bool GetSecretFlag();
};