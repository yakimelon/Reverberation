#include"../header/define.h"

/*------------
 | キークラス |
  ------------*/
/*インスタンス取得*/
KeyClass* KeyClass::GetInstance(){
	static KeyClass i;
	return &i;
}

/*キー状態取得*/
void KeyClass::SetHitKey(){
	char TmpKey[256];
	
	GetHitKeyStateAll( TmpKey );

	for( int i=0 ; i<256 ; i++ ){
		if( TmpKey[i] == 1 )	KeyState[i]++;
		else					KeyState[i]=0;
	}
}

/*指定されたキー状態を返す*/
int KeyClass::GetState(int KeyCode){
	return KeyState[KeyCode];
}
