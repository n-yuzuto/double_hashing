#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "open_addressing.h"

int main(void) {
  double t1,t2;
  const int trynum =100000;
  int len=3571;
  DictOpenAddr *test_dict = create_dict(len);
  
  float a=0.0;
  int lim=len*a;
  int s;
  

  int i;
  srand(10);
  for (i=0;i<lim;i++){
      int d=rand()%trynum;
      insert_hash(test_dict,d);
  }
  srand(10);
  int search=rand()%trynum;

  t1=get_realtime();
  s=search_hash(test_dict,search);
  t2=get_realtime();

  double res=get_realtime();

  
  printf("占有率:%f  ",a);
  printf("実行時間: %G s\n",t2-t1);
  printf("分解能: %G s\n",res);


  delete_dict(test_dict);


  return EXIT_SUCCESS;

}
