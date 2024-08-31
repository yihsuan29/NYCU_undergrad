object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Linked list/ stack/ queue by109705001'#38515#20197#29764
  ClientHeight = 523
  ClientWidth = 713
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 233
    Top = 0
    Width = 1
    Height = 523
    ExplicitLeft = 235
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 233
    Height = 523
    Align = alLeft
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 232
      Height = 521
      ActivePage = TabSheet1
      Align = alLeft
      MultiLine = True
      TabOrder = 0
      TabPosition = tpLeft
      ExplicitLeft = -4
      ExplicitTop = 2
      object TabSheet1: TTabSheet
        Caption = 'singly linked list'
        object GroupBox1: TGroupBox
          Left = 27
          Top = 16
          Width = 146
          Height = 118
          Caption = 'Insert'
          TabOrder = 0
          object Label1: TLabel
            Left = 13
            Top = 24
            Width = 52
            Height = 13
            Caption = 'element = '
          end
          object Edit1: TEdit
            Left = 66
            Top = 21
            Width = 67
            Height = 21
            TabOrder = 0
            Text = '11'
          end
          object InsertFirst: TButton
            Left = 12
            Top = 48
            Width = 122
            Height = 25
            Caption = 'Insert first'
            TabOrder = 1
            OnClick = InsertFirstClick
          end
          object InsertLast: TButton
            Left = 12
            Top = 79
            Width = 122
            Height = 25
            Caption = 'Insert last'
            TabOrder = 2
            OnClick = InsertLastClick
          end
        end
        object GroupBox2: TGroupBox
          Left = 27
          Top = 140
          Width = 146
          Height = 177
          Caption = 'Search target'
          TabOrder = 1
          object Label2: TLabel
            Left = 12
            Top = 24
            Width = 44
            Height = 13
            Caption = 'target = '
          end
          object SearchTarget: TButton
            Left = 12
            Top = 49
            Width = 122
            Height = 25
            Caption = 'Search target'
            TabOrder = 0
            OnClick = SearchTargetClick
          end
          object SearchInsertAfter: TButton
            Left = 12
            Top = 111
            Width = 122
            Height = 25
            Caption = 'Search_Insert after'
            TabOrder = 1
            OnClick = SearchInsertAfterClick
          end
          object SearchInsertBefore: TButton
            Left = 12
            Top = 80
            Width = 122
            Height = 25
            Caption = 'Search_Insert before'
            TabOrder = 2
            OnClick = SearchInsertBeforeClick
          end
          object DeleteTarget: TButton
            Left = 12
            Top = 142
            Width = 122
            Height = 25
            Caption = 'Delete target'
            TabOrder = 3
            OnClick = DeleteTargetClick
          end
          object Edit2: TEdit
            Left = 62
            Top = 22
            Width = 72
            Height = 21
            TabOrder = 4
            Text = '23'
          end
        end
        object GroupBox3: TGroupBox
          Left = 27
          Top = 323
          Width = 146
          Height = 110
          Caption = 'Random'
          TabOrder = 2
          object Label3: TLabel
            Left = 13
            Top = 24
            Width = 20
            Height = 13
            Caption = 'n = '
          end
          object Label4: TLabel
            Left = 8
            Top = 48
            Width = 42
            Height = 13
            Caption = 'range = '
          end
          object Edit3: TEdit
            Left = 39
            Top = 21
            Width = 95
            Height = 21
            TabOrder = 0
            Text = '5'
          end
          object Edit4: TEdit
            Left = 56
            Top = 48
            Width = 78
            Height = 21
            TabOrder = 1
            Text = '100'
          end
          object RandomlyInsert: TButton
            Left = 12
            Top = 75
            Width = 122
            Height = 25
            Caption = 'Random insert last '
            TabOrder = 2
            OnClick = RandomlyInsertClick
          end
        end
        object ClearAll: TButton
          Left = 38
          Top = 439
          Width = 122
          Height = 25
          Caption = 'Clear All'
          TabOrder = 3
          OnClick = ClearAllClick
        end
        object Reverse: TButton
          Left = 39
          Top = 470
          Width = 121
          Height = 25
          Caption = 'Reverse'
          TabOrder = 4
          OnClick = ReverseClick
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'linked stack'
        ImageIndex = 1
        object GroupBox4: TGroupBox
          Left = 27
          Top = 20
          Width = 146
          Height = 93
          Caption = 'Push'
          TabOrder = 0
          object Label5: TLabel
            Left = 13
            Top = 33
            Width = 52
            Height = 13
            Caption = 'element = '
          end
          object PushStack: TButton
            Left = 12
            Top = 56
            Width = 124
            Height = 25
            Caption = 'Push'
            TabOrder = 0
            OnClick = PushStackClick
          end
          object Edit5: TEdit
            Left = 71
            Top = 29
            Width = 65
            Height = 21
            TabOrder = 1
            Text = '13'
          end
        end
        object GroupBox5: TGroupBox
          Left = 27
          Top = 119
          Width = 146
          Height = 90
          Caption = 'Pop'
          TabOrder = 1
          object Label6: TLabel
            Left = 13
            Top = 32
            Width = 41
            Height = 13
            Caption = 'result = '
          end
          object Label7: TLabel
            Left = 56
            Top = 32
            Width = 3
            Height = 13
          end
          object PopStack: TButton
            Left = 11
            Top = 51
            Width = 124
            Height = 25
            Caption = 'Pop'
            TabOrder = 0
            OnClick = PopStackClick
          end
        end
        object GroupBox6: TGroupBox
          Left = 27
          Top = 215
          Width = 146
          Height = 122
          Caption = 'Random'
          TabOrder = 2
          object Label8: TLabel
            Left = 13
            Top = 32
            Width = 20
            Height = 13
            Caption = 'n = '
          end
          object Label9: TLabel
            Left = 13
            Top = 57
            Width = 39
            Height = 13
            Caption = 'range ='
          end
          object Edit6: TEdit
            Left = 39
            Top = 30
            Width = 95
            Height = 21
            TabOrder = 0
            Text = '5'
          end
          object Edit7: TEdit
            Left = 58
            Top = 57
            Width = 76
            Height = 21
            TabOrder = 1
            Text = '100'
          end
          object RandomPushStack: TButton
            Left = 11
            Top = 84
            Width = 124
            Height = 25
            Caption = 'Random push'
            TabOrder = 2
            OnClick = RandomPushStackClick
          end
        end
        object ClearAllStack: TButton
          Left = 40
          Top = 343
          Width = 123
          Height = 25
          Caption = 'Clear All'
          TabOrder = 3
          OnClick = ClearAllStackClick
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'linked queue'
        ImageIndex = 2
        object GroupBox7: TGroupBox
          Left = 27
          Top = 16
          Width = 146
          Height = 97
          Caption = 'Add'
          TabOrder = 0
          object Label10: TLabel
            Left = 13
            Top = 32
            Width = 52
            Height = 13
            Caption = 'element = '
          end
          object Edit8: TEdit
            Left = 68
            Top = 29
            Width = 66
            Height = 21
            TabOrder = 0
            Text = '12'
          end
          object AddQueue: TButton
            Left = 11
            Top = 56
            Width = 124
            Height = 25
            Caption = 'Add'
            TabOrder = 1
            OnClick = AddQueueClick
          end
        end
        object GroupBox8: TGroupBox
          Left = 27
          Top = 119
          Width = 146
          Height = 98
          Caption = 'Delete'
          TabOrder = 1
          object Label11: TLabel
            Left = 14
            Top = 32
            Width = 41
            Height = 13
            Caption = 'result = '
          end
          object Label12: TLabel
            Left = 56
            Top = 32
            Width = 3
            Height = 13
          end
          object DeleteQueue: TButton
            Left = 11
            Top = 51
            Width = 123
            Height = 25
            Caption = 'Delete'
            TabOrder = 0
            OnClick = DeleteQueueClick
          end
        end
        object GroupBox9: TGroupBox
          Left = 27
          Top = 223
          Width = 146
          Height = 122
          Caption = 'Random'
          TabOrder = 2
          object Label13: TLabel
            Left = 14
            Top = 32
            Width = 20
            Height = 13
            Caption = 'n = '
          end
          object Label14: TLabel
            Left = 14
            Top = 60
            Width = 42
            Height = 13
            Caption = 'range = '
          end
          object Edit9: TEdit
            Left = 40
            Top = 30
            Width = 95
            Height = 21
            TabOrder = 0
            Text = '5'
          end
          object Edit10: TEdit
            Left = 62
            Top = 57
            Width = 73
            Height = 21
            TabOrder = 1
            Text = '100'
          end
          object RandomAdd: TButton
            Left = 11
            Top = 84
            Width = 123
            Height = 25
            Caption = 'Random Add'
            TabOrder = 2
            OnClick = RandomAddClick
          end
        end
        object ClearAllQueue: TButton
          Left = 39
          Top = 351
          Width = 123
          Height = 25
          Caption = 'Clear All'
          TabOrder = 3
          OnClick = ClearAllQueueClick
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'double linked list'
        ImageIndex = 3
        object GroupBox10: TGroupBox
          Left = 28
          Top = 16
          Width = 146
          Height = 129
          Caption = 'Insert'
          TabOrder = 0
          object Label15: TLabel
            Left = 12
            Top = 32
            Width = 52
            Height = 13
            Caption = 'element = '
          end
          object Edit11: TEdit
            Left = 62
            Top = 29
            Width = 70
            Height = 21
            TabOrder = 0
            Text = '13'
          end
          object DInsertFirst: TButton
            Left = 12
            Top = 56
            Width = 122
            Height = 25
            Caption = 'Insert first'
            TabOrder = 1
            OnClick = DInsertFirstClick
          end
          object DInsertLast: TButton
            Left = 12
            Top = 87
            Width = 122
            Height = 25
            Caption = 'Insert last'
            TabOrder = 2
            OnClick = DInsertLastClick
          end
        end
        object GroupBox11: TGroupBox
          Left = 28
          Top = 151
          Width = 146
          Height = 186
          Caption = 'Search'
          TabOrder = 1
          object Label16: TLabel
            Left = 13
            Top = 32
            Width = 41
            Height = 13
            Caption = 'target= '
          end
          object Edit12: TEdit
            Left = 60
            Top = 29
            Width = 73
            Height = 21
            TabOrder = 0
            Text = '20'
          end
          object DSearchTarget: TButton
            Left = 13
            Top = 56
            Width = 121
            Height = 25
            Caption = 'Search target'
            TabOrder = 1
            OnClick = DSearchTargetClick
          end
          object DSearchInsert_before: TButton
            Left = 13
            Top = 87
            Width = 121
            Height = 25
            Caption = 'Search_Insert before'
            TabOrder = 2
            OnClick = DSearchInsert_beforeClick
          end
          object DSearchInsertAfter: TButton
            Left = 12
            Top = 118
            Width = 121
            Height = 25
            Caption = 'Search_Insert after'
            TabOrder = 3
            OnClick = DSearchInsertAfterClick
          end
          object DSearchDelete: TButton
            Left = 12
            Top = 149
            Width = 121
            Height = 25
            Caption = 'Delete target'
            TabOrder = 4
            OnClick = DSearchDeleteClick
          end
        end
        object GroupBox12: TGroupBox
          Left = 28
          Top = 343
          Width = 146
          Height = 114
          Caption = 'Random'
          TabOrder = 2
          object Label17: TLabel
            Left = 13
            Top = 24
            Width = 17
            Height = 13
            Caption = 'n ='
          end
          object Label18: TLabel
            Left = 13
            Top = 50
            Width = 39
            Height = 13
            Caption = 'range ='
          end
          object Edit13: TEdit
            Left = 36
            Top = 21
            Width = 98
            Height = 21
            TabOrder = 0
            Text = '3'
          end
          object Edit14: TEdit
            Left = 58
            Top = 48
            Width = 76
            Height = 21
            TabOrder = 1
            Text = '100'
          end
          object DRandom: TButton
            Left = 12
            Top = 75
            Width = 121
            Height = 25
            Caption = 'Random insert last'
            TabOrder = 2
            OnClick = DRandomClick
          end
        end
        object DClearAll: TButton
          Left = 41
          Top = 472
          Width = 122
          Height = 25
          Caption = 'Clear All'
          TabOrder = 3
          OnClick = DClearAllClick
        end
      end
    end
  end
  object Memo1: TMemo
    Left = 234
    Top = 0
    Width = 479
    Height = 523
    Align = alClient
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
