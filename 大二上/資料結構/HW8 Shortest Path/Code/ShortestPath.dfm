object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Shortest Path by '#38515#20197#29764
  ClientHeight = 429
  ClientWidth = 726
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
    Height = 429
    Align = alLeft
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 181
      Top = 1
      Height = 427
      Align = alRight
      ExplicitLeft = 184
      ExplicitTop = 280
      ExplicitHeight = 100
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 56
      Width = 167
      Height = 217
      Caption = 'Randomly Generate G=(V,E)'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 20
        Height = 13
        Caption = 'n = '
      end
      object Label2: TLabel
        Left = 16
        Top = 51
        Width = 75
        Height = 13
        Caption = 'range (w(e)) = '
      end
      object Label3: TLabel
        Left = 16
        Top = 78
        Width = 42
        Height = 13
        Caption = 'if w(e) >'
      end
      object Label4: TLabel
        Left = 16
        Top = 105
        Width = 36
        Height = 13
        Caption = 'w(e) = '
      end
      object Label5: TLabel
        Left = 16
        Top = 132
        Width = 65
        Height = 13
        Caption = 'source no. = '
      end
      object Edit1: TEdit
        Left = 97
        Top = 21
        Width = 57
        Height = 21
        TabOrder = 0
        Text = '5'
      end
      object Edit2: TEdit
        Left = 97
        Top = 48
        Width = 57
        Height = 21
        TabOrder = 1
        Text = '50'
      end
      object Edit3: TEdit
        Left = 97
        Top = 75
        Width = 57
        Height = 21
        TabOrder = 2
        Text = '30'
      end
      object Edit4: TEdit
        Left = 97
        Top = 102
        Width = 57
        Height = 21
        TabOrder = 3
        Text = '99999'
      end
      object Edit5: TEdit
        Left = 97
        Top = 129
        Width = 57
        Height = 21
        TabOrder = 4
        Text = '3'
      end
      object Button1: TButton
        Left = 16
        Top = 156
        Width = 138
        Height = 25
        Caption = 'Generate'
        TabOrder = 5
        OnClick = Button1Click
      end
      object CheckBox1: TCheckBox
        Left = 16
        Top = 187
        Width = 97
        Height = 17
        Caption = 'Undirect'
        TabOrder = 6
      end
    end
    object GroupBox2: TGroupBox
      Left = 10
      Top = 279
      Width = 165
      Height = 122
      Caption = 'Shortest Path Solver'
      TabOrder = 1
      object Button2: TButton
        Left = 14
        Top = 24
        Width = 138
        Height = 25
        Caption = 'Single Source All Destination'
        TabOrder = 0
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 14
        Top = 55
        Width = 138
        Height = 25
        Caption = 'All Pair'
        TabOrder = 1
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 14
        Top = 86
        Width = 138
        Height = 25
        Caption = 'Transitive Colusure'
        TabOrder = 2
        OnClick = Button4Click
      end
    end
    object Button5: TButton
      Left = 24
      Top = 24
      Width = 138
      Height = 25
      Caption = 'Read G'
      TabOrder = 2
      OnClick = Button5Click
    end
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 541
    Height = 429
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Text'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Adjecent  Matrix'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'SSAD table'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid2DrawCell
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'All Pair'
      ImageIndex = 3
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'All Pair Table'
      ImageIndex = 4
      object StringGrid4: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Transitive closure'
      ImageIndex = 5
      object StringGrid5: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 401
        Align = alClient
        TabOrder = 0
      end
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = 'C:\Users\yihsu\OneDrive\'#26700#38754'\'#36039#32080#20316#26989'\HW08_109705001_'#38515#20197#29764'\weight.txt'
    Left = 128
    Top = 24
  end
end
