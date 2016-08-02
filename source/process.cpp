#include"../header/define.h"

/*メインループで必ず実行する処理*/
int ProcessLoop(){
	//インスタンス化
	KeyClass   *Key   = KeyClass::GetInstance();
	MouseClass *Mouse = MouseClass::GetInstance();

	//固定処理
	ScreenFlip();
	if( ClearDrawScreen() != 0 ) return -1;
	if( ProcessMessage()  != 0 ) return -1;
	Key->SetHitKey();
	Mouse->SetHitMouse();

	return 0;
}
