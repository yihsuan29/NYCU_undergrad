//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "SelectionSort.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//macro (全部大寫)
#define SWAP(x,y,t) (t=x,x=y,y=t)

//全域變數
int original_data[20][100000];
int data_sort[20][100000];
float BubSortTime[20];
float SelSortTime[20];
float RandGenTime[20];
int n;
int step;
int repeat;

//functions
void RandData(int list[], int n, int range);
void getData(int list1[], int list2[], int n);
void SelectionSort(int list[], int n);
void BubbleSort(int list[], int n);
int BinarySearch(int list[], int n, int target);
void PrintData(int list[], int n,int memo);
void SelfCheck(int list[], int n, int memo);

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//GenerateRandomNumbers
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	n = StrToInt(Edit1->Text); //sort的function也要用n 所以要用全域變數
	repeat = StrToInt(Edit4->Text);
	step = StrToInt(Edit5->Text);
	int range = StrToInt(Edit2->Text);
	clock_t t_begin,t_end;
	int i;
    srand(time(NULL));
	for(i=0;i<repeat;i++)
	{
		t_begin= clock();

		RandData(original_data[i],n+step*i,range);
		t_end= clock();
		if(CheckBox1->Checked) PrintData(original_data[i], n+step*i,1);
		RandGenTime[i] = ((float)(t_end-t_begin)/CLOCKS_PER_SEC);
		Form1->Memo1->Lines->Add("#"+IntToStr(i+1)+". "+"CPU time (sec.)"+FloatToStr(RandGenTime[i]));
        Form1->Memo1->Lines->Add("");
	}
	Form1->Memo1->Lines->Add("------------------------------");
}

//---------------------------------------------------------------------------
//SelectionSort
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	clock_t t_begin,t_end;
	int i;
	for(i=0;i<repeat;i++)
	{
		t_begin= clock();
		getData(data_sort[i],original_data[i],n+step*i);   //不把原始的那個洗掉 不然下一次會sort已經排好的
		SelectionSort(data_sort[i], n+step*i);
		t_end= clock();
		if(CheckBox1->Checked) PrintData(data_sort[i], n+step*i,2);
		SelSortTime[i]=(float)(t_end-t_begin)/CLOCKS_PER_SEC;
		Form1->Memo2->Lines->Add("#"+IntToStr(i+1)+". "+"CPU time (sec.)"+FloatToStr(SelSortTime[i]));
		if(CheckBox2->Checked) SelfCheck(data_sort[i], n+step*i,2);
		Form1->Memo2->Lines->Add("");
	}
	Form1->Memo2->Lines->Add("------------------------------");
}

//---------------------------------------------------------------------------
//BubbleSort
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	clock_t t_begin,t_end;
	int i;
	for(i=0;i<repeat;i++)
	{
		t_begin= clock();
		getData(data_sort[i],original_data[i],n+step*i);
		BubbleSort(data_sort[i], n+step*i);
		t_end= clock();
		if(CheckBox1->Checked) PrintData(data_sort[i], n+step*i,3);
		BubSortTime[i]=(float)(t_end-t_begin)/CLOCKS_PER_SEC;
		Form1->Memo3->Lines->Add("#"+IntToStr(i+1)+". "+"CPU time (sec.)"+FloatToStr(BubSortTime[i]));
		if(CheckBox2->Checked) SelfCheck(data_sort[i], n+step*i,3);
		Form1->Memo3->Lines->Add("");
	}
	Form1->Memo3->Lines->Add("------------------------------");
}

//---------------------------------------------------------------------------
//BinarySearch
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int target = StrToInt(Edit3->Text);
	int i;
	int find;
	for(i=0;i<repeat;i++)
	{
        find=-1;
		find = BinarySearch(data_sort[i],n+step*i,target);
		if(find>=0 && find<n+step*i)
			Form1->Memo4->Lines->Add("#"+IntToStr(i+1)+". "+IntToStr(target)+" has been found in data["+IntToStr(find)+"]");
		else
			Form1->Memo4->Lines->Add("#"+IntToStr(i+1)+". "+IntToStr(target)+" has NOT been found!");
		Form1->Memo4->Lines->Add("");
	}
	Form1->Memo4->Lines->Add("------------------------------");

}

//---------------------------------------------------------------------------
//LoadChart

void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
    int i;
		Chart1->RemoveAllSeries();             // 刪掉預設的
		Chart1->Title->Text->Clear();
		Chart1->Title->Text->Add("Bar Chart of Sorting Time"); //換title
		Chart1->BottomAxis->Title->Caption = "data size";    // x-axis' title
		Chart1->LeftAxis->Title->Caption = "CPU time (sec.)";    // y-axis' title
		//Tbar
		Chart1->AddSeries( new TBarSeries (this) );
		Chart1->Series[0]->Title = "Bubble Sort";
				for (i=0; i<repeat; i++) Chart1->Series[0]->Add( BubSortTime[i], 10000*(i+1) );
		Chart1->AddSeries( new TBarSeries (this) );      // create a new BAR series
		Chart1->Series[1]->Title = "Selection Sort";
				for (i=0; i<repeat; i++) Chart1->Series[1]->Add( SelSortTime[i], 10000*(i+1));

		//Tline
		Chart1->AddSeries( new TLineSeries (this) );
		Chart1->Series[2]->Title = "Bubble Sort";
				for (i=0; i<repeat; i++) Chart1->Series[2]->Add( BubSortTime[i], 10000*(i+1) );
		Chart1->AddSeries( new TLineSeries (this) );      // create a new BAR series
		Chart1->Series[3]->Title = "Selection Sort";
				for (i=0; i<repeat; i++) Chart1->Series[3]->Add( SelSortTime[i], 10000*(i+1));

		//Tarea
		Chart1->AddSeries( new TAreaSeries (this) );
		Chart1->Series[4]->Title = "Bubble Sort";
				for (i=0; i<repeat; i++) Chart1->Series[4]->Add( BubSortTime[i], 10000*(i+1) );
        Chart1->AddSeries( new TAreaSeries (this) );      // create a new BAR series
		Chart1->Series[5]->Title = "Selection Sort";
				for (i=0; i<repeat; i++) Chart1->Series[5]->Add( SelSortTime[i], 10000*(i+1));
		//Tpoint
		Chart1->AddSeries( new TPointSeries (this) );
		Chart1->Series[6]->Title = "Bubble Sort";
				for (i=0; i<repeat; i++) Chart1->Series[6]->Add( BubSortTime[i], 10000*(i+1) );
		Chart1->AddSeries( new TPointSeries (this) );      // create a new BAR series
		Chart1->Series[7]->Title = "Selection Sort";
				for (i=0; i<repeat; i++) Chart1->Series[7]->Add( SelSortTime[i], 10000*(i+1));

		//Tfastline
		Chart1->AddSeries( new TFastLineSeries  (this) );
		Chart1->Series[8]->Title = "Bubble Sort";
				for (i=0; i<repeat; i++) Chart1->Series[8]->Add( BubSortTime[i], 10000*(i+1) );

		Chart1->AddSeries( new TFastLineSeries (this) );      // create a new BAR series
		Chart1->Series[9]->Title = "Selection Sort";
				for (i=0; i<repeat; i++) Chart1->Series[9]->Add( SelSortTime[i], 10000*(i+1));
		for (int i=2; i<10; i++)     // Set marks visible
			{      Chart1->Series[i]->Visible = false;
			}
		for (int i=0; i<2; i++)     // Set marks visible
			{      Chart1->Series[i]->Marks->Visible = true;
					Chart1->Series[i]->Marks->Style = smsValue;
			}

}

//---------------------------------------------------------------------------
//GraphType
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
	int index=(RadioGroup1->ItemIndex);
	int i;
	for ( i=0; i<10; i++)     // Set marks visible
	{
		if(i==index*2||i==index*2+1)
		{
			Chart1->Series[i]->Visible = true;
			if(CheckBox3->Checked)
			{
				Chart1->Series[i]->Marks->Visible = true;
					Chart1->Series[i]->Marks->Style = smsValue;
			}
			else
			{
				Chart1->Series[i]->Marks->Visible = false;
					Chart1->Series[i]->Marks->Style = smsValue;
			}
		}
		else
			Chart1->Series[i]->Visible = false;
	}


}

//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
	int index=(RadioGroup1->ItemIndex);
	int i;
	for ( i=0; i<10; i++)     // Set marks visible
	{
		if((i==index*2||i==index*2+1)&&CheckBox3->Checked)
				Chart1->Series[i]->Marks->Visible = true;
		else
			Chart1->Series[i]->Marks->Visible = false;
		Chart1->Series[i]->Marks->Style = smsValue;
	}



}

//---------------------------------------------------------------------------
void RandData(int list[], int n, int range)
{
	int i;
	for(i=0; i<n ;i++)
	{
		  list[i]= rand()%range+1;
    }

}

//---------------------------------------------------------------------------
void getData(int list1[], int list2[], int n)
{
	int i;
	for(i=0;i<n;i++)
		list1[i]=list2[i];
}

//---------------------------------------------------------------------------
void SelectionSort(int list[], int n)
{
	int i,j,min,tmp;
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			if(list[j]<list[min])
				min=j;
		}
			SWAP(list[i],list[min],tmp);
		/*
		tmp=list[i];
		list[i]=list[min];
		list[min]=tmp;
		*/
	}
}

//---------------------------------------------------------------------------
void BubbleSort(int list[], int n)
{
	int i,j,tmp;
	for(i=0;i<n-1;i++)//做n-1次即可排序完成
	{
		for(j=0;j<n-i-1;j++)//從第0開始 比右邊大就交換又移
		{
			if(list[j]>list[j+1])
				SWAP(list[j],list[j+1],tmp);
		}
	}
}

//---------------------------------------------------------------------------
int BinarySearch(int list[], int n, int target)
{
	int left,right,mid;
	left=0;
	right=n-1;
	while(right-left>=0)
	{
		mid=(left+right+1)/2;
		/*
		cout<<left<<" "<<right<<" "<<mid<<" ";
		cout<<"list[mid]="<<list[mid]<<endl;
		*/
		if(target<list[mid])
			right=mid-1;
		else if(target>list[mid])
			left=mid+1;
		else
			return mid;
	}
	return -1;
}

//---------------------------------------------------------------------------
void PrintData(int list[], int n,int memo)
{
	int i;
	if(memo==1)
	{
		for(i=0;i<n;i++)
		{
			Form1->Memo1->Lines->Add("data["+IntToStr(i)+"]="+list[i]);
		}
	}
	else if(memo==2)
	{
		for(i=0;i<n;i++)
		{
			Form1->Memo2->Lines->Add("data["+IntToStr(i)+"]="+list[i]);
		}
	}
	else if(memo==3)
	{
		for(i=0;i<n;i++)
		{
			Form1->Memo3->Lines->Add("data["+IntToStr(i)+"]="+list[i]);
		}
	}
}

//---------------------------------------------------------------------------
void SelfCheck(int list[], int n, int memo)
{
	int i,j,flag=0;
	for(i=0;i<n-1;i++)
	{
		if(list[i]>list[i+1])
		{
			flag==1;
			break;
		}
	}
	if(memo==2)
	{
		if(flag==1)
		Form1->Memo2->Lines->Add("Self Check: Fail");
		else
			Form1->Memo2->Lines->Add("Self Check: Success!");
	}
	else if(memo==3)
	{
		if(flag==1)
		Form1->Memo3->Lines->Add("Self Check: Fail");
		else
			Form1->Memo3->Lines->Add("Self Check: Success!");
	}

}
//---------------------------------------------------------------------------


