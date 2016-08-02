/*各種ライブラリインクルード*/
#include<DxLib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<vector>
#include<map>

/*二次元配列のvectorを定義*/
using std::vector;
typedef vector< vector<int> > Dvector_i;
typedef vector< vector<std::string> > Dvector_s;

/*各種ヘッダインクルード*/
#include"struct.h"
#include"user.h"
#include"mode.h"
#include"input.h"
#include"anime.h"
#include"graph.h"
#include"sound.h"
#include"menu.h"
#include"save.h"
#include"title.h"
#include"text.h"
#include"config_menu.h"
#include"config.h"
#include"secret.h"
#include"ending.h"
#include"page.h"
#include"function.h"
#include"scroll_bar.h"
#include"back_log.h"
#include"dialog.h"

/*グローバル変数宣言 暇があれば消す*/
#ifdef GLOBAL_INSTANCE
RECT rect;					//ウィンドウサイズ格納
int  MenuFontHandle;		//メニューに使うフォントハンドル
int  TextFontHandle;		//テキスト全般に使うフォントハンドル
#else
extern RECT rect;
extern int MenuFontHandle;
extern int TextFontHandle;
#endif


/*----------
 | 定数定義 |
  ----------*/

//ウィンドウの縦横サイズ
#define windowX 1280
#define windowY 720

//メニュークラスで使う
namespace MENU{
	enum{IMAGE,TEXT,DATA};
	enum{COL,ROW};
	enum{GOSIC,MINTYO};
}

//マウスクラスで使う
namespace MOUSE{
	enum{LEFT,RIGHT};
}

//画像描画座標で使う
namespace GRAPH{
	 enum{X,Y};
}

//タイトル画面のメニューで使う
namespace TITLE{
 	enum{START=1,LOAD,SECRET,CONFIG,END};
}

//ゲーム画面のメニューで使う
namespace GAME_MENU{
	enum{SAVE,LOAD,AUTO,BACKLOG,CONFIG};
}

//ページ一覧
namespace PAGE{
	enum{TITLE,GAME,END,SECRET};
 }

//モード一覧
namespace MODE{
	enum{MAIN,SAVE,LOAD,CONFIG,BACKLOG,SECRET,OTHER,END};
}

//コンフィグで使う
namespace CONFIG{
	enum{INIT,SAVE,BACK};
}

//確認ダイアログで使う
namespace DIALOG{
	enum{YES,NO};
}

//ゲーム音楽コード
namespace GAME_BGM{
	enum{KAISOU1,KAISOU2,DEAI,WAKARE,TITLE,STOP};
}

//ゲーム背景コード
namespace GAME_BACK{
	enum{KAWARA,YOZORA,BLACK};
}

//ゲームキャラクターコード
namespace GAME_CHAR{
	enum{AI,NOT};
}

