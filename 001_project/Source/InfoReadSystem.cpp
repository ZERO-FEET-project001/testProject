#include<stdio.h>

/*=================================================================
			�t�@�C���̓ǂݍ��݊֐�
			�߂�l�@TRUE�AFALSE
			���@���@�t�@�C���l�[���A
			�T�@�v�@�t�@�C���̓ǂݍ���
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
			�f�[�^�̓ǂݍ��݊֐�
			�߂�l�@�f�[�^
			���@���@�J�E���g�A
			�T�@�v�@�f�[�^�̓ǂݍ���
=================================================================*/
int RadeDate(unsigned char *work,int count)
{
	int value=0;
	int i,j=0;

	for( i=0 ; i < count ; i++ )
	{
		//,�𐁂���΂�!!
		while(*(work+j) != '\n' && *(work+j) != ',')
		{
			j++;
		}
		j++;	
	}

	//�I����T��
	for(i=j ; *(work+i) != ',' && *(work+i) != '#' ; i++)
	{
		//�����R�[�h�𐔒l�ɕϊ�
		value = value * 10 + ( *(work+i) - '0' );
	}
	return value;
};
/*=================================================================
			�f�[�^�̐ݒ�֐�
			�߂�l�@�f�[�^
			���@���@�ݒ�ꏊ�AHI�AWID�A
			�T�@�v�@�f�[�^�̐ݒ�
=================================================================*/
void SetReadDate(int *work,unsigned char *datework,int count)
{
	*(work) = RadeDate(datework,count);
};