//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "BST.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
struct BSTNode
{
	struct BSTNode * left;
	int data;
	struct BSTNode * right;

};
//產生新節點
struct BSTNode * newnode(int element)
{
	struct BSTNode * p = (BSTNode *)malloc(sizeof(BSTNode));
	p->data = element;
	p->left = NULL;
	p->right = NULL;
	return p;
}
struct BSTNode * root;
String s;
void r_inorder(struct BSTNode * node);
void draw(struct BSTNode * root);
//---------------------------------------------------------------------------
//Insert
struct BSTNode * insert(struct BSTNode * node,int element)
{
	if(node==NULL)
		return newnode(element);
	else if(element==node->data)
		Form2->Memo1->Lines->Add("Element "+IntToStr(element)+" is already in the Binary Tree.")  ;
	else if(element<node->data)
		node->left = insert(node->left,element);//element小 在左子樹找element
	else
		node->right = insert(node->right,element);
	return node;
}
void __fastcall TForm2::InsertClick(TObject *Sender)
{
	int element = StrToInt(Edit1->Text);
	root = insert(root,element);
	s="";
	r_inorder(root);
	Form2->Memo1->Lines->Add(s);
	srand(time(NULL));
	int i=rand()%2;
	if(i==0)
		Edit1->Text=element+rand()%5+1;
	else
		Edit1->Text=element-rand()%5-1;
	if(StrToInt(Edit1->Text)<0)
        Edit1->Text=rand()%100+1;
	draw(root);
}
//---------------------------------------------------------------------------
//Delete
struct BSTNode * deletetarget(struct BSTNode * node,int element)
{
	if(node==NULL)//找到底了
	{
        Form2->Memo1->Lines->Add("Element "+IntToStr(element)+" is NOT in the Binary Tree.")  ;
		return node;
	}
	if(element<node->data)
		node->left = deletetarget(node->left,element);//element小 在左子樹找element
	else if((element>node->data))
		node->right = deletetarget(node->right,element);
	//找到了
	else
	{
		 struct BSTNode * tmp = (BSTNode *)malloc(sizeof(BSTNode));

		//如果他是樹葉
		 if(node->left==NULL&&node->right==NULL)
		 {
			tmp = node;
			node = NULL;
			free(tmp);
		 }
		 //如果他有兩個子樹
		 else if(node->left!=NULL&&node->right!=NULL)
		 {
			 //找出右子樹的最左孫子來取代他
			 tmp = node->right;
			 while(tmp->left!=NULL)
			 {
				 tmp=tmp->left;
			 }
			 node->data = tmp->data;
			 //並在右子樹刪除tmp
			 node->right = deletetarget(node->right,tmp->data);
		 }
		 else//只有一棵子樹
		 {
			tmp=(node->left!=NULL)?node->left:node->right;
			//用下面那個節點取代掉上面這個(包含子樹阿data阿)
			*node = *tmp;
			free(tmp);
         }

	}
    return node;

}
void __fastcall TForm2::DeleteClick(TObject *Sender)
{
	int target = StrToInt(Edit2->Text);
	if(root==NULL)
		Form2->Memo1->Lines->Add("BST is Empty.");
	else
	{
		root = deletetarget(root,target);
		s="";
		r_inorder(root);
		Form2->Memo1->Lines->Add(s);
		if(root==NULL)
		   Edit2->Text=Edit1->Text;
		else
			Edit2->Text=root->data;
		draw(root);
	}
}
void clearall(struct BSTNode * node)
{
	if (node != NULL)
	{
		clearall(node->left);
		clearall(node->right);
	    free(node);
	}
}

void __fastcall TForm2::Button4Click(TObject *Sender)
{
	int target = root->data;
    s="";
	while(root!=NULL)
	{
		root = deletetarget(root,target);
		if(root!=NULL)
			target=root->data;
	}
	r_inorder(root);
	if(s=="")
		s="BST is Empty.";
	Form2->Memo1->Lines->Add(s);
	Edit2->Text=Edit1->Text;
	draw(root);
}
//---------------------------------------------------------------------------
//Randomly Insert
void __fastcall TForm2::Button3Click(TObject *Sender)
{
	int n = StrToInt(Edit4->Text);
	int range = StrToInt(Edit3->Text);
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		int num = rand()%range+1;
		root = insert(root,num);
	}
    s="";
	r_inorder(root);
	Form2->Memo1->Lines->Add(s);
    draw(root);

}
//---------------------------------------------------------------------------
//Recursive Traversal
//中序走訪
void r_inorder(struct BSTNode * node)
{
	//走到樹葉的接地時
	if(node!=NULL)
	{
		//先走左邊
		r_inorder(node->left);
		//再走中間(把自己印出來)
		s+=IntToStr(node->data)+"_";
		//然後處裡右邊
		r_inorder(node->right);
	}
}
//前序走訪
void r_preorder(struct BSTNode * node)
{
	//走到樹葉的接地時
	if(node!=NULL)
	{
		//先把自己(中間)印出來
		s+=IntToStr(node->data)+"_";
		//再走左邊
		r_preorder(node->left);
		//然後處裡右邊
		r_preorder(node->right);
	}
}
//後序走訪
void r_postorder(struct BSTNode * node)
{
	//走到樹葉的接地時
	if(node!=NULL)
	{
		//先走左邊
		r_postorder(node->left);
		//然後處裡右邊
		r_postorder(node->right);
        //再走中間(把自己印出來)
		s+=IntToStr(node->data)+"_";
	}
}
void __fastcall TForm2::travelClick(TObject *Sender)
{
	s="";
	if(RadioButton1->Checked) r_inorder(root);
	else if(RadioButton2->Checked)r_preorder(root);
	else if(RadioButton3->Checked)r_postorder(root);
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//Non Recursive Traversal
struct StackNode{
	struct BSTNode * treenode;
	struct StackNode * next;
};
struct StackNode * top;
void push(struct BSTNode * node)
{
	struct StackNode * oldtop;
	oldtop = top;
	//新增一個StackNode
	top = (struct StackNode *)malloc(sizeof(StackNode));
	top->treenode = node;
	top->next = oldtop;
}
struct BSTNode * pop()
{
	struct StackNode * p;
	struct BSTNode * node;
	p=top;
	node = p->treenode;
	top = top->next;
	free(p);
	return node;
}
//中序走訪
void inorder(struct BSTNode * node)
{
	do
	{
		//先走左邊
		while(node!=NULL)
		{
			push(node);
			//一直往左走
			node = node->left;
		}
		if(top!=NULL)
		{
			//然後做中間
			node=pop();
			s+=IntToStr(node->data)+"_";
			//再做右邊
			node = node->right;
		}
	}while(top!=NULL||node!=NULL);
	//左子樹走完 右子樹走完
}
//前序走訪
void preorder(struct BSTNode * node)
{
	do
	{
		while(node!=NULL)
		{
			//做中間
			s+=IntToStr(node->data)+"_";
			push(node);
			//做左邊 一直往左走
			node = node->left;
		}
		if(top!=NULL)
		{
			node=pop();
			//再做右邊
			node = node->right;
		}
	}while(top!=NULL||node!=NULL);
}
//後序走訪 LRV = inverse(VRL)
void postorder(struct BSTNode * node)
{
	do
	{
		while(node!=NULL)
		{
			//做中間 (inverse的加上去)
			s=IntToStr(node->data)+"_"+s;
			push(node);
			//V->R 做右邊 一直往右走
			node = node->right;
		}
		if(top!=NULL)
		{
			node=pop();
			//再做右邊
			node = node->left;
		}
	}while(top!=NULL||node!=NULL);
}
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	s="";
	if(RadioButton1->Checked) inorder(root);
	else if(RadioButton2->Checked)preorder(root);
	else if(RadioButton3->Checked)postorder(root);
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//Level Order
struct QueueNode
{
	struct BSTNode * treenode;
	struct QueueNode * next;
};
struct QueueNode * front;
struct QueueNode * rear;
void add(struct BSTNode * node)
{
	struct QueueNode * newnode = (QueueNode *)malloc (sizeof(QueueNode));
	newnode->treenode = node;
	newnode->next=NULL;
	//如果是空的
	if(front==NULL)front=newnode;
	else
		rear->next=newnode;
	//更新尾巴
	rear=newnode;
}
struct BSTNode * deleteQueue()
{
	struct QueueNode * oldfront;
	oldfront = front;
	front = front->next;
	struct BSTNode * node;
	node=oldfront->treenode;
	free(oldfront);
	return node;
}
void levelorder(struct BSTNode * node)
{
	add(node);
	while(front!=NULL)
	{
		//從頭拿出node
		node = deleteQueue();
		//把他印出來
		s+=IntToStr(node->data)+"_";
		//如果左邊不是空的就放進去Queue
		if(node->left!=NULL)
			add(node->left);
		//如果右邊不是空的就放進去Queue
		if(node->right!=NULL)
			add(node->right);
	}
}
void __fastcall TForm2::Button2Click(TObject *Sender)
{
    s="";
	levelorder(root);
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//畫畫
struct DrawTreeNode
{	struct DrawTreeNode* left;
	int data;
	int index;
	struct DrawTreeNode* right;
};
struct DrawTreeNode* DrawRoot;
int * X;
int * Y;
//求樹高
int Depth_BTree(struct BSTNode* node, int level)
{
	int depth, l_depth, r_depth;
	if (node!=NULL)
	{
		l_depth=Depth_BTree(node->left,level+1);
	    r_depth = Depth_BTree(node->right,level+1);
	    depth = (l_depth>r_depth)? l_depth : r_depth;
		return depth+1;
	}
	else return (level);
}

//求他的xy座標
void determine_X(struct DrawTreeNode * node, int left, int right)
{
	if (node != NULL)
	{
		int m = (left+right)/2;
	    X[node->index] = (m == 0) ? left : m;
		determine_X(node->left, left, m-1);
	    determine_X(node->right, m+1, right);
	}
}
void determine_Y(struct DrawTreeNode * node, int top, int bottom, int depth)
{
	int detH = (top+bottom)/(depth+1)== 0 ? 1 :(top+bottom)/(depth+1);
	 for (int i=0; i<depth; i++)
	 {
		Y[i] = (detH < 10) ? 10*i : detH*i;
	 }
}


//把普通的BST資料轉成有行有列的資料的DrawTreeNode
struct DrawTreeNode* CopyBSTtoDT(struct BSTNode * TreeRoot, int index)
{
	if (TreeRoot==NULL)
		return NULL;
	struct DrawTreeNode* copyRoot = (struct DrawTreeNode*)malloc(sizeof(DrawTreeNode));
	copyRoot->data = TreeRoot->data;
	copyRoot->index = index;
	copyRoot->left=CopyBSTtoDT(TreeRoot->left,2*index);
	copyRoot->right=CopyBSTtoDT(TreeRoot->right,2*index+1);
	return copyRoot;
}

//畫畫
void Draw_BST(struct DrawTreeNode* DrawRoot, int node_radius)
{
	if (DrawRoot!=NULL)
	{
		Form2->Image1->Canvas->Pen->Color = clBlue;
        int level = ceil(log(DrawRoot->index+1)/log(2.0));
		if (DrawRoot->left != NULL)
		{
			Form2->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);
			Form2->Image1->Canvas->LineTo(X[DrawRoot->left->index],Y[level+1]);
		}
		if (DrawRoot->right != NULL)
		{
			Form2->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);
			Form2->Image1->Canvas->LineTo(X[DrawRoot->right->index],Y[level+1]);
		}
		//給圓外接正方形的左上跟右下座標
		Form2->Image1->Canvas->Ellipse(X[DrawRoot->index]-node_radius, Y[level]-node_radius,X[DrawRoot->index]+node_radius, Y[level]+node_radius);
		Form2->Image1->Canvas->TextOut(X[DrawRoot->index]-5, Y[level]-7,IntToStr(DrawRoot->data));
		Draw_BST(DrawRoot->left, node_radius);
		Draw_BST(DrawRoot->right, node_radius);
	}
}


void draw(struct BSTNode * root)
{
	Form2->Image1->Picture->Assign(NULL); //Clear Image
	int depth = Depth_BTree(root, 1);
	int tree_Height = Form2->ScrollBox1->Height;
	int tree_Width = Form2->ScrollBox1->Width;
	int total_node = pow(2, depth)-1;
	int detW = tree_Width/(total_node+1);
	int detH = tree_Height/(depth+1);
	int node_radius = (detW*5/6 > detH/2) ? detH/2 : detW*5/6;
	Form2->Image1->Top =0;
	Form2->Image1->Left = 0;
	Form2->Image1->Height = tree_Height;
	Form2->Image1->Width = tree_Width;
	DrawRoot = CopyBSTtoDT(root, 1);
	X = new int [total_node+2];
	Y = new int [depth+1];
	determine_X(DrawRoot, node_radius, tree_Width-node_radius);
	determine_Y(DrawRoot, 0, tree_Height, depth);
	Draw_BST(DrawRoot, node_radius);
	delete(X);
	delete(Y);

}
//---------------------------------------------------------------------------

