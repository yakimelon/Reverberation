
/*------------------------
 | タイトル画面制御クラス |
  ------------------------*/
class TitleClass{
	protected:
		int Select;
		int FadeFlag;

	public:
		void Main(int &ChangeFlag,UserClass &User);						//メイン関数
		void ModeChange(int &ModeFlag,int &ChangFlag,UserClass &User);	//モードチェンジ
		void InitSaveData(UserClass &User);								//ユーザーのデータ初期化
		TitleGraphClass Graph;											//タイトルグラフィック制御
};	

