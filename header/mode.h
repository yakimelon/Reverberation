/*--------------------------
 | モードクラス(抽象クラス) |
  --------------------------*/
class ModeClass{
	public:
		virtual void Main(int &ChangeFlag) = 0;
		virtual void Main(UserClass& User) = 0;
		virtual void ModeChange(int &ModeFlag,int &ChangeFlag,UserClass &User) = 0;	
};