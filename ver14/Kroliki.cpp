//---------------------------------------------------------------------------
#pragma hdrstop

#include "Kroliki.h"
#include "math.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Kroliki::Kroliki(int **pole,int szer,int wys,DynamicArray <Krolik> *Ktab, DynamicArray <Lis> *Ltab)
{
        this->pole=pole;
        this->szer=szer;
        this->wys=wys;
        this->Ktab=Ktab;
        this->Ltab=Ltab;

    this->vk = 1;
    this->metabolizm = 4;
    this->kes = 64;
    this->zoladek = 100;
    this->glod = 60;
    this->starving = 20;

    this->pole_widz = 25;

    this->dl_zycia = 100;
    this->wiek_dojrz = 21;
    this->dl_ciazy = 20;
}

void Kroliki::czysc()
{
  Ktab->Length=0;
}

void Kroliki::def_par(int n, int x, int y, int zoladek)
{
            (*Ktab)[n].x=x;
            (*Ktab)[n].y=y;
            (*Ktab)[n].zoladek=zoladek;
            (*Ktab)[n].wiek=0;
            (*Ktab)[n].plec=true;
            if (random(2)==0) (*Ktab)[n].plec=false;
            (*Ktab)[n].ciaza=-1;
}

void Kroliki::generuj(int l,int s, int r)
{
        int x,y,sx,sy;
        Ktab->Length=l;
        for (int n=0; n<l; n++)
        {
          do{
                x=random(szer);
                y=random(wys);
            } while (pole[x][y]<=0);
          def_par(n,x,y,zoladek/2);
        }
}

void Kroliki::rusz()
{
  int n;
  for (n=0; n<Ktab->Length; n++) stat(n);
  for (n=0; n<Ktab->Length; n++) rusz(n);
  
  n=0;
  while (n<Ktab->Length) {
    if (((*Ktab)[n].zoladek<0)||((*Ktab)[n].wiek>dl_zycia))        //zgon(dek)
    {
        (*Ktab)[n]=(*Ktab)[Ktab->Length-1];
        Ktab->Length--;
        n--;
    };
    n++;
  };
}

void Kroliki::stat(int n)
{
  if ((*Ktab)[n].wiek>wiek_dojrz)(*Ktab)[n].status=3; else (*Ktab)[n].status=2;
  if ((*Ktab)[n].zoladek<glod) (*Ktab)[n].status=2;

  float min=99999,odl,dx=0,dy=0,x,y,i=-1;

    for (int m=0; m<Ltab->Length; m++)
    {
      dx=(*Ktab)[n].x-(*Ltab)[m].x;
      dy=(*Ktab)[n].y-(*Ltab)[m].y;
      odl=dx*dx+dy*dy;
      if (odl<min)
      {
        min=odl;
        x=(*Ltab)[m].x;
        y=(*Ltab)[m].y;
        i=m;
      }
    }
    if (i>=0) min=sqrt(min);

  if (min<pole_widz)
  {
   (*Ktab)[n].status=1;
   (*Ktab)[n].index=i;
  }
  if ((*Ktab)[n].zoladek<=starving) (*Ktab)[n].status=0;
}
void Kroliki::dodaj(float x,float y,int zarcie)
{
         Ktab->Length++;
         def_par(Ktab->Length-1,x,y,zarcie);
         stat(Ktab->Length-1);
}
void Kroliki::rusz(int n)
{
  float x=(*Ktab)[n].x;
  float y=(*Ktab)[n].y;

  if (((*Ktab)[n].status==0)||((*Ktab)[n].status==2))
  {
    if (pole[(int)x][(int)y]<2)
    {
      int t[10][2];

      int ile=1;
      t[0][0]=(*Ktab)[n].x;
      t[0][1]=(*Ktab)[n].y;    //inicjalizujemy poszukiwanie trawy
      int max=pole[t[0][0]][t[0][1]];

      for (int a=-1; a<=1; a++)
        for (int b=-1; b<=1; b++)
        {
          if (pole[a+(int)(*Ktab)[n].x][b+(int)(*Ktab)[n].y]>max)
          {
            ile=1;
            t[0][0]=(*Ktab)[n].x+a;
            t[0][1]=(*Ktab)[n].y+b;
            max=pole[t[0][0]][t[0][1]];
          }
          else if (pole[a+(int)(*Ktab)[n].x][b+(int)(*Ktab)[n].y]==max)
          {
            t[ile][0]=(*Ktab)[n].x+a;
            t[ile][1]=(*Ktab)[n].y+b;
            ile++;
          }
        }

        max=random(ile);
        x=t[max][0];
        y=t[max][1];
        
       } else
       {
          if (pole[(int)x][(int)y]<kes+1) { (*Ktab)[n].zoladek+=pole[(int)x][(int)y]; pole[(int)x][(int)y]=1;}
          else {(*Ktab)[n].zoladek+=kes; pole[(int)x][(int)y]-=kes;}
       }
    };

    if ((*Ktab)[n].status==1)
    {
        float min,dx=0,dy=0;
        int i=(*Ktab)[n].index;

        dx=(*Ktab)[n].x-(*Ltab)[i].x;
        dy=(*Ktab)[n].y-(*Ltab)[i].y;

        min=dx*dx+dy*dy;
        min=sqrt(min);

        dx=vk*dx/min; dy=vk*dy/min;

        x=(*Ktab)[n].x+dx;
        y=(*Ktab)[n].y+dy;
    };

    if ((*Ktab)[n].status==3)
    {
      float min=999999999,dx=0,dy=0,odl;
      int i=-1;

      for (int m=0; m<Ktab->Length; m++)
        if ((m!=n)&&((*Ktab)[m].status==3)&&((*Ktab)[n].plec!=(*Ktab)[m].plec)
        &&((*Ktab)[m].wiek>wiek_dojrz))
        {
          dx=(*Ktab)[n].x-(*Ktab)[m].x;
          dy=(*Ktab)[n].y-(*Ktab)[m].y;
          odl=dx*dx+dy*dy;
          if (odl<min)
          {
            min=odl;
            x=(*Ktab)[m].x;
            y=(*Ktab)[m].y;
            i=m;
          }
        }
      if (min>0) min=sqrt(min);
      if (i>=0)
      {
         if (min>3){
         dx=(*Ktab)[n].x-(*Ktab)[i].x;
         dy=(*Ktab)[n].y-(*Ktab)[i].y;

         dx=vk*dx/min; dy=vk*dy/min;

         } else
         {
           dx=random(3)-1;
           dy=random(3)-1;
         }

         x=(*Ktab)[n].x-dx;
         y=(*Ktab)[n].y-dy;

        if ((min<5)&&(Ktab->Length<999)&&((*Ktab)[n].ciaza<0)&&((*Ktab)[n].plec==false))
          (*Ktab)[n].ciaza=dl_ciazy;

      }else
      {
        x=(*Ktab)[n].x;
        y=(*Ktab)[n].y;
      }
    };
    if (y<2) y=2;
    if (x<2) x=2;
    if (x>szer-2) x=szer-2;
    if (y>wys-2) y=wys-2;

    if (pole[(int)x][(int)y]>=0)
    {
      (*Ktab)[n].x=x;
      (*Ktab)[n].y=y;
    }

    if ((*Ktab)[n].ciaza==0)
        {
           dodaj((*Ktab)[n].x,(*Ktab)[n].y,(*Ktab)[n].zoladek/=3);
          (*Ktab)[n].zoladek/=3;
          (*Ktab)[n].ciaza=-1;
        }


   (*Ktab)[n].zoladek-=metabolizm;
   (*Ktab)[n].wiek++;
   if ((*Ktab)[n].ciaza>=0) (*Ktab)[n].ciaza--;
}

void Kroliki::kill(int n)
{
       (*Ktab)[n]=(*Ktab)[Ktab->Length-1];
       Ktab->Length--;
}
