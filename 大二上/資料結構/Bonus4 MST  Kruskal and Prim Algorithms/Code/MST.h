//---------------------------------------------------------------------------

#ifndef MSTH
#define MSTH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TMemo *Memo1;
	TStringGrid *StringGrid1;
	TStringGrid *StringGrid2;
	TStringGrid *StringGrid3;
	TStringGrid *StringGrid4;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label3;
	TEdit *Edit4;
	TLabel *Label4;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox2;
	TCheckBox *CheckBox2;
	TGroupBox *GroupBox3;
	TLabel *Label5;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TTabSheet *TabSheet6;
	TStringGrid *StringGrid5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
