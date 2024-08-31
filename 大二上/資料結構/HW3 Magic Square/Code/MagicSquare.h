//---------------------------------------------------------------------------

#ifndef MagicSquareH
#define MagicSquareH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TMemo *Memo1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TRadioGroup *RadioGroup1;
	TCheckBox *CheckBox1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TStringGrid *StringGrid1;
	TRadioGroup *RadioGroup2;
	TLabel *Label2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
