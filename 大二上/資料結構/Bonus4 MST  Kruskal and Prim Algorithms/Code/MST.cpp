//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <time.h>
#include "MST.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define SWAP(x,y)(tmp=x,x=y,y=tmp)
int ** w;
int ** e;
int NodeNum=0;
int range;
int bound;
int M;
int EdgeNum=0;
int *heap;
int *sort;
int ** data;
int * mask;
int n_mst_edge;
int n_cycle_edge;
int *MST;
int MSTCost;
clock_t t_begin,t_end;

void Generate();
void EdgeMatrix();
void PrintInGrid1(int n);
void PrintInGrid2(int n);
void PrintInGrid3(int n);
void PrintInGrid4(int n);
void PrepareGrid5();
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	PrepareGrid5();
}
//---------------------------------------------------------------------------
//Generate Data
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	Generate();
	EdgeMatrix();
	Form2->Memo1->Lines->Add("[Nodes: "+IntToStr(NodeNum)+"]");
}
void Generate()
{
	NodeNum =StrToInt(Form2->Edit1->Text);
	range =StrToInt(Form2->Edit2->Text);
	bound =StrToInt(Form2->Edit3->Text);
	M=StrToInt(Form2->Edit4->Text);
	EdgeNum=0;
	int i,j;
	srand(time(NULL));
	w = (int**)malloc(NodeNum*sizeof(int*));
	for(i=0;i<NodeNum;i++)
	{
		w[i] = (int*)malloc(NodeNum*sizeof(int));
	}
	for(i=0;i<NodeNum;i++)
		for(j=i;j<NodeNum;j++)
		{
			if(i==j)
				w[i][j]=M;
			else
			{
				EdgeNum++;
				w[i][j]=rand()%range+1;
				if(w[i][j]>bound)
				{
					w[i][j]=M;
					EdgeNum--;
				}
				w[j][i]=w[i][j];
			}
		}
	if(Form2->CheckBox1->Checked)PrintInGrid1(NodeNum);
}
void EdgeMatrix()
{
	int i,j,count=1;
	e = (int**)malloc((EdgeNum+1)*sizeof(int*));
	for(i=0;i<=EdgeNum;i++)
		e[i] = (int*)malloc(3*sizeof(int));
	for(i=0;i<NodeNum;i++)
	{
		for(j=i+1;j<NodeNum;j++)
		{
			if(w[i][j]!=M)
			{
				e[count][0]=i;
				e[count][1]=j;
				e[count++][2]=w[i][j];
			}
			if(count==EdgeNum+1)
				break;
		}
		if(count==EdgeNum+1)
			break;
	}
	if(Form2->CheckBox1->Checked)PrintInGrid2(EdgeNum);

}
void PrintInGrid1(int n)
{
	int i,j;
	Form2->StringGrid1->RowCount = n+1;
	Form2->StringGrid1->ColCount = n+1;
	Form2->StringGrid1->Cells[0][0]="From\\To";
	for (i=1;i<=n;i++)
	{
		Form2->StringGrid1->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid1->Cells[i][0] = IntToStr(i-1);
	}
	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++)
			Form2->StringGrid1->Cells[j][i] = IntToStr(w[i-1][j-1]);
}
void PrintInGrid2(int n)
{
	int i,j;
	Form2->StringGrid2->RowCount = n+1;
	Form2->StringGrid2->ColCount = 4;
	Form2->StringGrid2->Cells[0][0]="UnSort";
	Form2->StringGrid2->Cells[1][0]="Vertex1";
	Form2->StringGrid2->Cells[2][0]="Vertex2";
	Form2->StringGrid2->Cells[3][0]="Weight";
	for (i=1;i<=n;i++)
		Form2->StringGrid2->Cells[0][i] = IntToStr(i);
	for (i=1; i<=n; i++)
		for (j=0; j<3; j++)
			Form2->StringGrid2->Cells[j+1][i] = IntToStr(e[i][j]);
}
//---------------------------------------------------------------------------
//Heap & HeapSort
int** CopyData()
{
	data = (int**)malloc((EdgeNum+1)*sizeof(int*));
	int i;
	for(i=1;i<=EdgeNum;i++)
	{
		data[i] = (int*)malloc(2*sizeof(int));
		data[i][0]=i;
		data[i][1]=e[i][2];
	}
	return data;
}
void Restore(int ** data,int s, int r)
{
	int tmpi=s,tmpj,*tmp;
	while(tmpi<=r/2)
	{
		if(tmpi*2+1>r||data[tmpi*2][1]<=data[tmpi*2+1][1])
			tmpj=tmpi*2;
		else
			tmpj=tmpi*2+1;
		if(data[tmpi][1]<=data[tmpj][1])
			break;
		SWAP(data[tmpj],data[tmpi]);
		tmpi=tmpj;
	}
}
void Heap()
{
	int i;
	for(i=EdgeNum/2;i>=1;i--)
	{
		Restore(data,i,EdgeNum);
	}
	for(i=1;i<=EdgeNum;i++)
	{
		heap[i]=data[i][0];
	}
}
void HeapSort()
{
	int i;
	for(i=EdgeNum/2;i>=1;i--)
	{
		Restore(data,i,EdgeNum);
	}
	for(i=EdgeNum;i>1;i--)
	{
		sort[EdgeNum-i+1]=data[1][0];
		data[1]=data[i];
		Restore(data,1,i-1);
	}
	sort[EdgeNum]=data[1][0];
}
void PrintInGrid3(int n)
{
	int i,j;
	Form2->StringGrid3->RowCount = n+1;
	Form2->StringGrid3->ColCount = 4;
	Form2->StringGrid3->Cells[0][0]="Sort";
	Form2->StringGrid3->Cells[1][0]="Vertex1";
	Form2->StringGrid3->Cells[2][0]="Vertex2";
	Form2->StringGrid3->Cells[3][0]="Weight";
	for (i=1;i<=n;i++)
		Form2->StringGrid3->Cells[0][i] = IntToStr(i);
	for (i=1; i<=n; i++)
	{
		for (j=0; j<3; j++)
			Form2->StringGrid3->Cells[j+1][i] = IntToStr(e[sort[i]][j]);
	}
}
void PrintInGrid4(int n)
{
	int i,j;
	Form2->StringGrid4->RowCount = n+1;
	Form2->StringGrid4->ColCount = 4;
	Form2->StringGrid4->Cells[0][0]="Heap";
	Form2->StringGrid4->Cells[1][0]="Vertex1";
	Form2->StringGrid4->Cells[2][0]="Vertex2";
	Form2->StringGrid4->Cells[3][0]="Weight";
	for (i=1;i<=n;i++)
		Form2->StringGrid4->Cells[0][i] = IntToStr(i);
	for (i=0; i<n; i++)
		for (j=0; j<3; j++)
			Form2->StringGrid4->Cells[j+1][i+1] = IntToStr(e[heap[i+1]][j]);
}
//Cycle Detect(大號變小號)
void ResetMask()
{
	mask = (int*)malloc(NodeNum*sizeof(int));
	int i;
	for(i=0;i<NodeNum;i++)
		mask[i]=i;
}
void CycleDetect(int min)
{
	int a=e[min][0];
	int b=e[min][1];
	if(mask[a]==mask[b])
		n_cycle_edge++;
	else
	{
		MST[n_mst_edge++]=min;
		MSTCost+=e[min][2];
		int big=(mask[a]>mask[b])?mask[a]:mask[b];
		int small=(mask[a]<mask[b])?mask[a]:mask[b];
		int i;
		for(i=0;i<NodeNum;i++)
			if(mask[i]==big)
				mask[i]=small;
	}
}
//Union&Find
struct node
{
	int data;
	struct node* parent;
};
struct node ** NodeList;
void ResetNode()
{
	NodeList=(struct node **)malloc(NodeNum*sizeof(struct node *));
	int i;
	for(i=0;i<NodeNum;i++)
	{
		NodeList[i]=(struct node *)malloc(sizeof(struct node ));
		NodeList[i]->data =i;
        NodeList[i]->parent =NodeList[i];
	}
}
struct node * Find(struct node * x)
{
	if(x->parent ==x)
		return x;
	x->parent = Find(x->parent);
	return x->parent;
}
void Union(struct node * x,struct node *y )
{
	struct node * xRoot = Find(x);
	struct node * yRoot = Find(y);
	xRoot->parent = yRoot;
}
void UnionAndFind(int min)
{
    struct node * aRoot = Find(NodeList[e[min][0]]);
	struct node * bRoot = Find(NodeList[e[min][1]]);
	if(aRoot!=bRoot)
	{
        MST[n_mst_edge++]=min;
		MSTCost+=e[min][2];
		Union(aRoot,bRoot);
	}
	else
	{
        n_cycle_edge++;
	}
}
void KruskalMin(int flag)
{
	MST = (int*)malloc((NodeNum-1)*sizeof(int));
	int tmp_edge_num=1,min,i;
	while(n_mst_edge<NodeNum-1&&tmp_edge_num<=EdgeNum)
	{
		min=sort[tmp_edge_num++];
		if(flag==1)CycleDetect(min);
		else UnionAndFind(min);
	}
	if(n_mst_edge<NodeNum-1)
		MSTCost=-1;
	else if(Form2->CheckBox2->Checked)
	{
		for(i=0;i<NodeNum-1;i++)
			Form2->Memo1->Lines->Add("edge"+IntToStr(i)+":("+IntToStr(e[MST[i]][0])+","+IntToStr(e[MST[i]][1])+") ["+IntToStr(e[MST[i]][2])+"]") ;
		Form2->Memo1->Lines->Add("# edges incurring cycles:"+IntToStr(n_cycle_edge));
	}
}
void KruskalHeap(int flag)
{
	MST = (int*)malloc((NodeNum-1)*sizeof(int));
	int tmp_edge_num=1,min,i;
	while(n_mst_edge<NodeNum-1&&tmp_edge_num<=EdgeNum)
	{
		min=heap[tmp_edge_num];
		if(flag==1)CycleDetect(min);
		else UnionAndFind(min);
		data[1]=data[EdgeNum-tmp_edge_num+1];
		Restore(data,1,EdgeNum-tmp_edge_num);
		tmp_edge_num++;
        heap[tmp_edge_num]=data[1][0];
	}
	if(n_mst_edge<NodeNum-1)
		MSTCost=-1;
	else if(Form2->CheckBox2->Checked)
	{
		for(i=0;i<NodeNum-1;i++)
			Form2->Memo1->Lines->Add("edge"+IntToStr(i)+":("+IntToStr(e[MST[i]][0])+","+IntToStr(e[MST[i]][1])+") ["+IntToStr(e[MST[i]][2])+"]") ;
		Form2->Memo1->Lines->Add("# edges incurring cycles:"+IntToStr(n_cycle_edge));
	}
}
//Kruskal Min
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	if(EdgeNum==0)
	{
		Form2->Memo1->Lines->Add("Kruskal    : #edges is zero. There's no MST of G.") ;
	}
	else
	{
		n_mst_edge=0;
		n_cycle_edge=0;
		MSTCost=0;
		data=CopyData();
		sort = (int*)malloc((EdgeNum+1)*sizeof(int));
		int flag=0;
		if(Form2->RadioButton1->Checked)
		{
			flag=1;
			ResetMask();
		}
		else
			ResetNode();
		t_begin= clock();
		HeapSort();
		if(Form2->CheckBox2->Checked)PrintInGrid3(EdgeNum);
		KruskalMin(flag);
		t_end= clock();
		float MSTTime=(float)(t_end-t_begin)/CLOCKS_PER_SEC;
		if(MSTCost!=-1)
			Form2->Memo1->Lines->Add("Kruskal    : ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,"+IntToStr(MSTCost)+" ,"+FloatToStr(MSTTime)+"(sec.)) #cycle_e/#e = "+IntToStr(n_cycle_edge)+"/"+IntToStr(EdgeNum)+"~"+FloatToStr(100*(float)(n_cycle_edge)/(float)(EdgeNum))+"%");
		else
			Form2->Memo1->Lines->Add("Kruskal    : ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,INFINITE ,"+FloatToStr(MSTTime)+"(sec.)) #cycle_e/#e = "+IntToStr(n_cycle_edge)+"/"+IntToStr(EdgeNum)+"~"+FloatToStr(100*(float)(n_cycle_edge)/(float)(EdgeNum))+"%");

	}
}
//Kruskal Heap
void __fastcall TForm2::Button3Click(TObject *Sender)
{
    if(EdgeNum==0)
	{
		Form2->Memo1->Lines->Add("Kruskal_H: #edges is zero. There's no MST of G.") ;
	}
	else
	{
		n_mst_edge=0;
		n_cycle_edge=0;
		MSTCost=0;
		data=CopyData();
		heap = (int*)malloc((EdgeNum+1)*sizeof(int));
		int flag=0;
		if(Form2->RadioButton1->Checked)
		{
			flag=1;
			ResetMask();
		}
		else
			ResetNode();
		t_begin= clock();
		Heap();
		if(Form2->CheckBox2->Checked)PrintInGrid4(EdgeNum);
		KruskalHeap(flag);
		t_end= clock();
		float MSTTime=(float)(t_end-t_begin)/CLOCKS_PER_SEC;
		if(MSTCost!=-1)
			Form2->Memo1->Lines->Add("Kruskal_H: ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,"+IntToStr(MSTCost)+" ,"+FloatToStr(MSTTime)+"(sec.)) #cycle_e/#e = "+IntToStr(n_cycle_edge)+"/"+IntToStr(EdgeNum)+"~"+FloatToStr(100*(float)(n_cycle_edge)/(float)(EdgeNum))+"%");
		else
			Form2->Memo1->Lines->Add("Kruskal_H: ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,INFINITE ," +FloatToStr(MSTTime)+"(sec.)) #cycle_e/#e = "+IntToStr(n_cycle_edge)+"/"+IntToStr(EdgeNum)+"~"+FloatToStr(100*(float)(n_cycle_edge)/(float)(EdgeNum))+"%");
	}
}
//---------------------------------------------------------------------------
//Prim
int ** color;
void PrepareGrid5()
{
	int i,j;
	color = (int **)malloc((NodeNum+2)*sizeof(int *));
	for(i=0;i<NodeNum+2;i++)
		color[i]=(int *)malloc((NodeNum+2)*sizeof(int));
	Form2->StringGrid5->RowCount = NodeNum+2;
	Form2->StringGrid5->ColCount = NodeNum+2;
	Form2->StringGrid5->Cells[0][0]="Prim";
	Form2->StringGrid5->Cells[NodeNum+1][0]="Last";
	Form2->StringGrid5->Cells[0][NodeNum+1]="Nearest";
	for(i=0;i<=NodeNum;i++)
		for(j=0;j<=NodeNum;j++)
			color[i][j]=0;
	color[0][0]=1;
	color[NodeNum+1][0]=5;
	color[0][NodeNum+1]=5;
	for (i=1;i<=NodeNum;i++)
	{
		Form2->StringGrid5->Cells[0][i] = IntToStr(i-1);
		Form2->StringGrid5->Cells[i][0] = IntToStr(i-1);
		color[0][i]=color[i][0]=1;
		color[NodeNum+1][i]=5;
		color[i][NodeNum+1]=5;
	}

}
void Prim()
{
	MST = (int*)malloc((NodeNum)*sizeof(int));
	int *l = (int *)malloc(NodeNum*sizeof(int));
	int *t = (int *)malloc(NodeNum*sizeof(int));
	int *found = (int *)malloc(NodeNum*sizeof(int));
	int i,nearest;
	int source = rand()%NodeNum;
	//先把從初始點走捯各處的距離填入
	for(i=0;i<NodeNum;i++)
	{
		if(i==source)
		l[i]=0;
		else
			l[i]= w[source][i];
		if(Form2->CheckBox2->Checked) Form2->StringGrid5->Cells[1][i+1] = l[i];
		t[i]=source;
		found[i] = 0;
	}
	found[source]=1;
	if(Form2->CheckBox2->Checked)
	{
		Form2->StringGrid5->Cells[1][NodeNum+1] = IntToStr(source);
		color[1][source+1]=2;
    }
	int solved=1;
	while(solved<NodeNum)
	{
		for(i=0;i<NodeNum;i++)
		{
			if(found[i]==0)
			{
				nearest=i;
                break;
            }
		}
		for(i=0;i<NodeNum;i++)
		{
			//找累積路徑最短 且還沒去過的
			if(l[i]<l[nearest]&&found[i]==0)
				nearest=i;
		}
		if(l[nearest]==M)break;
		MST[solved]=nearest;
		found[nearest]=1;
		if(Form2->CheckBox2->Checked)
		{
			Form2->StringGrid5->Cells[solved+1][NodeNum+1] = IntToStr(nearest);
			color[solved+1][nearest+1]=3;
		}
		MSTCost+=  w[t[nearest]][nearest];
		for(i=0;i<NodeNum;i++)
		{
			//沒去過的地方透過他轉運可以更進嗎?
			if(found[i]==0&&w[nearest][i]<l[i])
			{
				l[i]=w[nearest][i];
				t[i]=nearest;
			}
        }
		solved++;
		if(Form2->CheckBox2->Checked)
		{
			for(i=0;i<NodeNum;i++)
			{
				Form2->StringGrid5->Cells[solved][i+1] = l[i];
				Form2->StringGrid5->Cells[NodeNum+1][i+1] = t[i];
			}
			Form2->StringGrid5->Refresh();
		}
	}

	if(solved<NodeNum)
		MSTCost=-1;
	else if(Form2->CheckBox2->Checked)
	{

		for(i=0;i<NodeNum-1;i++)
		{
			int u=MST[i+1];
			int v=t[u];
			if(u<v)
				Form2->Memo1->Lines->Add("edge"+IntToStr(i)+":("+IntToStr(u)+","+IntToStr(v)+") ["+IntToStr(w[u][v])+"]") ;
			else
				Form2->Memo1->Lines->Add("edge"+IntToStr(i)+":("+IntToStr(v)+","+IntToStr(u)+") ["+IntToStr(w[u][v])+"]") ;
		}
        if(Form2->CheckBox2->Checked) Form2->Memo1->Lines->Add("* starting from vertex:"+IntToStr(source));

	}

}
void __fastcall TForm2::StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	AnsiString text =  StringGrid5->Cells[ACol][ARow];
	int col =color[ACol][ARow];
	if (col == 1)
		StringGrid5->Canvas->Brush->Color = TColor (RGB(234, 227, 200));
	else if (col == 2)
		StringGrid5->Canvas->Brush->Color = TColor (RGB(239, 194, 206));
	else if (col == 3)
		StringGrid5->Canvas->Brush->Color = TColor (RGB(177, 220, 227));
	else if (col == 5)
		StringGrid5->Canvas->Brush->Color = TColor (RGB(231, 235, 219));
	StringGrid5->Canvas->FillRect(Rect);
	StringGrid5->Canvas->TextRect(Rect, Rect.Left+8, Rect.Top+8, text);
}
void __fastcall TForm2::Button4Click(TObject *Sender)
{
    if(EdgeNum==0)
	{
		Form2->Memo1->Lines->Add("Prim        : #edges is zero. There's no MST of G.") ;
	}
	else
	{
		n_mst_edge=0;
		MSTCost = 0;
		if(Form2->CheckBox2->Checked)
		{
			PrepareGrid5();
			StringGrid5->Refresh();
		}
		t_begin= clock();
		Prim();
		t_end= clock();
		float MSTTime=(float)(t_end-t_begin)/CLOCKS_PER_SEC;
		if(MSTCost!=-1)
			Form2->Memo1->Lines->Add("Prim        : ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,"+IntToStr(MSTCost)+" ,"+FloatToStr(MSTTime)+"(sec.))");
		else
            Form2->Memo1->Lines->Add("Prim        : ("+IntToStr(NodeNum)+" ,"+FloatToStr((float)(bound)/(float)(range))+" ,INFINITE ,"+FloatToStr(MSTTime)+"(sec.))");
	}
}
//---------------------------------------------------------------------------

