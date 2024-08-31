//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Infix_Postfix_Prefix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
String stack_operand[100];
String stack_operator[100];
int print;
int top1;
int top2;
int flag;
int trace=1;
int P_value(String x)
{
	if(x=="@")
		return 9;
	else if(x=="("||x==")")
		return 8;
	else if(x=="^")
		return 7;
	else if(x=="*"||x=="/"||x=="%")
		return 6;
	else if(x=="+"||x=="-")
		return 5;
	else if(x=="&")
		return 4;
	else if(x=="|")
		return 3;
	else if(x=="#")
		return 1;
	else
		return 0;
}
int Q_value(String x)
{

    if(x=="@")
		return 9;
	else if(x=="(")
		return 2;
	else if(x=="^")
		return 7;
	else if(x=="*"||x=="/"||x=="%")
		return 6;
	else if(x=="+"||x=="-")
		return 5;
    else if(x=="&")
		return 4;
	else if(x=="|")
		return 3;
	else if(x=="#")
		return 1;
}
void push(String x,int opn)
{
	if(opn==1)
		stack_operand[++top1] =x;
	else
		stack_operator[++top2] =x;
    if(trace)
	{
		Form2->Memo1->Lines->Add("Push "+x+" into Stack"+IntToStr(opn));
	}
}
String pop(int opn)
{

	if(opn==1)
	{
		if(trace)
		{
			Form2->Memo1->Lines->Add("Pop the top element "+stack_operand[top1]+" from Stack1");
		}
		return stack_operand[top1--];
    }

	else
	{
        if(trace)
		{
			Form2->Memo1->Lines->Add("Pop the top element "+stack_operator[top2]+" from Stack2");
		}
		return stack_operator[top2--];
	}
}
void PrintStack(int x)
{

	if(print)
	{
		int i;
		String s="Stack";
		s+=IntToStr(x);
		s+="=> ";
		if(x==1)
			for(i=0;i<=top1;i++)
				s+=stack_operand[i]+" ";
		else
			for(i=0;i<=top2;i++)
				s+=stack_operator[i]+" ";
		Form2->Memo1->Lines->Add(s);
	}
}
void TraceCompare(String s,String s1,int p,int q,int x)
{

	if(trace)
	{
		if(x==1)
			Form2->Memo1->Lines->Add("P("+s+")="+IntToStr(p)+"<= Q("+s1+")="+IntToStr(q));
	   else
			Form2->Memo1->Lines->Add("P("+s+")="+IntToStr(p)+"> Q("+s1+")="+IntToStr(q));
	}
}

String get_fix(String s,int flag)
{
	String a=pop(1);
	String b=pop(1);
	//後序
	if(flag==0)
		a=b+a+s;
	else
		a=s+b+a;
	return a;
}
String In2PostOrPre(String s,int flag)
{
	int i;
	int Operand=1;
	int Operator=2;
	String s_tmp;
	PrintStack(1);
	PrintStack(2);
	push("#",2);
	PrintStack(1);
	PrintStack(2);
	for(i=1;i<=s.Length();i++)
	{
		String x=s[i];
		if(P_value(x)==0)
		{
			if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand==>");
			push(x,Operand);
			PrintStack(1);
			PrintStack(2);
		}
		else if(x==")")
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" ==>");
			while((s_tmp=pop(Operator))!="(")
			{
				push(get_fix(s_tmp,flag),Operand);
				PrintStack(1);
				PrintStack(2);
			}
		}
		else
		{

			while(P_value(x)<=Q_value(stack_operator[top2]))
			{
                if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
				TraceCompare(x,stack_operator[top2],P_value(x),Q_value(stack_operator[top2]),1);
				s_tmp=pop(Operator);
				push(get_fix(s_tmp,flag),Operand);
				PrintStack(1);
				PrintStack(2);
			}
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
			TraceCompare(x,stack_operator[top2],P_value(x),Q_value(stack_operator[top2]),0);
			push(x,Operator);
			PrintStack(1);
			PrintStack(2);
		}
	}
	while((s_tmp=pop(Operator))!="#")
	{
         if(trace)
			Form2->Memo1->Lines->Add("The Stack is Not empty==>");
		 push(get_fix(s_tmp,flag),Operand);
		 PrintStack(1);
		 PrintStack(2);
	}
	pop(2);
	PrintStack(1);
	PrintStack(2);
	return pop(Operand);
}
String Post2Pre(String s)
{
	int i;
	int Operand=1;
	int Operator=2;
	PrintStack(1);
	for(i=1;i<=s.Length();i++)
	{
		String x=s[i];
		if(P_value(x)==0)
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand==>");
			push(x,Operand);
			PrintStack(1);
		}
		//順序已經排好不用檢測
		else
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
			push(get_fix(x,1),Operand);
			PrintStack(1);
		}
	}
	return pop(Operand);
}
String Pre2Post(String s)
{
	//一起運算的operand會黏再一起
	//只要一個Stack就好(可以看出operand是不是相連)
	int i;
	PrintStack(1);
	push("#",1);
	PrintStack(1);
	for(i=1;i<=s.Length();i++)
	{
		String x=s[i],y,z;
		if(P_value(x)==0)
		{
			//查是不是有相連的operand
			while(P_value(stack_operand[top1])==0)
			{
                if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand and the top element int the stack is also an operand==>");
				//pop出來變 從+yx變 yx+
				y=pop(1);
				z=pop(1);
				x=y+x+z;
			}
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand and the top element int the stack is Not an operand==>");
            push(x,1);
			PrintStack(1);
		}
		else
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
			push(x,1);
			PrintStack(1);
		}
	}
	PrintStack(1);
	return pop(1);
}
String Post2In(String s)
{
	//後序排法中位階低的會排在位階高的後面
	//所以如果遇到位階低的排前面代表他受到括號的加持位階提高
	//因此還原時 若發現有位階高的放在位階低後面記得先幫位階低的運算組合加上括號
	int i;
	int Operand=1;
	int Operator=2;
	PrintStack(1);
	PrintStack(2);
	for(i=1;i<=s.Length();i++)
	{
		String x=s[i],d1,d2,r1,r2;//d是operand r是operator
		if(P_value(x)==0)
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand==>");
			push(x,Operand);
			//一組Operand要有一個對應的運算子 所以放入@
			//為了避免出現(x)+(y)這種多餘的括號 @的Q_value最高
			push("@",Operator);
			PrintStack(1);
			PrintStack(2);
		}
		else
		{
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
			//比較他跟前兩組operand各自夾帶的運算子 位階高低
			//後項
			d1=pop(Operand);
			r1=pop(Operator);
			//如果d1這組所帶的運算子位階小於s代表他被括號加持了 要還原回去
			if(Q_value(r1)<P_value(x))
			{
				if(trace)
					Form2->Memo1->Lines->Add("P("+x+")="+IntToStr(P_value(x))+"> Q("+r1+")="+IntToStr(Q_value(r1))+" ==>Add Parentheses to"+d1);
				d1="("+d1+")";
			}
			//前項
			d2=pop(Operand);
			r2=pop(Operator);
			if(Q_value(r2)<P_value(x))
			{
                if(trace)
					Form2->Memo1->Lines->Add("P("+x+")="+IntToStr(P_value(x))+"> Q("+r2+")="+IntToStr(Q_value(r2))+" ==>Add Parentheses to"+d2);
				d2="("+d2+")";
			}
			//把位階還原之後的組合存回去
			push(d2+x+d1,Operand);
			push(x,Operator);
			PrintStack(1);
			PrintStack(2);
		}

	}
	while(top2>0)
	{
		if(trace)
			Form2->Memo1->Lines->Add("The Stack is Not empty==>");
		pop(2);
		PrintStack(1);
		PrintStack(2);
    }
	return pop(Operand);
}
String Pre2In(String s)
{
	//STACK1 運算子是銜接兩個"相鄰"的運算元
    //STACK2
	//前序排法中位階低的會排在位階高的前面
	//所以如果遇到位階低的排後面代表他受到括號的加持位階提高
	//因此還原時 若發現有位階高的放在位階低前面記得先幫位階低的運算組合加上括號

	int i;
	int Normal=1;
	int Special=2;
	PrintStack(1);
	PrintStack(2);
	push("#",Normal);
	PrintStack(1);
	PrintStack(2);
	for(i=1;i<=s.Length();i++)
	{
		String x=s[i],d2,d3,r1,r2;//d是operand r是operator
		if(P_value(x)==0)
		{
			r1="@";
			//如果有相連的
			while(P_value(stack_operand[top1])==0)
			{
				if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand and the top element int the stack is also an operand==>");
				//d2 r2是存前項跟他夾住的運算子;
				d2=pop(Normal);
				r2=pop(Special);
				//d3是銜接前後項的運算子
				d3=pop(Normal);
				//檢查是否位階有顛倒
				if(P_value(d3)>Q_value(r1))
				{
					if(trace)
						Form2->Memo1->Lines->Add("P("+d3+")="+IntToStr(P_value(d3))+"> Q("+r1+")="+IntToStr(Q_value(r1))+" ==>Add Parentheses to"+x);
					x="("+x+")";
				}
				if(P_value(d3)>Q_value(r2))
				{
                    if(trace)
						Form2->Memo1->Lines->Add("P("+d3+")="+IntToStr(P_value(d3))+"> Q("+r2+")="+IntToStr(Q_value(r2))+" ==>Add Parentheses to"+d2);
					d2="("+d2+")";
				}
				x=d2+d3+x;
				r1=d3;
			}
            if(trace)
					Form2->Memo1->Lines->Add(x+" is an operand and the top element int the stack is Not an operand==>");
            push(x,Normal);
			push(r1,Special);
			PrintStack(1);
			PrintStack(2);

		}
		else
		{
			if(trace)
					Form2->Memo1->Lines->Add(x+" is an operator==>");
			push(x,Normal);
			PrintStack(1);
			PrintStack(2);
		}

	}
    while(top2>0)
	{
        if(trace)
			Form2->Memo1->Lines->Add("The Stack is Not empty==>");
		pop(2);
		PrintStack(1);
		PrintStack(2);
	}
	return pop(Normal);
}

//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if(CheckBox1->Checked)
		print=1;
	else
		print=0;
    if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit1->Text;
	String s1;
	top1=0;
	top2=0;
	s1=In2PostOrPre(s,0);
	Form2->Memo1->Lines->Add("Infix:  "+s);
	Form2->Memo1->Lines->Add("Postfix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit2->Text=s1;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
    if(CheckBox1->Checked)
		print=1;
	else
		print=0;
    if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit1->Text;
	String s1;
	top1=0;
	top2=0;
	s1=In2PostOrPre(s,1) ;
	Form2->Memo1->Lines->Add("Infix:  "+s);
	Form2->Memo1->Lines->Add("Prefix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit3->Text=s1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
    if(CheckBox1->Checked)
		print=1;
	else
		print=0;
    if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit4->Text;
	String s1;
	top1=0;
	top2=0;
	s1=Post2In(s) ;
	Form2->Memo1->Lines->Add("Postfix:  "+s);
	Form2->Memo1->Lines->Add("Infix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit5->Text=s1;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
    if(CheckBox1->Checked)
		print=1;
	else
		print=0;
    if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit4->Text;
	String s1;
	top1=0;
	top2=0;
	s1=Post2Pre(s) ;
	Form2->Memo1->Lines->Add("Postfix:  "+s);
	Form2->Memo1->Lines->Add("Prefix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit6->Text=s1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button5Click(TObject *Sender)
{
    if(CheckBox1->Checked)
		print=1;
	else
		print=0;
	if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit7->Text;
	String s1;
	top1=0;
	top2=0;
	s1=Pre2In(s) ;
	Form2->Memo1->Lines->Add("Prefix:  "+s);
	Form2->Memo1->Lines->Add("Infix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit8->Text=s1;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button6Click(TObject *Sender)
{
    if(CheckBox1->Checked)
		print=1;
	else
		print=0;
	if(CheckBox2->Checked)
		trace=1;
	else
		trace=0;
	String s=Edit7->Text;
	String s1;
	top1=0;
	s1=Pre2Post(s) ;
	PrintStack(1);
	pop(1);
	PrintStack(1);
	Form2->Memo1->Lines->Add("Prefix:  "+s);
	Form2->Memo1->Lines->Add("Postfix:  "+s1);
	Form2->Memo1->Lines->Add("-------------------------------------");
	Form2->Edit9->Text=s1;
}
//---------------------------------------------------------------------------


