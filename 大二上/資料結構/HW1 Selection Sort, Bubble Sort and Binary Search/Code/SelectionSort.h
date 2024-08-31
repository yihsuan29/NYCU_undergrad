//---------------------------------------------------------------------------

#ifndef SelectionSortH
#define SelectionSortH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TMemo *Memo1;
	TButton *Button2;
	TMemo *Memo2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TButton *Button3;
	TButton *Button4;
	TMemo *Memo3;
	TMemo *Memo4;
	TLabel *Label3;
	TEdit *Edit3;
	TChart *Chart1;
	TBarSeries *Series2;
	TBarSeries *Series1;
	TLabel *Label4;
	TEdit *Edit4;
	TLabel *Label5;
	TEdit *Edit5;
	TPageControl *PageControl1;
	TTabSheet *Main;
	TTabSheet *Chart;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TRadioGroup *RadioGroup1;
	TCheckBox *CheckBox3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
