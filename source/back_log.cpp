#include"../header/define.h"

/*-------------------
 |セリフカウント更新 |
  ------------------- */
BackLogClass::BackLogClass(){
	UpButtonHandle   = LoadGraph("./resource/graph/log_up.png");
	DownButtonHandle = LoadGraph("./resource/graph/log_down.png");
}

void BackLogClass::Update(int *ArgLineNo,int ArgSerifCount){
	//メンバ変数初期化
	LineNo     = ArgLineNo;
	SerifCount = ArgSerifCount;
	LineHeight = 70;
	DrawLine   = 0;

	//各値取得
	GetDrawLine();
	GetDrawSize();
	GetLogDrawPoint();
	ScrollBar.SizeCalc(DrawSize);
}

/*----------
 | 行数取得 |
  ----------*/
void BackLogClass::GetDrawLine(){
	for( int i=0 ; i<=SerifCount ; i++ ) DrawLine += LineNo[i];
}

/*--------------------------
 | テキスト描画縦サイズ取得 |
  --------------------------*/
void BackLogClass::GetDrawSize(){
	const int BottomSpace = 60;
	DrawSize = DrawLine * LineHeight ;
}

/*--------------
 | 描画座標取得 |
  --------------*/
void BackLogClass::GetLogDrawPoint(){
	//定数定義
	const int BottomSpace = 80;
	const int TextIndent  = 200;
	const int NameIndent  = 50;

	//全体描画座標取得
	LogDrawX = 0;
	LogDrawY = windowY - DrawSize + BottomSpace;
	
	//各描画座標取得
	DrawNameX = LogDrawX + NameIndent;
	DrawNameY = LogDrawY;
	DrawTextX = LogDrawX + TextIndent;
	DrawTextY = LogDrawY;
}

/*----------------
 | バックログ描画 |
  ----------------*/
int BackLogClass::DrawLog(std::string Name[1024],std::string Text[1024]){
	const int END_FLAG = -100000000;
	const int FontSize = 28;

	int  TmpTextCount    = 0;
	int  TmpSerifCount   = 0;
	int  TmpCount	     = 0;
	int  ContCount		 = 0;
	int  EventCount      = 0;
	int  EventCodeHeight = 0;
	bool ButtonDrawFlag  = FALSE;
	std::string TmpStr;

	unsigned int Color;

	//テキスト描画カウント初期化
	DrawTextCount = 0;

	//スクロールバー移動量取得
	//MoveScroll = ScrollBar.MoveCalc();
	
	//配列初期化
	ButtonY1.clear();
	ButtonY2.clear();
	JumpTextCount.clear();
	JumpSerifCount.clear();

	//ボタン座標定義
	ButtonX1  = 0;
	ButtonX2  = windowX-110;
	
	//背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,200);
	DrawBox(0,0,windowX,windowY,GetColor(0,0,0),TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	//移動量取得
	MoveScroll = MouseScroll();
	if( MoveScroll == END_FLAG ) return END_FLAG;

	//カウンタ更新
	JumpLoopCount = SerifCount;

	//バックログ描画
	for( int i=0 ; i<=SerifCount ; i++ ){
		//テキストチェック
		if( Name[DrawTextCount] == "続き"  || Name[DrawTextCount] == "主人公" ) Name[DrawTextCount] = "\0";

		if( Name[DrawTextCount] == "背景" || Name[DrawTextCount] == "キャラ" || Name[DrawTextCount] == "音楽" || Name[DrawTextCount] == "イベント" || Name[DrawTextCount] == "エンド" ){
			DrawTextCount++;
			//TmpTextCount++;
			TmpSerifCount++;
			EventCount++;
			JumpLoopCount--;
			continue;
		}
		
		//イベントコードの高さ
		EventCodeHeight = LineHeight * EventCount;

		//座標とカウントを取得
		ButtonY1.push_back( DrawNameY+(LineHeight*DrawTextCount)-LineHeight-EventCodeHeight+EventCodeSize );
		ButtonY2.push_back( DrawNameY+(LineHeight*DrawTextCount)+FontSize-LineHeight-EventCodeHeight+EventCodeSize );
		
		//ジャンプボタン描画
		//DrawBox(ButtonX1,ButtonY1[TmpCount],ButtonX2,ButtonY2[TmpCount],GetColor(255,255,255),TRUE);
	

		//デバッグ用
		TmpStr = Name[DrawTextCount];

		//名前描画
		DrawString(DrawNameX,DrawNameY+(LineHeight*DrawTextCount)-LineHeight-EventCodeHeight+EventCodeSize,TmpStr.c_str(),GetColor(255,255,255));
		
		//セリフ描画
		for( int j=0 ; j<LineNo[i] ; j++ ){
			DrawString(DrawTextX,DrawTextY+(LineHeight*DrawTextCount)-LineHeight-EventCodeHeight+EventCodeSize,Text[DrawTextCount].c_str(),GetColor(255,255,255));
			DrawTextCount++;
			ContCount++;
		}
		
		JumpTextCount.push_back( DrawTextCount - ContCount );
		JumpSerifCount.push_back( i );
		TmpCount++;
		ContCount=0;
	}

	//イベントコードの全体サイズ取得
	EventCodeSize = EventCodeHeight;

	//スクロールバー描画
	//ScrollBar.DrawScrollBar();

	if( EndFlag == TRUE ) return END_FLAG;
	else				  return 0;
}

/*マウスホイールの移動量*/
int BackLogClass::MouseScroll(){
	auto *Mouse = MouseClass::GetInstance();
	int MoveScroll;

	const int END_FLAG = -100000000;
	static bool BackFlag = FALSE;
	static int  Count = 0;
	static int  Timer = 0;
	static bool TimerFlag = FALSE;
	int ClickX,ClickY;

	//ボタン座標
	const int UpButtonX1 = windowX-100;
	const int UpButtonY1 = 0;
	const int UpButtonX2 = windowX;
	const int UpButtonY2 = 100;

	const int DownButtonX1 = windowX-100;
	const int DownButtonY1 = windowY-100;
	const int DownButtonX2 = windowX;
	const int DownButtonY2 = windowY;

	//画面を超えたサイズならスクロール許可
	if( DrawSize - EventCodeSize > windowY ){
		//上に回転
		if( Mouse->GetWheel() > 0 && DialogFlag == FALSE ){
			if(DrawNameY - LineHeight + EventCodeSize <= 0){
				DrawNameY += 40;
				DrawTextY += 40;
				BackFlag   = FALSE;
				Count      = 0;
			}
		}

		//下に回転(複雑な分岐と汚すぎるif連鎖、元気なときにリファクタリングする)
		if( Mouse->GetWheel() < 0 && DialogFlag == FALSE ){
			if(  DrawNameY >= windowY - DrawSize + LineHeight+20 ){
				DrawNameY -= 40;
				DrawTextY -= 40;
			}else{
				if( BackFlag == TRUE && DialogFlag == FALSE ) return END_FLAG;
				else{
					Count++;
					if( Count > 3 )  BackFlag = TRUE;
				}
			}
		}	

		//スクロールボタン設置		
		//DrawBox(UpButtonX1,UpButtonY1,UpButtonX2,UpButtonY2,GetColor(255,255,255),TRUE);
		//DrawBox(DownButtonX1,DownButtonY1,DownButtonX2,DownButtonY2,GetColor(255,255,255),TRUE);

		//スクロールボタン画像
		DrawGraph(UpButtonX1,UpButtonY1,UpButtonHandle,TRUE);
		DrawGraph(DownButtonX1,DownButtonY1,DownButtonHandle,TRUE);

		//マウス座標取得
		Mouse->GetPoint(&ClickX,&ClickY);

		//クリックされた
		if( Mouse->GetState(MOUSE::LEFT) > 0 ){
			//ページアップボタン
			if( UpButtonX1 < ClickX && ClickX < UpButtonX2 ){
				if( UpButtonY1 < ClickY && ClickY < UpButtonY2 ){
					if( DrawNameY + LineHeight+20 <= 0 ){
					DrawNameY += 40;
					DrawTextY += 40;
					}
				}
			}
			//ページダウンボタン
			if( DownButtonX1 < ClickX && ClickX < DownButtonX2 ){
				if( DownButtonY1 < ClickY && ClickY < DownButtonY2 ){
					if( DrawNameY >= windowY - DrawSize + LineHeight+20 ){
					DrawNameY -= 40;
					DrawTextY -= 40;
					}
				}
			}
		}
	
	}else{
		if( Mouse->GetWheel() < 0 && DialogFlag == FALSE ) return END_FLAG;
	}

	//右クリックで戻る
	if( Mouse->GetState( MOUSE::RIGHT ) > 0 && DialogFlag == FALSE ) TimerFlag = TRUE;
	if( TimerFlag == TRUE ){
		Timer++;
		if( Timer > 20 ){
			TimerFlag = FALSE;
			Timer     = 0;
			return END_FLAG;
		}
	}
}

/*前のセリフにジャンプ*/
int BackLogClass::Jump(short int &TextCount,short int &SerifCount,UserClass &User){
	auto *Mouse = MouseClass::GetInstance();
	static DialogClass Dialog;

	int ClickX,ClickY;

	static bool JumpFlag   = FALSE;
	static bool ClearFlag  = FALSE;
	static int  Timer1     = 0;
	static int  Timer2     = 0;
	static int  JumpNo	   = 0;

	//定数
	const int END_FLAG = -100000000;
	const int WaitTime = 30;


	//座標取得
	Mouse->GetPoint(&ClickX,&ClickY);

	//ダイアログフラグ取得
	DialogFlag = Dialog.GetDrawFlag();


	if( Mouse->GetState(MOUSE::LEFT) > 0 && DialogFlag == FALSE ){
		for( int i=0 ; i<=JumpLoopCount ; i++ ){
			if( ButtonX1 < ClickX && ClickX < ButtonX2 ){
				if( ButtonY1[i] < ClickY && ClickY < ButtonY2[i] ){
					SelectNo = i; //選択してるジャンプボタンのナンバーセット
					Dialog.SetSelectNo( i , "ジャンプしてよろしいですか？" );
				}
			}
		}
	}

	//ダイアログが描画されているならば
	if( DialogFlag == TRUE ){

		//ダイアログ描画
		Dialog.Draw(User);

		//Yes
		if( Dialog.GetSelectFlag() == DIALOG::YES ){

			//選択番号を受け取る
			JumpNo = Dialog.GetSelectNo();

			//ジャンプ処理
			TextCount  = (short int)JumpTextCount[JumpNo];
			SerifCount = (short int)JumpSerifCount[JumpNo];
			JumpFlag   = TRUE;

			//ダイアログ削除
			ClearFlag = TRUE;
			//Dialog.Clear();
		}

		//No
		if( Dialog.GetSelectFlag() == DIALOG::NO ){
			ClearFlag = TRUE;
			//Dialog.Clear();
		}
	}


	if( ClearFlag == TRUE ){
		Timer2++;
		if( Timer2 > WaitTime ){
			Timer2 = 0;
			Dialog.Clear();
			ClearFlag = FALSE;
		}
	}


	if( JumpFlag == TRUE ){
		Timer1++;
		if( Timer1 > WaitTime ){
			Timer1 = 0;
			JumpFlag = FALSE;
			return END_FLAG;
		}
	}
}