object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Knight Tour by109705001'#38515#20197#29764
  ClientHeight = 467
  ClientWidth = 722
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
    Height = 467
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 16
      Width = 171
      Height = 185
      Caption = 'Find Knight Tour'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 32
        Width = 20
        Height = 13
        Caption = 'n = '
      end
      object Label2: TLabel
        Left = 16
        Top = 56
        Width = 78
        Height = 13
        Caption = 'Starting Position'
      end
      object Edit1: TEdit
        Left = 42
        Top = 29
        Width = 63
        Height = 21
        TabOrder = 0
        Text = '6'
      end
      object RadioButton1: TRadioButton
        Left = 16
        Top = 75
        Width = 113
        Height = 17
        Caption = 'Random Generate'
        TabOrder = 1
      end
      object RadioButton2: TRadioButton
        Left = 16
        Top = 98
        Width = 139
        Height = 17
        Caption = '(x,y)=(             ,             )'
        Checked = True
        TabOrder = 2
        TabStop = True
      end
      object Edit2: TEdit
        Left = 71
        Top = 98
        Width = 34
        Height = 21
        TabOrder = 3
        Text = '1'
      end
      object Edit3: TEdit
        Left = 111
        Top = 98
        Width = 34
        Height = 21
        TabOrder = 4
        Text = '1'
      end
      object Button1: TButton
        Left = 16
        Top = 125
        Width = 139
        Height = 25
        Caption = 'Knight Tour'
        TabOrder = 5
        OnClick = Button1Click
      end
      object CheckBox1: TCheckBox
        Left = 16
        Top = 156
        Width = 97
        Height = 17
        Caption = 'trace'
        TabOrder = 6
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 207
      Width = 171
      Height = 162
      Caption = 'Animation'
      TabOrder = 1
      object Label3: TLabel
        Left = 16
        Top = 26
        Width = 55
        Height = 13
        Caption = 'Grid Size = '
      end
      object Label4: TLabel
        Left = 16
        Top = 85
        Width = 44
        Height = 13
        Caption = 'Speed = '
      end
      object Edit4: TEdit
        Left = 77
        Top = 24
        Width = 78
        Height = 21
        TabOrder = 0
        Text = '50'
      end
      object Button2: TButton
        Left = 16
        Top = 51
        Width = 139
        Height = 25
        Caption = 'Knight Tour Animate'
        TabOrder = 1
        OnClick = Button2Click
      end
      object TrackBar1: TTrackBar
        Left = 56
        Top = 82
        Width = 99
        Height = 23
        TabOrder = 2
      end
      object CheckBox2: TCheckBox
        Left = 16
        Top = 111
        Width = 97
        Height = 17
        Caption = 'next next move'
        TabOrder = 3
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 134
        Width = 152
        Height = 17
        Caption = 'show next next'
        TabOrder = 4
      end
    end
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 537
    Height = 467
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Tour in memo'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 529
        Height = 439
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Tour in StringGrid'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 529
        Height = 439
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Tour in Animation'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 529
        Height = 439
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid2DrawCell
      end
    end
  end
end
