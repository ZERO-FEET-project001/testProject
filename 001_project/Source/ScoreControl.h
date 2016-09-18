#include "TaskFuncs.h"
#include <math.h> 

/*========================================================

				ScoreControl

========================================================*/

class ScoreControl {

	//タスクコントロールのポインタの保持
	CTaskCtrl*	m_g_pCTaskCtrl;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//画像用ポインタの保持
	SetTexture* m_pt_Texture ;

	//今現在のスコア
	INT m_Score;
	//スコア追加される
	INT m_ScoreDisplay;


public:

	//コンストラクタ
	ScoreControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* m_pt_Texture);
	//初期化関数
	void	Init();
	//main関数
	void	main();
	//GameOver時のDisplay(表示)
	void	GameOverScoreDisplay();
};

