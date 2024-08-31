//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<time.h>
#include "KnightTour.h"
#include "NextNextWindow.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
void InitialColor(int n);
void PrepareGrid2(int n);
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//基本
struct offset
{
	int dx,dy;
};
offset move[8]={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
int ** board;
String trace;
void InitialPosition(int n,int *a,int *b)
{
    srand(time(NULL));
	if(Form2->RadioButton2->Checked)
	{
		*a=StrToInt(Form2->Edit2->Text);
		*b=StrToInt(Form2->Edit3->Text);
	}
	if(Form2->RadioButton1->Checked||*a>=n||*b>=n)
	{
		*a=rand()%n;
		*b=rand()%n;
		Form2->Edit2->Text=*a;
		Form2->Edit3->Text=*b;
	}
}
void InitialBoard(int n,int x,int y)
{
	int i,j;
	board=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		board[i]=(int*)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			board[i][j]=0;
	}
    board[x][y]=1;
}
int InBoard(int n,int a,int b)
{
	if(0<=a&&a<n&&0<=b&&b<n)
		return 1;
	return 0;
}
int KnightTour(int n, int x,int y)
{
	int data = 2,best,bad,i,j,u,v,tmpu,tmpv,test[8];
    String message;
	while(data<=n*n)
	{
		trace+="("+IntToStr(x)+","+IntToStr(y)+")->";
		best=0;//下一步的方向
		bad=0; //有多少方向不能走
		for(i=0;i<8;i++)
		{
			test[i]=0;//記錄走了該方向後下一步有多少 可能的方向
			u=x+move[i].dx;
			v=y+move[i].dy;
			if(InBoard(n,u,v)==0||board[u][v]!=0)
			{
				bad++;
				continue;
			}
			if(data==n*n)
			{
				best=i;
				break;
			}
			for(j=0;j<8;j++)
			{
				tmpu=u+move[j].dx;
				tmpv=v+move[j].dy;
				if(InBoard(n,tmpu,tmpv)==1&&board[tmpu][tmpv]==0)
				{
					test[i]++;
				}

			}
			if(test[i]==0)
			{
				bad++;
            }
			else if(test[best]==0||(test[i]<test[best]))
				best=i;
		}
		if(data==n*n)
		{
            x=x+move[best].dx;
			y=y+move[best].dy;
			board[x][y]=n*n;
			trace+="("+IntToStr(x)+","+IntToStr(y)+") ";
			return 1;
		}
		if(bad==8)
			return 0;
		x=x+move[best].dx;
		y=y+move[best].dy;
		board[x][y]=data;
        data++;
	}
}
void PrintTourInMemo(int n,int x,int y,int FindTour)
{
	int tmp=n*n, i,j,k;
	String s;
	for(i=0;i<n;i++)
	{
		s="";
		for(j=0;j<n;j++)
		{
			tmp= board[i][j];
			s+="\t"+IntToStr(tmp);
			if(tmp<10)
				s+="  ";
			else if(tmp<100)
                s+=" ";

		}
		Form2->Memo1->Lines->Add(s);
	}
	s="n = "+IntToStr(n)+"  (x,y) = ("+IntToStr(x)+","+IntToStr(y)+")  ";
	if(FindTour==1)
		s+="O";
	else
		s+="X";
	Form2->Memo1->Lines->Add(s);
	if(Form2->CheckBox1->Checked&&FindTour==1)
		Form2->Memo1->Lines->Add(trace);

}
void PrintTourInGrid1(int n)
{
	int i,j,gridsize;
	gridsize=StrToInt(Form2->Edit4->Text);
	Form2->StringGrid1->RowCount = n;
	Form2->StringGrid1->ColCount = n;
	for (i=0; i<n; i++)
	{
		Form2->StringGrid1->RowHeights[i] = gridsize;
		Form2->StringGrid1->ColWidths[i] = gridsize;
		for (j=0; j<n; j++)
		{
			Form2->StringGrid1->Cells[j][i] = IntToStr(board[i][j]);
		}
	}
}
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	int n=StrToInt(Edit1->Text);
	int x,y,FindTour;
	trace="Trace: ";
	InitialPosition(n,&x,&y);
	InitialBoard(n,x,y);
	FindTour=KnightTour(n,x,y);
	PrintTourInMemo(n,x,y,FindTour);
    PrintTourInGrid1(n);
}
//---------------------------------------------------------------------------
//animate
struct ColorNode
{
	int r,g,b;
};
struct ColorNode ** color;
struct ColorNode A;
int Draw=0;
int ShowNext=0;
int ClearNext=0;
void InitialColor(int n)
{
	int i,j;
	color=(struct ColorNode**)malloc(n*sizeof(struct ColorNode*));
	for(i=0;i<n;i++)
	{
		color[i]=(struct ColorNode*)malloc(n*sizeof(struct ColorNode));
		for(j=0;j<n;j++)
            color[i][j].r=color[i][j].g=color[i][j].b=255;
	}
	Draw=1;

}
void ChangeColor(int R,int G,int B)
{
	if(R==255&&G==225&&B==225)
	{
		A.r=0;A.g=2;A.b=0;
	}
	else if(R==255&&G==255&&B==225)
	{
		A.r=-2;A.g=0;A.b=0;
	}
	else if(R==225&&G==255&&B==225)
	{
		A.r=0;A.g=0;A.b=2;
	}
	else if(R==225&&G==255&&B==255)
	{
		A.r=0;A.g=-2;A.b=0;
	}
	else if(R==225&&G==225&&B==255)
	{
		A.r=2;A.g=0;A.b=0;
	}
	else if(R==255&&G==225&&B==255)
	{
		A.r=0;A.g=0;A.b=-2;
    }
}
void InitialGrid2(int n)
{
    int i,j,gridsize;
	gridsize=StrToInt(Form2->Edit4->Text);
    Form2->StringGrid2->RowCount = n;
	Form2->StringGrid2->ColCount = n;
	for (i=0; i<n; i++)
	{
		Form2->StringGrid2->RowHeights[i] = gridsize;
		Form2->StringGrid2->ColWidths[i] = gridsize;
		for (j=0; j<n; j++)
		{
			Form2->StringGrid2->Cells[j][i] =" ";
		}
	}
	Form2->StringGrid2->Refresh();
}
void KnightTourAnimate(int n, int x,int y)
{
	int data = 2,best,bad,i,j,u,v,tmpu,tmpv,test[8];
    Form3->Label2->Caption="如果不想再顯示視窗請按\"Cancel\"";
	String message;
	int R=255;
	int G=225;
	int B=225;
	ChangeColor(R,G,B);
	while(data<=n*n)
	{
		message="";
		Form2->StringGrid2->Cells[y][x] = data-1;
		color[y][x].r=R;
		color[y][x].g=G;
		color[y][x].b=B;
		Sleep(20*Form2->TrackBar1->Position);
		Form2->StringGrid2->Refresh();
		R+=A.r;
		G+=A.g;
		B+=A.b;
		if(R==225||G==225||B==225||R==255||G==255||B==255) ChangeColor(R,G,B);
		trace+="("+IntToStr(x)+","+IntToStr(y)+")->";
		best=0;//下一步的方向
		bad=0; //有多少方向不能走
		for(i=0;i<8;i++)
		{
			test[i]=0;//記錄走了該方向後下一步有多少 可能的方向
			u=x+move[i].dx;
			v=y+move[i].dy;
			if(InBoard(n,u,v)==0||board[u][v]!=0)
			{
				bad++;
				continue;
			}
			if(data==n*n)
			{
				best=i;
				break;
			}
			for(j=0;j<8;j++)
			{
				tmpu=u+move[j].dx;
				tmpv=v+move[j].dy;
				if(InBoard(n,tmpu,tmpv)==1&&board[tmpu][tmpv]==0)
				{
					test[i]++;
				}

			}
			if(test[i]==0)
			{
				bad++;
				continue;
			}
			message+="("+IntToStr(u)+","+IntToStr(v)+")="+IntToStr(test[i])+" ; ";
			if(test[best]==0||(test[i]<test[best]))
				best=i;
			if(Form2->CheckBox2->Checked||ShowNext==1)
			{
				color[v][u].r=color[v][u].g=color[v][u].b=200;
				Form2->StringGrid2->Cells[v][u] = test[i];
				Sleep(20*Form2->TrackBar1->Position);
				Form2->StringGrid2->Refresh();
			}
		}
		if(data==n*n)
		{
            x=x+move[best].dx;
			y=y+move[best].dy;
			board[x][y]=n*n;
			trace+="("+IntToStr(x)+","+IntToStr(y)+") ";
			color[y][x].r=R;
			color[y][x].g=G;
			color[y][x].b=B;
			Form2->StringGrid2->Cells[y][x] = data;
			Sleep(20*Form2->TrackBar1->Position);
			Form2->StringGrid2->Refresh();
			message="Find a KnightTour!!";
			Form3->Label1->Caption=message;
			Form3->Label2->Caption="";
			Form3->ShowModal();
			break;
		}

		if(bad==8)
		{
			message="k="+IntToStr(data-1)+"  No More Move!! No Knight Tour!!";
			Form3->Label1->Caption=message;
			Form3->Label2->Caption="";
			Form3->ShowModal();
			ShowNext=0;
			break;
		}

		message="k="+IntToStr(data-1)+" , next:"+IntToStr(8-bad)+" ; "+message;
		message+="\n\nChoose("+IntToStr(x+move[best].dx)+","+IntToStr(y+move[best].dy)+") be the next step";
		Form3->Label1->Caption=message;
		if(ShowNext==1&&Form3->ShowModal()==mrCancel)
			ShowNext=0;
		if(Form2->CheckBox2->Checked||ClearNext==1)
		{
			for(i=0;i<8;i++)
			{
				u=x+move[i].dx;
				v=y+move[i].dy;
				if(InBoard(n,u,v)!=0&&board[u][v]==0)
				{
					color[v][u].r=color[v][u].g=color[v][u].b=255;
					Form2->StringGrid2->Cells[v][u] ="";
				}
			}
			Sleep(20*Form2->TrackBar1->Position);
			Form2->StringGrid2->Refresh();
		}
		x=x+move[best].dx;
		y=y+move[best].dy;
		board[x][y]=data;
		data++;
		ClearNext=ShowNext;

	}
}
void __fastcall TForm2::Button2Click(TObject *Sender)
{
    PageControl1->ActivePage=TabSheet3;
	int n=StrToInt(Edit1->Text);
	int x,y,FindTour;
	trace="Trace: ";
    InitialPosition(n,&x,&y);
	InitialBoard(n,x,y);
	InitialColor(n);
	InitialGrid2(n);
	ShowNext=ClearNext=0;
	if(CheckBox3->Checked)
		ShowNext=ClearNext=1;
	KnightTourAnimate(n,x,y);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
	int gridsize=StrToInt(Form2->Edit4->Text);
	AnsiString text =  StringGrid2->Cells[ACol][ARow];
	if(Draw)StringGrid2->Canvas->Brush->Color = TColor (RGB(color[ACol][ARow].r,color[ACol][ARow].g,color[ACol][ARow].b));
	StringGrid2->Canvas->FillRect(Rect);
	StringGrid2->Canvas->TextRect(Rect, Rect.Left+gridsize/2-9, Rect.Top+gridsize/2-9, text);
}
//---------------------------------------------------------------------------



