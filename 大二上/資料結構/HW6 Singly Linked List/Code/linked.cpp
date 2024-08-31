//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "linked.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//singly list
//定義singly linked node
struct node
{
	int data;
	struct node * next;
};
struct node * last;
struct node * header;//最開始的空白節點
int element;
int target;
int length=0;
int n;
int range;
//新增節點
struct node * NewNode(int element)
{
	struct node * p=(node *)malloc(sizeof(node));
	p->data = element;
	p->next = NULL;
	return p;
}
//印出list
void PrintList(struct node * header)
{
	struct node * p;
	String s="Singly Linked List: ";
	//終止條件為他逛了一圈
	for(p=header->next;p!=header;p=p->next)
	{
		s+=IntToStr(p->data)+"=>";
	}
	if(s=="Singly Linked List: ")
		s+=">";
	s+="<";
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//InsertFirst
void Insert_first(int element)
{
	struct node * x = NewNode(element);
	//先把原本第一個的指給新的
	x->next =header->next;
	//再將新的串上去
	header->next = x;
	//如果他是最後一個last就要指他
	if(x->next==header)last=x;
	length++;
}
void __fastcall TForm2::InsertFirstClick(TObject *Sender)
{
	element = StrToInt(Edit1->Text);
	Insert_first(element);
	PrintList(header);
	srand(time(NULL));
	Edit1->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//InsertLast
void Insert_last(int element)
{
	struct node * x = NewNode(element);
	last->next = x;
	x->next = header;
	last = x;
	length++;

}
void __fastcall TForm2::InsertLastClick(TObject *Sender)
{
	element = StrToInt(Edit1->Text);
	Insert_last(element);
	PrintList(header);
    srand(time(NULL));
	Edit1->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchTarget
int Search_target(int target)
{
	struct node * p;
	int tmp_length=1;
	//逛一圈找
	for(p=header->next;(p!=header&&p->data!=target);(p=p->next,tmp_length++));
	return tmp_length;
}
void __fastcall TForm2::SearchTargetClick(TObject *Sender)
{
	target= StrToInt(Edit2->Text);
	int tmp_length=Search_target(target);
	if(tmp_length==length+1)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
		Form2->Memo1->Lines->Add(IntToStr(target)+" is the "+IntToStr(tmp_length)+"th one.");
}
//---------------------------------------------------------------------------
//SearchBefore
int Search_before(int target,int element)
{
	struct node * p;
	struct node * q=header;
	//逛一圈找
	for(p=header->next;(p!=header&&p->data!=target);(q=q->next,p=p->next));
	if(p==header)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{
		struct node * x = NewNode(element);
		x->next = p;
		q->next = x;
		length++;
		PrintList(header);
	}
}
void __fastcall TForm2::SearchInsertBeforeClick(TObject *Sender)
{
	element = StrToInt(Edit1->Text);
	target= StrToInt(Edit2->Text);
	Search_before(target,element);
	srand(time(NULL));
	Edit1->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchAfter
int Search_after(int target,int element)
{
	struct node * p;
	//逛一圈找
	for(p=header->next;(p!=header&&p->data!=target);(p=p->next));
	if(p==header)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{
		struct node * x = NewNode(element);
		if(p->next==header)last=x;
		x->next = p->next;
		p->next = x;
        length++;
		PrintList(header);
	}
}

void __fastcall TForm2::SearchInsertAfterClick(TObject *Sender)
{
	element = StrToInt(Edit1->Text);
	target= StrToInt(Edit2->Text);
	Search_after(target,element);
	srand(time(NULL));
	Edit1->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchDelete
int Search_delete(int target)
{
	struct node * p;
	struct node * q=header;
	//逛一圈找
	for(p=header->next;(p!=header&&p->data!=target);(q=p,p=p->next));
	if(p==header)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{

		if(p->next==header)last = q;
		q->next = p->next;
		free(p);
		PrintList(header);
		length--;
	}
}
void __fastcall TForm2::DeleteTargetClick(TObject *Sender)
{
	target= StrToInt(Edit2->Text);
	Search_delete(target);
}
//---------------------------------------------------------------------------
//RandomlyInsert
void __fastcall TForm2::RandomlyInsertClick(TObject *Sender)
{
	n=StrToInt(Edit3->Text);
	range = StrToInt(Edit4->Text);
	int i,num;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		num = rand()%range+1;
		Insert_last(num);
	}
	PrintList(header);
}
//---------------------------------------------------------------------------
//ClearAll
void __fastcall TForm2::ClearAllClick(TObject *Sender)
{
	struct node * p=header;
	struct node * q;
	while(p->next!=header)
	{
		q=p->next;
		p->next=q->next;
		free(q);
        length--;
		//PrintList(header);
	}
	last=header;
	PrintList(header);
}
//---------------------------------------------------------------------------
//reverse
void ReverseList()
{
	struct node * x;
	struct node * y=header;
	struct node * z=header->next;
	last=z;
	while(z!=header)
	{
		x=y;
		y=z;
		z=z->next;
		y->next=x;
	}
	header->next=y;
	PrintList(header);
}
void __fastcall TForm2::ReverseClick(TObject *Sender)
{
	ReverseList();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//double linked list
struct DoubleNode
{
	struct DoubleNode * pre;
	int data;
	struct DoubleNode * next;
};
struct DoubleNode * DoubleLast;
struct DoubleNode * DoubleHeader;//最開始的空白節點
int DoubleLength=0;
//新增節點
struct DoubleNode * NewDoubleNode(int element)
{
	struct DoubleNode * p=(DoubleNode *)malloc(sizeof(DoubleNode));
	p->pre = NULL;
	p->data = element;
	p->next = NULL;
	return p;
}
//印出list
void PrintDoubleList(struct DoubleNode * DoubleHeader)
{
	struct DoubleNode * p;
	String s="Doubly Linked List:" ;
	Form2->Memo1->Lines->Add(s);
	s="(next->) >";
	//終止條件為他逛了一圈
	for(p=DoubleHeader->next;p!=DoubleHeader;p=p->next)
	{
		s+=IntToStr(p->data)+"<=>";
	}
	s+="<";
	Form2->Memo1->Lines->Add(s);
	s="(<-pre ) >";
	//終止條件為他逛了一圈
	for(p=DoubleHeader->pre;p!=DoubleHeader;p=p->pre)
	{
		s+=IntToStr(p->data)+"<=>";
	}
	s+="<";
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//InsertFirst
void DoubleInsert_first(int element)
{
	struct DoubleNode * x = NewDoubleNode(element);
	//先把原本第一個的指給新的
	x->next =DoubleHeader->next;
	x->pre = DoubleHeader;
	//再將新的串上去
	DoubleHeader->next->pre=x;
	DoubleHeader->next = x;
	//如果他是最後一個last就要指他
	if(x->next==DoubleHeader)DoubleLast=x;
	DoubleLength++;
}
void __fastcall TForm2::DInsertFirstClick(TObject *Sender)
{
	element = StrToInt(Edit11->Text);
	DoubleInsert_first(element);
	PrintDoubleList(DoubleHeader);
	srand(time(NULL));
	Edit11->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//InsertLast
void DoubleInsert_last(int element)
{
	struct DoubleNode * x = NewDoubleNode(element);
	x->pre = DoubleLast;
	DoubleLast->next = x;
	x->next = DoubleHeader;
	DoubleHeader->pre = x;
	DoubleLast = x;
	DoubleLength++;

}
void __fastcall TForm2::DInsertLastClick(TObject *Sender)
{
	element = StrToInt(Edit11->Text);
	DoubleInsert_last(element);
	PrintDoubleList(DoubleHeader);
	srand(time(NULL));
	Edit11->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchTarget
int DoubleSearch_target(int target)
{
	struct DoubleNode * p;
	int tmp_length=1;
	//逛一圈找
	for(p=DoubleHeader->next;(p!=DoubleHeader&&p->data!=target);(p=p->next,tmp_length++));
	return tmp_length;
}
void __fastcall TForm2::DSearchTargetClick(TObject *Sender)
{
	target= StrToInt(Edit12->Text);
	int tmp_length=DoubleSearch_target(target);
	if(tmp_length==DoubleLength+1)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
		Form2->Memo1->Lines->Add(IntToStr(target)+" is the "+IntToStr(tmp_length)+"th one.");
}
//---------------------------------------------------------------------------
//SearchBefore
int DoubleSearch_before(int target,int element)
{
	struct DoubleNode * p;
	//逛一圈找
	for(p=DoubleHeader->next;(p!=DoubleHeader&&p->data!=target);(p=p->next));
	if(p==DoubleHeader)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{
		struct DoubleNode * x = NewDoubleNode(element);
		x->next = p;
		x->pre = p->pre;
		p->pre->next = x;
		p->pre = x;
		DoubleLength++;
		PrintDoubleList(DoubleHeader);
	}
}
void __fastcall TForm2::DSearchInsert_beforeClick(TObject *Sender)
{
	element = StrToInt(Edit11->Text);
	target= StrToInt(Edit12->Text);
	DoubleSearch_before(target,element);
	srand(time(NULL));
	Edit11->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchAfter
int DoubleSearch_after(int target,int element)
{
	struct DoubleNode * p;
	//逛一圈找
	for(p=DoubleHeader->next;(p!=DoubleHeader&&p->data!=target);(p=p->next));
	if(p==DoubleHeader)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{
		struct DoubleNode * x = NewDoubleNode(element);
		if(p->next==DoubleHeader)DoubleLast=x;
		x->next = p->next;
		x->pre = p;
		p->next->pre = x;
		p->next = x;
		DoubleLength++;
		PrintDoubleList(DoubleHeader);
	}
}
void __fastcall TForm2::DSearchInsertAfterClick(TObject *Sender)
{
	element = StrToInt(Edit11->Text);
	target= StrToInt(Edit12->Text);
	DoubleSearch_after(target,element);
	srand(time(NULL));
	Edit11->Text=IntToStr(element+rand()%10+1);
}
//---------------------------------------------------------------------------
//SearchDelete
int DoubleSearch_delete(int target)
{
	struct DoubleNode * p;
	//逛一圈找
	for(p=DoubleHeader->next;(p!=DoubleHeader&&p->data!=target);(p=p->next));
	if(p==DoubleHeader)
		Form2->Memo1->Lines->Add(IntToStr(target)+" is Not in the list.");
	else
	{
		if(p->next==DoubleHeader)DoubleLast = p->pre;
		p->pre->next = p->next;
        p->next->pre = p->pre;
		free(p);
		DoubleLength--;
		PrintDoubleList(DoubleHeader);
	}
}
void __fastcall TForm2::DSearchDeleteClick(TObject *Sender)
{
	target= StrToInt(Edit12->Text);
	DoubleSearch_delete(target);
}
//---------------------------------------------------------------------------
//RandomlyInsert
void __fastcall TForm2::DRandomClick(TObject *Sender)
{
	n=StrToInt(Edit13->Text);
	range = StrToInt(Edit14->Text);
	int i,num;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		num = rand()%range+1;
		DoubleInsert_last(num);
	}
	PrintDoubleList(DoubleHeader);
}
//---------------------------------------------------------------------------
//ClearAll
void __fastcall TForm2::DClearAllClick(TObject *Sender)
{
	struct DoubleNode * p=DoubleHeader;
	struct DoubleNode * q;
	while(p->next!=DoubleHeader)
	{
		DoubleLength--;
		q=p->next;
		p->next=q->next;
		p->next->pre=p;
		free(q);
	}
	DoubleLast=DoubleHeader;
	PrintDoubleList(DoubleHeader);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Stack
struct StackNode
{
	int data;
	struct StackNode * next;
};
struct StackNode * top;
int StackHeight=0;
struct StackNode * NewStackNode(int element)
{
	struct StackNode * p = (StackNode *)malloc(sizeof(StackNode));
	p->data = element;
	p->next=NULL;
	return p;
}
void PrintStack(struct StackNode * top)
{
	struct StackNode * p;
	String s="Linked Stack: ";
	//終止條件為他逛了一圈
	for(p=top;p!=NULL;p=p->next)
	{
		s+=IntToStr(p->data)+"=>";
	}
	if(s=="Linked Stack: ")
		s+=">";
	s+="<";
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//PushStack
void PushInStack(int element)
{
	struct StackNode * x = NewStackNode(element);
	x->next=top;
	top = x;
	StackHeight++;
}
void __fastcall TForm2::PushStackClick(TObject *Sender)
{
	element = StrToInt(Edit5->Text);
	PushInStack(element);
	Edit5->Text=IntToStr(element+rand()%10+1);
	PrintStack(top);
}
//---------------------------------------------------------------------------
//PopStack
int PopFromStack()
{
	struct StackNode * x;
	int result;
	x=top;
	result = x->data;
	top = top->next;
	free(x);
	StackHeight--;
	return result;
}
void __fastcall TForm2::PopStackClick(TObject *Sender)
{
	if(StackHeight!=0)
	{
		int result=PopFromStack();
		Label7->Caption=IntToStr(result);
	}
	else
		Label7->Caption="Stack is empty";
	PrintStack(top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RandomPushStackClick(TObject *Sender)
{
	n = StrToInt(Edit6->Text);
	range  = StrToInt(Edit7->Text);
	int i,num;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		num = rand()%range+1;
		PushInStack(num);
	}
	PrintStack(top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClearAllStackClick(TObject *Sender)
{
	while(top!=0)PopFromStack();
	PrintStack(top);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Queue先進先出
struct QueueNode
{
	int data;
	struct QueueNode * next;
};
struct QueueNode * front;
struct QueueNode * back;
int QueueLength=0;
struct QueueNode * NewQueueNode(int element)
{
	struct QueueNode * p = (QueueNode *)malloc(sizeof(QueueNode));
	p->data = element;
	p->next=NULL;
	return p;
}
void PrintQueue(struct QueueNode * front)
{
	struct QueueNode * p;
	String s="Linked Queue: ";
	//終止條件為他逛了一圈
	for(p=front;p!=NULL;p=p->next)
	{
		s+=IntToStr(p->data)+"=>";
	}
	if(s=="Linked Queue: ")
		s+=">";
	s+="<";
	Form2->Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
//AddQueue
void AddToQueue(int element)
{
	struct QueueNode * x = NewQueueNode(element);
	if(back==NULL)front=x;
	else
		back->next=x;
	back=x;
    QueueLength++;
}
void __fastcall TForm2::AddQueueClick(TObject *Sender)
{
	element = StrToInt(Edit8->Text);
	AddToQueue(element);
	Edit8->Text=IntToStr(element+rand()%10+1);
	PrintQueue(front);
}
//---------------------------------------------------------------------------
//DeleteQueue
int DeleteFromQueue()
{
	struct QueueNode * x;
	int result;
    if(back==front)back=NULL;
	x=front;
	front=front->next;
	result=x->data;
	free(x);
	QueueLength--;
	return result;
}


//---------------------------------------------------------------------------

void __fastcall TForm2::DeleteQueueClick(TObject *Sender)
{
    if(QueueLength!=0)
	{
		int result=DeleteFromQueue();
		Label12->Caption=IntToStr(result);
	}
	else
		Label12->Caption="Queue is empty";
	PrintQueue(front);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RandomAddClick(TObject *Sender)
{
	n = StrToInt(Edit9->Text);
	range  = StrToInt(Edit10->Text);
	int i,num;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		num = rand()%range+1;
		AddToQueue(num);
	}
	PrintQueue(front);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClearAllQueueClick(TObject *Sender)
{
	while(front!=NULL)DeleteFromQueue();
	PrintQueue(front);
}

//---------------------------------------------------------------------------
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	//產生singly空白節點
	header = NewNode(0);
	header->next = header;
	last = header;
	//產生doubly空白節點
	DoubleHeader = NewDoubleNode(0);
	DoubleHeader->next = DoubleHeader;
	DoubleHeader->pre = DoubleHeader;
	DoubleLast = DoubleHeader;
}
