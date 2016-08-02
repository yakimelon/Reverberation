/*----------------------
 | アニメーションクラス |
  ----------------------*/
class AnimeClass{
	private:
		int FadeFlag;			//フェード完了フラグ
		int Count;				//フェード時のカウンタ

	public:
		AnimeClass();
		int	 FadeIn(int Speed);	//画面全体フェードイン処理(黒→白)
		void Reset();			//フラグを全て初期化
}; 
 

