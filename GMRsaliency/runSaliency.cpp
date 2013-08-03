/*
demo for paper "Saliency Detection via Graph-based Manifold Ranking"
by Chuan Yang, Lihe Zhang, Huchuan Lu, Xiang Ruan, and Ming-Hsuan Yang
in CVPR13.
written by Chuan Yang
email: ycscience86@gmail.com
date: 2013.5.7
*/

#include <cstring>
#include <windows.h>
#include <time.h>
#include "Saliency\GMRsaliency.h"

void GetImageNames(char* filepath,vector<string> &imnames);

int main(int argc,char *argv[])
{
	char filepath[MAX_PATH+1];
	sprintf(filepath,"%s*%s",argv[1],argv[2]);
	vector<string> imnames;
	GetImageNames(filepath,imnames);
	Mat sal,img;
	vector<string>::iterator itf=imnames.begin();
	int count=1;
	clock_t nTimeStart;      
    clock_t nTimeStop;       
    nTimeStart = clock();
	for(;itf!=imnames.end();itf++)
	{
		printf("%d\n",count++);
		char imname[MAX_PATH+1];
		sprintf(imname,"%s%s",argv[1],(*itf).c_str());
		img=imread(imname);
		GMRsaliency GMRsal;
		sal=GMRsal.GetSal(img);
		char salname[MAX_PATH+1];
		sprintf(salname,"%s_our.png",imname);
		imwrite(salname,sal*255);
	}
	nTimeStop = clock();
	cout <<"the average running time:"<<(double)(nTimeStop - nTimeStart)/CLOCKS_PER_SEC/(count-1)<<"seconds"<< endl;

	system("pause");
	return 0;
}
void GetImageNames(char* filepath,vector<string> &imnames)
{
	imnames.clear();
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile(filepath , &f);
	if(h != INVALID_HANDLE_VALUE)
	{
		do
		{
			imnames.push_back(f.cFileName);
		} while(FindNextFile(h, &f));

	}
	FindClose(h);	
}
