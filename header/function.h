/*ゲーム画面*/
namespace Game{
	void main();
	void title();
	void save(int ModeFlag);
	void debug();
	enum {TITLE,START,LOAD,SECRET,SYSTEM,END,SAVE,DEBUG};
	enum {S_MODE,L_MODE};
};

/*メインループで実行する処理*/
int ProcessLoop();

/*影付きテキスト描画*/
void DrawStringShadow(int DrawX,int DrawY,std::string DrawText,unsigned int TextColor,unsigned int ShadowColor);

/*メニューパラメータセット　―タイトル画面―*/
void SetMenuParam_Title(MenuArg_rec &MenuArg,bool SecretFlag);

/*メニューパラメータセット　―ゲーム画面―*/
void SetMenuParam_GameRight(MenuArg_rec &MenuArg);