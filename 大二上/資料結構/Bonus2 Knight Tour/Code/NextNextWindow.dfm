object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Show Next Next'
  ClientHeight = 112
  ClientWidth = 418
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
    Width = 418
    Height = 112
    Align = alClient
    TabOrder = 0
    ExplicitHeight = 148
    object Label1: TLabel
      Left = 48
      Top = 20
      Width = 3
      Height = 13
    end
    object Label2: TLabel
      Left = 48
      Top = 78
      Width = 37
      Height = 13
    end
    object Button1: TButton
      Left = 239
      Top = 73
      Width = 75
      Height = 25
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 320
      Top = 73
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
end
