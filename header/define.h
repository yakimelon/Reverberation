/*�e�탉�C�u�����C���N���[�h*/
#include<DxLib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<vector>
#include<map>

/*�񎟌��z���vector���`*/
using std::vector;
typedef vector< vector<int> > Dvector_i;
typedef vector< vector<std::string> > Dvector_s;

/*�e��w�b�_�C���N���[�h*/
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

/*�O���[�o���ϐ��錾 �ɂ�����Ώ���*/
#ifdef GLOBAL_INSTANCE
RECT rect;					//�E�B���h�E�T�C�Y�i�[
int  MenuFontHandle;		//���j���[�Ɏg���t�H���g�n���h��
int  TextFontHandle;		//�e�L�X�g�S�ʂɎg���t�H���g�n���h��
#else
extern RECT rect;
extern int MenuFontHandle;
extern int TextFontHandle;
#endif


/*----------
 | �萔��` |
  ----------*/

//�E�B���h�E�̏c���T�C�Y
#define windowX 1280
#define windowY 720

//���j���[�N���X�Ŏg��
namespace MENU{
	enum{IMAGE,TEXT,DATA};
	enum{COL,ROW};
	enum{GOSIC,MINTYO};
}

//�}�E�X�N���X�Ŏg��
namespace MOUSE{
	enum{LEFT,RIGHT};
}

//�摜�`����W�Ŏg��
namespace GRAPH{
	 enum{X,Y};
}

//�^�C�g����ʂ̃��j���[�Ŏg��
namespace TITLE{
 	enum{START=1,LOAD,SECRET,CONFIG,END};
}

//�Q�[����ʂ̃��j���[�Ŏg��
namespace GAME_MENU{
	enum{SAVE,LOAD,AUTO,BACKLOG,CONFIG};
}

//�y�[�W�ꗗ
namespace PAGE{
	enum{TITLE,GAME,END,SECRET};
 }

//���[�h�ꗗ
namespace MODE{
	enum{MAIN,SAVE,LOAD,CONFIG,BACKLOG,SECRET,OTHER,END};
}

//�R���t�B�O�Ŏg��
namespace CONFIG{
	enum{INIT,SAVE,BACK};
}

//�m�F�_�C�A���O�Ŏg��
namespace DIALOG{
	enum{YES,NO};
}

//�Q�[�����y�R�[�h
namespace GAME_BGM{
	enum{KAISOU1,KAISOU2,DEAI,WAKARE,TITLE,STOP};
}

//�Q�[���w�i�R�[�h
namespace GAME_BACK{
	enum{KAWARA,YOZORA,BLACK};
}

//�Q�[���L�����N�^�[�R�[�h
namespace GAME_CHAR{
	enum{AI,NOT};
}
