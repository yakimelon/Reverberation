#include"../header/define.h"

/*--------
 | 初期化 |
  --------*/
ScrollBarClass::ScrollBarClass(){
	//メンバ変数初期化
	MoveScroll = 10;
	MaxScroll  = 720;
	MinScroll  = 0;
	BarWidth   = 30;
	MoveAdd    = 1;
	BarDrawX   = 1200;
}

/*--------------------------
 | スクロールバーサイズ計算 |
  --------------------------*/
void ScrollBarClass::SizeCalc(int DrawHeight){
	//スクロールバーの最小値
	const int BarHeightMin = 50;

	//はみ出てる分のテキスト縦サイズ取得
	SubHeight = DrawHeight - windowY;

	//そもそもはみ出ているのか
	if( SubHeight < 0 ){
		BarHeight = MaxScroll;
		NewDrawY  = MinScroll;
		OldDrawY  = MinScroll;
		BarDrawY  = MinScroll;
	}else{
		//スクロールバーサイズ取得
		BarHeight = MaxScroll - SubHeight;

		//スクロールバーのサイズが最小値を下回っていないか
		if( BarHeight < BarHeightMin ){
			//スクロールの量を増加させる
			MoveAdd   = (double)DrawHeight / ( MaxScroll );

			BarHeight = BarHeightMin;
			BarDrawY  = MaxScroll - BarHeight;
			NewDrawY  = MaxScroll - BarHeight;
			OldDrawY  = MaxScroll - BarHeight;
			SubHeight = MaxScroll - BarHeight;
		}else{
			BarDrawY  = MinScroll + SubHeight;
			NewDrawY  = MinScroll + SubHeight;
			OldDrawY  = MinScroll + SubHeight;
		}
	}
}

/*------------
 | 移動量計算 |
  ------------*/
double ScrollBarClass::MoveCalc(){
	MouseClass* Mouse = MouseClass::GetInstance();

	int          TmpDrawY;
	const int    CLICK_FRAME = 1;
	const double ROUNDING    = 0.5;
	const int    BASE_SCROLL = MaxScroll - BarHeight;
	const int    END_FLAG    = -100000000;
	

	//スクロールバーがクリックされた
	if( Mouse->GetState(MOUSE::LEFT) >= CLICK_FRAME ){
		//座標取得
		Mouse->GetPointY(TmpDrawY);
		
		//スクロールバーがクリックされた
		if( BarDrawY <= TmpDrawY && TmpDrawY < BarDrawY + BarHeight ){
			NewDrawY = TmpDrawY - OldDrawY; //NewDrawYは差分を表してる、後で名前変更
			if( MinScroll < BarDrawY + NewDrawY && BarDrawY + NewDrawY + BarHeight < MaxScroll ){
				BarDrawY   += NewDrawY;
				MoveScroll -= NewDrawY * MoveAdd + ROUNDING;
				OldDrawY   =  BarDrawY;
			}
		}else if( MinScroll < TmpDrawY && TmpDrawY < MaxScroll ){
			//バー領域の下のほうをクリックした
			if( windowY - BarHeight < TmpDrawY ){
				BarDrawY   = MinScroll + SubHeight;
				MoveScroll = 0;
				OldDrawY   = BarDrawY;
			}else{
				BarDrawY   = TmpDrawY;
				MoveScroll = (BASE_SCROLL - BarDrawY) * MoveAdd + ROUNDING;
				OldDrawY   = BarDrawY;
			}
		}
	}

	//マウスホイールが回転した
	if( Mouse->GetWheel() > 0 ){
		if( MinScroll < BarDrawY - 20 ){
			BarDrawY   -= 20;
			MoveScroll += 20 * MoveAdd + ROUNDING;
			OldDrawY   =  BarDrawY;
		}
	}
	if( Mouse->GetWheel() < 0 ){
		if( BarDrawY + BarHeight + 20 < MaxScroll ){
			BarDrawY   += 20;
			MoveScroll -= 20 * MoveAdd + ROUNDING;
			OldDrawY   =  BarDrawY;
		}else{
			return END_FLAG;
		}
	}

	return MoveScroll;
}

/*--------------------
 | スクロールバー描画 |
  --------------------*/
void ScrollBarClass::DrawScrollBar(){
	DrawBox(BarDrawX,BarDrawY,BarDrawX+BarWidth,BarDrawY+BarHeight,GetColor(155,155,155),TRUE);
}