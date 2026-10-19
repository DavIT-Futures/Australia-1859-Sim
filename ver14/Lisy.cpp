//---------------------------------------------------------------------------
#pragma hdrstop

#include "math.h"
#include "Lisy.h"

#include "glowny.h"
//---------------------------------------------------------------------------
Lisy::Lisy(int **pole,int szer,int wys,DynamicArray <Krolik> *Ktab, DynamicArray <Lis> *Ltab)
{
        this->pole=pole;
        this->szer=szer;
        this->wys=wys;
        this->Ktab=Ktab;
        this->Ltab=Ltab;
        timer=0;

    this->vl = 2;
    this->metabolizm = 3;
    this->kes = 1500;
    this->zoladek = 2000;
    this->glod = 1000;

    this->dl_zycia = 3000;
    this->wiek_dojrz = 30;
    this->dl_ciazy = 30;
}

void Lisy::czysc()
{
  Ltab->Length=0;
}

void Lisy::generuj(int l,int s, int r)
{
        int x,y,sx,sy;
        Ltab->Length=l;
        for (int n=0; n<l; n++)
        {
          do{
                x=random(szer);
                y=random(wys);
            } while (pole[x][y]<=0);
            (*Ltab)[n].x=x;
            (*Ltab)[n].y=y;
            (*Ltab)[n].zoladek=zoladek/2+random(zoladek/2);
            (*Ktab)[n].plec=true;
            if (random(2)==0) (*Ktab)[n].plec=false;
            (*Ktab)[n].wiek=0;
            }
}
void Lisy::stat(int n)
{
  (*Ltab)[n].status=2;
   if ((*Ltab)[n].zoladek<glod) (*Ltab)[n].status=1;
   if (Ktab->Length<1) (*Ltab)[n].status=0;
}

void Lisy::rusz()
{
  int n;
  for (n=0; n<Ltab->Length; n++) stat(n);
  for (n=0; n<Ltab->Length; n++) rusz(n);
  n=0;
  while (n<Ltab->Length) {
    if (((*Ltab)[n].zoladek<0)||((*Ltab)[n].wiek>=dl_zycia))
    {
        (*Ltab)[n]=(*Ltab)[Ltab->Length-1];
        Ltab->Length--;
        n--;
    };
    n++;
  };
  timer++;
}

void Lisy::dodaj(float x,float y,int zarcie)
{
           Ltab->Length++;
          (*Ltab)[Ltab->Length-1].x=x;
          (*Ltab)[Ltab->Length-1].y=y;
          (*Ltab)[Ltab->Length-1].wiek=0;
          (*Ltab)[Ltab->Length-1].zoladek=zarcie;
          (*Ltab)[Ltab->Length-1].plec=true;
           if (random(2)==0) (*Ltab)[Ltab->Length-1].plec=false;
           (*Ltab)[Ltab->Length-1].ciaza=-1;
          stat(Ltab->Length-1);
 
}

void Lisy::rusz(int n)
{
  float min=99999,odl,dx=0,dy=0,x,y,i=-1;
  if ((*Ltab)[n].status==1)
  {
    for (int m=0; m<Ktab->Length; m++)
    {
      dx=(*Ltab)[n].x-(*Ktab)[m].x;
      dy=(*Ltab)[n].y-(*Ktab)[m].y;
      odl=dx*dx+dy*dy;
      if (odl<min)
      {
        min=odl;
        x=(*Ktab)[m].x;
        y=(*Ktab)[m].y;
        i=m;
      }
    }

    if (i>=0)
    {
     min=sqrt(min);
     dx=(*Ltab)[n].x-(*Ktab)[i].x;
     dy=(*Ltab)[n].y-(*Ktab)[i].y;

     dx=vl*dx/min; dy=vl*dy/min;

     x=(*Ltab)[n].x-dx;
     y=(*Ltab)[n].y-dy;

     if (min<3)
     {
       (*Ktab)[i]=(*Ktab)[Ktab->Length-1];
       Ktab->Length--;
       (*Ltab)[n].zoladek=kes;
     }
    }
    }
    if ((*Ltab)[n].status==0)
    {
      x=(*Ltab)[n].x+2*sin(timer/2+n);
      y=(*Ltab)[n].y+2*cos(timer/2+n);
    }

    if ((*Ltab)[n].status==2)
    {
      float min=999999999,dx=0,dy=0,odl;
      int i=-1;

      for (int m=0; m<Ltab->Length; m++)
        if ((m!=n)&&((*Ltab)[m].status==2)&&((*Ltab)[n].plec!=(*Ltab)[m].plec)
        &&((*Ltab)[m].wiek>wiek_dojrz))
        {
          dx=(*Ltab)[n].x-(*Ltab)[m].x;
          dy=(*Ltab)[n].y-(*Ltab)[m].y;
          odl=dx*dx+dy*dy;
          if (odl<min)
          {
            min=odl;
            x=(*Ltab)[m].x;
            y=(*Ltab)[m].y;
            i=m;
          }
        }
      if (min>0) min=sqrt(min);
      if (i>=0)
      {
         if (min>2){
         dx=(*Ltab)[n].x-(*Ltab)[i].x;
         dy=(*Ltab)[n].y-(*Ltab)[i].y;

         dx=vl*dx/min; dy=vl*dy/min;

         } else
         {
           dx=random(3)-1;
           dy=random(3)-1;
         }

         x=(*Ltab)[n].x-dx;
         y=(*Ltab)[n].y-dy;

          if ((min<10)&&(Ltab->Length<999)&&((*Ltab)[n].ciaza<0)&&((*Ltab)[n].plec==false))
          (*Ltab)[n].ciaza=dl_ciazy;
      }
    }
    if (pole[(int)x][(int)y]>=0)
    {
      (*Ltab)[n].x=x;
      (*Ltab)[n].y=y;
    }

   if ((*Ltab)[n].ciaza==0)
        {
           dodaj((*Ltab)[n].x,(*Ltab)[n].y,(*Ltab)[n].zoladek/=3);
          (*Ltab)[n].zoladek/=3;
          (*Ltab)[n].ciaza=-1;
        }

  (*Ltab)[n].zoladek-=metabolizm;
  (*Ltab)[n].wiek++;
//(*Ltab)[n].wiek=100;
  if ((*Ltab)[n].ciaza>=0) (*Ltab)[n].ciaza--;
}
#pragma package(smart_init)
