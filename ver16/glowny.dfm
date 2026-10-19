object Okno: TOkno
  Left = 234
  Top = 191
  BorderStyle = bsDialog
  Caption = 
    'Wyspa  "Spy VsSpy 1.3."   (gdzie'#347' na skraju Imperium)           ' +
    ' ....:::::::    Autor: Dawid Domaga'#322'a   :::::::....'
  ClientHeight = 407
  ClientWidth = 732
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bog: TGroupBox
    Left = 512
    Top = 16
    Width = 209
    Height = 265
    Caption = 'Generator "B'#243'g ver. 1.3.12"'
    TabOrder = 0
    object Aniol: TPageControl
      Left = 2
      Top = 15
      Width = 205
      Height = 248
      ActivePage = TabSheet1
      Align = alClient
      TabIndex = 0
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Kszta'#322't'
        DesignSize = (
          197
          220)
        object Label_Ksztalt: TLabel
          Left = 32
          Top = 24
          Width = 60
          Height = 20
          Caption = 'Kszta'#322't'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Bevel2: TBevel
          Left = 8
          Top = 0
          Width = 169
          Height = 129
        end
        object Edit_ksztalt: TEdit
          Left = 112
          Top = 24
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          TabOrder = 0
          Text = '130'
        end
        object PstrykZ: TUpDown
          Left = 153
          Top = 24
          Width = 15
          Height = 21
          Associate = Edit_ksztalt
          Min = 1
          Max = 1000
          Position = 130
          TabOrder = 1
          Wrap = False
          OnChanging = PstrykZChanging
        end
        object But_generuj: TButton
          Left = 24
          Top = 64
          Width = 137
          Height = 55
          Anchors = [akLeft]
          Caption = 'Generuj'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          OnClick = But_generujClick
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Zatoki'
        ImageIndex = 1
        object Bevel3: TBevel
          Left = 8
          Top = 0
          Width = 169
          Height = 193
        end
        object Label_ilosc_zat: TLabel
          Left = 32
          Top = 10
          Width = 73
          Height = 13
          Caption = 'Liczba zatok'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label_WZatok: TLabel
          Left = 45
          Top = 35
          Width = 46
          Height = 13
          Caption = 'Rozmiar'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label_wygaszenie: TLabel
          Left = 20
          Top = 60
          Width = 86
          Height = 13
          Caption = 'Nieregularno'#347#263
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Edit_LZatok: TEdit
          Left = 112
          Top = 8
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 2
          ParentFont = False
          TabOrder = 0
          Text = '3'
        end
        object UpDown_Lzatok: TUpDown
          Left = 153
          Top = 8
          Width = 14
          Height = 21
          Associate = Edit_LZatok
          Min = 1
          Max = 99
          Position = 3
          TabOrder = 1
          Wrap = False
        end
        object UpDown_WZatok: TUpDown
          Left = 153
          Top = 32
          Width = 14
          Height = 21
          Associate = Edit_WZatok
          Min = 1
          Max = 1000
          Position = 30
          TabOrder = 2
          Wrap = False
        end
        object Edit_WZatok: TEdit
          Left = 112
          Top = 32
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          TabOrder = 3
          Text = '30'
        end
        object Edit_RZatok: TEdit
          Left = 112
          Top = 56
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          TabOrder = 4
          Text = '88'
        end
        object UpDown_RZatok: TUpDown
          Left = 153
          Top = 56
          Width = 14
          Height = 21
          Associate = Edit_RZatok
          Min = 0
          Max = 999
          Position = 88
          TabOrder = 5
          Wrap = False
        end
        object But_zatoki: TButton
          Left = 32
          Top = 96
          Width = 121
          Height = 33
          Caption = 'Dodaj zatoki'
          TabOrder = 6
          OnClick = But_zatokiClick
        end
        object But_zat2: TButton
          Left = 32
          Top = 144
          Width = 121
          Height = 33
          Caption = 'Dodaj zatoki na pla'#380'y'
          TabOrder = 7
          OnClick = But_zat2Click
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Korekta'
        ImageIndex = 2
        object Bevel4: TBevel
          Left = 8
          Top = 0
          Width = 169
          Height = 193
        end
        object Label5: TLabel
          Left = 29
          Top = 27
          Width = 54
          Height = 13
          Caption = 'Powi'#281'ksz'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label6: TLabel
          Left = 101
          Top = 27
          Width = 57
          Height = 13
          Caption = 'Pomniejsz'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object But_zwieksz: TButton
          Left = 24
          Top = 52
          Width = 57
          Height = 57
          Caption = '+'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -29
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = But_zwiekszClick
        end
        object But_zmniejsz: TButton
          Left = 104
          Top = 52
          Width = 57
          Height = 57
          Caption = '-'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -29
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = But_zmniejszClick
        end
        object But_wygladz: TButton
          Left = 24
          Top = 132
          Width = 81
          Height = 25
          Caption = 'Wyg'#322'ad'#378' brzeg'
          TabOrder = 2
          OnClick = But_wygladzClick
        end
        object Edit_gladz: TEdit
          Left = 112
          Top = 136
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 4
          ParentFont = False
          TabOrder = 3
          Text = '1'
        end
        object UpDown_gladz: TUpDown
          Left = 153
          Top = 136
          Width = 14
          Height = 21
          Associate = Edit_gladz
          Min = 1
          Max = 20
          Position = 1
          TabOrder = 4
          Wrap = False
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'Wn'#281'trze'
        ImageIndex = 3
        object Bevel1: TBevel
          Left = 8
          Top = 0
          Width = 169
          Height = 193
        end
        object Label7: TLabel
          Left = 24
          Top = 133
          Width = 77
          Height = 16
          Caption = 'Ziarnisto'#347#263
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Edit_ziarno: TEdit
          Left = 112
          Top = 128
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          TabOrder = 0
          Text = '8'
          OnChange = Edit_plazaChange
        end
        object UpDown_ziarno: TUpDown
          Left = 153
          Top = 128
          Width = 15
          Height = 21
          Associate = Edit_ziarno
          Min = 0
          Max = 16
          Position = 8
          TabOrder = 1
          Wrap = False
        end
        object Button1: TButton
          Left = 24
          Top = 160
          Width = 137
          Height = 25
          Caption = 'Akceptuj'
          TabOrder = 2
          OnClick = Button1Click
        end
        object Button2: TButton
          Left = 40
          Top = 48
          Width = 99
          Height = 33
          Caption = 'Edytuj wn'#281'trze'
          TabOrder = 4
          OnClick = Button2Click
        end
        object Panel_wnetrze: TPanel
          Left = 16
          Top = 8
          Width = 153
          Height = 105
          TabOrder = 3
          Visible = False
          DesignSize = (
            153
            105)
          object Label1: TLabel
            Left = 40
            Top = 13
            Width = 40
            Height = 16
            Anchors = [akTop, akRight]
            Caption = 'Pla'#380'a'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label2: TLabel
            Left = 32
            Top = 45
            Width = 44
            Height = 16
            Anchors = [akTop, akRight]
            Caption = 'Trawa'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label3: TLabel
            Left = 40
            Top = 77
            Width = 41
            Height = 16
            Anchors = [akTop, akRight]
            Caption = #346'nieg'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Edit_snieg: TEdit
            Left = 88
            Top = 72
            Width = 41
            Height = 21
            Anchors = [akTop, akRight]
            Color = clYellow
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clPurple
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Pitch = fpVariable
            Font.Style = [fsBold]
            MaxLength = 3
            ParentFont = False
            TabOrder = 0
            Text = '50'
            OnChange = Edit_plazaChange
          end
          object Edit_trawa: TEdit
            Left = 88
            Top = 40
            Width = 41
            Height = 21
            Anchors = [akTop, akRight]
            Color = clYellow
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clPurple
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Pitch = fpVariable
            Font.Style = [fsBold]
            MaxLength = 3
            ParentFont = False
            TabOrder = 1
            Text = '30'
            OnChange = Edit_plazaChange
          end
          object Edit_plaza: TEdit
            Left = 88
            Top = 8
            Width = 41
            Height = 21
            Anchors = [akTop, akRight]
            Color = clYellow
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clPurple
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Pitch = fpVariable
            Font.Style = [fsBold]
            MaxLength = 3
            ParentFont = False
            TabOrder = 2
            Text = '10'
            OnChange = Edit_plazaChange
          end
          object UpDown_plaza: TUpDown
            Left = 129
            Top = 8
            Width = 15
            Height = 21
            Anchors = [akTop, akRight]
            Associate = Edit_plaza
            Min = 0
            Max = 200
            Position = 10
            TabOrder = 3
            Wrap = False
          end
          object UpDown_trawa: TUpDown
            Left = 129
            Top = 40
            Width = 15
            Height = 21
            Anchors = [akTop, akRight]
            Associate = Edit_trawa
            Min = 0
            Max = 200
            Position = 30
            TabOrder = 4
            Wrap = False
          end
          object UpDown_snieg: TUpDown
            Left = 129
            Top = 72
            Width = 15
            Height = 21
            Anchors = [akTop, akRight]
            Associate = Edit_snieg
            Min = 0
            Max = 200
            Position = 50
            TabOrder = 5
            Wrap = False
          end
        end
      end
    end
  end
  object Krolik: TGroupBox
    Left = 512
    Top = 16
    Width = 209
    Height = 265
    Caption = 'Generator "Kr'#243'liczek ver. 1.3.1"'
    TabOrder = 2
    Visible = False
    DesignSize = (
      209
      265)
    object Label4: TLabel
      Left = 80
      Top = 37
      Width = 44
      Height = 16
      Caption = 'Kr'#243'liki'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 80
      Top = 69
      Width = 42
      Height = 16
      Caption = 'Stada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Label9: TLabel
      Left = 32
      Top = 93
      Width = 96
      Height = 16
      Caption = 'Rozproszenie'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object UpDown_ileK: TUpDown
      Left = 177
      Top = 32
      Width = 15
      Height = 21
      Associate = Edit1
      Min = 0
      Max = 999
      Position = 200
      TabOrder = 0
      Wrap = False
    end
    object Edit1: TEdit
      Left = 136
      Top = 32
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 1
      Text = '200'
    end
    object Edit2: TEdit
      Left = 136
      Top = 64
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 2
      Text = '8'
      Visible = False
    end
    object UpDown_stadaK: TUpDown
      Left = 177
      Top = 64
      Width = 15
      Height = 21
      Associate = Edit2
      Min = 0
      Max = 16
      Position = 8
      TabOrder = 3
      Visible = False
      Wrap = False
    end
    object Edit3: TEdit
      Left = 136
      Top = 88
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 4
      Text = '8'
      Visible = False
    end
    object UpDown_rozpK: TUpDown
      Left = 177
      Top = 88
      Width = 15
      Height = 21
      Associate = Edit3
      Min = 0
      Max = 16
      Position = 8
      TabOrder = 5
      Visible = False
      Wrap = False
    end
    object But_genK: TButton
      Left = 48
      Top = 122
      Width = 137
      Height = 55
      Anchors = [akLeft]
      Caption = 'Generuj'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = But_genKClick
    end
  end
  object Przyciski_na_dole: TPanel
    Left = 512
    Top = 288
    Width = 209
    Height = 105
    TabOrder = 1
    object But_ok: TBitBtn
      Left = 80
      Top = 8
      Width = 121
      Height = 89
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
      OnClick = But_okClick
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object But_powrot: TBitBtn
      Left = 8
      Top = 8
      Width = 65
      Height = 89
      Caption = 'Powr'#243't'
      Enabled = False
      TabOrder = 1
      OnClick = But_powrotClick
      Kind = bkNo
      Layout = blGlyphTop
    end
  end
  object Lisek: TGroupBox
    Left = 512
    Top = 16
    Width = 209
    Height = 265
    Caption = 'Generator "Lisek ver. 1.3.1"'
    TabOrder = 3
    Visible = False
    DesignSize = (
      209
      265)
    object Label10: TLabel
      Left = 88
      Top = 37
      Width = 29
      Height = 16
      Caption = 'Lisy'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 80
      Top = 69
      Width = 42
      Height = 16
      Caption = 'Stada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Label12: TLabel
      Left = 32
      Top = 93
      Width = 96
      Height = 16
      Caption = 'Rozproszenie'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object UpDown_ileL: TUpDown
      Left = 177
      Top = 32
      Width = 15
      Height = 21
      Associate = Edit4
      Min = 0
      Max = 999
      Position = 20
      TabOrder = 0
      Wrap = False
    end
    object Edit4: TEdit
      Left = 136
      Top = 32
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 1
      Text = '20'
    end
    object Edit5: TEdit
      Left = 136
      Top = 64
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 2
      Text = '8'
      Visible = False
    end
    object UpDown_stadaL: TUpDown
      Left = 177
      Top = 64
      Width = 15
      Height = 21
      Associate = Edit5
      Min = 0
      Max = 16
      Position = 8
      TabOrder = 3
      Visible = False
      Wrap = False
    end
    object Edit6: TEdit
      Left = 136
      Top = 88
      Width = 41
      Height = 21
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpVariable
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 4
      Text = '8'
      Visible = False
    end
    object UpDown_rozpL: TUpDown
      Left = 177
      Top = 88
      Width = 15
      Height = 21
      Associate = Edit6
      Min = 0
      Max = 16
      Position = 8
      TabOrder = 5
      Visible = False
      Wrap = False
    end
    object But_genL: TButton
      Left = 48
      Top = 122
      Width = 137
      Height = 55
      Anchors = [akLeft]
      Caption = 'Generuj'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = But_genLClick
    end
  end
  object Informer: TGroupBox
    Left = 512
    Top = 16
    Width = 209
    Height = 265
    Caption = 'Informer "UB ver. 1.3.6"'
    TabOrder = 4
    Visible = False
    object Agent: TPageControl
      Left = 2
      Top = 15
      Width = 205
      Height = 248
      ActivePage = TabSheet5
      Align = alClient
      MultiLine = True
      TabIndex = 4
      TabOrder = 0
      object Trawka: TTabSheet
        Caption = 'Trawka'
        object Label15: TLabel
          Left = 16
          Top = 28
          Width = 112
          Height = 16
          Caption = 'Okres wegetacji'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Edit7: TEdit
          Left = 136
          Top = 24
          Width = 33
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          Text = '10'
          OnChange = Edit7Change
        end
        object Wegetacja_pstryk: TUpDown
          Left = 169
          Top = 24
          Width = 16
          Height = 24
          Associate = Edit7
          Min = 1
          Position = 10
          TabOrder = 1
          Wrap = False
          OnClick = Wegetacja_pstrykClick
        end
        object BitBtn1: TBitBtn
          Left = 8
          Top = 64
          Width = 177
          Height = 41
          Caption = 'Zazielen'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          OnClick = Button3Click
          Kind = bkYes
        end
        object BitBtn2: TBitBtn
          Left = 8
          Top = 160
          Width = 177
          Height = 41
          Caption = 'Skos trawe'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = BitBtn2Click
          Kind = bkCancel
        end
        object Reset_trawy: TBitBtn
          Left = 8
          Top = 112
          Width = 177
          Height = 41
          Caption = 'Reset'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = Reset_trawyClick
          Kind = bkRetry
        end
      end
      object Kroliki: TTabSheet
        Caption = 'Kroliki'
        ImageIndex = 1
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 197
          Height = 202
          Align = alClient
          TabOrder = 0
          object Label16: TLabel
            Left = 8
            Top = 16
            Width = 60
            Height = 16
            Caption = 'v krolika'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label17: TLabel
            Left = 72
            Top = 16
            Width = 36
            Height = 16
            Caption = '0,1 x '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label18: TLabel
            Left = 16
            Top = 48
            Width = 80
            Height = 16
            Caption = 'metabolizm'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label19: TLabel
            Left = 72
            Top = 80
            Width = 26
            Height = 16
            Caption = 'k'#281's'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label20: TLabel
            Left = 40
            Top = 112
            Width = 56
            Height = 16
            Caption = #380'o'#322#261'dek'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label21: TLabel
            Left = 64
            Top = 144
            Width = 32
            Height = 16
            Caption = 'g'#322#243'd'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label22: TLabel
            Left = 40
            Top = 176
            Width = 58
            Height = 16
            Caption = 'G'#321#211'D !!!'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label23: TLabel
            Left = 0
            Top = 208
            Width = 100
            Height = 16
            Caption = 'detekcja lis'#243'w'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label24: TLabel
            Left = 0
            Top = 244
            Width = 96
            Height = 16
            Caption = 'd'#322'ugosc '#380'ycia'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label25: TLabel
            Left = 24
            Top = 276
            Width = 73
            Height = 16
            Caption = 'dojrzalosc'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label26: TLabel
            Left = 56
            Top = 308
            Width = 38
            Height = 16
            Caption = 'ci'#261#380'a'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Edit8: TEdit
            Left = 107
            Top = 12
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Text = '5'
            OnChange = Edit9Change
          end
          object vk_pstryk: TUpDown
            Left = 140
            Top = 12
            Width = 16
            Height = 24
            Associate = Edit8
            Min = 1
            Position = 5
            TabOrder = 1
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object metaK_pstryk: TUpDown
            Left = 140
            Top = 44
            Width = 16
            Height = 24
            Associate = Edit9
            Min = 1
            Position = 4
            TabOrder = 2
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit9: TEdit
            Left = 107
            Top = 44
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
            Text = '4'
            OnChange = Edit9Change
          end
          object Edit10: TEdit
            Left = 107
            Top = 76
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 4
            Text = '64'
            OnChange = Edit9Change
          end
          object kesK_pstryk: TUpDown
            Left = 140
            Top = 76
            Width = 16
            Height = 24
            Associate = Edit10
            Min = 1
            Position = 64
            TabOrder = 5
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit11: TEdit
            Left = 107
            Top = 108
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
            Text = '100'
            OnChange = Edit9Change
          end
          object zoladekK_pstryk: TUpDown
            Left = 140
            Top = 108
            Width = 16
            Height = 24
            Associate = Edit11
            Min = 1
            Max = 1000
            Position = 100
            TabOrder = 7
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object glodK_pstryk: TUpDown
            Left = 140
            Top = 140
            Width = 16
            Height = 24
            Associate = Edit12
            Min = 1
            Max = 1000
            Position = 60
            TabOrder = 8
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit12: TEdit
            Left = 107
            Top = 140
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 9
            Text = '60'
            OnChange = Edit9Change
          end
          object Edit13: TEdit
            Left = 107
            Top = 172
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 10
            Text = '20'
            OnChange = Edit9Change
          end
          object starvingK_pstryk: TUpDown
            Left = 140
            Top = 172
            Width = 16
            Height = 24
            Associate = Edit13
            Min = 1
            Max = 1000
            Position = 20
            TabOrder = 11
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object detekcjaK_pstryk: TUpDown
            Left = 140
            Top = 204
            Width = 16
            Height = 24
            Associate = Edit14
            Min = 1
            Position = 25
            TabOrder = 12
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit14: TEdit
            Left = 107
            Top = 204
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 13
            Text = '25'
            OnChange = Edit9Change
          end
          object zycieK_pstryk: TUpDown
            Left = 140
            Top = 236
            Width = 16
            Height = 24
            Associate = Edit15
            Min = 1
            Max = 1000
            Position = 100
            TabOrder = 14
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit15: TEdit
            Left = 107
            Top = 236
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 15
            Text = '100'
            OnChange = Edit9Change
          end
          object Edit16: TEdit
            Left = 107
            Top = 268
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 16
            Text = '21'
            OnChange = Edit9Change
          end
          object dojrzaloscK_pstryk: TUpDown
            Left = 140
            Top = 268
            Width = 16
            Height = 24
            Associate = Edit16
            Min = 1
            Max = 1000
            Position = 21
            TabOrder = 17
            Wrap = False
            OnClick = vk_pstrykClick
          end
          object Edit17: TEdit
            Left = 107
            Top = 300
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 18
            Text = '20'
            OnChange = Edit9Change
          end
          object ciazaK_pstryk: TUpDown
            Left = 140
            Top = 300
            Width = 16
            Height = 24
            Associate = Edit17
            Min = 1
            Max = 1000
            Position = 20
            TabOrder = 19
            Wrap = False
            OnClick = vk_pstrykClick
          end
        end
      end
      object Lisy: TTabSheet
        Caption = 'Lisy'
        ImageIndex = 2
        object ScrollBox2: TScrollBox
          Left = 0
          Top = 0
          Width = 197
          Height = 202
          VertScrollBar.Position = 62
          Align = alClient
          TabOrder = 0
          object Label27: TLabel
            Left = 24
            Top = -46
            Width = 38
            Height = 16
            Caption = 'v lisa'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label28: TLabel
            Left = 72
            Top = -46
            Width = 36
            Height = 16
            Caption = '0,1 x '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label29: TLabel
            Left = 16
            Top = -14
            Width = 80
            Height = 16
            Caption = 'metabolizm'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label30: TLabel
            Left = 8
            Top = 18
            Width = 95
            Height = 16
            Caption = 'w.od'#380'. kr'#243'lika'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label31: TLabel
            Left = 40
            Top = 50
            Width = 56
            Height = 16
            Caption = #380'o'#322#261'dek'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label32: TLabel
            Left = 64
            Top = 82
            Width = 32
            Height = 16
            Caption = 'g'#322#243'd'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label35: TLabel
            Left = 0
            Top = 118
            Width = 96
            Height = 16
            Caption = 'd'#322'ugosc '#380'ycia'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label36: TLabel
            Left = 24
            Top = 150
            Width = 73
            Height = 16
            Caption = 'dojrzalosc'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label37: TLabel
            Left = 56
            Top = 182
            Width = 38
            Height = 16
            Caption = 'ci'#261#380'a'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Edit18: TEdit
            Left = 107
            Top = -50
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Text = '10'
            OnChange = Edit18Change
          end
          object vl_pstryk: TUpDown
            Left = 140
            Top = -50
            Width = 16
            Height = 24
            Associate = Edit18
            Min = 1
            Position = 10
            TabOrder = 1
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object metaL_pstryk: TUpDown
            Left = 140
            Top = -18
            Width = 16
            Height = 24
            Associate = Edit19
            Min = 1
            Position = 3
            TabOrder = 2
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object Edit19: TEdit
            Left = 107
            Top = -18
            Width = 33
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
            Text = '3'
          end
          object Edit20: TEdit
            Left = 107
            Top = 14
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 4
            Text = '1'#160'500'
          end
          object wodzL_pstryk: TUpDown
            Left = 145
            Top = 14
            Width = 16
            Height = 24
            Associate = Edit20
            Min = 1
            Max = 9999
            Position = 1500
            TabOrder = 5
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object Edit21: TEdit
            Left = 107
            Top = 46
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
            Text = '2'#160'000'
          end
          object zoladekL_pstryk: TUpDown
            Left = 145
            Top = 46
            Width = 16
            Height = 24
            Associate = Edit21
            Min = 1
            Max = 9999
            Position = 2000
            TabOrder = 7
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object glodL_pstryk: TUpDown
            Left = 145
            Top = 78
            Width = 16
            Height = 24
            Associate = Edit22
            Min = 1
            Max = 9999
            Position = 1000
            TabOrder = 8
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object Edit22: TEdit
            Left = 107
            Top = 78
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 9
            Text = '1'#160'000'
          end
          object zycieL_pstryk: TUpDown
            Left = 145
            Top = 110
            Width = 16
            Height = 24
            Associate = Edit25
            Min = 1
            Max = 9999
            Position = 800
            TabOrder = 10
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object Edit25: TEdit
            Left = 107
            Top = 110
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 11
            Text = '800'
          end
          object Edit26: TEdit
            Left = 107
            Top = 142
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 12
            Text = '30'
          end
          object dojrzaloscL_pstryk: TUpDown
            Left = 145
            Top = 142
            Width = 16
            Height = 24
            Associate = Edit26
            Min = 1
            Max = 9999
            Position = 30
            TabOrder = 13
            Wrap = False
            OnClick = vl_pstrykClick
          end
          object Edit27: TEdit
            Left = 107
            Top = 174
            Width = 38
            Height = 24
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 14
            Text = '30'
          end
          object ciazaL_pstryk: TUpDown
            Left = 145
            Top = 174
            Width = 16
            Height = 24
            Associate = Edit27
            Min = 1
            Max = 9999
            Position = 30
            TabOrder = 15
            Wrap = False
            OnClick = vl_pstrykClick
          end
        end
      end
      object Statystyki: TTabSheet
        Caption = 'Statystyki'
        ImageIndex = 3
        object Label13: TLabel
          Left = 8
          Top = 13
          Width = 29
          Height = 16
          Caption = 'Lisy'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label14: TLabel
          Left = 104
          Top = 13
          Width = 44
          Height = 16
          Caption = 'Kroliki'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label50: TLabel
          Left = 64
          Top = 45
          Width = 56
          Height = 20
          Caption = 'Zgony:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label51: TLabel
          Left = 80
          Top = 77
          Width = 32
          Height = 16
          Caption = 'g'#322#243'd'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label54: TLabel
          Left = 72
          Top = 117
          Width = 52
          Height = 16
          Caption = 'starosc'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label52: TLabel
          Left = 24
          Top = 157
          Width = 102
          Height = 16
          Caption = 'przez po'#380'arcie'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Llis: TEdit
          Left = 40
          Top = 8
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Text = '0'
        end
        object Lkrol: TEdit
          Left = 152
          Top = 8
          Width = 41
          Height = 21
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clPurple
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Pitch = fpVariable
          Font.Style = [fsBold]
          MaxLength = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
          Text = '0'
        end
        object Edit40: TEdit
          Left = 8
          Top = 72
          Width = 57
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          Text = '0'
          OnChange = Edit7Change
        end
        object Edit41: TEdit
          Left = 136
          Top = 72
          Width = 57
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          Text = '0'
          OnChange = Edit7Change
        end
        object Edit42: TEdit
          Left = 136
          Top = 112
          Width = 57
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          Text = '0'
          OnChange = Edit7Change
        end
        object Edit43: TEdit
          Left = 8
          Top = 112
          Width = 57
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          Text = '0'
          OnChange = Edit7Change
        end
        object Edit44: TEdit
          Left = 132
          Top = 152
          Width = 57
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          Text = '0'
          OnChange = Edit7Change
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Moj krolik'
        ImageIndex = 4
        object Label33: TLabel
          Left = 0
          Top = 13
          Width = 46
          Height = 16
          Caption = 'Numer'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label34: TLabel
          Left = 40
          Top = 77
          Width = 42
          Height = 16
          Caption = 'status'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label38: TLabel
          Left = 32
          Top = 141
          Width = 38
          Height = 16
          Caption = 'ci'#261#380'a'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label39: TLabel
          Left = 16
          Top = 173
          Width = 32
          Height = 16
          Caption = 'wiek'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label40: TLabel
          Left = 120
          Top = 173
          Width = 8
          Height = 16
          Caption = '/'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label41: TLabel
          Left = 8
          Top = 109
          Width = 77
          Height = 16
          Caption = 'najedzenie'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label48: TLabel
          Left = 16
          Top = 45
          Width = 61
          Height = 16
          Caption = 'wielkosc'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object wybr_edit: TEdit
          Left = 48
          Top = 8
          Width = 41
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          Text = '0'
          OnChange = Edit7Change
        end
        object wybr_pstryk: TUpDown
          Left = 89
          Top = 8
          Width = 16
          Height = 24
          Associate = wybr_edit
          Min = 0
          Position = 0
          TabOrder = 1
          Wrap = False
          OnClick = Wegetacja_pstrykClick
        end
        object w_stat_edit: TEdit
          Left = 88
          Top = 72
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object Edit23: TEdit
          Left = 116
          Top = 8
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object Edit24: TEdit
          Left = 88
          Top = 136
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object Edit28: TEdit
          Left = 64
          Top = 168
          Width = 57
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
        object Edit29: TEdit
          Left = 128
          Top = 168
          Width = 57
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
        end
        object Edit30: TEdit
          Left = 88
          Top = 104
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
        end
        object Edit38: TEdit
          Left = 88
          Top = 40
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
        end
      end
      object TabSheet6: TTabSheet
        Caption = 'Moj lis'
        ImageIndex = 5
        object Label42: TLabel
          Left = 0
          Top = 13
          Width = 46
          Height = 16
          Caption = 'Numer'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label43: TLabel
          Left = 40
          Top = 77
          Width = 42
          Height = 16
          Caption = 'status'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label44: TLabel
          Left = 8
          Top = 109
          Width = 77
          Height = 16
          Caption = 'najedzenie'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label45: TLabel
          Left = 32
          Top = 141
          Width = 38
          Height = 16
          Caption = 'ci'#261#380'a'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label46: TLabel
          Left = 16
          Top = 173
          Width = 32
          Height = 16
          Caption = 'wiek'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label47: TLabel
          Left = 120
          Top = 173
          Width = 8
          Height = 16
          Caption = '/'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label49: TLabel
          Left = 16
          Top = 45
          Width = 61
          Height = 16
          Caption = 'wielkosc'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Edit31: TEdit
          Left = 48
          Top = 8
          Width = 41
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          Text = '0'
          OnChange = Edit7Change
        end
        object wybr2_pstryk: TUpDown
          Left = 89
          Top = 8
          Width = 16
          Height = 24
          Associate = Edit31
          Min = 0
          Position = 0
          TabOrder = 1
          Wrap = False
          OnClick = Wegetacja_pstrykClick
        end
        object Edit32: TEdit
          Left = 116
          Top = 8
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object Edit33: TEdit
          Left = 88
          Top = 72
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object Edit34: TEdit
          Left = 88
          Top = 104
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object Edit35: TEdit
          Left = 88
          Top = 136
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
        object Edit36: TEdit
          Left = 128
          Top = 168
          Width = 57
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
        end
        object Edit37: TEdit
          Left = 64
          Top = 168
          Width = 57
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
        end
        object Edit39: TEdit
          Left = 88
          Top = 40
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
        end
      end
      object TabSheet7: TTabSheet
        Caption = 'Ewolucja'
        ImageIndex = 6
        object Label53: TLabel
          Left = 40
          Top = 45
          Width = 61
          Height = 16
          Caption = 'wielkosc'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label55: TLabel
          Left = 8
          Top = 13
          Width = 105
          Height = 20
          Caption = #346'rednie lisy:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label56: TLabel
          Left = 24
          Top = 69
          Width = 76
          Height = 16
          Caption = 'prog glodu'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label57: TLabel
          Left = 8
          Top = 101
          Width = 126
          Height = 20
          Caption = #346'rednie kr'#243'liki:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label58: TLabel
          Left = 40
          Top = 133
          Width = 61
          Height = 16
          Caption = 'wielkosc'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label59: TLabel
          Left = 24
          Top = 157
          Width = 76
          Height = 16
          Caption = 'prog glodu'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label60: TLabel
          Left = 0
          Top = 181
          Width = 102
          Height = 16
          Caption = 'alarm g'#322'odowy'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Edit45: TEdit
          Left = 112
          Top = 40
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object Edit46: TEdit
          Left = 112
          Top = 64
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object Edit47: TEdit
          Left = 112
          Top = 128
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object Edit48: TEdit
          Left = 112
          Top = 152
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object Edit49: TEdit
          Left = 112
          Top = 176
          Width = 73
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
      end
    end
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
  end
end
