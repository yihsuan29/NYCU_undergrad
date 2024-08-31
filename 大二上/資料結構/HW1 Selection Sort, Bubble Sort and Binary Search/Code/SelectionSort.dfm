object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Selection vs. Bubble Sort by '#38515#20197#29764'(109705001) 2021/10/01'
  ClientHeight = 525
  ClientWidth = 754
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 754
    Height = 525
    ActivePage = Chart
    Align = alClient
    TabOrder = 0
    OnChange = PageControl1Change
    object Main: TTabSheet
      Caption = 'Main'
      object Label1: TLabel
        Left = 33
        Top = 19
        Width = 14
        Height = 13
        Caption = 'n='
      end
      object Label2: TLabel
        Left = 203
        Top = 19
        Width = 39
        Height = 13
        Caption = 'range ='
      end
      object Label3: TLabel
        Left = 584
        Top = 64
        Width = 41
        Height = 13
        Caption = 'target ='
      end
      object Label4: TLabel
        Left = 19
        Top = 62
        Width = 66
        Height = 13
        Caption = 'repeatition = '
      end
      object Label5: TLabel
        Left = 207
        Top = 62
        Width = 35
        Height = 13
        Caption = 'step = '
      end
      object Button1: TButton
        Left = 16
        Top = 93
        Width = 169
        Height = 41
        Caption = 'Generate Random Numbers'
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 207
        Top = 93
        Width = 169
        Height = 41
        Caption = 'Selection Sort'
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 392
        Top = 93
        Width = 161
        Height = 41
        Caption = 'Bubble Sort'
        TabOrder = 2
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 575
        Top = 93
        Width = 153
        Height = 41
        Caption = 'Binary Search'
        TabOrder = 3
        OnClick = Button4Click
      end
      object Memo2: TMemo
        Left = 207
        Top = 155
        Width = 169
        Height = 326
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 4
      end
      object Memo4: TMemo
        Left = 575
        Top = 156
        Width = 153
        Height = 325
        Lines.Strings = (
          'Memo4')
        ScrollBars = ssVertical
        TabOrder = 5
      end
      object Memo3: TMemo
        Left = 392
        Top = 155
        Width = 161
        Height = 326
        Lines.Strings = (
          'Memo3')
        ScrollBars = ssVertical
        TabOrder = 6
      end
      object Memo1: TMemo
        Left = 19
        Top = 155
        Width = 169
        Height = 326
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 7
      end
      object CheckBox1: TCheckBox
        Left = 392
        Top = 18
        Width = 97
        Height = 17
        Caption = 'Echo Print'
        TabOrder = 8
      end
      object CheckBox2: TCheckBox
        Left = 392
        Top = 61
        Width = 97
        Height = 17
        Caption = 'Self Check'
        Checked = True
        State = cbChecked
        TabOrder = 9
      end
      object Edit1: TEdit
        Left = 64
        Top = 16
        Width = 121
        Height = 21
        TabOrder = 10
        Text = '10000'
      end
      object Edit2: TEdit
        Left = 248
        Top = 16
        Width = 121
        Height = 21
        TabOrder = 11
        Text = '100000'
      end
      object Edit3: TEdit
        Left = 640
        Top = 61
        Width = 73
        Height = 21
        TabOrder = 12
        Text = '20'
      end
      object Edit4: TEdit
        Left = 91
        Top = 59
        Width = 94
        Height = 21
        TabOrder = 13
        Text = '5'
      end
      object Edit5: TEdit
        Left = 248
        Top = 59
        Width = 121
        Height = 21
        TabOrder = 14
        Text = '10000'
      end
    end
    object Chart: TTabSheet
      Caption = 'Chart'
      ImageIndex = 1
      object Splitter1: TSplitter
        Left = 185
        Top = 0
        Height = 497
        ExplicitLeft = 184
        ExplicitTop = 200
        ExplicitHeight = 100
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 497
        Align = alLeft
        TabOrder = 0
        object RadioGroup1: TRadioGroup
          Left = 1
          Top = 1
          Width = 172
          Height = 495
          Align = alLeft
          Caption = 'Type of Chart'
          ItemIndex = 0
          Items.Strings = (
            'Bar'
            'Line'
            'Area'
            'Point'
            'FastLine')
          TabOrder = 0
          OnClick = RadioGroup1Click
        end
      end
      object Chart1: TChart
        Left = 188
        Top = 0
        Width = 558
        Height = 497
        Title.Text.Strings = (
          'Bar Chart of Sorting Time')
        Align = alClient
        TabOrder = 1
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series1: TBarSeries
          SeriesColor = clBlue
          Title = 'Selection Sort'
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
        object Series2: TBarSeries
          SeriesColor = clGreen
          Title = 'Bubble Sort'
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 17
        Width = 49
        Height = 32
        Caption = 'Marks'
        Checked = True
        State = cbChecked
        TabOrder = 2
        OnClick = CheckBox3Click
      end
    end
  end
end
