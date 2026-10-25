//---------------------------------------------------------------------------

#ifndef glownyH
#define glownyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>

#include "kolejka.h"
#include "kroliki.h"
#include "lisy.h"
#include "krolik.h"
#include "lis.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TOkno : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TGroupBox *Bog;
        TPanel *Przyciski_na_dole;
        TBitBtn *But_ok;
        TPageControl *Aniol;
        TTabSheet *TabSheet1;
        TLabel *Label_Ksztalt;
        TBevel *Bevel2;
        TEdit *Edit_ksztalt;
        TUpDown *PstrykZ;
        TButton *But_generuj;
        TTabSheet *TabSheet2;
        TBevel *Bevel3;
        TLabel *Label_ilosc_zat;
        TLabel *Label_WZatok;
        TLabel *Label_wygaszenie;
        TEdit *Edit_LZatok;
        TUpDown *UpDown_Lzatok;
        TUpDown *UpDown_WZatok;
        TEdit *Edit_WZatok;
        TEdit *Edit_RZatok;
        TUpDown *UpDown_RZatok;
        TButton *But_zatoki;
        TButton *But_zat2;
        TTabSheet *TabSheet3;
        TBevel *Bevel4;
        TLabel *Label5;
        TLabel *Label6;
        TButton *But_zwieksz;
        TButton *But_zmniejsz;
        TButton *But_wygladz;
        TEdit *Edit_gladz;
        TUpDown *UpDown_gladz;
        TTabSheet *TabSheet4;
        TBevel *Bevel1;
        TLabel *Label7;
        TEdit *Edit_ziarno;
        TUpDown *UpDown_ziarno;
        TButton *Button1;
        TButton *Button2;
        TPanel *Panel_wnetrze;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit_snieg;
        TEdit *Edit_trawa;
        TEdit *Edit_plaza;
        TUpDown *UpDown_plaza;
        TUpDown *UpDown_trawa;
        TUpDown *UpDown_snieg;
        TBitBtn *But_powrot;
        TGroupBox *Krolik;
        TUpDown *UpDown_ileK;
        TEdit *Edit1;
        TLabel *Label4;
        TEdit *Edit2;
        TUpDown *UpDown_stadaK;
        TLabel *Label8;
        TEdit *Edit3;
        TUpDown *UpDown_rozpK;
        TLabel *Label9;
        TButton *But_genK;
        TGroupBox *Lisek;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TUpDown *UpDown_ileL;
        TEdit *Edit4;
        TEdit *Edit5;
        TUpDown *UpDown_stadaL;
        TEdit *Edit6;
        TUpDown *UpDown_rozpL;
        TButton *But_genL;
        TGroupBox *Informer;
        TTabSheet *Trawka;
        TTabSheet *Kroliki;
        TEdit *Edit7;
        TUpDown *Wegetacja_pstryk;
        TLabel *Label15;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *Reset_trawy;
        TTabSheet *Lisy;
        TPageControl *Agent;
        TTabSheet *Statystyki;
        TEdit *Llis;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Lkrol;
        TScrollBox *ScrollBox1;
        TLabel *Label16;
        TEdit *Edit8;
        TUpDown *vk_pstryk;
        TLabel *Label17;
        TUpDown *metaK_pstryk;
        TEdit *Edit9;
        TLabel *Label18;
        TLabel *Label19;
        TEdit *Edit10;
        TUpDown *kesK_pstryk;
        TLabel *Label20;
        TEdit *Edit11;
        TUpDown *zoladekK_pstryk;
        TUpDown *glodK_pstryk;
        TEdit *Edit12;
        TLabel *Label21;
        TLabel *Label22;
        TEdit *Edit13;
        TUpDown *starvingK_pstryk;
        TUpDown *detekcjaK_pstryk;
        TEdit *Edit14;
        TLabel *Label23;
        TUpDown *zycieK_pstryk;
        TEdit *Edit15;
        TLabel *Label24;
        TLabel *Label25;
        TEdit *Edit16;
        TUpDown *dojrzaloscK_pstryk;
        TLabel *Label26;
        TEdit *Edit17;
        TUpDown *ciazaK_pstryk;
        TScrollBox *ScrollBox2;
        TLabel *Label27;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label32;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TEdit *Edit18;
        TUpDown *vl_pstryk;
        TUpDown *metaL_pstryk;
        TEdit *Edit19;
        TEdit *Edit20;
        TUpDown *wodzL_pstryk;
        TEdit *Edit21;
        TUpDown *zoladekL_pstryk;
        TUpDown *glodL_pstryk;
        TEdit *Edit22;
        TUpDown *zycieL_pstryk;
        TEdit *Edit25;
        TEdit *Edit26;
        TUpDown *dojrzaloscL_pstryk;
        TEdit *Edit27;
        TUpDown *ciazaL_pstryk;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall But_generujClick(TObject *Sender);
        void __fastcall But_zatokiClick(TObject *Sender);
        void __fastcall But_zmniejszClick(TObject *Sender);
        void __fastcall But_zwiekszClick(TObject *Sender);
        void __fastcall But_wygladzClick(TObject *Sender);
        void __fastcall Edit_plazaChange(TObject *Sender);
        void __fastcall But_zat2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall PstrykZChanging(TObject *Sender,
          bool &AllowChange);
        void __fastcall But_okClick(TObject *Sender);
        void __fastcall But_powrotClick(TObject *Sender);
        void __fastcall But_genKClick(TObject *Sender);
        void __fastcall But_genLClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Reset_trawyClick(TObject *Sender);
        void __fastcall Wegetacja_pstrykClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall Edit7Change(TObject *Sender);
        void __fastcall vk_pstrykClick(TObject *Sender, TUDBtnType Button);
        void __fastcall Edit8Change(TObject *Sender);
        void __fastcall vl_pstrykClick(TObject *Sender, TUDBtnType Button);
        void __fastcall Edit18Change(TObject *Sender);
private:   void fale();
           void lad();
           void pallad();
           void ziarno();
public:    Graphics::TBitmap *bmp, *bmpK, *bmpL;

           int wegetacja;

        __fastcall TOkno(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOkno *Okno;

//---------------------------------------------------------------------------
#endif
