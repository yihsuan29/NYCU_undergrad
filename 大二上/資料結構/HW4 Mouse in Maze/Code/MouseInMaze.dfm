object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'MouseInMaze by109705001'#38515#20197#29764' 20211117'
  ClientHeight = 454
  ClientWidth = 714
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
    Left = 185
    Top = 0
    Height = 454
    ExplicitLeft = 184
    ExplicitTop = 256
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 454
    Align = alLeft
    TabOrder = 0
    object Label4: TLabel
      Left = 11
      Top = 418
      Width = 38
      Height = 13
      Caption = 'Speed='
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 24
      Width = 153
      Height = 129
      Caption = 'Size'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 35
        Width = 45
        Height = 13
        Caption = 'Height = '
      end
      object Label2: TLabel
        Left = 16
        Top = 64
        Width = 45
        Height = 13
        Caption = 'Width  = '
      end
      object Label3: TLabel
        Left = 16
        Top = 89
        Width = 42
        Height = 13
        Caption = 'Grid    = '
      end
      object Edit1: TEdit
        Left = 64
        Top = 32
        Width = 73
        Height = 21
        TabOrder = 0
        Text = '8'
      end
      object Edit2: TEdit
        Left = 67
        Top = 59
        Width = 73
        Height = 21
        TabOrder = 1
        Text = '8'
      end
      object Edit3: TEdit
        Left = 64
        Top = 86
        Width = 73
        Height = 21
        TabOrder = 2
        Text = '50'
      end
    end
    object Button1: TButton
      Left = 16
      Top = 176
      Width = 153
      Height = 33
      Caption = 'Generate Maze'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 16
      Top = 223
      Width = 153
      Height = 34
      Caption = 'Save Maze'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 16
      Top = 271
      Width = 153
      Height = 33
      Caption = 'Load Maze'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 16
      Top = 320
      Width = 153
      Height = 33
      Caption = 'Find a Tour'
      TabOrder = 4
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 16
      Top = 368
      Width = 153
      Height = 33
      Caption = 'Find a 4-way Tour'
      TabOrder = 5
      OnClick = Button5Click
    end
    object TrackBar1: TTrackBar
      Left = 55
      Top = 412
      Width = 114
      Height = 26
      TabOrder = 6
    end
  end
  object PageControl1: TPageControl
    Left = 188
    Top = 0
    Width = 526
    Height = 454
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Text'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 518
        Height = 426
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Grid'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 518
        Height = 426
        Align = alClient
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnDrawCell = StringGrid1DrawCell
      end
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = 'C:\Users\yihsu\OneDrive\'#26700#38754'\'#36039#32080#20316#26989'\HW04_109705001_'#38515#20197#29764'\'#36855#23470'.txt'
    Left = 128
    Top = 272
  end
  object SaveDialog1: TSaveDialog
    FileName = 'C:\Users\yihsu\OneDrive\'#26700#38754'\'#36039#32080#20316#26989'\HW04_109705001_'#38515#20197#29764'\'#36855#23470'.txt'
    Left = 152
    Top = 272
  end
end
