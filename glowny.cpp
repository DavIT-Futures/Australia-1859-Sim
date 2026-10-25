//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "glowny.h"
#include "math.h"
#include "mem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TOkno *Okno;

const int slona=40;

 typedef Byte rgb[3];
  rgb *ptr;
  rgb pal[800]; //paelta otoczenia
  rgb fala[slona];
  rgb falaS[slona/2];
  int plus,szer,wys;

  int **wyspa,**trawa;

  Kroliki* krol;// = new Kroliki();
  Lisy* lis;

  int poziom=0;

  DynamicArray <Lis> Ltab;
  DynamicArray <Krolik> Ktab;

void nowe()
{
        krol = new Kroliki(trawa,szer,wys,&Ktab,&Ltab);   //obiekty
        lis = new Lisy(trawa,szer,wys,&Ktab,&Ltab);

        Okno->vk_pstrykClick(Okno,NULL);         //wartosci pocatkowe z okna do obiektow
        Okno->vl_pstrykClick(Okno,NULL);
}
int toInt(int r,int g, int b)
{
  return (b<<16)+(g<<8)+r;          //1 liczba
}
void TOkno::fale()
{
        int x,y;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
                if (wyspa[x][y]>=slona) wyspa[x][y]=0;   //lad
                else wyspa[x][y]=-1;                     //woda

// <BFS>
        FIFO *Kol = new FIFO();
        int c;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]==0) Kol->push(x,y,0);      //lad na wierzch

        while (!Kol->empty())      //gdy nie pusta
        {
          Kol->pop(x,y,c);
          c++;
          if ((y>0)&&(wyspa[x][y-1]==-1)) { wyspa[x][y-1]=c; Kol->push(x,y-1,c);};     //c>0
          if ((y<wys)&&(wyspa[x][y+1]==-1)) { wyspa[x][y+1]=c; Kol->push(x,y+1,c);};   // i zaznaczamy przez c przeszukane
          if ((x<szer)&&(wyspa[x+1][y]==-1)) { wyspa[x+1][y]=c; Kol->push(x+1,y,c);};   // i wtedy juz c olewamy
          if ((x>0)&&(wyspa[x-1][y]==-1)) { wyspa[x-1][y]=c; Kol->push(x-1,y,c);};
        };

        delete(Kol);
// <</BFS>

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
                if (wyspa[x][y]!=0) wyspa[x][y]=wyspa[x][y]%slona;
                else wyspa[x][y]=slona;                //lad
 lad();
};

void TOkno::pallad()
{
        int pas=slona;
        // plaza
        for (int n=0; n<UpDown_plaza->Position; n++)
        {
          pal[pas+n][0]=0;           //0
          pal[pas+n][1]=224;        //216
          pal[pas+n][2]=255;
        }
        pas+=UpDown_plaza->Position;

        if (Bog->Visible)
        {
                // plaza/trawa
                for (int n=0; n<32; n++)
                {
                  pal[pas+n][0]=0;           //0
                  pal[pas+n][1]=224-n;        //216
                  pal[pas+n][2]=255-n*8;
                }
                pas+=32;
                //trawa
                for (int n=0; n<UpDown_trawa->Position; n++)
                {
                  pal[pas+n][0]=0;           //0
                  pal[pas+n][1]=192;        //216
                  pal[pas+n][2]=0;
                }
                pas+=UpDown_trawa->Position;
                //trawa/snieg
                for (int n=0; n<32; n++)
                {
                  pal[pas+n][0]=n*8;           //0
                  pal[pas+n][1]=192+n*2;        //216
                  pal[pas+n][2]=n*8;
                }
                pas+=32;
        } else
        {
                // plaza - pod trawa
                for (int n=0; n<32; n++)
                {
                  pal[pas+n][0]=0;           //0
                  pal[pas+n][1]=224;        //216               //spodnia warstwa
                  pal[pas+n][2]=255;
                }
                pas+=32;
                //plaza/snieg
                int trawa=UpDown_trawa->Position;
                for (int n=0; n<trawa; n++)
                {
                  pal[pas+n][0]=255*n/trawa;           //0
                  pal[pas+n][1]=224+32*n/trawa;        //216
                  pal[pas+n][2]=255;
                }
                pas+=UpDown_trawa->Position;
                //snieg - pod trawa
                for (int n=0; n<32; n++)
                {
                  pal[pas+n][0]=255;           //0
                  pal[pas+n][1]=255;        //216
                  pal[pas+n][2]=255;
                }
                pas+=32;
        }
        //snieg
        for (int n=0; n<UpDown_snieg->Position; n++)
        {
          pal[pas+n][0]=255;           //0
          pal[pas+n][1]=255;        //216
          pal[pas+n][2]=255;
        }
        pas+=UpDown_snieg->Position;
        //snieg/ziemia
         for (int n=0; n<32; n++)
        {
          pal[pas+n][0]=255-n*8;           //0
          pal[pas+n][1]=255-n*8;        //216
          pal[pas+n][2]=255-n*8;
        }
        pas+=32;
        //ziemia
        for (int n=0; n<8; n++)
        {
          pal[pas+n][0]=0;           //0
          pal[pas+n][1]=0;        //216
          pal[pas+n][2]=0;
        }
        pas+=8;

        //ziemia/lawa
        for (int n=0; n<16; n++)
        {
          pal[pas+n][0]=0;           //0
          pal[pas+n][1]=0;        //216
          pal[pas+n][2]=n*16;
        }
        pas+=16;
        //lawa/ogien
        for (int n=0; n<32; n++)
        {
          pal[pas+n][0]=0;           //0
          pal[pas+n][1]=n*8;        //216
          pal[pas+n][2]=255;
        }

        pas+=32;
        //ogien
        for (int n=pas; n<512; n++)
        {
          pal[n][0]=0;           //0
          pal[n][1]=255;        //216
          pal[n][2]=255;
        }

     //   pal[512][0]=255;
     //   pal[512][1]=255;
      //  pal[512][2]=0;
};

void TOkno::ziarno()
{
  int z=UpDown_ziarno->Position+1;
  int gora=UpDown_plaza->Position+UpDown_trawa->Position+UpDown_snieg->Position+138;
  for (int x=0 ; x<szer; x++)
    for (int y=0 ; y<wys ; y++)
            if (wyspa[x][y]>=slona)
                if (wyspa[x][y]<gora)
                    {
                        wyspa[x][y]+=random(z)-random(z);
                        if (wyspa[x][y]>=512) wyspa[x][y]=511;         //zeby nie przekroczyc palety
                        if (wyspa[x][y]<slona) wyspa[x][y]=slona;      //zeby wyspa sie nie zmienila w wode
                    }
                else
                    {
                        wyspa[x][y]+=5.0*sin(1.0*x/8);
                        wyspa[x][y]+=5.0*sin(1.0*y/8);
                        if (wyspa[x][y]>=512) wyspa[x][y]=511;
                        if (wyspa[x][y]<gora) wyspa[x][y]=gora;     //zeby lawa nie wchodzila na gory
                    }

}

void TOkno::lad()
{
 pallad();

 FIFO *Kol = new FIFO();
  int x,y,c;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]<slona) Kol->push(x,y,slona);

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          c++;
          if ((y>0)&&(wyspa[x][y-1]==slona))    {wyspa[x][y-1]=c+1; Kol->push(x,y-1,c);};
          if ((y<wys)&&(wyspa[x][y+1]==slona))  {wyspa[x][y+1]=c+1; Kol->push(x,y+1,c);};
          if ((x<szer)&&(wyspa[x+1][y]==slona)) {wyspa[x+1][y]=c+1; Kol->push(x+1,y,c);};
          if ((x>0)&&(wyspa[x-1][y]==slona))    {wyspa[x-1][y]=c+1; Kol->push(x-1,y,c);};
        };

        delete(Kol);
}
//---------------------------------------------------------------------------
__fastcall TOkno::TOkno(TComponent* Owner)
        : TForm(Owner)
{
        Randomize();

        bmp = new Graphics::TBitmap();
        bmp->Width=500;
        bmp->Height=400;
        bmp->PixelFormat=pf24bit;

        bmpK = new Graphics::TBitmap();
        bmpK->LoadFromFile("krolik.bmp");

        bmpL = new Graphics::TBitmap();
        bmpL->LoadFromFile("lis.bmp");

        bmpW = new Graphics::TBitmap();
        bmpW->LoadFromFile("wybrany.bmp");

        szer=bmp->Width;
        wys=bmp->Height;

        PstrykZ->Max=wys-20;

        wyspa = new int*[szer+1];
        trawa = new int*[szer+1];      //tablica wskaznikow (wiersze)

        for (int x=0; x<szer+1; x++)
        {
          wyspa[x]= new int[wys+1];  //elementy wiersza
          trawa[x]= new int[wys+1];  //pokazuja na kolumny
        }

        nowe();                      //init obiektow (K i L)

        for (int x=0; x<szer; x++) for (int y=0; y<wys; y++)
                trawa[x][y]=0;//x%256;


        plus=0;
//init palety:
//      matryca fali
        for (int n=0; n<slona/2; n++)
        {
          fala[n][0]=255;
          fala[n][1]=160-2*n;
          fala[n][2]=64-n;
        }
        for (int n=slona/2; n<slona; n++)
        {
          fala[n][0]=255;
          fala[n][1]=160-slona+n;
          fala[n][2]=64-slona+n;
        }
 //woda slodka
        for (int n=0; n<slona/2; n++)
        {
          falaS[n][0]=255;
          falaS[n][1]=224+4*sin(M_PI*n/(slona/8));
          falaS[n][2]=64+2*sin(M_PI*n/(slona/8));
        }

     But_generujClick(this);
}
//---------------------------------------------------------------------------


void __fastcall TOkno::Timer1Timer(TObject *Sender)
{
    float zielen=192.0/255;   //netmask :)
    int tmpi,zi;
    float tmp2;

    for (int y = 0; y <wys; y++)
    {
      ptr = (rgb *)bmp->ScanLine[y]; // ustawiam wskaznik na linie bmp

      for (int x = 0; x< szer; x++)  {
        memcpy((void*)&ptr[x][0],(void*)&pal[wyspa[x][y]][0],3); //wybieram x i kopiuje kolor ktory pokazuje wyspa

        if (trawa[x][y]>0)
        {
                tmpi=trawa[x][y];    //tam gdzie trawa to od 1-255, reszta 0 chyba)
                zi=tmpi*zielen;
                tmp2=(255.0-tmpi)/255;

                ptr[x][0]=ptr[x][0]*tmp2;     //tlumienie
                ptr[x][1]=ptr[x][1]*tmp2+zi;
                ptr[x][2]=ptr[x][2]*tmp2;

                if ((random(wegetacja)==0)&&(trawa[x][y]<255)) trawa[x][y]++;
        }

       /* if (trawa[x][y]<0)
        {
                ptr[x][0]=0;
                ptr[x][1]=0;                    //debug mode :)
                ptr[x][2]=255;
        }*/  //maska zabronionego terenu

      }
    }

    for (int n=0; n<Ktab.Length; n++)
        bmp->Canvas->Draw(Ktab[n].x-2,Ktab[n].y-2,bmpK);
    for (int n=0; n<Ltab.Length; n++)
        bmp->Canvas->Draw(Ltab[n].x-2,Ltab[n].y-2,bmpL);  //rysuje na srodku

        Lkrol->Text=Ktab.Length;
        Llis->Text=Ltab.Length;
        this->Edit40->Text=lis->z1;
        this->Edit43->Text=lis->z2;
        this->Edit41->Text=krol->z1;
        this->Edit42->Text=krol->z2;
        this->Edit44->Text=lis->z3;

        this->wybr_pstryk->Max=Ktab.Length-1;
        //this->wybr_pstryk->Position=0;
        if ((Ktab.Length>0)&&(Agent->ActivePage->PageIndex==4))
        {
          int n =wybr_pstryk->Position;

          bmp->Canvas->Draw(Ktab[n].x-3,Ktab[n].y-3,bmpW);
          switch (Ktab[n].status){
            case 3:this->w_stat_edit->Text="szuka pary"; break;
            case 2:this->w_stat_edit->Text="g³ód"; break;
            case 1:this->w_stat_edit->Text="ucieka"; break;
            case 0:this->w_stat_edit->Text="G£ÓD!"; break;
          }
          if (Ktab[n].plec) this->Edit23->Text="ON";
          else this->Edit23->Text="ONA";
          if (Ktab[n].ciaza>=0) this->Edit24->Text=Ktab[n].ciaza;
          else this->Edit24->Text="---";
          this->Edit28->Text= Ktab[n].wiek;
          this->Edit29->Text=krol->dl_zycia;
          this->Edit30->Text=Ktab[n].zoladek;
          this->Edit38->Text=Ktab[n].wielkosc;
        }

        this->wybr2_pstryk->Max=Ltab.Length-1;
        //this->wybr2_pstryk->Position=0;
        //if (this->wybr2_pstryk->Position>=Ltab.Length) this->wybr2_pstryk->Position--;
        if ((Ltab.Length>0)&&(Agent->ActivePage->PageIndex==5))
        {
          int n =wybr2_pstryk->Position;

          bmp->Canvas->Draw(Ltab[n].x-3,Ltab[n].y-3,bmpW);
          switch (Ltab[n].status){
            case 2:this->Edit33->Text="szuka pary"; break;
            case 1:this->Edit33->Text="goni królika"; break;
            case 0:this->Edit33->Text="krêcio³a"; break;
          }
          if (Ltab[n].plec) this->Edit32->Text="ON";
          else this->Edit32->Text="ONA";
          if (Ltab[n].ciaza>=0) this->Edit35->Text=Ltab[n].ciaza;
          else this->Edit35->Text="---";
          this->Edit37->Text= Ltab[n].wiek;
          this->Edit36->Text=lis->dl_zycia;
          this->Edit34->Text=Ltab[n].zoladek;
          this->Edit39->Text=Ltab[n].wielkosc;
        }

    float a=0,b=0,c=0;
    for (int n=0; n<Ltab.Length; n++)
    {
      a+=Ltab[n].wielkosc;
      b+=Ltab[n].glod;
    }
    a/=Ltab.Length;
    b/=Ltab.Length;

    this->Edit45->Text=a;
    this->Edit46->Text=b;

   a=0; b=0;
   for (int n=0; n<Ktab.Length; n++)
    {
      a+=Ktab[n].wielkosc;
      b+=Ktab[n].glod;
      c+=Ktab[n].starving;
    }
    a/=Ktab.Length;
    b/=Ktab.Length;
    c/=Ktab.Length;

    this->Edit47->Text=a;
    this->Edit48->Text=b;
    this->Edit49->Text=c;

    Okno->Canvas->Draw(4,4,bmp);    //odswieza (bmp na plotno)

    plus++;          //do fal
    rgb tmp;

            int mn;
            int mod=slona*sin(0.02*plus);  // oblicza sin z plusa
            while (mod<0) mod+=slona;
            for (int n=0; n<slona; n++)
            {
              mn=(n+mod)%slona;
              pal[n][0]=fala[mn][0];
              pal[n][1]=fala[mn][1];
              pal[n][2]=fala[mn][2];
            }

            mod=(slona/2)*sin(0.01*plus);
            while (mod<0) mod+=slona/2;
            for (int n=0; n<slona/2; n++)
            {
              mn=(n+mod)%(slona/2);
              pal[512+n][0]=falaS[mn][0];
              pal[512+n][1]=falaS[mn][1];
              pal[512+n][2]=falaS[mn][2];
            }
    krol->rusz();  //porusza zwierzatka
    lis->rusz();
}
//---------------------------------------------------------------------------


void __fastcall TOkno::But_generujClick(TObject *Sender)
{
  int zaok = PstrykZ->Position;
  if (zaok>=wys) zaok=wys-10;
  int x1,x2,y1,y2;
  int sy,sx;
  int x,y;

  for (x=0; x<szer; x++) for (y=0; y<wys; y++) wyspa[x][y]=slona;  //wypelniamy wyspe wysp¹

  y1=10;
  y2=10;
  x1=10;
  x2=10;

  for (x=0; x<szer; x++)
  {
    y1+=random(3)-1;
    y2+=random(3)-1;

    sy=(int)zaok*sin(x*M_PI/szer)-zaok;

    if (y1<1) y1=1;
    if (y2<1) y2=1;

    for (y=0; y<y1-sy; y++) wyspa[x][y]=0;        //ustawiamy wode
    for (y=wys-y2+sy; y<wys; y++) wyspa[x][y]=0;  //od dolu i od gory bo x
  }

  for (y=0; y<wys; y++)
  {
    x1+=random(3)-1;
    x2+=random(3)-1;

    sx=(int)zaok*sin(y*M_PI/wys)-zaok;

    if (x1<1) x1=1;
    if (x2<1) x2=1;

    for (x=0; x<x1-sx; x++) wyspa[x][y]=0;
    for (x=szer-x2+sx; x<szer; x++) wyspa[x][y]=0; //j.w.
  }

  fale();
}
//---------------------------------------------------------------------------



void __fastcall TOkno::But_zatokiClick(TObject *Sender)
{
  int x,y,c,n;
  for (int n=0; n<UpDown_Lzatok->Position; n++)
  {
    FIFO *Kol = new FIFO();

    c=0;      // :)
    do {
    x=random(szer);
    y=random(wys);
    c++;
    } while ((c<100000)&&(wyspa[x][y]<slona)); //szukam punktu na ladzie zeby zaczac BFSa
    Kol->push(x,y,0);

    int ran = UpDown_RZatok->Position;
    int wie = UpDown_WZatok->Position;
    while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          c++;
          if (c<wie){   //dziament
            if ((y>0)   &&(wyspa[x][y-1]>=slona)) { wyspa[x][y-1]=0; Kol->push(x,y-1,c);};
            if ((y<wys) &&(wyspa[x][y+1]>=slona)) { wyspa[x][y+1]=0; Kol->push(x,y+1,c);};
            if ((x<szer)&&(wyspa[x+1][y]>=slona)) { wyspa[x+1][y]=0; Kol->push(x+1,y,c);};
            if ((x>0)   &&(wyspa[x-1][y]>=slona)) { wyspa[x-1][y]=0; Kol->push(x-1,y,c);};
          } else for(int m=0; m<ran; m++)
          {
            wyspa[x][y]=0;
            x+=random(3)-1;   //farfocle
            y+=random(3)-1;
            if (y<0) y=0;
            if (y>=wys)  y=wys-1;
            if (x<0) x=0;
            if (x>=szer) x=szer-1;
          };
        };

    delete(Kol);
  }
  fale();
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_zmniejszClick(TObject *Sender)
{
  FIFO *Kol = new FIFO();
  int x,y,c;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]<slona) Kol->push(x,y,0);      // z wody

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          if ((y>0)&&(wyspa[x][y-1]>=slona))    wyspa[x][y-1]=0;
          if ((y<wys)&&(wyspa[x][y+1]>=slona))  wyspa[x][y+1]=0;
          if ((x<szer)&&(wyspa[x+1][y]>=slona)) wyspa[x+1][y]=0;
          if ((x>0)&&(wyspa[x-1][y]>=slona))    wyspa[x-1][y]=0;

          if ((y>1)&&(wyspa[x][y-1]>=slona))      wyspa[x][y-2]=0;
          if ((y<wys-1)&&(wyspa[x][y+1]>=slona))  wyspa[x][y+2]=0;
          if ((x<szer-1)&&(wyspa[x+1][y]>=slona)) wyspa[x+2][y]=0;
          if ((x>1)&&(wyspa[x-1][y]>=slona))      wyspa[x-2][y]=0;

          if ((y>0)&&(x<szer)&&(wyspa[x+1][y-1]>=slona))    wyspa[x+1][y-1]=0;
          if ((y<wys)&&(x<szer)&&(wyspa[x+1][y+1]>=slona))  wyspa[x+1][y+1]=0;
          if ((x>0)&&(y>0)&&(wyspa[x-1][y-1]>=slona))       wyspa[x-1][y-1]=0;
          if ((x>0)&&(y<wys)&&(wyspa[x-1][y+1]>=slona))     wyspa[x-1][y+1]=0;
        };

        delete(Kol);

  fale();
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_zwiekszClick(TObject *Sender)
{
 FIFO *Kol = new FIFO();
  int x,y,c;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]>=slona) Kol->push(x,y,0);      //z ladu

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          if ((y>1)&&(wyspa[x][y-1]<slona))    wyspa[x][y-1]=slona;
          if ((y<wys-2)&&(wyspa[x][y+1]<slona))  wyspa[x][y+1]=slona;
          if ((x<szer-2)&&(wyspa[x+1][y]<slona)) wyspa[x+1][y]=slona;
          if ((x>1)&&(wyspa[x-1][y]<slona))    wyspa[x-1][y]=slona;

          if ((y>2)&&(wyspa[x][y-1]<slona))      wyspa[x][y-2]=slona;
          if ((y<wys-3)&&(wyspa[x][y+1]<slona))  wyspa[x][y+2]=slona;
          if ((x<szer-3)&&(wyspa[x+1][y]<slona)) wyspa[x+2][y]=slona;
          if ((x>2)&&(wyspa[x-1][y]<slona))      wyspa[x-2][y]=slona;

          if ((y>1)&&(x<szer-2)&&(wyspa[x+1][y-1]<slona))    wyspa[x+1][y-1]=slona;
          if ((y<wys-2)&&(x<szer-2)&&(wyspa[x+1][y+1]<slona))  wyspa[x+1][y+1]=slona;
          if ((x>1)&&(y>1)&&(wyspa[x-1][y-1]<slona))       wyspa[x-1][y-1]=slona;
          if ((x>1)&&(y<wys-2)&&(wyspa[x-1][y+1]<slona))     wyspa[x-1][y+1]=slona;
        };

        delete(Kol);

  fale();
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_wygladzClick(TObject *Sender)
{
  FIFO *Kol = new FIFO();
  int x,y,c;
  int gladz=UpDown_gladz->Position;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]<slona) Kol->push(x,y,0);

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          if (c<gladz){
            c++;
            if ((y>0)&&(wyspa[x][y-1]>=slona))    {wyspa[x][y-1]=0; Kol->push(x,y-1,c);};
            if ((y<wys)&&(wyspa[x][y+1]>=slona))  {wyspa[x][y+1]=0; Kol->push(x,y+1,c);};
            if ((x<szer)&&(wyspa[x+1][y]>=slona)) {wyspa[x+1][y]=0; Kol->push(x+1,y,c);};
            if ((x>0)&&(wyspa[x-1][y]>=slona))    {wyspa[x-1][y]=0; Kol->push(x-1,y,c);};

            if ((y>1)&&(wyspa[x][y-1]>=slona))      wyspa[x][y-2]=0;
            if ((y<wys-1)&&(wyspa[x][y+1]>=slona))  wyspa[x][y+2]=0;
            if ((x<szer-1)&&(wyspa[x+1][y]>=slona)) wyspa[x+2][y]=0;
            if ((x>1)&&(wyspa[x-1][y]>=slona))      wyspa[x-2][y]=0;

            if ((y>0)&&(x<szer)&&(wyspa[x+1][y-1]>=slona))    {wyspa[x+1][y-1]=0; Kol->push(x+1,y-1,c);};
            if ((y<wys)&&(x<szer)&&(wyspa[x+1][y+1]>=slona))  {wyspa[x+1][y+1]=0; Kol->push(x+1,y+1,c);};
            if ((x>0)&&(y>0)&&(wyspa[x-1][y-1]>=slona))       {wyspa[x-1][y-1]=0; Kol->push(x-1,y-1,c);};
            if ((x>0)&&(y<wys)&&(wyspa[x-1][y+1]>=slona))     {wyspa[x-1][y+1]=0; Kol->push(x-1,y+1,c);};
          }
        };

//part 2

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]>=slona) Kol->push(x,y,0);

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          if (c<gladz){
            c++;
            if ((y>0)&&(wyspa[x][y-1]<slona))    {wyspa[x][y-1]=slona; Kol->push(x,y-1,c);};
            if ((y<wys)&&(wyspa[x][y+1]<slona))  {wyspa[x][y+1]=slona; Kol->push(x,y+1,c);};
            if ((x<szer)&&(wyspa[x+1][y]<slona)) {wyspa[x+1][y]=slona; Kol->push(x+1,y,c);};
            if ((x>0)&&(wyspa[x-1][y]<slona))    {wyspa[x-1][y]=slona; Kol->push(x-1,y,c);};

            if ((y>1)&&(wyspa[x][y-1]<slona))      wyspa[x][y-2]=slona;
            if ((y<wys-1)&&(wyspa[x][y+1]<slona))  wyspa[x][y+2]=slona;
            if ((x<szer-1)&&(wyspa[x+1][y]<slona)) wyspa[x+2][y]=slona;
            if ((x>1)&&(wyspa[x-1][y]<slona))      wyspa[x-2][y]=slona;

            if ((y>0)&&(x<szer)&&(wyspa[x+1][y-1]<slona))    {wyspa[x+1][y-1]=slona; Kol->push(x+1,y-1,c);};
            if ((y<wys)&&(x<szer)&&(wyspa[x+1][y+1]<slona))  {wyspa[x+1][y+1]=slona; Kol->push(x+1,y+1,c);};
            if ((x>0)&&(y>0)&&(wyspa[x-1][y-1]<slona))       {wyspa[x-1][y-1]=slona; Kol->push(x-1,y-1,c);};
            if ((x>0)&&(y<wys)&&(wyspa[x-1][y+1]<slona))     {wyspa[x-1][y+1]=slona; Kol->push(x-1,y+1,c);};
          }
        };

        delete(Kol);

  fale();
}
//---------------------------------------------------------------------------


void __fastcall TOkno::Edit_plazaChange(TObject *Sender)
{
  pallad();
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_zat2Click(TObject *Sender)
{
  int x,y,c,n;
  for (int n=0; n<UpDown_Lzatok->Position; n++)
  {
    FIFO *Kol = new FIFO();

    c=0;
    do {
    x=random(szer);
    y=random(wys);
    c++;
    } while ((c<100000)&&((wyspa[x][y]<slona)||(wyspa[x][y]>42)));
    Kol->push(x,y,0);

    int ran = UpDown_RZatok->Position;
    int wie = UpDown_WZatok->Position;
    while (!Kol->empty())
        {
          Kol->pop(x,y,c);
          c++;
          if ((c<wie)&&(wyspa[x][y]<=42)){
            if ((y>0)   &&(wyspa[x][y-1]>=slona)) { wyspa[x][y-1]=0; Kol->push(x,y-1,c);};
            if ((y<wys) &&(wyspa[x][y+1]>=slona)) { wyspa[x][y+1]=0; Kol->push(x,y+1,c);};
            if ((x<szer)&&(wyspa[x+1][y]>=slona)) { wyspa[x+1][y]=0; Kol->push(x+1,y,c);};
            if ((x>0)   &&(wyspa[x-1][y]>=slona)) { wyspa[x-1][y]=0; Kol->push(x-1,y,c);};
          } else for(int m=0; m<ran; m++)
          {
            wyspa[x][y]=0;
            x+=random(3)-1;
            y+=random(3)-1;
            if (y<0) y=0;
            if (y>=wys)  y=wys-1;
            if (x<0) x=0;
            if (x>=szer) x=szer-1;
          };
        };

    delete(Kol);
  }
  fale();
}
//---------------------------------------------------------------------------


void __fastcall TOkno::Button1Click(TObject *Sender)
{
  this->Panel_wnetrze->Visible=false;
  fale();
  ziarno();
}
//---------------------------------------------------------------------------


void __fastcall TOkno::Button2Click(TObject *Sender)
{
  this->Panel_wnetrze->Visible=true;
  fale();
}
//---------------------------------------------------------------------------

void __fastcall TOkno::PstrykZChanging(TObject *Sender, bool &AllowChange)
{
 if (PstrykZ->Position>=wys) PstrykZ->Position=wys-20;
  But_generujClick(this);
}
//---------------------------------------------------------------------------



void __fastcall TOkno::But_okClick(TObject *Sender)
{
        int x,y;

  if (poziom==0)
  {

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
            if (wyspa[x][y]<slona) wyspa[x][y]+=512;

// <BFS> woda slodka
        FIFO *Kol = new FIFO();
        int c;

       Kol->push(0,0,0);       //puszczamy BFSa od rogu

        while (!Kol->empty())
        {
          Kol->pop(x,y,c);

          if ((y>0)&&(wyspa[x][y-1]>=512))    {Kol->push(x,y-1,0); wyspa[x][y-1]-=512;};
          if ((y<wys)&&(wyspa[x][y+1]>=512))  {Kol->push(x,y+1,0); wyspa[x][y+1]-=512;};
          if ((x<szer)&&(wyspa[x+1][y]>=512)) {Kol->push(x+1,y,0); wyspa[x+1][y]-=512;};
          if ((x>0)&&(wyspa[x-1][y]>=512))    {Kol->push(x-1,y,0); wyspa[x-1][y]-=512;};
        };

        delete(Kol);
// <</BFS>

        this->Reset_trawyClick(this);
        this->Wegetacja_pstrykClick(this,NULL);

        Bog->Visible=false;
        But_powrot->Enabled=true;
        Krolik->Visible=true;
        pallad();

        krol->generuj(UpDown_ileK->Position,UpDown_stadaK->Position,UpDown_rozpK->Position);
    } else if (poziom==1)
    {
        Krolik->Visible=false;
        Lisek->Visible=true;

        lis->generuj(UpDown_ileL->Position,UpDown_stadaL->Position,UpDown_rozpL->Position);
    } else if (poziom==2)
    {
        Lisek->Visible=false;
        Informer->Visible=true;

       But_ok->Enabled=false;
    }
    poziom++;
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_powrotClick(TObject *Sender)
{
        int x,y;

  if (poziom==1)
  {
        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
          {
            if (wyspa[x][y]>=512) wyspa[x][y]=0;
            trawa[x][y]=0;
          }

          krol->czysc();

          fale();

          Bog->Visible=true;
          But_powrot->Enabled=false;
          Krolik->Visible=false;
          pallad();
   } else if (poziom==2)
   {
          lis->czysc();

          Krolik->Visible=true;
          Lisek->Visible=false;

   } else if (poziom==3)
   {
          Lisek->Visible=true;
          Informer->Visible=false;

          But_ok->Enabled=true;
   }
   poziom--;
}
//---------------------------------------------------------------------------


void __fastcall TOkno::But_genKClick(TObject *Sender)
{
   krol->generuj(UpDown_ileK->Position,UpDown_stadaK->Position,UpDown_rozpK->Position);
}
//---------------------------------------------------------------------------

void __fastcall TOkno::But_genLClick(TObject *Sender)
{
   lis->generuj(UpDown_ileL->Position,UpDown_stadaL->Position,UpDown_rozpL->Position);
}
//---------------------------------------------------------------------------

void __fastcall TOkno::Button3Click(TObject *Sender)
{
        for (int n=0; n<szer; n++)
                for (int m=0; m<wys; m++)
                        if (trawa[n][m]>0) trawa[n][m]=255;        
}
//---------------------------------------------------------------------------




void __fastcall TOkno::BitBtn2Click(TObject *Sender)
{
        for (int n=0; n<szer; n++)
                for (int m=0; m<wys; m++)
                        if (trawa[n][m]>0) trawa[n][m]=1;         
}
//---------------------------------------------------------------------------

void __fastcall TOkno::Reset_trawyClick(TObject *Sender)
{
   int x,y;
        int min = slona+UpDown_plaza->Position;
        int max =slona+UpDown_plaza->Position+UpDown_trawa->Position+64;
        int max2=slona+UpDown_plaza->Position+UpDown_trawa->Position+64+UpDown_snieg->Position+32;
        int a;

        for (x=0 ; x<szer; x++)
          for (y=0 ; y<wys ; y++)
          {
            if (wyspa[x][y]>=512) wyspa[x][y]=(wyspa[x][y]-512)/2+512;

            a=wyspa[x][y];
            if ((a>=min)&&(a<max)) if (a<min+32) trawa[x][y]=8*(a-min);
                                else if (a>max-32) trawa[x][y]=8*(max-a);
                                      else trawa[x][y]=255;

            else if (a<=slona) trawa[x][y]=-255;
                 else if (a>=max) if (a>=max2) trawa[x][y]=max-a;
                                                else trawa[x][y]=0;
                                  else trawa[x][y]=0;

          }
}
//---------------------------------------------------------------------------

void __fastcall TOkno::Wegetacja_pstrykClick(TObject *Sender,
      TUDBtnType Button)
{
  wegetacja=this->Wegetacja_pstryk->Position;        
}
//---------------------------------------------------------------------------

void __fastcall TOkno::Edit7Change(TObject *Sender)
{
   this->Wegetacja_pstrykClick(this,NULL);        
}
//---------------------------------------------------------------------------




void __fastcall TOkno::vk_pstrykClick(TObject *Sender, TUDBtnType Button)
{

   krol->vk=0.1*this->vk_pstryk->Position;
   krol->metabolizm=this->metaK_pstryk->Position;
   krol->kes=this->kesK_pstryk->Position;
   krol->pojemnoscZ=this->zoladekK_pstryk->Position;
   krol->glod=this->glodK_pstryk->Position;
   krol->starving=this->starvingK_pstryk->Position;
   krol->pole_widz=this->detekcjaK_pstryk->Position;
   krol->dl_zycia=this->zycieK_pstryk->Position;
   krol->wiek_dojrz=this->dojrzaloscK_pstryk->Position;
   krol->dl_ciazy=this->ciazaK_pstryk->Position;
}
//---------------------------------------------------------------------------


void __fastcall TOkno::vl_pstrykClick(TObject *Sender, TUDBtnType Button)
{

   lis->vl=0.1*this->vl_pstryk->Position;
   lis->metabolizm=this->metaL_pstryk->Position;
   lis->kes=this->wodzL_pstryk->Position;
   lis->pojemnoscZ=this->zoladekL_pstryk->Position;
   lis->glod=this->glodL_pstryk->Position;
   lis->dl_zycia=this->zycieL_pstryk->Position;
   lis->wiek_dojrz=this->dojrzaloscL_pstryk->Position;
   lis->dl_ciazy=this->ciazaL_pstryk->Position;
   
}
//---------------------------------------------------------------------------

void __fastcall TOkno::Edit18Change(TObject *Sender)
{
  this->vl_pstrykClick(this,NULL);
}
//---------------------------------------------------------------------------



void __fastcall TOkno::Edit9Change(TObject *Sender)
{
this->vk_pstrykClick(this,NULL);        
}
//---------------------------------------------------------------------------



