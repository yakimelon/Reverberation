#include"../header/define.h"

/*--------------
 | マウスクラス |
  --------------*/
MouseClass* MouseClass::GetInstance(){
	static MouseClass i;
	return &i;
}

/*マウスの状態を取得*/
void MouseClass::SetHitMouse(){
	//クリックされたキーを取得
	if( GetMouseInput() & MOUSE_INPUT_LEFT )	   MouseState[LeftClick]++;
	else										   MouseState[LeftClick]=0;
	if( GetMouseInput() & MOUSE_INPUT_RIGHT )	   MouseState[RightClick]++;
	else										   MouseState[RightClick]=0;

	//現在のマウス座標を取得
	GetMousePoint(&MouseX,&MouseY);

	//マウスホイールの回転量を取得
	MouseWheel = GetMouseWheelRotVol();
}

/*マウスの座標を返す*/
void MouseClass::GetPoint(int *x,int *y){
	//現在のマウス座標をポインタに代入
	*x = MouseX;
	*y = MouseY;
}

/*マウスの各座標を返す*/
void MouseClass::GetPointX(int &x){	x = MouseX; }
void MouseClass::GetPointY(int &y){ y = MouseY; }

/*マウスホイールの回転量を取得*/
int MouseClass::GetWheel(){
	return MouseWheel;
}


/*マウスの状態を返す*/
int MouseClass::GetState(int MouseCode){
	//マウスの状態を返す
	return MouseState[MouseCode];
}