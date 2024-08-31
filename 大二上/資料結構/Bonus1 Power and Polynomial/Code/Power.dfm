object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Power by109705001'#38515#20197#29764
  ClientHeight = 425
  ClientWidth = 720
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
    Width = 720
    Height = 425
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'power'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 397
        Align = alLeft
        TabOrder = 0
        object Label1: TLabel
          Left = 32
          Top = 56
          Width = 17
          Height = 13
          Caption = 'x ='
        end
        object Label2: TLabel
          Left = 32
          Top = 88
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label6: TLabel
          Left = 32
          Top = 171
          Width = 55
          Height = 13
          Caption = 'Run Time ='
        end
        object Edit1: TEdit
          Left = 58
          Top = 53
          Width = 95
          Height = 21
          TabOrder = 0
          Text = '2'
        end
        object Edit2: TEdit
          Left = 58
          Top = 85
          Width = 95
          Height = 21
          TabOrder = 1
          Text = '30'
        end
        object Button1: TButton
          Left = 32
          Top = 120
          Width = 121
          Height = 33
          Caption = 'x^n'
          TabOrder = 2
          OnClick = Button1Click
        end
        object Edit3: TEdit
          Left = 90
          Top = 168
          Width = 63
          Height = 21
          TabOrder = 3
          Text = '10000000'
        end
        object GroupBox1: TGroupBox
          Left = 32
          Top = 208
          Width = 121
          Height = 177
          Caption = 'Algorithm'
          TabOrder = 4
          object CheckBox1: TCheckBox
            Left = 21
            Top = 32
            Width = 97
            Height = 17
            Caption = 'pow(k,n)'
            Checked = True
            State = cbChecked
            TabOrder = 0
          end
          object CheckBox2: TCheckBox
            Left = 21
            Top = 71
            Width = 97
            Height = 17
            Caption = 'for-loop'
            TabOrder = 1
          end
          object CheckBox3: TCheckBox
            Left = 21
            Top = 102
            Width = 97
            Height = 17
            Caption = 'squaring'
            TabOrder = 2
          end
          object CheckBox4: TCheckBox
            Left = 21
            Top = 133
            Width = 97
            Height = 17
            Caption = 'squaring _>>'
            TabOrder = 3
          end
        end
      end
      object Memo1: TMemo
        Left = 185
        Top = 0
        Width = 527
        Height = 397
        Align = alClient
        Lines.Strings = (
          'Memo1')
        TabOrder = 1
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'polynomial'
      ImageIndex = 1
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 397
        Align = alLeft
        TabOrder = 0
        object Label3: TLabel
          Left = 24
          Top = 40
          Width = 129
          Height = 13
          Caption = 'a[k] is randomly generated'
        end
        object Label4: TLabel
          Left = 24
          Top = 72
          Width = 19
          Height = 13
          Caption = 'k = '
        end
        object Label5: TLabel
          Left = 24
          Top = 109
          Width = 20
          Height = 13
          Caption = 'n = '
        end
        object Label7: TLabel
          Left = 23
          Top = 199
          Width = 58
          Height = 13
          Caption = 'Run Time = '
        end
        object Edit4: TEdit
          Left = 49
          Top = 69
          Width = 103
          Height = 21
          TabOrder = 0
          Text = '15'
        end
        object Button2: TButton
          Left = 23
          Top = 144
          Width = 129
          Height = 33
          Caption = 'f(0),f(1),f(2),...'
          TabOrder = 1
          OnClick = Button2Click
        end
        object Edit5: TEdit
          Left = 49
          Top = 106
          Width = 103
          Height = 21
          TabOrder = 2
          Text = '2'
        end
        object GroupBox2: TGroupBox
          Left = 24
          Top = 256
          Width = 129
          Height = 121
          Caption = 'Algorithm'
          TabOrder = 3
          object CheckBox5: TCheckBox
            Left = 16
            Top = 24
            Width = 97
            Height = 17
            Caption = 'Pow(x,n)'
            Checked = True
            State = cbChecked
            TabOrder = 0
          end
          object CheckBox6: TCheckBox
            Left = 16
            Top = 55
            Width = 97
            Height = 17
            Caption = 'for-loop'
            Checked = True
            State = cbChecked
            TabOrder = 1
          end
          object CheckBox7: TCheckBox
            Left = 16
            Top = 88
            Width = 97
            Height = 17
            Caption = 'Horner'#39's rule'
            Checked = True
            State = cbChecked
            TabOrder = 2
          end
        end
        object CheckBox8: TCheckBox
          Left = 23
          Top = 225
          Width = 97
          Height = 17
          Caption = 'Compare Algorithm'
          Checked = True
          State = cbChecked
          TabOrder = 4
          OnClick = CheckBox8Click
        end
        object Edit6: TEdit
          Left = 80
          Top = 195
          Width = 73
          Height = 21
          TabOrder = 5
          Text = '100000'
        end
      end
      object Memo2: TMemo
        Left = 185
        Top = 0
        Width = 527
        Height = 397
        Align = alClient
        Lines.Strings = (
          'Memo2')
        TabOrder = 1
      end
    end
  end
end
