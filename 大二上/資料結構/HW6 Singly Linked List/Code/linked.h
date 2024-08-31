//---------------------------------------------------------------------------

#ifndef linkedH
#define linkedH
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
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *InsertFirst;
	TButton *InsertLast;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TButton *SearchTarget;
	TButton *SearchInsertAfter;
	TButton *SearchInsertBefore;
	TButton *DeleteTarget;
	TEdit *Edit2;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TButton *RandomlyInsert;
	TButton *ClearAll;
	TButton *Reverse;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox4;
	TLabel *Label5;
	TButton *PushStack;
	TEdit *Edit5;
	TGroupBox *GroupBox5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *PopStack;
	TGroupBox *GroupBox6;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *Edit6;
	TEdit *Edit7;
	TButton *RandomPushStack;
	TButton *ClearAllStack;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox7;
	TLabel *Label10;
	TEdit *Edit8;
	TButton *AddQueue;
	TGroupBox *GroupBox8;
	TLabel *Label11;
	TLabel *Label12;
	TButton *DeleteQueue;
	TGroupBox *GroupBox9;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *Edit9;
	TEdit *Edit10;
	TButton *RandomAdd;
	TButton *ClearAllQueue;
	TTabSheet *TabSheet4;
	TGroupBox *GroupBox10;
	TLabel *Label15;
	TEdit *Edit11;
	TButton *DInsertFirst;
	TButton *DInsertLast;
	TGroupBox *GroupBox11;
	TLabel *Label16;
	TEdit *Edit12;
	TButton *DSearchTarget;
	TButton *DSearchInsert_before;
	TButton *DSearchInsertAfter;
	TButton *DSearchDelete;
	TGroupBox *GroupBox12;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *Edit13;
	TEdit *Edit14;
	TButton *DRandom;
	TButton *DClearAll;
	TMemo *Memo1;
	TSplitter *Splitter1;
	void __fastcall InsertLastClick(TObject *Sender);
	void __fastcall InsertFirstClick(TObject *Sender);
	void __fastcall SearchTargetClick(TObject *Sender);
	void __fastcall SearchInsertBeforeClick(TObject *Sender);
	void __fastcall SearchInsertAfterClick(TObject *Sender);
	void __fastcall DeleteTargetClick(TObject *Sender);
	void __fastcall RandomlyInsertClick(TObject *Sender);
	void __fastcall ClearAllClick(TObject *Sender);
	void __fastcall PushStackClick(TObject *Sender);
	void __fastcall PopStackClick(TObject *Sender);
	void __fastcall RandomPushStackClick(TObject *Sender);
	void __fastcall ClearAllStackClick(TObject *Sender);
	void __fastcall AddQueueClick(TObject *Sender);
	void __fastcall DeleteQueueClick(TObject *Sender);
	void __fastcall RandomAddClick(TObject *Sender);
	void __fastcall ClearAllQueueClick(TObject *Sender);
	void __fastcall ReverseClick(TObject *Sender);
	void __fastcall DInsertFirstClick(TObject *Sender);
	void __fastcall DInsertLastClick(TObject *Sender);
	void __fastcall DSearchTargetClick(TObject *Sender);
	void __fastcall DSearchInsert_beforeClick(TObject *Sender);
	void __fastcall DSearchInsertAfterClick(TObject *Sender);
	void __fastcall DSearchDeleteClick(TObject *Sender);
	void __fastcall DRandomClick(TObject *Sender);
	void __fastcall DClearAllClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
