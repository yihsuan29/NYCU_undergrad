object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Addition of Polynomial by109705001'#38515#20197#29764
  ClientHeight = 442
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
    Height = 442
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 171
      Height = 153
      Caption = 'New Term'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 32
        Width = 64
        Height = 13
        Caption = 'coefficient = '
      end
      object Label2: TLabel
        Left = 16
        Top = 59
        Width = 60
        Height = 13
        Caption = 'exponent = '
      end
      object Edit1: TEdit
        Left = 86
        Top = 29
        Width = 71
        Height = 21
        TabOrder = 0
        Text = '3'
      end
      object Edit2: TEdit
        Left = 86
        Top = 56
        Width = 71
        Height = 21
        TabOrder = 1
        Text = '2'
      end
      object Button1: TButton
        Left = 16
        Top = 83
        Width = 141
        Height = 25
        Caption = 'New Term In Polynomial A'
        TabOrder = 2
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 16
        Top = 114
        Width = 141
        Height = 25
        Caption = 'New Term In Polynomial B'
        TabOrder = 3
        OnClick = Button2Click
      end
    end
    object GroupBox2: TGroupBox
      Left = 12
      Top = 167
      Width = 167
      Height = 146
      Caption = 'Random Setting'
      TabOrder = 1
      object Label3: TLabel
        Left = 15
        Top = 26
        Width = 61
        Height = 13
        Caption = 'max expo = '
      end
      object Label4: TLabel
        Left = 15
        Top = 54
        Width = 83
        Height = 13
        Caption = 'max range(+/-)='
      end
      object Label5: TLabel
        Left = 15
        Top = 81
        Width = 88
        Height = 13
        Caption = 'zero term range= '
      end
      object Edit3: TEdit
        Left = 104
        Top = 24
        Width = 49
        Height = 21
        TabOrder = 0
        Text = '6'
      end
      object Edit4: TEdit
        Left = 104
        Top = 51
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '5'
      end
      object Edit5: TEdit
        Left = 104
        Top = 78
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '2'
      end
      object Button3: TButton
        Left = 15
        Top = 105
        Width = 138
        Height = 25
        Caption = 'Random Poly A,B'
        TabOrder = 3
        OnClick = Button3Click
      end
    end
    object Button5: TButton
      Left = 27
      Top = 319
      Width = 138
      Height = 25
      Caption = 'Clear'
      TabOrder = 2
      OnClick = Button5Click
    end
    object GroupBox3: TGroupBox
      Left = 12
      Top = 350
      Width = 167
      Height = 88
      Caption = 'Addition'
      TabOrder = 3
      object Button4: TButton
        Left = 15
        Top = 24
        Width = 138
        Height = 25
        Caption = 'C=A+B'
        TabOrder = 0
        OnClick = Button4Click
      end
      object Button6: TButton
        Left = 15
        Top = 55
        Width = 138
        Height = 25
        Caption = 'Clear'
        TabOrder = 1
        OnClick = Button6Click
      end
    end
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 532
    Height = 442
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Polynomial'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 524
        Height = 414
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Addition'
      ImageIndex = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 524
        Height = 414
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
end
