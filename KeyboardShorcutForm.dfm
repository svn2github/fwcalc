object KeyboardShorcutDlg: TKeyboardShorcutDlg
  Left = 0
  Top = 0
  Caption = 'Keybord Shortcuts'
  ClientHeight = 567
  ClientWidth = 260
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    260
    567)
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 260
    Height = 529
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'Operator      Key'
      '+             +'
      '-             -'
      '/             /'
      '*             *'
      '%             %'
      'AND           &'
      'OR            |'
      'NOT           ~'
      'LSH           <'
      'RSH           >'
      'MOD           m'
      'XOR           x'
      'y^x           ^'
      'sqrt          q'
      'sqrt          r'
      'sin           s'
      'cos           c'
      'tan           t'
      'asin          i s'
      'acos          i c'
      'atan          i t'
      'sinh          h s'
      'cosh          h c'
      'tanh          h t'
      'asinh         i h s'
      'acosh         i h c'
      'atanh         i h t'
      'PI            p'
      'x!            !'
      'ln x          l'
      'exp x         i l'
      '1/x           o'
      '<-            Backspace'
      'CLR           Delete'
      'CHS           Escape'
      'EEX           e'
      ''
      'X<>Y          \'
      ''
      'STO 0         F1'
      '...'
      'STO 9         F10                        '
      'STO N         "Arror Up" N   (0<= N <= 9)'
      ''
      'RCL 0         CTRL+F1  or SHIFT+F1'
      '...'
      'RCL 9         CTRL+F10  or SHIFT+F10'
      'RCL N         "Arrow Down" N   (0 <= N <= 9)'
      ''
      ''
      'Consequitive keys means multiple '
      'consequitive key pressed')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object Button1: TButton
    Left = 88
    Top = 535
    Width = 75
    Height = 25
    Anchors = [akBottom]
    Caption = 'Close'
    Default = True
    TabOrder = 1
    OnClick = Button1Click
  end
end
