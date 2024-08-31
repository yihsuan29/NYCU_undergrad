//---------------------------------------------------------------------------

#ifndef BSTH
#define BSTH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Insert;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TEdit *Edit2;
	TButton *Delete;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TLabel *Label3;
	TGroupBox *Traversal;
	TButton *travel;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit3;
	TEdit *Edit4;
	TButton *Button3;
	TLabel *Label6;
	TButton *Button4;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *Memo1;
	TScrollBox *ScrollBox1;
	TImage *Image1;
	void __fastcall InsertClick(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall travelClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
