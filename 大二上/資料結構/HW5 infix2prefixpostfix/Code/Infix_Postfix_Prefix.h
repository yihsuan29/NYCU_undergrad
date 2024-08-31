//---------------------------------------------------------------------------

#ifndef Infix_Postfix_PrefixH
#define Infix_Postfix_PrefixH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TEdit *Edit3;
	TButton *Button1;
	TButton *Button2;
	TTabSheet *TabSheet2;
	TSplitter *Splitter1;
	TEdit *Edit2;
	TEdit *Edit1;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TButton *Button3;
	TButton *Button4;
	TTabSheet *TabSheet3;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TButton *Button5;
	TButton *Button6;
	TPanel *Panel1;
	TCheckBox *CheckBox1;
	TSplitter *Splitter2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *CheckBox2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
