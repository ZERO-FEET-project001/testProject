#include<stdio.h>

/*=================================================================
			ファイルの読み込み関数
			戻り値　TRUE、FALSE
			引　数　ファイルネーム、
			概　要　ファイルの読み込み
=================================================================*/
int SetReadFile(unsigned char *work,char *filename)
{
	FILE *fp;
	fp = fopen(filename,"rb");

	if(fp ==NULL)
	{
		return false;
	}

	fread(work,sizeof(unsigned char),0x1000,fp);
	fclose(fp);
	return true;
};
/*=================================================================
			データの読み込み関数
			戻り値　データ
			引　数　カウント、
			概　要　データの読み込み
=================================================================*/
int RadeDate(unsigned char *work,int count)
{
	int value=0;
	int i,j=0;

	for( i=0 ; i < count ; i++ )
	{
		//,を吹っ飛ばす!!
		while(*(work+j) != '\n' && *(work+j) != ',')
		{
			j++;
		}
		j++;	
	}

	//終焉を探す
	for(i=j ; *(work+i) != ',' && *(work+i) != '#' ; i++)
	{
		//文字コードを数値に変換
		value = value * 10 + ( *(work+i) - '0' );
	}
	return value;
};
/*=================================================================
			データの設定関数
			戻り値　データ
			引　数　設定場所、HI、WID、
			概　要　データの設定
=================================================================*/
void SetReadDate(int *work,unsigned char *datework,int count)
{
	*(work) = RadeDate(datework,count);
};