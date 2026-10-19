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

        this->wielkosc=1;
        this->evol=0.5;

        this->z1=0;
        this->z2=0;
        this->z3=0;
}

void Lisy::czysc()
{
  Ltab->Length=0;
}

void Lisy::def_par(int n,int x,int y,int zarcie)
{
            (*Ltab)[n].x=x;
            (*Ltab)[n].y=y;
            (*Ltab)[n].zoladek=zarcie;
            (*Ltab)[n].wiek=0;
            (*Ltab)[n].plec=true;
            if (random(2)==0) (*Ltab)[n].plec=false;
            (*Ltab)[n].ciaza=-1;
}

void Lisy::evolve(int n)
{
  (*Ltab)[n].wielkosc=(*Ltab)[n].wielkosc+evol*(random(201)-100)*(*Ltab)[n].wielkosc/100;
  (*Ltab)[n].glod=(*Ltab)[n].glod+evol*(random(201)-100)*(*Ltab)[n].glod/100;

            (*Ltab)[n].pojemnoscZ=this->pojemnoscZ*(*Ltab)[n].wielkosc;
            (*Ltab)[n].vl=this->vl*(*Ltab)[n].wielkosc;
            (*Ltab)[n].metabolizm=this->metabolizm*(*Ltab)[n].wielkosc;
};

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
          def_par(n,x,y,pojemnoscZ/2+random(pojemnoscZ/2));
          (*Ltab)[n].wiek=random(0.2*dl_zycia);

          (*Ltab)[n].wielkosc=this->wielkosc;
          (*Ltab)[n].glod=this->glod;
          evolve(n);
        }
}
void Lisy::stat(int n)
{
  (*Ltab)[n].status=2;
   if (((*Ltab)[n].zoladek<(*Ltab)[n].glod)||((*Ltab)[n].ciaza>=0)) (*Ltab)[n].status=1;
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
        if ((*Ltab)[n].zoladek<0) z1++;
        else z2++;

        (*Ltab)[n]=(*Ltab)[Ltab->Length-1];
        Ltab->Length--;
        n--;
    };
    n++;
  };
  timer++;
}

void Lisy::dodaj(float x,float y,int zarcie,int kto)
{
          Ltab->Length++;
          def_par(Ltab->Length-1,x,y,zarcie);

            (*Ltab)[Ltab->Length-1].glod=(*Ltab)[kto].plod->glod;
            (*Ltab)[Ltab->Length-1].wielkosc=(*Ltab)[kto].plod->wielkosc;
            delete((*Ltab)[kto].plod);

          evolve(Ltab->Length-1);
          stat(Ltab->Length-1);

}

void Lisy::rusz(int n)
{
   float vl = (*Ltab)[n].vl;

 float min=99999,odl,dx=0,dy=0,x,y,i=-1;

  x=(*Ltab)[n].x;
  y=(*Ltab)[n].y;

  if ((*Ltab)[n].status==1)
  {
    i=-1;
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
     if (sqrt(dx*dx+dy*dy)>vl)
     { dx=vl*dx/min; dy=vl*dy/min; };

     x=(*Ltab)[n].x-dx;
     y=(*Ltab)[n].y-dy;

     if (min<3)
     {
       (*Ktab)[i]=(*Ktab)[Ktab->Length-1];
       (*Ltab)[n].zoladek=(*Ktab)[Ktab->Length-1].wielkosc*kes;
       Ktab->Length--;
       z3++;
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
                if (sqrt(dx*dx+dy*dy)) { dx=vl*dx/min; dy=vl*dy/min;};
         }

         x=(*Ltab)[n].x-dx;
         y=(*Ltab)[n].y-dy;

          if ((min<10)&&(Ltab->Length<999)&&((*Ltab)[n].ciaza<0)&&((*Ltab)[n].plec==false))
          {
            (*Ltab)[n].ciaza=dl_ciazy;
            (*Ltab)[n].plod=new PlodL();

            (*Ltab)[n].plod->wielkosc=((*Ltab)[n].wielkosc+(*Ltab)[i].wielkosc)/2;
            (*Ltab)[n].plod->glod=((*Ltab)[n].glod+(*Ltab)[i].glod)/2;
          }
      }  else
         {
           dx=random(3)-1;
           dy=random(3)-1;
         x=(*Ltab)[n].x-dx;
         y=(*Ltab)[n].y-dy;

         }
    }
    if (pole[(int)x][(int)y]>=0)
    {
      (*Ltab)[n].x=x;
      (*Ltab)[n].y=y;
    }

   if ((*Ltab)[n].ciaza==0)
        {
           dodaj((*Ltab)[n].x,(*Ltab)[n].y,(*Ltab)[n].zoladek/=3,n);
          (*Ltab)[n].zoladek/=3;
          (*Ltab)[n].ciaza=-1;
        }

  (*Ltab)[n].zoladek-=(*Ltab)[n].metabolizm;
  (*Ltab)[n].wiek++;
  if ((*Ltab)[n].ciaza>=0) (*Ltab)[n].ciaza--;

}
#pragma package(smart_init)
