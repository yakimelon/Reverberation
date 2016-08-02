#include"../header/define.h" 

/*----------------
 | メニュークラス |
  ----------------*/
/*選択肢に使う情報をセット*/
MenuClass::MenuClass(MenuArg_rec &MenuArg){
	//パラメータ取得
	DrawX			= MenuArg.DrawX;			//描画オブジェクトの左上X
	DrawY			= MenuArg.DrawY;			//描画オブジェクトの左上Y
	Interval		= MenuArg.Interval;			//描画オブジェクト同士の間隔
	Height		    = MenuArg.Height;			//描画オブジェクトの高さ
	ListMin			= MenuArg.ListMin;			//描画オブジェクトの初期ナンバー
	ListMax			= MenuArg.ListMax;			//描画オブジェクトの最大ナンバー
	AtherNo			= MenuArg.AtherNo;			//描画オブジェクトを選択していなときに返すナンバー
	AlphaNo			= MenuArg.AlphaNo;			//選択中オブジェクトの透明度
	DrawFlag		= MenuArg.DrawFlag;			//描画するオブジェクトの種類(0==画像描画 1==テキスト描画)
	DirectionFlag	= MenuArg.DirectionFlag;	//描画方向(0==縦 1==横)

	//描画オブジェクト取得
	for( int i=0 ; i<ListMax-ListMin ; i++ ){								//描画オブジェクト数ループ
		if( DrawFlag == MENU::IMAGE ){
			DrawHandle[i] = MenuArg.DrawHandle[i];							//描画画像を取得
			Width[i]      = MenuArg.Width;									//画像の横幅を取得
		}
		if( DrawFlag == MENU::TEXT ){
			strcpy(DrawText[i],MenuArg.DrawText[i]);						//描画テキストを取得
			Width[i]      = strlen(MenuArg.DrawText[i])*(MenuArg.Width/2);	//テキストの横幅を取得
			TextColor     = MenuArg.TextColor;								//テキストの色を取得
			FontSize      = MenuArg.Width;									//フォントサイズ取得
			FontFamily	  = MenuArg.FontFamily;								//フォントファミリー取得
		}
		if( DrawFlag == MENU::DATA ){
			Width[i]	  = MenuArg.Width;
		}
	}

}

/*メニュー設置処理*/
void MenuClass::Create(){
	Select();	//メニュー選択処理
	Draw();		//メニュー描画処理
}

/*メニュー選択処理*/
void MenuClass::Select(){
	//変数宣言
	static int x,y;
	int i;
	int RowWidth=0;

	//インスタンス化
	MouseClass* Mouse = MouseClass::GetInstance();

	//マウス座標取得
	Mouse->GetPoint(&x,&y);


	//マウス選択取得(縦並びの場合)
	if( DirectionFlag == MENU::COL ){
		for( i=0 ; i<ListMax-ListMin ; i++ ){
			if( x >= DrawX && x <= DrawX + Width[i] ){
				if( y >= DrawY + ( Interval + Height ) * i && y <= DrawY + ( Interval + Height ) * i + Height ){
					SelectNo = i;
					break;
				}
			}
		}
	}

	//マウス選択取得(横並びの場合)
	if( DirectionFlag == MENU::ROW ){
		for( i=0 ; i<ListMax-ListMin ; i++ ){
			
			//列の現在地までの横幅を取得
			for( int p=0 ; p<i ; p++ ) RowWidth = Width[p]+Interval;

			//マウス選択取得
			if( x >= DrawX + RowWidth  * i && x <= DrawX + RowWidth * i + Width[i] ){
				if( y >= DrawY && y <= DrawY + Height ){
					SelectNo = i;
					break;
				}
			}
		}
	}

	//メニューを選択していなければフラグを折る(ListMinで引いてるのは、値を渡すときにListMinを加算してしまうため)
	if( i+ListMin == ListMax ) SelectNo = AtherNo-ListMin;

}

/*メニュー描画処理*/
void MenuClass::Draw(){
	//変数宣言
	int RowWidth = 0;
	static int FirstFlag;
	static int FontHandle;

	//フォント関連設定
	if( DrawFlag == 1 ){
		if( FontFamily == MENU::GOSIC ) ChangeFont("ＭＳ ゴシック");
		if( FontFamily == MENU::MINTYO) ChangeFont("ＭＳ 明朝");

		if( FirstFlag == 0 ){
			FontHandle = CreateFontToHandle( NULL , FontSize , -1 , DX_FONTTYPE_ANTIALIASING );
			FirstFlag++;
		}
		SetFontSize(FontSize);
	}

	//メニュー描画(縦並びの場合)
	if( DirectionFlag == MENU::COL ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			//if( SelectNo == i ) TextColor = GetColor(255,0,0);
			//else				TextColor = GetColor(40,40,40);


			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX , DrawY + ( Interval + Height ) * i , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawStringShadow( DrawX , DrawY + ( Interval + Height ) * i , DrawText[i] , TextColor , GetColor(0,0,0));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

	//メニュー描画(横並びの場合)
	if( DirectionFlag == MENU::ROW ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			//列の現在地までの横幅を取得
			for( int p=0 ; p<i ; p++ ) RowWidth = Width[p]+Interval;

			//オブジェクト描画
			if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX + RowWidth * i,DrawY , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawString( DrawX + RowWidth * i,DrawY , DrawText[i] , TextColor ); 
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

}

/*選択中番号取得*/
int MenuClass::GetSelectNo(){
	return SelectNo+ListMin;
}


/*----------------------
 | セーブメニュークラス |
  ----------------------*/
/*初期化*/
SaveMenuClass::SaveMenuClass(MenuArg_rec &MenuArg):MenuClass(MenuArg){}

/*セーブデータ描画*/
void SaveMenuClass::Draw(int Page){
	//変数宣言
	//char Str[256];
	std::vector<std::string> Str(2);
	char TmpDateText[100];

	//定数
	enum{SCENE,TEXT,SERIF};
	enum{YEAR,MON,DAY};
	enum{DATE};
	const int FontSize = 24;

	//フォントサイズセット
	SetFontSize(FontSize);

	//項目数繰り返す
	for( int i=0 ; i<ListMax-ListMin ; i++ ){
		//データがあれば、情報を代入
		if( SaveDate[i][YEAR] != 0){
			//データ加工
			sprintf(TmpDateText,"%d年%d月%d日",SaveDate[i][YEAR],SaveDate[i][MON],SaveDate[i][DAY]);
			if( strlen( SaveText[i] ) > 40 ){
				SaveText[i][42] = '.';
				SaveText[i][43] = '.';
				SaveText[i][44] = '.';
				SaveText[i][45] = '\0';
			}

			//加工データ代入
			Str[DATE] = TmpDateText;
			Str[TEXT] = SaveText[i];
		}else{
			Str[DATE] = "Not Found.";
			Str[TEXT] = "";
		}

		//背景描画
		if( SelectNo == i )		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
		/******************春のマジックナンバー祭り****************/
		DrawBox(DrawX+5,DrawY+Height*i+5,DrawX+Width[i]-5,Height+60+(Height*i)-5,GetColor(30,30,30),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		//データ描画
		DrawString(DrawX+FontSize,DrawY+30+(Height*i),Str[DATE].c_str(),GetColor(255,255,255));
		DrawString(DrawX+FontSize,DrawY+30+40+((Height)*i),Str[TEXT].c_str(),GetColor(255,255,255));

		//ページ番号描画
		DrawFormatString(1000,20,GetColor(255,255,255),"― %dページ ―",Page+1);
	}
}

/*セーブデータ更新*/
void SaveMenuClass::UpdateData(Dvector_i Date,std::vector<char*> Text){
	this->SaveDate = Date;
	this->SaveText = Text;
}

/*------------------------
 | タイトルメニュークラス |
  ------------------------*/
/*初期化*/
TitleMenuClass::TitleMenuClass(MenuArg_rec &MenuArg):MenuClass(MenuArg){}

/*描画*/
void TitleMenuClass::Draw(){
	//変数宣言
	int RowWidth = 0;
	static int FirstFlag;
	static int FontHandle;

	//フォント関連設定
	if( DrawFlag == 1 ){
		if( FontFamily == MENU::GOSIC ) ChangeFont("ＭＳ ゴシック");
		if( FontFamily == MENU::MINTYO) ChangeFont("ＭＳ 明朝");

		if( FirstFlag == 0 ){
			FontHandle = CreateFontToHandle( NULL , FontSize , -1 , DX_FONTTYPE_ANTIALIASING );
			FirstFlag++;
		}
		SetFontSize(FontSize);
	}

	//メニュー描画(縦並びの場合)
	if( DirectionFlag == MENU::COL ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			//if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			if( SelectNo == i ) TextColor = GetColor(255,0,0);
			else				TextColor = GetColor(40,40,40);
			
			//DrawStringS(DrawX,DrawY-50,"かわしぃ",GetColor(255,255,255),28);

			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX , DrawY + ( Interval + Height ) * i , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawStringShadow( DrawX , DrawY + ( Interval + Height ) * i , DrawText[i] , TextColor , GetColor(230,230,230));
			//SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

	//メニュー描画(横並びの場合)
	if( DirectionFlag == MENU::ROW ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			//列の現在地までの横幅を取得
			for( int p=0 ; p<i ; p++ ) RowWidth = Width[p]+Interval;

			//オブジェクト描画
			if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX + RowWidth * i,DrawY , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawString( DrawX + RowWidth * i,DrawY , DrawText[i] , TextColor ); 
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}
}


/*--------------------------
 | コンフィグメニュークラス |
  --------------------------*/
/*初期化*/
ConfigListClass::ConfigListClass(int SetNo,MenuArg_rec &MenuArg):MenuClass(MenuArg){
	this->SetNo = SetNo;
}

/*コンフィグメニュー描画*/
void ConfigListClass::Draw(){
	//変数宣言
	int RowWidth = 0;
	static int FirstFlag;
	static int FontHandle;

	//フォント関連設定
	if( FontFamily == MENU::GOSIC ) ChangeFont("ＭＳ ゴシック");
	if( FontFamily == MENU::MINTYO) ChangeFont("ＭＳ 明朝");
	//SetFontSize(FontSize);

	if( FirstFlag == 0 ){
		FontHandle = CreateFontToHandle( NULL , FontSize , -1 , DX_FONTTYPE_ANTIALIASING );
		FirstFlag++;
	}

	//メニュー描画
	for( int i=0 ; i<ListMax-ListMin ; i++ ){
		//列の現在地までの横幅を取得
		for( int p=0 ; p<i ; p++ ) RowWidth = Width[p]+Interval;

		//オブジェクト描画
		if( SelectNo == i || SetNo == i ){
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			//SetDrawBlendMode(DX_BLENDMODE_ADD,255);
			TextColor = GetColor(255,80,80);
		}else TextColor = GetColor(255,255,255);
		//if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX + RowWidth * i,DrawY , DrawHandle[i] , TRUE );
		if( DrawFlag == MENU::TEXT )  DrawStringToHandle( DrawX + RowWidth * i,DrawY , DrawText[i] , TextColor , MenuFontHandle ); 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}


}


/*----------------------------
 | シークレットメニュークラス |
  ----------------------------*/
/*初期化*/
SecretMenuClass::SecretMenuClass(MenuArg_rec &MenuArg):MenuClass(MenuArg){}

/*描画*/
void SecretMenuClass::Draw(int SetNo){
	//変数宣言
	int RowWidth = 0;
	static int FirstFlag;
	static int FontHandle;

	//フォント関連設定
	if( DrawFlag == 1 ){
		if( FontFamily == MENU::GOSIC ) ChangeFont("ＭＳ ゴシック");
		if( FontFamily == MENU::MINTYO) ChangeFont("ＭＳ 明朝");

		if( FirstFlag == 0 ){
			FontHandle = CreateFontToHandle( NULL , FontSize , -1 , DX_FONTTYPE_ANTIALIASING );
			FirstFlag++;
		}
		SetFontSize(FontSize);
	}

	//メニュー描画(縦並びの場合)
	if( DirectionFlag == MENU::COL ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			//if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			if( SelectNo == i || SetNo == i ) TextColor = GetColor(255,0,0);
			else				TextColor = GetColor(255,255,255);


			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX , DrawY + ( Interval + Height ) * i , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawStringShadow( DrawX , DrawY + ( Interval + Height ) * i , DrawText[i] , TextColor , GetColor(0,0,0));
			//SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

	//メニュー描画(横並びの場合)
	if( DirectionFlag == MENU::ROW ){
		for( int i=0 ; i<ListMax-ListMin ; i++ ){
			//列の現在地までの横幅を取得
			for( int p=0 ; p<i ; p++ ) RowWidth = Width[p]+Interval;

			//オブジェクト描画
			if( SelectNo == i ) SetDrawBlendMode(DX_BLENDMODE_ALPHA,AlphaNo);
			if( DrawFlag == MENU::IMAGE ) DrawGraph(  DrawX + RowWidth * i,DrawY , DrawHandle[i] , TRUE );
			if( DrawFlag == MENU::TEXT )  DrawString( DrawX + RowWidth * i,DrawY , DrawText[i] , TextColor ); 
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

}