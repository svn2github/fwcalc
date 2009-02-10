object FwCalcMainDlg: TFwCalcMainDlg
  Left = 537
  Top = 236
  Caption = 'Fairwood Calculator'
  ClientHeight = 228
  ClientWidth = 398
  Color = clBtnFace
  Constraints.MinHeight = 244
  Constraints.MinWidth = 406
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Shell Dlg 2'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnKeyUp = FormKeyUp
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar: TStatusBar
    Left = 0
    Top = 209
    Width = 398
    Height = 19
    Panels = <
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
  end
  object ButtonPanel: TPanel
    Left = 0
    Top = 49
    Width = 398
    Height = 160
    Align = alBottom
    TabOrder = 1
    object Num7Button: TSpeedButton
      Left = 219
      Top = 28
      Width = 41
      Height = 25
      Hint = 'Enter Digit 7'
      Caption = '7'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num8Button: TSpeedButton
      Left = 261
      Top = 28
      Width = 41
      Height = 25
      Hint = 'Enter Digit 8'
      Caption = '8'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num9Button: TSpeedButton
      Left = 303
      Top = 28
      Width = 41
      Height = 25
      Hint = 'Enter Digit 9'
      Caption = '9'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num4Button: TSpeedButton
      Left = 219
      Top = 54
      Width = 41
      Height = 25
      Hint = 'Enter Digit 4'
      Caption = '4'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num5Button: TSpeedButton
      Left = 261
      Top = 54
      Width = 41
      Height = 25
      Hint = 'Enter Digit 5'
      Caption = '5'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num6Button: TSpeedButton
      Left = 303
      Top = 54
      Width = 41
      Height = 25
      Hint = 'Enter Digit 6'
      Caption = '6'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num1Button: TSpeedButton
      Left = 219
      Top = 80
      Width = 41
      Height = 25
      Hint = 'Enter Digit 1'
      Caption = '1'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num2Button: TSpeedButton
      Left = 261
      Top = 80
      Width = 41
      Height = 25
      Hint = 'Enter Digit 2'
      Caption = '2'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num3Button: TSpeedButton
      Left = 303
      Top = 80
      Width = 41
      Height = 25
      Hint = 'Enter Digit 3'
      Caption = '3'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object Num0Button: TSpeedButton
      Left = 219
      Top = 106
      Width = 41
      Height = 25
      Hint = 'Enter Digit 0'
      Caption = '0'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object NumDotButton: TSpeedButton
      Left = 261
      Top = 106
      Width = 41
      Height = 25
      Hint = 'Enter Decimal Seperator'
      Caption = '.'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object NumEEXButton: TSpeedButton
      Left = 303
      Top = 106
      Width = 41
      Height = 25
      Hint = 'Enter Exponent'
      Caption = 'EEX'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object EnterButton: TSpeedButton
      Left = 219
      Top = 132
      Width = 83
      Height = 25
      Hint = 'Push value to stack'
      Caption = 'Enter'
      ParentShowHint = False
      ShowHint = True
      OnClick = EnterButtonClick
    end
    object CHSButton: TSpeedButton
      Left = 303
      Top = 132
      Width = 41
      Height = 25
      Hint = 'Change sign of value or exponent'
      Caption = '+/-'
      ParentShowHint = False
      ShowHint = True
      OnClick = CHSButtonClick
    end
    object SpeedButton1: TSpeedButton
      Left = 349
      Top = 28
      Width = 41
      Height = 25
      Hint = 'Division operator'
      Caption = '/'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object SpeedButton2: TSpeedButton
      Left = 349
      Top = 54
      Width = 41
      Height = 25
      Hint = 'Multiplication operator'
      Caption = '*'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object SpeedButton3: TSpeedButton
      Left = 349
      Top = 80
      Width = 41
      Height = 25
      Hint = 'Addition operator'
      Caption = '+'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object SpeedButton4: TSpeedButton
      Left = 349
      Top = 106
      Width = 41
      Height = 25
      Hint = 'Subtraction operator'
      Caption = '-'
      ParentShowHint = False
      ShowHint = True
      OnClick = HandleEnterNum
    end
    object SetHexButton: TSpeedButton
      Left = 3
      Top = 4
      Width = 30
      Height = 19
      Hint = 'Switch to hexadecimal (base 16) mode'
      Caption = 'Hex'
      ParentShowHint = False
      ShowHint = True
      OnClick = SetHexButtonClick
    end
    object SetDecButton: TSpeedButton
      Left = 35
      Top = 4
      Width = 30
      Height = 19
      Hint = 'Switch to decimal (base 10) mode'
      Caption = 'Dec'
      ParentShowHint = False
      ShowHint = True
      OnClick = SetDecButtonClick
    end
    object SetOctButton: TSpeedButton
      Left = 67
      Top = 4
      Width = 30
      Height = 19
      Hint = 'Switch to ochtadecimal (base 8) mode'
      Caption = 'Oct'
      ParentShowHint = False
      ShowHint = True
      OnClick = SetOctButtonClick
    end
    object SetBinButton: TSpeedButton
      Left = 99
      Top = 4
      Width = 30
      Height = 19
      Hint = 'Switch to binary (base 2) mode'
      Caption = 'Bin'
      ParentShowHint = False
      ShowHint = True
      OnClick = SetBinButtonClick
    end
    object ToggleTrigButton: TSpeedButton
      Left = 135
      Top = 4
      Width = 30
      Height = 19
      Hint = 'Select trigometric mode (Radians, Degrees or Grad)'
      Caption = 'Rad'
      ParentShowHint = False
      ShowHint = True
      OnClick = ToggleTrigButtonClick
    end
    object STOButton: TSpeedButton
      Left = 219
      Top = 2
      Width = 41
      Height = 25
      Hint = 'Store value to memory'
      Caption = 'STO'
      ParentShowHint = False
      ShowHint = True
      OnClick = StoreMemButtonClick
    end
    object RCLButton: TSpeedButton
      Left = 261
      Top = 2
      Width = 41
      Height = 25
      Hint = 'Recall value from memory'
      Caption = 'RCL'
      ParentShowHint = False
      ShowHint = True
      OnClick = RecallMemButtonClick
    end
    object CLRButton: TSpeedButton
      Left = 303
      Top = 2
      Width = 41
      Height = 25
      Hint = 'Clear value from stack'
      Caption = 'CLR'
      ParentShowHint = False
      ShowHint = True
      OnClick = CLRButtonClick
    end
    object BackButton: TSpeedButton
      Left = 349
      Top = 2
      Width = 41
      Height = 25
      Hint = 'Delete last character'
      Caption = #231
      Font.Charset = SYMBOL_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Wingdings'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = BackButtonClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 398
    Height = 49
    Align = alClient
    BevelKind = bkSoft
    BevelOuter = bvLowered
    TabOrder = 2
    object PaintBox: TPaintBox
      Left = 1
      Top = 1
      Width = 392
      Height = 43
      Align = alClient
      Color = 15204319
      ParentColor = False
      OnPaint = PaintBoxPaint
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 426
      ExplicitHeight = 77
    end
  end
  object MainMenu1: TMainMenu
    Left = 288
    Top = 24
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object Copy1: TMenuItem
        Caption = 'Copy'
        ShortCut = 16451
        OnClick = Copy1Click
      end
      object Paste1: TMenuItem
        Caption = 'Paste'
        ShortCut = 16470
        OnClick = Paste1Click
      end
    end
    object Config1: TMenuItem
      Caption = 'Config'
      object Digits2: TMenuItem
        Caption = 'Digits'
        object Auto1: TMenuItem
          Caption = 'Auto'
          OnClick = SetDigitsMenuClick
        end
        object N02: TMenuItem
          Caption = '0'
          OnClick = SetDigitsMenuClick
        end
        object N12: TMenuItem
          Caption = '1'
          OnClick = SetDigitsMenuClick
        end
        object N22: TMenuItem
          Caption = '2'
          OnClick = SetDigitsMenuClick
        end
        object N32: TMenuItem
          Caption = '3'
          OnClick = SetDigitsMenuClick
        end
        object N42: TMenuItem
          Caption = '4'
          OnClick = SetDigitsMenuClick
        end
        object N52: TMenuItem
          Caption = '5'
          OnClick = SetDigitsMenuClick
        end
        object N62: TMenuItem
          Caption = '6'
          OnClick = SetDigitsMenuClick
        end
        object N72: TMenuItem
          Caption = '7'
          OnClick = SetDigitsMenuClick
        end
        object N82: TMenuItem
          Caption = '8'
          OnClick = SetDigitsMenuClick
        end
        object N92: TMenuItem
          Caption = '9'
          OnClick = SetDigitsMenuClick
        end
        object N102: TMenuItem
          Caption = '10'
          OnClick = SetDigitsMenuClick
        end
        object N112: TMenuItem
          Caption = '11'
          OnClick = SetDigitsMenuClick
        end
        object N122: TMenuItem
          Caption = '12'
          OnClick = SetDigitsMenuClick
        end
        object N131: TMenuItem
          Caption = '13'
          OnClick = SetDigitsMenuClick
        end
        object N141: TMenuItem
          Caption = '14'
          OnClick = SetDigitsMenuClick
        end
        object N151: TMenuItem
          Caption = '15'
          OnClick = SetDigitsMenuClick
        end
        object N161: TMenuItem
          Caption = '16'
          OnClick = SetDigitsMenuClick
        end
        object N171: TMenuItem
          Caption = '17'
          OnClick = SetDigitsMenuClick
        end
        object N181: TMenuItem
          Caption = '18'
          OnClick = SetDigitsMenuClick
        end
        object N19201: TMenuItem
          Caption = '19'
          OnClick = SetDigitsMenuClick
        end
      end
      object Layout1: TMenuItem
        Caption = 'Layout'
        object NormalLayoutMenu: TMenuItem
          Caption = 'Normal'
          RadioItem = True
          OnClick = NormalLayoutMenuClick
        end
        object SciAlt1LayoutMenu: TMenuItem
          Caption = 'Sci Alt 1'
          Hint = 'Scientific Layout 1 - Select with Ctrl'
          RadioItem = True
          OnClick = SciAlt1LayoutMenuClick
        end
        object ComputationalLayoutMenu: TMenuItem
          Caption = 'Computational'
          Hint = 'Scientific Layout 1 - Select with Alt'
          RadioItem = True
          OnClick = ComputationalLayoutMenuClick
        end
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object Keyboard1: TMenuItem
        Caption = 'Keyboard'
        OnClick = Keyboard1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
  object STOPopupMenu: TPopupMenu
    Left = 56
    Top = 24
    object miMem0: TMenuItem
      Caption = '0:'
      OnClick = StoMemClick
    end
    object miMem1: TMenuItem
      Tag = 1
      Caption = '1:'
      OnClick = StoMemClick
    end
    object miMem2: TMenuItem
      Tag = 2
      Caption = '2:'
      OnClick = StoMemClick
    end
    object miMem3: TMenuItem
      Tag = 3
      Caption = '3:'
      OnClick = StoMemClick
    end
    object miMem4: TMenuItem
      Tag = 4
      Caption = '4:'
      OnClick = StoMemClick
    end
    object miMem5: TMenuItem
      Tag = 5
      Caption = '5:'
      OnClick = StoMemClick
    end
    object miMem6: TMenuItem
      Tag = 6
      Caption = '6:'
      OnClick = StoMemClick
    end
    object miMem7: TMenuItem
      Tag = 7
      Caption = '7:'
      OnClick = StoMemClick
    end
    object miMem8: TMenuItem
      Tag = 8
      Caption = '8:'
      OnClick = StoMemClick
    end
    object miMem9: TMenuItem
      Tag = 9
      Caption = '9:'
      OnClick = StoMemClick
    end
  end
  object RCLPopupMenu: TPopupMenu
    Left = 88
    Top = 24
    object MenuItem1: TMenuItem
      Caption = '0:'
      OnClick = RclMemClick
    end
    object MenuItem2: TMenuItem
      Tag = 1
      Caption = '1:'
      OnClick = RclMemClick
    end
    object MenuItem3: TMenuItem
      Tag = 2
      Caption = '2:'
      OnClick = RclMemClick
    end
    object MenuItem4: TMenuItem
      Tag = 3
      Caption = '3:'
      OnClick = RclMemClick
    end
    object MenuItem5: TMenuItem
      Tag = 4
      Caption = '4:'
      OnClick = RclMemClick
    end
    object MenuItem6: TMenuItem
      Tag = 5
      Caption = '5:'
      OnClick = RclMemClick
    end
    object MenuItem7: TMenuItem
      Tag = 6
      Caption = '6:'
      OnClick = RclMemClick
    end
    object MenuItem8: TMenuItem
      Tag = 7
      Caption = '7:'
      OnClick = RclMemClick
    end
    object MenuItem9: TMenuItem
      Tag = 8
      Caption = '8:'
      OnClick = RclMemClick
    end
    object MenuItem10: TMenuItem
      Tag = 9
      Caption = '9:'
      OnClick = RclMemClick
    end
  end
  object TrigPopupMenu: TPopupMenu
    Left = 120
    Top = 24
    object SelectDegMenu: TMenuItem
      Caption = 'Degrees'
      OnClick = SelectDegMenuClick
    end
    object SelectRadMenu: TMenuItem
      Caption = 'Radians'
      OnClick = SelectRadMenuClick
    end
    object SelectGradMenu: TMenuItem
      Caption = 'Grads'
      OnClick = SelectGradMenuClick
    end
  end
end
