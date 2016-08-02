#include"../header/define.h" 

/*------------------
 | ユーザ情報クラス |
  ------------------*/
/*メンバ変数初期化*/
UserClass::UserClass(){
	PageFlag			= PAGE::TITLE;
	SaveData.SceneCount = 0;
	SaveData.TextCount	= 0;

	//コンフィグデータ初期化

}

/*現在ページをセット*/
void UserClass::SetPage(int Page){
	PageFlag = Page;
}

/*現在ページを取得*/
int UserClass::GetPage(){
	return PageFlag;
}

/*セーブデータセット*/
void UserClass::SetSaveData(SaveData_rec &SaveData){this->SaveData = SaveData;}
SaveData_rec UserClass::GetSaveData(){ return this->SaveData;}

/*コンフィグ情報ロード*/
void UserClass::LoadConfigData(){
	//定数
	enum{TEXTSPEED,AUTOSPEED,SKIP,ALLVOL,BGMVOL,SEVOL};

	FILE *fp;
	int  TmpData[6];

	//コンフィグデータ読み込み
	fp = fopen("./resource/data/conf.dat","rb+");
	fread(TmpData,6,sizeof(TmpData),fp);
	fclose(fp);

	//読み込んだデータをユーザークラスにコピー
	ConfigData.TextSpeed = TmpData[TEXTSPEED];
	ConfigData.AutoSpeed = TmpData[AUTOSPEED];
	ConfigData.SkipFlag  = TmpData[SKIP];
	ConfigData.AllBolume = TmpData[ALLVOL];
	ConfigData.BGMBolume = TmpData[BGMVOL];
	ConfigData.SEBolume  = TmpData[SEVOL];

}

void UserClass::SaveConfigData(){
	//定数
	enum{TEXTSPEED,AUTOSPEED,SKIP,ALLVOL,BGMVOL,SEVOL};

	FILE *fp;
	int  TmpData[6];

	//ユーザークラスのコンフィグ情報をコピー
	TmpData[TEXTSPEED] = ConfigData.TextSpeed;
	TmpData[AUTOSPEED] = ConfigData.AutoSpeed;
	TmpData[SKIP]      = ConfigData.SkipFlag; 
	TmpData[ALLVOL]    = ConfigData.AllBolume;
	TmpData[BGMVOL]    = ConfigData.BGMBolume;
	TmpData[SEVOL]     = ConfigData.SEBolume;  

	//コンフィグデータ書き込み
	fp = fopen("./resource/data/conf.dat","wb+");
	fwrite(TmpData,6,sizeof(int),fp);
	fclose(fp);

}

/*コンフィグデータセット・取得*/
void UserClass::SetConfigData(ConfigData_rec &ConfigData){ this->ConfigData = ConfigData; }
ConfigData_rec UserClass::GetConfigData(){ return ConfigData; }


/*コンフィグデータを一つ取得*/
int UserClass::GetTextSpeed(){	
	int TextSpeed;

	if( ConfigData.TextSpeed == 0 ) TextSpeed = 5; 
	if( ConfigData.TextSpeed == 1 ) TextSpeed = 4; 
	if( ConfigData.TextSpeed == 2 ) TextSpeed = 3; 
	if( ConfigData.TextSpeed == 3 ) TextSpeed = 2; 
	if( ConfigData.TextSpeed == 4 ) TextSpeed = 1; 

	return TextSpeed; 
}

int UserClass::GetAutoTextSpeed(){
	int AutoSpeed;

	if( ConfigData.AutoSpeed == 0 ) AutoSpeed = 5; 
	if( ConfigData.AutoSpeed == 1 ) AutoSpeed = 4; 
	if( ConfigData.AutoSpeed == 2 ) AutoSpeed = 3; 
	if( ConfigData.AutoSpeed == 3 ) AutoSpeed = 2; 
	if( ConfigData.AutoSpeed == 4 ) AutoSpeed = 1; 


	return AutoSpeed; 
}

int UserClass::GetSkipFlag(){
	return ConfigData.SkipFlag;  
}

int UserClass::GetBGMVol(){
	int VolLevel;

	VolLevel = ConfigData.AllBolume + ConfigData.BGMBolume;
	
	if( VolLevel >= 6 && VolLevel <= 8 ) VolLevel = ( VolLevel - 3 ) * 50;
	if( VolLevel >= 2 && VolLevel <= 5 ) VolLevel = ( ( VolLevel - 1 ) * 25 ) + 25; 

	if( ConfigData.AllBolume == 0 || ConfigData.BGMBolume == 0 ) VolLevel = 0;

	return VolLevel;
}

int UserClass::GetSEVol(){
	int VolLevel;

	VolLevel = ConfigData.AllBolume + ConfigData.SEBolume;
	
	if( VolLevel >= 6 && VolLevel <= 8 ) VolLevel = ( VolLevel - 3 ) * 50;
	if( VolLevel >= 2 && VolLevel <= 5 ) VolLevel = ( ( VolLevel - 1 ) * 25 ) + 25; 

	if( ConfigData.AllBolume == 0 || ConfigData.SEBolume == 0 ) VolLevel = 0;


	//VolLevel = ConfigData.AllBolume + ConfigData.SEBolume - 6 + 2;
	//if( VolLevel <= 0 ) VolLevel = 0;
	return VolLevel;
}

/*既読関係*/
void UserClass::ReadUpdate(){
	short int WriteData[2];
	FILE *fp;

	//削除
	/*
	if( ConfigData.SkipFlag == 1 ){
		fp = fopen("./resource/data/read.dat","wb+");
		WriteData[0] = 0;
		WriteData[1] = 0;
		fwrite(WriteData,2,sizeof(short int),fp);
		fclose(fp);
	}

	//埋める
	if( ConfigData.SkipFlag == 0 ){
		fp = fopen("./resource/data/read.dat","wb+");
		WriteData[0] = 999;
		WriteData[1] = 999;
		fwrite(WriteData,2,sizeof(short int),fp);
		fclose(fp);
	}*/
}

/*BGMコードセット･ゲット*/
void UserClass::SetBGMCode(int Code){ this->BGMCode = Code; }
int  UserClass::GetBGMCode(){return BGMCode;}

/*背景コードセット･ゲット*/
void UserClass::SetBackCode(int Code){ this->BackCode = Code; }
int  UserClass::GetBackCode(){return BackCode;}

/*キャラクタコードセット･ゲット*/
void UserClass::SetCharacterCode(int Code){ this->CharCode = Code; }
int  UserClass::GetCharacterCode(){return CharCode;}

/*シークレットフラグ*/
void UserClass::SetSecretFlag(){
	//変数宣言
	FILE *fp;
	int SecretFlag;

	//定数定義
	const int Key = 831;

	//ファイルオープン
	fp = fopen("./resource/data/syslog.dat","rb+");
	
	//ファイル読み込み
	fread(&SecretFlag,1,sizeof(int),fp);

	//フラグチェック
	if( SecretFlag == Key ) this->SecretFlag = TRUE;
	else					this->SecretFlag = FALSE;

	//ファイルクローズ
	fclose(fp);
}
bool UserClass::GetSecretFlag(){return SecretFlag;}