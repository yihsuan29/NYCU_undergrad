object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'InfixPostfixPrefix  by109705001'#38515#20197#29764'21211117'
  ClientHeight = 427
  ClientWidth = 721
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
    Left = 0
    Top = 193
    Width = 721
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitWidth = 234
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 721
    Height = 193
    ActivePage = TabSheet3
    Align = alTop
    TabOrder = 0
    ExplicitTop = -3
    object TabSheet1: TTabSheet
      Caption = 'Infix'
      object Label1: TLabel
        Left = 32
        Top = 10
        Width = 526
        Height = 13
        Caption = 
          'Operators:{+,-,*,/,^,&,|}  (^ means power not XOR)    Each Opera' +
          'nd is represented by one English character'
      end
      object Edit3: TEdit
        Left = 152
        Top = 112
        Width = 513
        Height = 21
        TabOrder = 0
      end
      object Button1: TButton
        Left = 32
        Top = 70
        Width = 105
        Height = 25
        Caption = 'Infix=>Postfix'
        TabOrder = 1
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 32
        Top = 110
        Width = 105
        Height = 25
        Caption = 'Infix=>Prefix'
        TabOrder = 2
        OnClick = Button2Click
      end
      object Edit2: TEdit
        Left = 152
        Top = 72
        Width = 513
        Height = 21
        TabOrder = 3
      end
      object Edit1: TEdit
        Left = 152
        Top = 32
        Width = 513
        Height = 21
        TabOrder = 4
        Text = '(A+B)*C^(D+E*F-G*(H+J))'
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Postfix'
      ImageIndex = 1
      object Label3: TLabel
        Left = 32
        Top = 10
        Width = 526
        Height = 13
        Caption = 
          'Operators:{+,-,*,/,^,&,|}  (^ means power not XOR)    Each Opera' +
          'nd is represented by one English character'
      end
      object Edit4: TEdit
        Left = 152
        Top = 32
        Width = 513
        Height = 21
        TabOrder = 0
        Text = 'ABC*-DEFG/+^+'
      end
      object Edit5: TEdit
        Left = 152
        Top = 72
        Width = 513
        Height = 21
        TabOrder = 1
      end
      object Edit6: TEdit
        Left = 152
        Top = 112
        Width = 513
        Height = 21
        TabOrder = 2
      end
      object Button3: TButton
        Left = 32
        Top = 70
        Width = 105
        Height = 25
        Caption = 'Postfix=>Infix'
        TabOrder = 3
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 32
        Top = 110
        Width = 105
        Height = 25
        Caption = 'Postfix=>Prefix'
        TabOrder = 4
        OnClick = Button4Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Prefix'
      ImageIndex = 2
      object Label2: TLabel
        Left = 32
        Top = 10
        Width = 526
        Height = 13
        Caption = 
          'Operators:{+,-,*,/,^,&,|}  (^ means power not XOR)    Each Opera' +
          'nd is represented by one English character'
      end
      object Edit7: TEdit
        Left = 152
        Top = 32
        Width = 513
        Height = 21
        TabOrder = 0
        Text = '^*A-BCD'
      end
      object Edit8: TEdit
        Left = 152
        Top = 72
        Width = 513
        Height = 21
        TabOrder = 1
      end
      object Edit9: TEdit
        Left = 152
        Top = 112
        Width = 513
        Height = 21
        TabOrder = 2
      end
      object Button5: TButton
        Left = 32
        Top = 70
        Width = 105
        Height = 25
        Caption = 'Prefix=>Infix'
        TabOrder = 3
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 32
        Top = 110
        Width = 105
        Height = 25
        Caption = 'Prefix=>Postfix'
        TabOrder = 4
        OnClick = Button6Click
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 196
    Width = 721
    Height = 231
    Align = alClient
    TabOrder = 1
    object Splitter2: TSplitter
      Left = 1
      Top = 35
      Width = 719
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitTop = 1
      ExplicitWidth = 37
    end
    object Memo1: TMemo
      Left = 1
      Top = 38
      Width = 719
      Height = 192
      Align = alBottom
      Lines.Strings = (
        'Memo1')
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 12
      Width = 97
      Height = 17
      Caption = 'Print Stack'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object CheckBox2: TCheckBox
      Left = 120
      Top = 12
      Width = 97
      Height = 17
      Caption = 'Tracing'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
  end
end
