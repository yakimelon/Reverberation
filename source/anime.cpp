#include"../header/define.h" 

/*----------------------
 | アニメーションクラス |
  ----------------------*/

/*― 画面全体の黒からのフェードイン ―
	引数　：フェードインの速度
　　戻り値：フェードイン終了で１を返す。
*/

/*変数初期化*/
AnimeClass::AnimeClass(){
	FadeFlag = 0;
	Count    = 0;
}

/*フェードイン処理*/
int AnimeClass::FadeIn(int Speed){
	//画面をだんだん明るくする
	if( FadeFlag == 0 ){
		SetDrawBright(Count,Count,Count);
		Count+=Speed;
	}

	//画面が最大まで明るくなったら停止
	if( Count >= 255 ) FadeFlag = 1;

	return FadeFlag;
}

/*全ての変数を初期化*/
void AnimeClass::Reset(){
	FadeFlag = 0;
	Count    = 0;
}