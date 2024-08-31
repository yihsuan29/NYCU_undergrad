object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'MST by 109705001 '#38515#20197#29764
  ClientHeight = 491
  ClientWidth = 717
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
    Height = 491
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 24
      Width = 171
      Height = 185
      Caption = 'G(V,E)'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 22
        Height = 13
        Caption = '|V|='
      end
      object Label2: TLabel
        Left = 16
        Top = 51
        Width = 66
        Height = 13
        Caption = 'range(w(e))='
      end
      object Label3: TLabel
        Left = 16
        Top = 78
        Width = 39
        Height = 13
        Caption = 'if w(e)>'
      end
      object Label4: TLabel
        Left = 16
        Top = 105
        Width = 46
        Height = 13
        Caption = 'w(e)=M='
      end
      object Edit1: TEdit
        Left = 88
        Top = 21
        Width = 65
        Height = 21
        TabOrder = 0
        Text = '1000'
      end
      object Edit2: TEdit
        Left = 88
        Top = 48
        Width = 65
        Height = 21
        TabOrder = 1
        Text = '10000'
      end
      object Edit3: TEdit
        Left = 88
        Top = 75
        Width = 65
        Height = 21
        TabOrder = 2
        Text = '10000'
      end
      object Edit4: TEdit
        Left = 88
        Top = 102
        Width = 65
        Height = 21
        TabOrder = 3
        Text = '99999'
      end
      object Button1: TButton
        Left = 16
        Top = 129
        Width = 137
        Height = 25
        Caption = 'Generate'
        TabOrder = 4
        OnClick = Button1Click
      end
      object CheckBox1: TCheckBox
        Left = 16
        Top = 160
        Width = 97
        Height = 17
        Caption = 'Echo Print'
        TabOrder = 5
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 215
      Width = 171
      Height = 242
      Caption = 'MST Solver'
      TabOrder = 1
      object CheckBox2: TCheckBox
        Left = 16
        Top = 24
        Width = 137
        Height = 17
        Caption = 'Echo Print Edges in MST'
        TabOrder = 0
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 47
        Width = 155
        Height = 154
        Caption = 'Kruskal'#39's Algorithm'
        TabOrder = 1
        object Label5: TLabel
          Left = 21
          Top = 24
          Width = 76
          Height = 13
          Caption = 'Cycle Detect by'
        end
        object RadioButton1: TRadioButton
          Left = 39
          Top = 43
          Width = 113
          Height = 17
          Caption = 'Loop'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton2: TRadioButton
          Left = 39
          Top = 66
          Width = 113
          Height = 17
          Caption = 'Union&& Find'
          TabOrder = 1
        end
        object Button2: TButton
          Left = 8
          Top = 89
          Width = 137
          Height = 25
          Caption = 'Kruskal_sort'
          TabOrder = 2
          OnClick = Button2Click
        end
        object Button3: TButton
          Left = 8
          Top = 120
          Width = 137
          Height = 25
          Caption = 'Kruskal_heap'
          TabOrder = 3
          OnClick = Button3Click
        end
      end
      object Button4: TButton
        Left = 16
        Top = 207
        Width = 137
        Height = 25
        Caption = 'Prim'#39's Algorithm'
        TabOrder = 2
        OnClick = Button4Click
      end
    end
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 532
    Height = 491
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'MST found'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Adjacent Matrix'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Edge Matrix'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Sorted Edge'
      ImageIndex = 3
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Edge Heap'
      ImageIndex = 4
      object StringGrid4: TStringGrid
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Prim'
      ImageIndex = 5
      object StringGrid5: TStringGrid
        Left = 0
        Top = 0
        Width = 524
        Height = 463
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid5DrawCell
      end
    end
  end
end
