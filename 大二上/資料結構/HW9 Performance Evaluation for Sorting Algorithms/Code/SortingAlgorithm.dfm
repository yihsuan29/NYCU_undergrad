object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Sorting Algorithm  Performance by.109705001'#38515#20197#29764
  ClientHeight = 449
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
  object Splitter1: TSplitter
    Left = 185
    Top = 0
    Height = 449
    ExplicitLeft = 184
    ExplicitTop = 280
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 449
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 171
      Height = 138
      Caption = 'Input'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 32
        Width = 41
        Height = 13
        Caption = 'Times = '
      end
      object Label2: TLabel
        Left = 16
        Top = 59
        Width = 21
        Height = 13
        Caption = 'N = '
      end
      object Label3: TLabel
        Left = 16
        Top = 86
        Width = 45
        Height = 13
        Caption = 'Range = '
      end
      object Edit1: TEdit
        Left = 63
        Top = 29
        Width = 98
        Height = 21
        TabOrder = 0
        Text = '10'
      end
      object Edit2: TEdit
        Left = 63
        Top = 56
        Width = 98
        Height = 21
        TabOrder = 1
        Text = '1000'
      end
      object Edit3: TEdit
        Left = 63
        Top = 83
        Width = 98
        Height = 21
        TabOrder = 2
        Text = '100000'
      end
      object CheckBox10: TCheckBox
        Left = 16
        Top = 110
        Width = 97
        Height = 17
        Caption = 'See Data'
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 152
      Width = 171
      Height = 242
      Caption = 'Algorithm'
      TabOrder = 1
      object CheckBox1: TCheckBox
        Left = 16
        Top = 24
        Width = 97
        Height = 17
        Caption = 'Selection Sort'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 16
        Top = 47
        Width = 97
        Height = 17
        Caption = 'Bubble Sort'
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 70
        Width = 97
        Height = 17
        Caption = 'Insertion Sort'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object CheckBox4: TCheckBox
        Left = 16
        Top = 93
        Width = 145
        Height = 17
        Caption = 'Quick Sort (Recursive)'
        Checked = True
        State = cbChecked
        TabOrder = 3
      end
      object CheckBox5: TCheckBox
        Left = 16
        Top = 116
        Width = 152
        Height = 17
        Caption = 'Quick Sort (Non-Recursive)'
        Checked = True
        State = cbChecked
        TabOrder = 4
      end
      object CheckBox6: TCheckBox
        Left = 16
        Top = 139
        Width = 145
        Height = 17
        Caption = 'Merge Sort (Recursive)'
        Checked = True
        State = cbChecked
        TabOrder = 5
      end
      object CheckBox7: TCheckBox
        Left = 16
        Top = 162
        Width = 152
        Height = 17
        Caption = 'Merge Sort (Non-Recursive)'
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
      object CheckBox8: TCheckBox
        Left = 16
        Top = 185
        Width = 97
        Height = 17
        Caption = 'Heap Sort'
        Checked = True
        State = cbChecked
        TabOrder = 7
      end
      object CheckBox9: TCheckBox
        Left = 16
        Top = 208
        Width = 97
        Height = 17
        Caption = 'Radix Sort'
        Checked = True
        State = cbChecked
        TabOrder = 8
      end
    end
    object Button1: TButton
      Left = 24
      Top = 400
      Width = 145
      Height = 25
      Caption = 'Run'
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 136
      Top = 408
      Width = 1
      Height = 33
      Caption = 'Button2'
      TabOrder = 3
    end
  end
  object PageControl1: TPageControl
    Left = 188
    Top = 0
    Width = 538
    Height = 449
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Data'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 530
        Height = 421
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Diagram'
      ImageIndex = 1
      object Chart1: TChart
        Left = 0
        Top = 0
        Width = 530
        Height = 421
        Title.Text.Strings = (
          'TChart')
        Align = alClient
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series1: TLineSeries
          SeriesColor = 9671679
          Title = 'Selection'
          Brush.BackColor = clDefault
          LinePen.Color = 12040191
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series2: TLineSeries
          SeriesColor = 9090303
          Title = 'Bubble'
          Brush.BackColor = clDefault
          LinePen.Color = 12177661
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series3: TLineSeries
          SeriesColor = 9103615
          Title = 'Insertion'
          Brush.BackColor = clDefault
          LinePen.Color = 12185597
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series4: TLineSeries
          SeriesColor = 9174713
          Title = 'Quick(rec)'
          Brush.BackColor = clDefault
          LinePen.Color = 12254430
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series5: TLineSeries
          SeriesColor = 12975500
          Title = 'Quick(non)'
          Brush.BackColor = clDefault
          LinePen.Color = 14154683
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series6: TLineSeries
          SeriesColor = 16706974
          Title = 'Merge(rec)'
          Brush.BackColor = clDefault
          LinePen.Color = 16579258
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series7: TLineSeries
          SeriesColor = 16762250
          Title = 'Merge(non)'
          Brush.BackColor = clDefault
          LinePen.Color = 16504251
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series8: TLineSeries
          SeriesColor = 16747178
          Title = 'Heap'
          Brush.BackColor = clDefault
          LinePen.Color = 16563386
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series9: TLineSeries
          SeriesColor = 16747231
          Title = 'Radix'
          Brush.BackColor = clDefault
          LinePen.Color = 16562907
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
  end
end
