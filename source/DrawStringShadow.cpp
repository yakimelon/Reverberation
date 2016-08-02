#include"../header/define.h" 


void DrawStringShadow(int DrawX,int DrawY,std::string DrawText,unsigned int TextColor,unsigned int ShadowColor){
	//描画座標変数宣言
	int TextX,TextY;

	//影に関する定数を定義
	const int ShadowX = 0;
	const int ShadowY = 3;


	/*背景を描画*/

	// 影の表示開始位置
	TextX = DrawX+ ShadowX;
	TextY = DrawY + ShadowY;

	// 影のベースとなる文字列を描画
	DrawString( TextX , TextY , DrawText.c_str(), ShadowColor);
	
	// テキスト表示開始位置
	TextX = DrawX;
	TextY = DrawY;

	// 文字列の描画
	DrawString(TextX, TextY,DrawText.c_str(), TextColor);

}