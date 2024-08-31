//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "ShortestPath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int **w; //權重
int *l; //路徑長
int *t;  //轉運
int *found;
int solved;
int n=0;
int range;
int bound;
int M;
int i,j,k;
int source;
int nearest;
int ** color;
int ** A; //all path
int **via;
int **TC;//transitive closure

void PrintInGrid1();
void PrepareGrid2();
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	PrepareGrid2();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	n=StrToInt(Edit1->Text);
	range=StrToInt(Edit2->Text);
	bound=StrToInt(Edit3->Text);
	M=StrToInt(Edit4->Text);
	w = (int **)malloc(n*sizeof(int *));
	for(i=0;i<n;i++)
		w[i]=(int *)malloc(n*sizeof(int));
	srand(time(NULL));
	if(CheckBox1->Checked)
	{
        for(i=0;i<n;i++)
		for(j=i;j<n;j++)
		{
			if(i==j)
				w[i][j] = M;
			else
			{
				w[i][j]= rand()%range+1;
				if(w[i][j]>bound)
					w[i][j]=M;
				w[j][i]=w[i][j];
			}
		}
	}
	else
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				if(i==j)
					w[i][j] = M;
				else
				{
					w[i][j]= rand()%range+1;
					if(w[i][j]>bound)
						w[i][j]=M;
				}
			}
    }
	PrintInGrid1();
}
void PrintInGrid1()
{
	Form2->StringGrid1->RowCount = n+1;
	Form2->StringGrid1->ColCount = n+1;
	Form2->StringGrid1->Cells[0][0]="From\\To";
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid1->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid1->Cells[i][0] = IntToStr(i-1);
	}
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			Form2->StringGrid1->Cells[j+1][i+1] = IntToStr(w[i][j]);
}
//---------------------------------------------------------------------------
//Single Source All Destination
void PrepareGrid2()
{
	color = (int **)malloc((n+2)*sizeof(int *));
	for(i=0;i<n+2;i++)
		color[i]=(int *)malloc((n+1)*sizeof(int));
	Form2->StringGrid2->RowCount = n+1;
	Form2->StringGrid2->ColCount = n+2;
	Form2->StringGrid2->Cells[0][0]="From\\To";
	Form2->StringGrid2->Cells[n+1][0]="Last";
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			color[i][j]=0;
	color[0][0]=1;
	color[n+1][0]=5;
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid2->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid2->Cells[i][0] = IntToStr(i-1);
		color[0][i]=color[i][0]=1;
		color[n+1][i]=5;
	}

}
void SSAD()
{
    n=StrToInt(Form2->Edit1->Text);
	l = (int *)malloc(n*sizeof(int));
	t = (int *)malloc(n*sizeof(int));
	found = (int *)malloc(n*sizeof(int));
	//先把從初始點走捯各處的距離填入
	for(i=0;i<n;i++)
	{
		if(i==source)
		l[i]=0;
		else
			l[i]= w[source][i];
		Form2->StringGrid2->Cells[1][i+1] = l[i];
		t[i]=source;
		found[i] = 0;
	}
	found[source]=1;
	color[1][source+1]=2;
	solved=1;
	while(solved<n)
	{
		for(i=0;i<n;i++)
		{
			if(found[i]==0)
			{
				nearest=i;
                break;
            }
		}
		for(i=0;i<n;i++)
		{
			//找累積路徑最短 且還沒去過的
			if(l[i]<l[nearest]&&found[i]==0)
				nearest=i;
		}
		found[nearest]=1;
		color[solved+1][nearest+1]=3;
		Form2->Memo1->Lines->Add(IntToStr(solved)+"th nearest = "+IntToStr(nearest));
		for(i=0;i<n;i++)
		{
			//沒去過的地方透過他轉運可以更進嗎?
			if(found[i]==0&&l[nearest]+w[nearest][i]<l[i])
			{
				l[i]=l[nearest]+w[nearest][i];
				t[i]=nearest;
				color[solved+1][i+1]=4;
			}
        }
		solved++;
		for(i=0;i<n;i++)
		{
			Form2->StringGrid2->Cells[solved][i+1] = l[i];
			Form2->StringGrid2->Cells[n+1][i+1] = t[i];
		}
		Form2->StringGrid2->Refresh();
	}
}
void PrintPath()
{
	String s="";
	for(i=0;i<n;i++)
	{
		if(i==source)
			continue;
		else
		{
			s=IntToStr(i);
			int head;
			int tail;
			//找上一個是誰
			for(head=i,tail=t[i];head!=tail;head=tail,tail=t[head])
				s=IntToStr(tail)+"--["+IntToStr(w[tail][head])+"]-->"+s;
			s="The shortest distance from "+IntToStr(source)+" to "+IntToStr(i)+" is "+IntToStr(l[i])+" with path "+s;
			Form2->Memo1->Lines->Add(s);
		}
	}
}
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	source = StrToInt(Form2->Edit5->Text);
	Form2->Memo1->Lines->Add("Single Source All Destinations ");
	Form2->Memo1->Lines->Add("Source = "+IntToStr(source));
	PrepareGrid2();
	StringGrid2->Refresh();
	SSAD();
	PrintPath();
	Form2->Memo1->Lines->Add("====================================");

}
void __fastcall TForm2::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	AnsiString text =  StringGrid2->Cells[ACol][ARow];
	int col =color[ACol][ARow];
	if (col == 1)
		StringGrid2->Canvas->Brush->Color = TColor (RGB(234, 227, 200));
	else if (col == 2)
		StringGrid2->Canvas->Brush->Color = TColor (RGB(239, 194, 206));
	else if (col == 3)
		StringGrid2->Canvas->Brush->Color = TColor (RGB(177, 220, 227));
	else if (col == 4)
		StringGrid2->Canvas->Brush->Color = TColor (RGB(249, 235, 174));
	else if (col == 5)
		StringGrid2->Canvas->Brush->Color = TColor (RGB(231, 235, 219));
	StringGrid2->Canvas->FillRect(Rect);
	StringGrid2->Canvas->TextRect(Rect, Rect.Left+8, Rect.Top+8, text);
}
//--------------------------------------------------------------------------
//All Pair
void AllPair()
{
	A=(int **)malloc((n)*sizeof(int *));
	via=(int **)malloc((n)*sizeof(int *));
	for(i=0;i<n;i++)
	{
		A[i]=(int *)malloc((n)*sizeof(int));
		via[i]=(int *)malloc((n)*sizeof(int));
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			A[i][j]=w[i][j];
			via[i][j]=i;
			if(i==j)
				A[i][j]=0;
		}
	//每次都多一個轉運站
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				//如果透過轉運站可以更快
				if(A[i][k]+A[k][j]<A[i][j])
				{
					A[i][j]=A[i][k]+A[k][j];
					via[i][j]=k;
				}
			}
}
void PrintInGrid3()
{
	Form2->StringGrid3->RowCount = n+1;
	Form2->StringGrid3->ColCount = n+1;
	Form2->StringGrid3->Cells[0][0]="From\\To";
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid3->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid3->Cells[i][0] = IntToStr(i-1);
	}
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			Form2->StringGrid3->Cells[j+1][i+1] = IntToStr(A[i][j]);
}
void PrintInGrid4()
{
	Form2->StringGrid4->RowCount = n+1;
	Form2->StringGrid4->ColCount = n+1;
	Form2->StringGrid4->Cells[0][0]="From\\To";
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid4->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid4->Cells[i][0] = IntToStr(i-1);
	}
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			Form2->StringGrid4->Cells[j+1][i+1] = IntToStr(via[i][j]);
}
void PrintAllPath()
{
	String s="";
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(i==k)
				continue;
			else
			{
				s="";
				int head;
				int tail;
				//找下一個是誰
				for(tail=k,head=via[k][i];tail!=head;tail=via[k][i],head=via[tail][head])
					s=s+IntToStr(tail)+"--["+IntToStr(A[tail][head])+"]-->";
				s=s+IntToStr(tail)+"--["+IntToStr(A[tail][i])+"]-->"+i;
				s="The shortest distance from "+IntToStr(k)+" to "+IntToStr(i)+" is "+IntToStr(A[k][i])+" with path "+s;
				Form2->Memo1->Lines->Add(s);
			}
		}
		if(k!=n-1)Form2->Memo1->Lines->Add("-------------------------------------");
	}
}
void __fastcall TForm2::Button3Click(TObject *Sender)
{
	AllPair();
	PrintInGrid3();
	PrintInGrid4();
	Form2->Memo1->Lines->Add("All Pair");
	PrintAllPath();
	Form2->Memo1->Lines->Add("====================================");

}
//---------------------------------------------------------------------------
//Transitive Closure
void Transitive()
{
	M=StrToInt(Form2->Edit4->Text);
	TC=(int **)malloc((n)*sizeof(int *));
	for(i=0;i<n+2;i++)
	{
		TC[i]=(int *)malloc((n)*sizeof(int));
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(w[i][j]!=M)
				TC[i][j]=1;
			else
				TC[i][j]=0;

		}

	//每次都多一個轉運站
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				TC[i][j]=TC[i][j]||(TC[i][k]&&TC[k][j]);


}
void PrintInGrid5()
{
	Form2->StringGrid5->RowCount = n+1;
	Form2->StringGrid5->ColCount = n+1;
	Form2->StringGrid5->Cells[0][0]="From\\To";
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid5->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid5->Cells[i][0] = IntToStr(i-1);
	}
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			Form2->StringGrid5->Cells[j+1][i+1] = IntToStr(TC[i][j]);
}
void __fastcall TForm2::Button4Click(TObject *Sender)
{
	Transitive();
	PrintInGrid5();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
	M=StrToInt(Form2->Edit4->Text);
	FILE *fp;     // Define fp as a pointer pointing to some file (with data type FILE) in HD
	String out;
	int i, j;
	AnsiString infile;   // Use builder's string (AnsiString) to ease the conversion (into const char *)
	if (OpenDialog1->Execute())
	{
		infile = OpenDialog1->FileName;
		fp = fopen(infile.c_str(), "r+");
		//c_str函?的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用
		fscanf(fp, "%d %d", &n, &source);    // Read in two integers m & n
		Edit1->Text=n;
        Edit5->Text = source;
		w = (int **)malloc(n*sizeof(int *));
		for(i=0;i<n;i++)
			w[i]=(int *)malloc(n*sizeof(int));
		for (i=0; i<n; i++)    // Reda in m*n 0/1/2's into maze[][]
			for (j=0; j<n; j++)
			{
				fscanf(fp, "%d", &w[i][j]);
				if(w[i][j]==0)
					w[i][j]=M;
			}
		fclose(fp);

  }
  PrintInGrid1();
}
//---------------------------------------------------------------------------

