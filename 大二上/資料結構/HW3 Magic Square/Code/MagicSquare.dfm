object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'MagicSquare('#22855#25976#20598#25976#37117#21487#20197') by'#38515#20197#29764'(109705001) 2021/1014'
  ClientHeight = 426
  ClientWidth = 725
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
    Height = 426
    ExplicitLeft = 184
    ExplicitTop = 248
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 426
    Align = alLeft
    TabOrder = 0
    ExplicitLeft = 1
    object Label1: TLabel
      Left = 24
      Top = 32
      Width = 69
      Height = 13
      Caption = 'Square size = '
    end
    object Label2: TLabel
      Left = 24
      Top = 60
      Width = 101
      Height = 13
      Caption = '(can be odd or even)'
    end
    object Button1: TButton
      Left = 24
      Top = 115
      Width = 145
      Height = 41
      Caption = 'Magic Square'
      TabOrder = 0
      OnClick = Button1Click
    end
    object RadioGroup1: TRadioGroup
      Left = 24
      Top = 162
      Width = 145
      Height = 129
      Caption = 'Start Point'
      Items.Strings = (
        'Top'
        'Right'
        'Bottom'
        'Left')
      TabOrder = 1
      OnClick = RadioGroup1Click
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 85
      Width = 97
      Height = 17
      Caption = 'CheckSum'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object RadioGroup2: TRadioGroup
      Left = 24
      Top = 297
      Width = 145
      Height = 129
      Caption = 'Direction '
      Items.Strings = (
        'Upper left'
        'Upper right'
        'Bottom left'
        'Bottom right')
      TabOrder = 3
    end
  end
  object Edit1: TEdit
    Left = 99
    Top = 24
    Width = 70
    Height = 21
    TabOrder = 1
    OnChange = Edit1Change
  end
  object PageControl1: TPageControl
    Left = 188
    Top = 0
    Width = 537
    Height = 426
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = 'Normal ver.'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 529
        Height = 398
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'StringGrid ver.'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 529
        Height = 398
        Align = alClient
        TabOrder = 0
      end
    end
  end
end
