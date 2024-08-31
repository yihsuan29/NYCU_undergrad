﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MouseInMaze.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
int ** maze; //地圖
int mark[100][100]; //走沒走過
int m,n,top;//m是長n是寬  top是堆疊堆到第幾個
int flag=0;
int dead;
//建方向
struct offset
{
	int di,dj;
};
offset move[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
//                               N:0    NE:1   E:2  SE:3   S:4   SW:5   W:6     NW:7
//存位置
struct position
{
	int i,j;
	int dir;
};
position *stack;
//初始化全沒走
void InitMap(int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<m;j++)
		{
			mark[i][j]=0;
			if(maze[i][j]==3)
                maze[i][j]=0;
			if(Form2->StringGrid1->Cells[j][i] == "->"||Form2->StringGrid1->Cells[j][i] == "*")
				Form2->StringGrid1->Cells[j][i] = "0";
		}
}
//走了就存到堆疊
void push(position data)
{
	if(top!=m*n-1)
		stack[++top] = data;
}
//沒路就退回前一步
struct position pop()
{
	if(top!=-1)
	{

	   return stack[top--];
	}

}

//怎麼走?
void path(int m,int n, int direction)
{
    stack = new struct position [m*n];
	position step;
	int i=1,j=0,u,v;  //i j是現在的座標 u v是測試鄰近方位能不能走
	int dir=0;
	top=-1;
	//預設的出發點
	step.i=1;
	step.j=0;
	step.dir=0;
	push(step);
	while(top!=-1)
	{
		Form2->StringGrid1->Cells[step.j][step.i] = "*";
		Sleep(Form2->TrackBar1->Position);
		Form2->StringGrid1->Refresh();
		step = pop();//退回前一步
		i=step.i;
		j=step.j;
		dir=step.dir;
		//嘗試各個方向
		while(dir<=7)
		{
			u=i+move[dir].di;
			v=j+move[dir].dj;
			//可以走且還沒走過
			if(maze[u][v]==0&&mark[u][v]==0)
			{
				Form2->StringGrid1->Cells[step.j][step.i] = "->";
				step.dir=dir;
				push(step);
				step.i=u;
				step.j=v;
				Form2->StringGrid1->Cells[step.j][step.i] = "->";
				Sleep(Form2->TrackBar1->Position);
				Form2->StringGrid1->Refresh();
				//輸出trace
				if((u==m-2)&&(v==n-1))
				{
					dead=0;
					maze[u][v]=3;
					String str;
					str = "("+IntToStr(m-2)+","+IntToStr(n-1)+")";
					Form2->StringGrid1->Cells[n-1][m-2] = "&";
					str = "("+IntToStr(step.i)+","+IntToStr(step.j)+","+IntToStr(step.dir)+")-->"+str;
					Form2->StringGrid1->Cells[step.j][step.i] = "->";
					String out;
					while (top != -1)
					{
						step = pop();
						int dir = step.dir;
                        maze[step.i][step.j]=3;
						str = "("+IntToStr(step.i)+","+IntToStr(step.j)+","+IntToStr(dir)+")-->"+str;
						Form2->StringGrid1->Cells[step.j][step.i] = "->";
					}
                    Form2->Memo1->Lines->Add(str);
                    for (i=0; i<m; i++)
					{
						out = "";
						for (j=0; j<n; j++) out += "  "+IntToStr(maze[i][j]);
						Form2->Memo1->Lines->Add(out);
					}

					break;
				}
				mark[u][v]=1;
				i=u;
				j=v;
				dir=0;


			}
			else
				dir+=1+direction;
		}


    }
}

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//讀迷宮
void __fastcall TForm2::Button3Click(TObject *Sender)
{
	FILE *fp;     // Define fp as a pointer pointing to some file (with data type FILE) in HD
	String out;
	int i, j;
	int grid_size = Edit3->Text.ToInt();
	AnsiString infile;   // Use builder's string (AnsiString) to ease the conversion (into const char *)
	if (OpenDialog1->Execute())
	{
		infile = OpenDialog1->FileName;
		fp = fopen(infile.c_str(), "r+");
		//c_str函数的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用
		fscanf(fp, "%d %d", &m, &n);    // Read in two integers m & n
		maze = new int * [m];
		for (i=0; i<m; i++)
		{
			maze[i] = new int [n];
		}
		Memo1->Lines->Add("(m, n)="+IntToStr(m)+", "+IntToStr(n));
		for (i=0; i<m; i++)    // Reda in m*n 0/1/2's into maze[][]
			for (j=0; j<n; j++)
				fscanf(fp, "%d", &maze[i][j]);
		fclose(fp);
		for (i=0; i<m; i++)      // Print out maze[][] in Memo1
		{
			out = "";
			for (j=0; j<n; j++) out += "  "+IntToStr(maze[i][j]);
			Memo1->Lines->Add(out);
		}
		// Print out maze[][] in StringGrid1
		StringGrid1->RowCount = m;
		StringGrid1->ColCount = n;
		for (i=0; i<m; i++) StringGrid1->RowHeights[i] = grid_size;
		for (i=0; i<n; i++) StringGrid1->ColWidths[i] = grid_size;
		for (i=0; i<m; i++)
			for (j=0; j<n; j++)
				StringGrid1->Cells[j][i] = maze[i][j];
		flag=1;
  }

 }
//---------------------------------------------------------------------------

//畫迷宮
void __fastcall TForm2::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	if (text == "0")
		StringGrid1->Canvas->Brush->Color = TColor (RGB(234, 227, 200));
	else if (text == "1")
		StringGrid1->Canvas->Brush->Color = TColor (RGB(207, 197, 165));
	else if (text == "2")
		StringGrid1->Canvas->Brush->Color = TColor (RGB(194, 176, 146));
	else if (text == "->")
		StringGrid1->Canvas->Brush->Color = TColor (RGB(164, 235, 243));
	else
		StringGrid1->Canvas->Brush->Color = TColor (RGB(204, 242, 244));
	StringGrid1->Canvas->FillRect(Rect);


}
//---------------------------------------------------------------------------
//走迷宮
//八方向
void __fastcall TForm2::Button4Click(TObject *Sender)
{
	dead=1;
	InitMap(m,n);
	path(m,n,0);
	if(dead==1)
        Form2->Memo1->Lines->Add("There's no path to reach the exit.");

}
//四方向
void __fastcall TForm2::Button5Click(TObject *Sender)
{
	InitMap(m,n);
	path(m,n,1);
}
//---------------------------------------------------------------------------
//寫迷宮
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	int m,n,i,j;
	m = Edit1->Text.ToInt();
	n = Edit2->Text.ToInt();
	if (SaveDialog1->Execute())     //確認SaveDialog1讀取檔案成功
	{
		// 取SaveDialog1所開啟的檔案名稱, 將檔案名稱轉為char格式後用fopen開啟此檔案
		AnsiString file_name = SaveDialog1->FileName;
		FILE *fp = fopen(file_name.c_str(),"w");  // "w" 表示開以寫檔的方式開啟
		//利用fprintf將g_matrix中的元素寫入fp, 當需要換行時使用putc將'\n'加入fp中
		if (fp)
		{
			fprintf(fp, "%d %d", m, n);
			putc('\n', fp);
			for  (int i=0 ; i<m ; i++)
			{
				for (int j=0 ; j<n ; j++)
				{
					fprintf(fp, "%d ", maze[i][j]);
				}
				putc('\n', fp);
			}
			fclose(fp);   // 寫完檔後請關檔
		}

	}


}
//---------------------------------------------------------------------------
//自動生成迷宮
int ** generatemaze(int ** maze, int x, int y)
{

	int direction;
	maze[x][y] =0;  // 標示此格已設定
	//Form2->Memo1->Lines->Add(IntToStr(x)+","+IntToStr(y));
	while ((y+2<n&&maze[x][y+2]!=0) || (x+2<m&&maze[x+2][y]!=0) || (y-2>=0&&maze[x][y-2]!=0 )|| (x-2>=0&&maze[x-2][y]!=0))// 如果沒設成牆
	{

		//Form2->Memo1->Lines->Add(IntToStr(x)+","+IntToStr(y));
		direction = rand()%4+1;  // 決定下一個位置
		//往右
		if (direction==1 && y+2<n&&maze[x][y+2]!=0)
		{
			//把右邊打通
            maze[x][y+1] =0;
			if(maze[x][y+2]!=2) //不可以捅破天花版
			{

				maze = generatemaze(maze, x,y+2);
			}
			else
				break;
		}
		//往上
		else if (direction==2 && x-2>=0&& maze[x-2][y]!=0)
		{
			maze[x-1][y] =0;
			//把上面打通
			if(maze[x-2][y]!=2) //不可以捅破天花版
			{

				maze = generatemaze(maze, x-2,y);
			}
			else
				break;
		}
		// 往左
		else if (direction==3 && y-2>=0&&maze[x][y-2]!=0)
		{
			//把左邊打通
			maze[x][y-1] =0;
			if(maze[x][y-2]!=2) //不可以捅破天花版
			{
				maze = generatemaze(maze, x,y-2);
			}
			else
				break;
		}
		//往下
		else if (direction==4 && x+2<m&&maze[x+2][y]!=0)
		{
            //把下面打通
			maze[x+1][y] =0;
			if(maze[x+2][y]!=2)
			{
				maze = generatemaze(maze, x+2,y);
			}
			else
				break;
		}
	}

	return maze;
}
//保證有入口
int ** entermaze(int ** maze, int x, int y,int last)
{
    int direction;
	maze[x][y] =0;  // 標示此格已設定
	//Form2->Memo1->Lines->Add("找路口"+IntToStr(x)+","+IntToStr(y));
	while((last==1&&(y+1<n&&maze[x][y+1]!=0)&& (x+1<m&&maze[x+1][y]!=0)&& (x-1>=0&&maze[x-1][y]!=0))||(last==4&&(y+1<n&&maze[x][y+1]!=0)&& (x+1<m&&maze[x+1][y]!=0) && (y-1>=0&&maze[x][y-1]!=0 )))
	{
		direction = rand()%4+1;  // 決定下一個位置
		//往右
		if (direction==1 && y+1<n&&maze[x][y+1]!=0)
		{
			if(maze[x][y+1]!=2) //不可以捅破天花版
			{
				maze = entermaze(maze, x,y+1,1);
			}
			else
				break;
		}
		//往下
		else if (direction==4 && x+1<m&&maze[x+1][y]!=0)
		{
			//把下面打通
			if(maze[x+1][y]!=2)
			{
				maze = entermaze(maze, x+1,y,4);
			}
			else
				break;
		}
	}
	return maze;
}
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	int i, j;
	int grid_size = Edit3->Text.ToInt();
	//把原本生成或是讀到的maze刪掉
	if (flag==1)
	{
		for (int i=0; i<m; i++)
			delete(maze[i]);
		delete(maze);
		flag=0;
	}
	//生成的長寬
	m = Edit1->Text.ToInt();
	n = Edit2->Text.ToInt();
	maze = new int * [m];
	for (i=0; i<m; i++)
	{
		maze[i] = new int [n];
	}
	flag=1;
	InitMap(m,n);
	int Start_i=1, Start_j=1, End_i=m-2, End_j=n-2;
	int x, y;
	srand(time(NULL));
	for (x=0; x<m; x++)
	{
		for (y=0; y<n; y++)
		{
			//外圍的牆是2
			if (x==0 || y==0 || x==m-1 || y==n-1 )
				maze[x][y] = 2;
			//預設裡面是1(都堵住啦)
			else maze[x][y] = 1;
		}
	}
	//產生迷宮

	maze = generatemaze(maze, End_i, End_j);
	if(maze[1][1]==1)
		maze = entermaze(maze, 1, 1,1);
	//入口的左邊是空的
	maze[Start_i][Start_j-1] =0;
	//出口的右邊是空的
	maze[End_i][End_j+1] =0;
	//寫到memo裡
	Memo1->Lines->Add("(m, n)="+IntToStr(m)+", "+IntToStr(n));
    String out;
	for (i=0; i<m; i++)
	{
		out = "";
		for (j=0; j<n; j++) out += "  "+IntToStr(maze[i][j]);
		Memo1->Lines->Add(out);
	}
	//寫道grid裡
	StringGrid1->RowCount = m;
	StringGrid1->ColCount = n;
    for (i=0; i<m; i++) StringGrid1->RowHeights[i] = grid_size;
	for (i=0; i<n; i++) StringGrid1->ColWidths[i] = grid_size;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			StringGrid1->Cells[j][i] = maze[i][j];
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

