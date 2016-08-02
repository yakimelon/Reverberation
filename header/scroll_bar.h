/*----------------------
 | スクロールバークラス |
  ----------------------*/
class ScrollBarClass{
	private:
		int BarDrawX;					//描画X座標
		int BarDrawY;					//描画Y座標
		int BarWidth;					//スクロールバー横サイズ
		int BarHeight;					//スクロールバー縦サイズ
		int MaxScroll;					//スクロール最大値
		int MinScroll;					//スクロール最小値
		int OldDrawY;					//クリックされる前のY座標
		int NewDrawY;					//クリックされた時のY座標
		double MoveScroll;					//移動量
		double MoveAdd;					//移動量追加
		int SubHeight;					//描画オブジェクトが画面からはみ出してる量

	public:
		ScrollBarClass();				//初期化
		double  MoveCalc();				//移動量計算
		void SizeCalc(int DrawHeight);	//スクロールバーサイズ計算
		void DrawScrollBar();			//スクロールバー描画
};