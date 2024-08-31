//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <time.h>
#include "SortingAlgorithm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

int * OriginData;
int * SortData;
int n;
int i,j,k,l;
int range;
int t;
int num;
float **SortTime;

#define SWAP(x,y)(tmp=x,x=y,y=tmp)
void DrawGram ();


//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//Data Generate
void DataGenerate (int num)
{
	OriginData=(int *)malloc(num *sizeof(int));
	String s="";
	for(j=0;j<num;j++)
	{
		OriginData[j]=rand()%range+1;
		s+=IntToStr(OriginData[j])+" ";
	}
	if(Form2->CheckBox10->Checked)Form2->Memo1->Lines->Add(s);
}
void CopyData (int num)
{
	SortData=(int *)malloc(num *sizeof(int));
	for(j=0;j<num;j++)
	{
		SortData[j]=OriginData[j];
	}
}
//---------------------------------------------------------------------------
//SelectionSort
void SelectionSort (int * data, int num)
{
	int min,tmp=0;
	for(j=0;j<num;j++)
	{
		min = j;
		for(k=j;k<num;k++)
			if(data[k]<data[min])
				min=k;
		if(min!=j)SWAP(data[min],data[j]);
	}
}
//---------------------------------------------------------------------------
//BubbleSort
void BubbleSort (int * data, int num)
{
	int min,tmp=0;
	for(j=0;j<num;j++)
	{
		min = j;
		for(k=j;k<num;k++)
			if(data[k]<data[min])
				SWAP(data[min],data[k]);
	}
}
//---------------------------------------------------------------------------
//InsertionSort
void InsertionSort (int * data, int num)
{
	int x;
	for(j=1;j<num;j++)
	{
		x=data[j];
		k=j;
		while(k>0&&x<data[k-1])
		{
			data[k]=data[k-1];
			k--;
		}
        data[k]=x;
	}
}
//---------------------------------------------------------------------------
//QuickSort (Recursive)
void QuickSort (int * data, int left,int right)
{
	int tmpi,tmpj,target,tmp=0;
	if(left<right)
	{
		tmpi=left+1;
		tmpj=right;
		target=data[left];
		do
		{
			while(tmpi<=tmpj&&data[tmpi]<target)tmpi++;
			while(tmpi<=tmpj&&data[tmpj]>=target)tmpj--;
			if(tmpi<tmpj)SWAP(data[tmpi],data[tmpj]);
		}while(tmpi<tmpj);
		if(left<tmpj)SWAP(data[left],data[tmpj]);
		QuickSort(data,left,tmpj-1);
		QuickSort(data,tmpj+1,right);
    }
}
//---------------------------------------------------------------------------
//QuickSort (Non-Recursive)
struct StackNode
{
	int l;
	int r;
	struct StackNode * next;
};
struct StackNode * top;
void PushStack( int left, int right)
{
	struct StackNode * old_top= top;
	top =(struct StackNode*)malloc(sizeof(struct StackNode));
	top->l=left;
	top->r=right;
	top->next=old_top;
}
struct StackNode * PopStack()
{
	struct StackNode * old_top= top;
	top=old_top->next;
	return old_top;
}
void QuickSortNon (int * data, int left,int right)
{
	top=NULL;
	PushStack(left,right);
	while(top!=NULL)
	{
		struct StackNode * node= PopStack();
		left=node->l;
		right=node->r;
		int target = data[left];
		int tmpi=left+1;
		int tmpj = right;
		int tmp;
		do
		{
			while(tmpi<=tmpj&&data[tmpi]<target)tmpi++;
			while(tmpi<=tmpj&&data[tmpj]>=target)tmpj--;
			if(tmpi<tmpj)SWAP(data[tmpi],data[tmpj]);
		}while(tmpi<tmpj);
		if(left<tmpj)SWAP(data[left],data[tmpj]);
		if(left<tmpj-1)PushStack(left,tmpj-1);
		if(tmpj+1<right)PushStack(tmpj+1,right);
	}
}
//---------------------------------------------------------------------------
//MergeSort (Recursive)
void Merge(int *C,int c,int *A,int a,int m,int*B,int b,int o)
{
	int *tmpArray=(int*)malloc((o+1)*sizeof(int));
	int p;
	for(p=a;p<=m;p++)
		tmpArray[p]=A[p];
	for(p=b;p<=o;p++)
		tmpArray[p]=B[p];
	while(a<=m&&b<=o)
	{
		if(tmpArray[a]<tmpArray[b])
			C[c++]=tmpArray[a++];
		else
			C[c++]=tmpArray[b++];
	}
	while(a<=m)
		C[c++]=tmpArray[a++];
	while(b<=o)
		C[c++]=tmpArray[b++];

}
void MergeSort(int * data, int left,int right)
{
	int m;
	if(left<right)
	{
		m=(left+right)/2;
		MergeSort(data,left,m);
		MergeSort(data,m+1,right);
		Merge(data,left,data,left,m,data,m+1,right);
	}
}
//MergeSort (NonRecursive)
void MergeSortNon(int * data, int num)
{
	int len=1,tmpi;
	while(len<=num)
	{
		tmpi=0;
		while(tmpi<num-len)
		{
			if(tmpi+2*len<num)
				Merge(data,tmpi,data,tmpi,tmpi+len-1,data,tmpi+len,tmpi+len*2-1);
			else
				Merge(data,tmpi,data,tmpi,tmpi+len-1,data,tmpi+len,num-1);
            tmpi+=2*len;
        }
		len*=2;
    }
}
//---------------------------------------------------------------------------
//HeapSort
int* Restore(int * data,int s, int r)
{
	int tmpi=s,tmpj,tmp;
	while(tmpi<=r/2)
	{
		if(tmpi*2+1>r||data[tmpi*2]<=data[tmpi*2+1])
			tmpj=tmpi*2;
		else
			tmpj=tmpi*2+1;
		if(data[tmpi]<=data[tmpj])
			break;
		SWAP(data[tmpj],data[tmpi]);
		tmpi=tmpj;
	}
	return data;
}
void HeapSort(int * data,int num)
{
	int *tmpArray=(int*)malloc((num+1)*sizeof(int));
	int j;
	for(j=0;j<num;j++)
		tmpArray[j+1]=data[j];
	for(j=num/2;j>=1;j--)
	{
		tmpArray=Restore(tmpArray,j,num);
	}
	for(j=num;j>1;j--)
	{
		SortData[num-j]=tmpArray[1];
		tmpArray[1]=tmpArray[j];
		tmpArray=Restore(tmpArray,1,j-1);
	}
    SortData[num-1]=tmpArray[1];
}
//---------------------------------------------------------------------------
//RadixSort
void RadixSort(int * data,int num)
{
	int max = 0,tmpi,radix=0,digit;
	int *tmpArray=(int*)malloc((num)*sizeof(int));
	int *count=(int*)malloc(10*sizeof(int));
	int *temp=(int*)malloc((num)*sizeof(int));
	int *index=(int*)malloc(10*sizeof(int));
	for (tmpi=0; tmpi<num; tmpi++)
	{
		tmpArray[tmpi]=data[tmpi];
		if (data[tmpi]>max)
			max = data[tmpi];
	}
	while(max!=0)
	{
		radix++;
        max/=10;
	}
	for (tmpi=1; tmpi<=radix; tmpi++)
	{
		for (j=0; j<10; j++)
			count[j]=0;
		for (j=0; j<num; j++)
		{
			digit = tmpArray[j]%10;
			count[digit]++;
		}
		index[0]=0;
		for (j=1;j<10;j++)
			index[j]=index[j-1]+count[j-1];
		for (j=0; j<num; j++)
		{
			digit = tmpArray[j]%10;
			temp[index[digit]++] = data[j];
		}
		for (j=0; j<num; j++)
		{
			tmpArray[j]=data[j] = temp[j];
		}
		int tmpk=tmpi;
		while(tmpk>0)
		{
			for (j=0; j<num; j++)
				tmpArray[j]/=10;
			tmpk--;
        }
	}
}
//---------------------------------------------------------------------------
int SelfCheck(int* data)
{
	int p;
	for(p=1;p<num;p++)
		if(data[p]<data[p-1])
			return 0;
	return 1;
}
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	t=StrToInt(Edit1->Text);
	n=StrToInt(Edit2->Text);
	range=StrToInt(Edit3->Text);
	String s;
	SortTime=(float**)malloc(9*sizeof(float*));
	for(i=0;i<9;i++)
	{
		SortTime[i]=(float*)malloc(t*sizeof(float));
		for(j=0;j<t;j++)
			SortTime[i][j]=0;
	}
	clock_t t_begin,t_end;
	srand(time(NULL));
	for(i=1;i<=t;i++)
	{
		num=i*n;
		DataGenerate (num);
		Form2->Memo1->Lines->Add("[Data Size: "+IntToStr(num)+"]");
		int flag=SelfCheck(OriginData);
		if(flag==0)
			Form2->Memo1->Lines->Add("sorted: false");
		else
			Form2->Memo1->Lines->Add("sorted: true");
		Form2->Memo1->Lines->Add("");
		if(CheckBox1->Checked)
		{
			CopyData(num);
			t_begin= clock();
			SelectionSort(SortData,num);
			t_end= clock();
			SortTime[0][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
			if(Form2->CheckBox10->Checked)
			{
				s="Selection Sort:";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Selection Sort Time:"+FloatToStr(SortTime[0][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox2->Checked)
		{
			CopyData(num);
			t_begin= clock();
			BubbleSort(SortData,num);
            t_end= clock();
			SortTime[1][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
			if(Form2->CheckBox10->Checked)
			{
				s="Bubble  Sort:";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Bubble Sort Time:"+FloatToStr(SortTime[1][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox3->Checked)
		{
			CopyData(num);
			t_begin= clock();
			InsertionSort(SortData,num);
            t_end= clock();
			SortTime[2][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Insertion Sort:";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Insertion Sort Time:"+FloatToStr(SortTime[2][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
        if(CheckBox4->Checked)
		{
			CopyData(num);
			t_begin= clock();
			QuickSort(SortData,0,num-1);
            t_end= clock();
			SortTime[3][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Quick Sort(recursive):";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Quick Sort(recursive) Time:"+FloatToStr(SortTime[3][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox5->Checked)
		{
			CopyData(num);
			t_begin= clock();
			QuickSortNon(SortData,0,num-1);
            t_end= clock();
			SortTime[4][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Quick Sort(non-recursive):";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Quick Sort(non-recursive) Time:"+FloatToStr(SortTime[4][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox6->Checked)
		{
			CopyData(num);
			t_begin= clock();
			MergeSort(SortData,0,num-1);
            t_end= clock();
			SortTime[5][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Merge Sort(recursive):";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Merge Sort(recursive) Time:"+FloatToStr(SortTime[5][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox7->Checked)
		{
			CopyData(num);
			t_begin= clock();
			MergeSortNon(SortData,num);
            t_end= clock();
			SortTime[6][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Merge Sort(non-recursive):";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Merge Sort(non-recursive) Time:"+FloatToStr(SortTime[6][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");

		}
		if(CheckBox8->Checked)
		{
			CopyData(num);
			t_begin= clock();
			HeapSort(SortData,num);
            t_end= clock();
			SortTime[7][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Heap Sort:";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Heap Sort Time:"+FloatToStr(SortTime[7][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
		if(CheckBox9->Checked)
		{
			CopyData(num);
            t_begin= clock();
			RadixSort(SortData,num);
            t_end= clock();
			SortTime[8][i]= ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
            if(Form2->CheckBox10->Checked)
			{
				s="Radix Sort:";
				for(j=0;j<num;j++)
					s+=IntToStr(SortData[j])+" ";
				Form2->Memo1->Lines->Add(s);
			}
			s="Radix Sort Time:"+FloatToStr(SortTime[8][i]);
			Form2->Memo1->Lines->Add(s);
			flag=SelfCheck(SortData);
			if(flag==0)
				Form2->Memo1->Lines->Add("sorted: false");
			else
				Form2->Memo1->Lines->Add("sorted: true");
			Form2->Memo1->Lines->Add("");
		}
        Form2->Memo1->Lines->Add("===================");


	}
    DrawGram ();
}
void DrawGram ()
{
	Form2->Chart1->RemoveAllSeries();             // �R���w�]��
	Form2->Chart1->Title->Text->Clear();
	Form2->Chart1->Title->Text->Add("Line Chart of Sorting Time"); //��title
	Form2->Chart1->BottomAxis->Title->Caption = "data size";    // x-axis' title
	Form2->Chart1->LeftAxis->Title->Caption = "CPU time (sec.)";    // y-axis' title

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[0]->Title = "Selection";
	Form2->Chart1->Series[0]->Color =TColor(RGB(255,147,147));
	for (i=1; i<=t; i++) Form2->Chart1->Series[0]->Add( SortTime[0][i], n*(i) );
	if(Form2->CheckBox1->Checked)Form2->Chart1->Series[0]->Visible = true;
	else  Form2->Chart1->Series[0]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[1]->Title = "Bubble";
	Form2->Chart1->Series[1]->Color =TColor(RGB(255,180,138));
	for (i=1; i<=t; i++) Form2->Chart1->Series[1]->Add( SortTime[1][i], n*(i) );
	if(Form2->CheckBox2->Checked)Form2->Chart1->Series[1]->Visible = true;
	else  Form2->Chart1->Series[1]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[2]->Title = "Insertion";
	Form2->Chart1->Series[2]->Color =TColor(RGB(255,232,138));
	for (i=1; i<=t; i++) Form2->Chart1->Series[2]->Add( SortTime[2][i], n*(i) );
	if(Form2->CheckBox3->Checked)Form2->Chart1->Series[2]->Visible = true;
	else  Form2->Chart1->Series[2]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[3]->Title = "Quick(rec)";
	Form2->Chart1->Series[3]->Color =TColor(RGB(185,254,139));
	for (i=1; i<=t; i++) Form2->Chart1->Series[3]->Add( SortTime[3][i], n*(i) );
	if(Form2->CheckBox4->Checked)Form2->Chart1->Series[3]->Visible = true;
	else  Form2->Chart1->Series[3]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[4]->Title = "Quick(non)";
	Form2->Chart1->Series[4]->Color =TColor(RGB(140,253,197));
	for (i=1; i<=t; i++) Form2->Chart1->Series[4]->Add( SortTime[4][i], n*(i) );
	if(Form2->CheckBox5->Checked)Form2->Chart1->Series[4]->Visible = true;
	else  Form2->Chart1->Series[4]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[5]->Title = "Merge(rec)";
	Form2->Chart1->Series[5]->Color =TColor(RGB(158,237,254));
	for (i=1; i<=t; i++) Form2->Chart1->Series[5]->Add( SortTime[5][i], n*(i) );
	if(Form2->CheckBox6->Checked)Form2->Chart1->Series[5]->Visible = true;
	else  Form2->Chart1->Series[5]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[6]->Title = "Merge(non)";
	Form2->Chart1->Series[6]->Color =TColor(RGB(138,197,255));
	for (i=1; i<=t; i++) Form2->Chart1->Series[6]->Add( SortTime[6][i], n*(i) );
	if(Form2->CheckBox7->Checked)Form2->Chart1->Series[6]->Visible = true;
	else  Form2->Chart1->Series[6]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[7]->Title = "Heap";
	Form2->Chart1->Series[7]->Color =TColor(RGB(170,128,255));
	for (i=1; i<=t; i++) Form2->Chart1->Series[7]->Add( SortTime[7][i], n*(i) );
	if(Form2->CheckBox8->Checked)Form2->Chart1->Series[7]->Visible = true;
	else  Form2->Chart1->Series[7]->Visible = false;

	Form2->Chart1->AddSeries( new TLineSeries (Form2) );
	Form2->Chart1->Series[8]->Title = "Radix";
	Form2->Chart1->Series[8]->Color =TColor (RGB(223,138,255));
	for (i=1; i<=t; i++) Form2->Chart1->Series[8]->Add( SortTime[8][i], n*(i) );
	if(Form2->CheckBox9->Checked)Form2->Chart1->Series[8]->Visible = true;
	else  Form2->Chart1->Series[8]->Visible = false;
}


