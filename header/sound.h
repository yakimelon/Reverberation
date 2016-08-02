/*----------------------------
 | サウンドクラス(抽象クラス) |
  ----------------------------*/
class SoundClass{
	protected:
		enum{PLAY,STOP};							//再生状態を表す定数
		int PlayFlag;								//再生中フラグ
		int BGMVol;									//BGMの音量を格納
		int SEVol;									//SEの音量を格納
		int NowPlayCode;							//現在再生中のコード

		void VarInit();								//メンバ変数初期化
		virtual void Load()=0;						//音楽ロード

	public:
		virtual void PlayMusic(UserClass &User) = 0;//音楽再生
		virtual void StopBGM()=0;					//音楽停止
		virtual	void SetVol(UserClass &User);		//音量セット
		//virtual void VolChange();					//音量チェンジ
};


/*------------------------
 | タイトルサウンドクラス |
  ------------------------*/
class TitleSoundClass : public SoundClass{
	private:
		int TitleBGM;						//タイトルBGMを格納
		int TitleBGM2;						//タイトルBGM２

		void Load();

	public:
		TitleSoundClass();					//初期化
		void PlayMusic(UserClass &User);	//音楽再生
		void StopBGM();						//音楽停止
};

/*----------------------
 | ゲームサウンドクラス |
  ----------------------*/
class GameSoundClass : public SoundClass{
	enum{HARA,END};

	private:
		std::vector<int> GameBGM;			//ゲームBGMを格納
		void Load();						//音楽読み込み

	public:
		GameSoundClass();					//初期化
		void PlayMusic(UserClass &User);	//音楽再生
		void StopBGM();						//音楽停止
};

/*--------------------------
 | システムエフェクトクラス |
  --------------------------*/
class SESoundClass : public SoundClass{
	enum{DIALOG,ENTER,CANCEL};

	private:
		int DialogSE;
		int EnterSE;
		int CancelSE;

		void Load();

	public:
		SESoundClass();
		void PlayMusic( int Code );
		void PlayMusic( UserClass &User );
		void StopBGM();
};

/*----------------------------
 | シークレットサウンドクラス |
  ----------------------------*/
class SecretSoundClass : public SoundClass{
	enum{TITLE,KAISOU,DEAI,WAKARE,ENDING};
	private:
		int TitleBGM;
		int kaisouBGM;
		int kaisou2BGM;
		int DeaiBGM;
		int WakareBGM;
		int EndingBGM;
		
		void Load();

	public:
		SecretSoundClass();					//初期化
		void PlayMusic(UserClass &User);	//音楽再生(ダミー)
		void PlayMusic(int Code);			//音楽再生
		void StopBGM();						//音楽停止
};


 