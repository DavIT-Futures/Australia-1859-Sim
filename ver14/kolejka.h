//---------------------------------------------------------------------------

#ifndef kolejkaH
#define kolejkaH
//---------------------------------------------------------------------------
#include <stddef.h>

class FIFO{

private:

  struct TEl{
    int x,y,c;
    TEl *nast;
  };

  TEl *head;
  TEl *tail;

public:

  FIFO()
  {
    head=NULL;
  };

  ~FIFO()          //oproznia kolejke przy zwolnieniu pamieci
  {
    int x,y,c;
    while (!empty()) pop(x,y,c);
  };

  void push(int nx, int ny, int nc)
  {
      if (head==NULL){
        tail = new TEl;
        head=tail;
      } else {
        tail->nast=new TEl;
        tail=tail->nast;
      }
      tail->nast=NULL;
      tail->x=nx;
      tail->y=ny;
      tail->c=nc;
  };

  void pop(int &nx, int &ny, int &nc)
  {
    if (head!=NULL)
    {
      nx=head->x;
      ny=head->y;
      nc=head->c;

      TEl *tmp = head;
      head=head->nast;
      delete(tmp);
    }
  };

  bool empty()            //sprawdza czy pusta
  {
    if (head==NULL) return true;
    else return false;
  }

};//  </KOLEJKA>

#endif
