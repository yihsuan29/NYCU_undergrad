object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'BST by109705001'#38515#20197#29764
  ClientHeight = 611
  ClientWidth = 719
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 611
    Align = alLeft
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 181
      Top = 1
      Height = 609
      Align = alRight
      ExplicitLeft = 56
      ExplicitTop = 256
      ExplicitHeight = 100
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 16
      Width = 167
      Height = 113
      Caption = 'Insert (inorder traversal)'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 27
        Width = 52
        Height = 13
        Caption = 'element = '
      end
      object Label3: TLabel
        Left = 14
        Top = 51
        Width = 150
        Height = 13
        Caption = '('#37325#35079#36664#20837#26178#19981#26371#21152#20837'BSTree)'
      end
      object Edit1: TEdit
        Left = 74
        Top = 24
        Width = 79
        Height = 21
        TabOrder = 0
        Text = '30'
      end
      object Insert: TButton
        Left = 16
        Top = 72
        Width = 137
        Height = 25
        Caption = 'Insert'
        TabOrder = 1
        OnClick = InsertClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 135
      Width = 167
      Height = 122
      Caption = 'Delete (inorder traversal)'
      TabOrder = 1
      object Label2: TLabel
        Left = 16
        Top = 32
        Width = 44
        Height = 13
        Caption = 'target = '
      end
      object Edit2: TEdit
        Left = 66
        Top = 30
        Width = 87
        Height = 21
        TabOrder = 0
        Text = '30'
      end
      object Delete: TButton
        Left = 16
        Top = 57
        Width = 137
        Height = 25
        Caption = 'Delete'
        TabOrder = 1
        OnClick = DeleteClick
      end
      object Button4: TButton
        Left = 16
        Top = 88
        Width = 137
        Height = 25
        Caption = 'Clear All'
        TabOrder = 2
        OnClick = Button4Click
      end
    end
    object Traversal: TGroupBox
      Left = 8
      Top = 384
      Width = 167
      Height = 187
      Caption = 'Traversal '
      TabOrder = 2
      object RadioButton1: TRadioButton
        Left = 32
        Top = 17
        Width = 113
        Height = 17
        Caption = 'Inorder'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton2: TRadioButton
        Left = 32
        Top = 40
        Width = 113
        Height = 17
        Caption = 'Preorder'
        TabOrder = 1
      end
      object RadioButton3: TRadioButton
        Left = 32
        Top = 63
        Width = 113
        Height = 17
        Caption = 'Postorder'
        TabOrder = 2
      end
      object travel: TButton
        Left = 16
        Top = 86
        Width = 137
        Height = 25
        Caption = 'Traversal (recursive)'
        TabOrder = 3
        OnClick = travelClick
      end
      object Button1: TButton
        Left = 16
        Top = 117
        Width = 137
        Height = 25
        Caption = 'Traversal (non-recursive)'
        TabOrder = 4
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 16
        Top = 148
        Width = 137
        Height = 25
        Caption = 'Level-Order Traversal'
        TabOrder = 5
        OnClick = Button2Click
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 263
      Width = 167
      Height = 115
      Caption = 'Random Insert (inorder traversal)'
      TabOrder = 3
      object Label4: TLabel
        Left = 16
        Top = 32
        Width = 17
        Height = 13
        Caption = 'n ='
      end
      object Label5: TLabel
        Left = 70
        Top = 32
        Width = 42
        Height = 13
        Caption = 'range = '
      end
      object Label6: TLabel
        Left = 14
        Top = 58
        Width = 150
        Height = 13
        Caption = '('#37325#35079#30340#25976#23383#19981#26371#21152#20837'BSTree)'
      end
      object Edit3: TEdit
        Left = 112
        Top = 30
        Width = 41
        Height = 21
        TabOrder = 0
        Text = '100'
      end
      object Edit4: TEdit
        Left = 39
        Top = 30
        Width = 25
        Height = 21
        TabOrder = 1
        Text = '5'
      end
      object Button3: TButton
        Left = 16
        Top = 77
        Width = 137
        Height = 25
        Caption = 'Random Insert'
        TabOrder = 2
        OnClick = Button3Click
      end
    end
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 534
    Height = 611
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'BST'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 526
        Height = 583
        Align = alClient
        Lines.Strings = (
          'Memo1')
        TabOrder = 0
        ExplicitLeft = 128
        ExplicitTop = 120
        ExplicitWidth = 185
        ExplicitHeight = 89
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'BST drawing'
      ImageIndex = 1
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 526
        Height = 583
        Align = alClient
        TabOrder = 0
        ExplicitLeft = 1
        object Image1: TImage
          Left = 0
          Top = 0
          Width = 522
          Height = 579
          Align = alClient
          ExplicitLeft = 200
          ExplicitTop = 344
          ExplicitWidth = 105
          ExplicitHeight = 105
        end
      end
    end
  end
end
