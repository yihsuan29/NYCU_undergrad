//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MagicSquare.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define SWAP(x,y,t) (t=x,x=y,y=t)
//---------------------------------------------------------------------------
//计
void MagicSquare(int square[100][100],int n,int i_tmp, int j_tmp, int start);
//4计
void MagicSquare4M(int square[100][100],int n);
//案计
void MagicSquare4Mplus2(int square[100][100],int n);
//Memo
void PrintSquare(int square[100][100],int n);
//StringGrid
void PrintSquareInGrid(int square[100][100],int n,int flag);
//浪琩︽计羆㎝
void CheckSum(int square[100][100],int n);
//---------------------------------------------------------------------------
// 办跑计
int square[100][100];
int direct;
int start;
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	int n = StrToInt(Edit1->Text);
	start=RadioGroup1->ItemIndex;
	direct=RadioGroup2->ItemIndex;
	if(n<3)
	{
		Form2->Memo1->Lines->Add("-------------------------------------");
		Form2->Memo1->Lines->Add("Failed! Please input a number that is >=3");

	}
	else
	{
		Form2->Memo1->Lines->Add("---------------"+IntToStr(n)+"x"+IntToStr(n)+"------------------");
		if(n%2==1)
		{
			if(direct==0)
				MagicSquare(square,n,-1,-1,start);
			else if(direct==1)
				MagicSquare(square,n,-1,1,start);
			else if(direct==2)
				MagicSquare(square,n,1,-1,start);
			else
				MagicSquare(square,n,1,1,start);
		}
		else if(n%4==0)
			MagicSquare4M(square,n);
		else
			MagicSquare4Mplus2(square,n);
		if(CheckBox1->Checked) CheckSum(square,n);
		PrintSquare(square,n);
		if(CheckBox1->Checked) PrintSquareInGrid(square,n,1);
		else  PrintSquareInGrid(square,n,0);
    }
}
//---------------------------------------------------------------------------
//案计ぃ匡よ
void __fastcall TForm2::Edit1Change(TObject *Sender)
{
	if((Edit1->Text)!="")
	 {
		 int n = StrToInt(Edit1->Text);
		 int i;
		 if(n%2==0)
		 {
			for(i=0;i<4;i++)
			{
				RadioGroup1->Controls[i]->Enabled=false;
				RadioGroup2->Controls[i]->Enabled=false;
			}
			RadioGroup1->ItemIndex=-1;
			RadioGroup2->ItemIndex=-1;
		 }
		 else
		 {
			for(i=0;i<4;i++)
			{
				RadioGroup1->Controls[i]->Enabled=true;
				RadioGroup2->Controls[i]->Enabled=true;
			}
			//箇砞 癬﹍よ よ┕オ
			RadioGroup1->ItemIndex=0;
			RadioGroup2->ItemIndex=0;
            RadioGroup2->Controls[2]->Enabled=false;
			RadioGroup2->Controls[3]->Enabled=false;
		 }
     }
}
//---------------------------------------------------------------------------
//匡拒癬﹍竚璶玛ぃ︽よ
void __fastcall TForm2::RadioGroup1Click(TObject *Sender)
{
	start=RadioGroup1->ItemIndex;
	RadioGroup2->ItemIndex=-1;
	if(start==0)
	{
			RadioGroup2->ItemIndex=0;
			RadioGroup2->Controls[0]->Enabled=true;
			RadioGroup2->Controls[1]->Enabled=true;
			RadioGroup2->Controls[2]->Enabled=false;
			RadioGroup2->Controls[3]->Enabled=false;
	}
	else if(start==1)
	{
			RadioGroup2->ItemIndex=1;
			RadioGroup2->Controls[0]->Enabled=false;
			RadioGroup2->Controls[1]->Enabled=true;
			RadioGroup2->Controls[2]->Enabled=false;
			RadioGroup2->Controls[3]->Enabled=true;
	}
	else if(start==2)
	{
			RadioGroup2->ItemIndex=2;
			RadioGroup2->Controls[0]->Enabled=false;
			RadioGroup2->Controls[1]->Enabled=false;
			RadioGroup2->Controls[2]->Enabled=true;
			RadioGroup2->Controls[3]->Enabled=true;
	}
	else
	{
            RadioGroup2->ItemIndex=0;
			RadioGroup2->Controls[0]->Enabled=true;
			RadioGroup2->Controls[1]->Enabled=false;
			RadioGroup2->Controls[2]->Enabled=true;
			RadioGroup2->Controls[3]->Enabled=false;
	}

}
//---------------------------------------------------------------------------
//计
void MagicSquare(int square[100][100],int n,int i_tmp, int j_tmp, int start)
{
	int i,j,k,l,data;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			square[i][j]=0;
	//癬﹍竚
	if(start==0)
	{
		i=0;
		j=(n-1)/2;
	}
	else if(start==1)
	{
		i=(n-1)/2;
		j=n-1;
	}
	else if(start==2)
	{
		i=n-1;
		j=(n-1)/2;
    }
	else
	{	i=(n-1)/2;
		j=0;
	}

	square[i][j]=1;
	data=2;
	while(data<=n*n)
	{
		k=(n+i+i_tmp)%n;
		l=(n+j+j_tmp)%n;
		//竒恶筁(沮癬﹍竚ぃτ跑)
		if(square[k][l]>0)
		{
			if(start==0||start==2)
				i=(i-i_tmp+n)%n;
			else
                j=(j-j_tmp+n)%n;
		}

		else
		{
			i=k;
			j=l;
		}
		square[i][j]=data;
		data++;
	}
}
//---------------------------------------------------------------------------
//计
void MagicSquare4M(int square[100][100],int n)
{
    int i,j,k,flag;
	int data=1;
	int used[n*n+1];
	for(i=0;i<=n*n;i++)
		used[i]=0;


	//㏕﹚à蛤い丁
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			flag=0;
			//オ
			if(i<n/4&&j<n/4)
				flag=1;
			//
			else if(i<n/4&&j>=3*n/4)
				flag=1;
			//オ
			else if(i>=3*n/4&&j<n/4)
				flag=1;
			//
			else if(i>=3*n/4&&j>=3*n/4)
				flag=1;
			//い丁
			else if(i>=n/4&&i<3*n/4&&j>=n/4&&j<3*n/4)
				flag=1;
			if(flag==1)
			{
				square[i][j]=data;
				used[data]=1;
			}
			else
				square[i][j]=0;
			data++;
		}
	data=n*n;
	//р逞竚恶Ч
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(square[i][j]==0)
			{
				//眖程⊿Τノ秨﹍恶
				for(k=data;k>0;k--)
				{

					if(used[k]==0)
					{
						square[i][j]=k;
						used[k]=1;
						break;
					}
				}
				data=k;
			}
		}
}
//---------------------------------------------------------------------------
//案计
void MagicSquare4Mplus2(int square[100][100],int n)
{
    int m=n/2;
	int l=m/2;
	int i,j;
	//オBlock
	MagicSquare(square,m,-1,1,0);
	//Block
	for(i=m;i<n;i++)
		for(j=m;j<n;j++)
			square[i][j]=square[i-m][j-m]+m*m;
	//Block
	for(i=0;i<m;i++)
		for(j=m;j<n;j++)
			square[i][j]=square[i][j-m]+m*m*2;
	//オBlock
	for(i=m;i<n;i++)
		for(j=0;j<m;j++)
			square[i][j]=square[i-m][j]+m*m*3;

	//オオユ传(疭)
	for(i=0;i<m;i++)
	{
		//い丁
		if(i==l)
		{
			for(j=1;j<l+1;j++)
			{
				square[i][j]+=m*m*3;//传Θオ竚计
			}
		}
		else
		{
			for(j=0;j<l;j++)
			{
				square[i][j]+=m*m*3;//传Θオ竚计
			}

		}
	}
	for(i=m;i<n;i++)
	{
		//い丁
		if(i==n-l-1)
		{
			for(j=1;j<l+1;j++)
			{
				square[i][j]-=m*m*3;//传Θオ竚计
			}
		}
		else
		{
			for(j=0;j<l;j++)
			{
				square[i][j]-=m*m*3;//传Θオ竚计
			}

		}
	}
	//ユ传(疭)
	for(i=0;i<m;i++)
		for(j=n-l+1;j<n;j++)
		{
			int tmp;
			SWAP(square[i][j],square[i+m][j],tmp);
		}
}
//---------------------------------------------------------------------------
//Memo
void PrintSquare(int square[100][100],int n)
{
	int i,j;
	String s;
	for(i=0;i<n;i++)
	{
		s="";
		for(j=0;j<n;j++)
		{
			s+="\t";
			if(square[i][j]<10)
				s+="  ";
			else if(square[i][j]<100)
				s+=" ";
			s+=IntToStr(square[i][j]);

		}
		if(Form2->CheckBox1->Checked) s+="\t---"+IntToStr(square[i][n]);
		Form2->Memo1->Lines->Add(s);
	}
	if(Form2->CheckBox1->Checked)
	{
		s="";
		for(j=0;j<n;j++)
		{
			s+="\t";
			s+="|"+IntToStr(square[n][j]);
		}
		s+="\t\\"+IntToStr(square[n][n])+"\t/"+IntToStr(square[n][n+1]);
		Form2->Memo1->Lines->Add(s);
	}
}
//---------------------------------------------------------------------------
//StringGrid
void PrintSquareInGrid(int square[100][100],int n,int flag)
{
    int i,j;
	for(int i=0;i<Form2->StringGrid1->RowCount;i++)
		for(int j=0;j<Form2->StringGrid1->ColCount;j++)
			Form2->StringGrid1->Cells[j][i] = "";
	Form2->StringGrid1->RowCount = n+flag*2;
	Form2->StringGrid1->ColCount = n+flag*3;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			Form2->StringGrid1->Cells[j+flag][i+flag] = IntToStr(square[i][j]);
		}
	}
	if(flag==1)
	{
		Form2->StringGrid1->Cells[0][n+1]="Check Sum";
		Form2->StringGrid1->Cells[n+1][0]="Check Sum";
        Form2->StringGrid1->Cells[n+2][0]="Check Sum";
		for (i=0; i<n; i++)
		{
			Form2->StringGrid1->Cells[n+1][i+1] = "---"+IntToStr(square[i][n]);
			Form2->StringGrid1->Cells[i+1][n+1] = "|"+IntToStr(square[n][i]);
		}
		Form2->StringGrid1->Cells[n+1][n+1] = "\\"+IntToStr(square[n][n]);
        Form2->StringGrid1->Cells[n+2][n+1] = "/"+IntToStr(square[n][n+1]);
	}
}
//---------------------------------------------------------------------------
//浪琩︽计羆㎝
void CheckSum(int square[100][100],int n)
{
	int i,j,sum;
	//璸衡材i︽
	for(i=0;i<n;i++)
	{
		sum=0;
		for(j=0;j<n;j++)
			sum+=square[i][j];
		square[i][n]=sum;
	}
	//璸衡材j
	for(j=0;j<n;j++)
	{
		sum=0;
		for(i=0;i<n;i++)
			sum+=square[i][j];
		square[n][j]=sum;
	}
	//璸衡オ
	sum=0;
	for(i=0;i<n;i++)
		sum+=square[i][i];
	square[n][n]=sum;
	//璸衡オ
	sum=0;
	for(i=0;i<n;i++)
		sum+=square[i][n-i-1];
	square[n][n+1]=sum;


}
//---------------------------------------------------------------------------


