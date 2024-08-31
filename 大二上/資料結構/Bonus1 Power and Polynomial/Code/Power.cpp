//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cmath>
#include <time.h>
#include "Power.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int x;
int n;
int runtime;
int i,j,t;
int co[30];
unsigned long long *f;
int k;
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//pow(x,n)
void pow()
{
	clock_t t_begin,t_end;
	t_begin= clock();
	int sum;
	for(i=0;i<runtime;i++)
	{
		sum=pow(x,n);
	}
	t_end= clock();
	Form2->Memo1->Lines->Add("pow(k,n) = "+IntToStr(sum)+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)]"+IntToStr(runtime)+" times");
}
//for
void forloop()
{
	clock_t t_begin,t_end;
	t_begin= clock();
	int sum;
	for(i=0;i<runtime;i++)
	{
		sum=1;
		for(j=0;j<n;j++)
			sum*=x;
	}
	t_end= clock();
	Form2->Memo1->Lines->Add("for-loop = "+IntToStr(sum)+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)]"+IntToStr(runtime)+" times");
}
void square()
{
	clock_t t_begin,t_end;
	t_begin= clock();
	int sum;
	int n_tmp;
	int x_tmp;
	for(i=0;i<runtime;i++)
	{
		sum=1;
		n_tmp=n;
        x_tmp=x;
		while(n_tmp>0)
		{
			if(n_tmp%2==1)
				sum*=x_tmp;
			x_tmp*=x_tmp;
			n_tmp/=2;

		}
	}
	t_end= clock();
	Form2->Memo1->Lines->Add("square = "+IntToStr(sum)+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)]"+IntToStr(runtime)+" times");
}
void square_bit()
{
	clock_t t_begin,t_end;
	t_begin= clock();
	int sum;
	int n_tmp;
	int x_tmp;
	for(i=0;i<runtime;i++)
	{
		sum=1;
		n_tmp=n;
		x_tmp=x;
		while(n_tmp>0)
		{
			if(n_tmp&1)
				sum*=x_tmp;
			x_tmp*=x_tmp;
			n_tmp>>=1;

		}
	}
	t_end= clock();
	Form2->Memo1->Lines->Add("square_>> = "+IntToStr(sum)+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)]"+IntToStr(runtime)+" times");
}
void generate()
{
	srand(time(NULL));
	String s="f(x)=" ;
	for(i=0;i<k;i++)
	{
		co[i]=rand()%100;
		if(i==0)
			s+=IntToStr(co[i]);
		else if(i==1)
			s+=" + "+IntToStr(co[i])+"x";
		else
			s+=" + "+IntToStr(co[i])+"x^"+IntToStr(i);
	}
	Form2->Memo2->Lines->Add(s);
}
void hornor(int time,int flag)
{
	String s;
	/*
	f(x)=a0+a1x1+a2x2+a3x3+...+ak-1xk-1
		=a0+x(a1+x(a2+x(a3+x(.....ak-3+x(ak-2+x(ak-1))
	先從裡面一個一個括號乘出來
	最裡面為 c0=x*ak-1;
	下一層是 c1=x*(ak-2+c0);
	下一層是 c2=x*(ak-3+c1);
	*/

	clock_t t_begin,t_end;
	t_begin= clock();
	for(t=0;t<time;t++)
	{
		s="";
		for(i=0;i<=n;i++)
		{

			f[i]=i*co[k-1];    //x*ak-1
			for(j=k-2;j>0;j--)
			{
				f[i]=i*(co[j]+f[i]); //c'=x*(aj+c)
			}
			//最後把常數項加回去
			f[i]+=co[0];
			s+="f("+IntToStr(i)+")="+f[i]+" ";
		}
	}
    t_end= clock();
	if(flag==0)
		Form2->Memo2->Lines->Add(s);
	else
		Form2->Memo2->Lines->Add("honor: "+s+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)] 1000000 times");
}
void pow_poly(int time)
{
	/*一項一項乘之後再乘係數*/
	unsigned long long  sum;
	String s;
	clock_t t_begin,t_end;
	t_begin= clock();
	for(t=0;t<time;t++)
	{
		s="";
		for(i=0;i<=n;i++)
		{
			f[i]=co[0];
			for(j=1;j<=k;j++)
			{
				f[i]+=co[j]*pow(i,j);
            }
			s+="f("+IntToStr(i)+")="+f[i]+" ";
		}
	}
	t_end= clock();
	Form2->Memo2->Lines->Add("pow: "+s+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)] 1000000 times");
}

void loop_poly(int time)
{
	/*一項一項乘之後再乘係數*/
	unsigned long long *p=(unsigned long long *)malloc(k*sizeof(unsigned long long));
	String s;
	clock_t t_begin,t_end;
	t_begin= clock();
	for(t=0;t<time;t++)
	{
		s="";
		for(i=0;i<=n;i++)
		{
			p[0]=1;
			for(j=1;j<=k;j++)
			{
				p[j]=i*p[j-1];
			}
			f[i]=co[0];
			for(j=1;j<=k;j++)
			{
				f[i]+=co[j]*p[j];
			}
			s+="f("+IntToStr(i)+")="+f[i]+" ";
		}
	}
	t_end= clock();
	Form2->Memo2->Lines->Add("loop: "+s+"["+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC)+"(sec.)] 1000000 times");
}

void __fastcall TForm2::Button1Click(TObject *Sender)
{
	x=StrToInt(Edit1->Text);
	n=StrToInt(Edit2->Text);
	runtime=StrToInt(Edit3->Text);
	if(CheckBox1->Checked)pow();
	if(CheckBox2->Checked)forloop();
	if(CheckBox3->Checked)square();
	if(CheckBox4->Checked)square_bit();
	Form2->Memo1->Lines->Add("-------------------------------");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	k=StrToInt(Edit4->Text);
	n=StrToInt(Edit5->Text);
	runtime=StrToInt(Edit6->Text);
	f=(unsigned long long *)malloc(k*sizeof(unsigned long long));
	generate();
	hornor(1,0);
    Form2->Memo2->Lines->Add("-------------------------------");
	if(CheckBox5->Enabled&&CheckBox5->Checked)pow_poly(runtime);
	if(CheckBox6->Enabled&&CheckBox6->Checked)loop_poly(runtime);
	if(CheckBox7->Enabled&&CheckBox7->Checked)hornor(runtime,1);
    free(f);
	if(CheckBox8->Checked)Form2->Memo2->Lines->Add("-------------------------------");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBox8Click(TObject *Sender)
{
	if(CheckBox8->Checked)
	{
		CheckBox5->Enabled=true;
		CheckBox6->Enabled=true;
		CheckBox7->Enabled=true;
    }
	else
	{
		CheckBox5->Enabled=false;
		CheckBox6->Enabled=false;
		CheckBox7->Enabled=false;
	}
}
//---------------------------------------------------------------------------

