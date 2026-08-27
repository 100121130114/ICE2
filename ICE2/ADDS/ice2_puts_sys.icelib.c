#include <stdio.h>

//var conf
 //basic
extern unsigned int ln; //longuitud de los numeros
extern unsigned int lc; //longuitud de los comandos
extern unsigned int lv; //longuitud de variables
extern unsigned int ls; //longuitud de script
extern unsigned int lj; //longuitud de jump
extern unsigned int ccv; //cantidad de CVAR
extern unsigned int lcv; //longuitud de los CVAR
//var save
 //basic
extern unsigned int* anv(unsigned int nde,unsigned int com,unsigned int dat);
extern void error(unsigned int errsig);

void input_sys(unsigned int x){
 switch(*anv(0,x,1)){
  case 0:{//scan num
   scanf("%u",anv(0,x,2));
  }break;
  default:{
   error(46);
  }break;
 };
 return;
}

void output_sys(unsigned int x){
 switch(*anv(0,x,1)){
  case 0:{//print num
   printf("%u",*anv(0,x,2));
  }break;
  case 1:{//print char
   printf("%c",(char)*anv(0,x,2));
  }break;
  case 2:{//print num-str
   for(unsigned int a=0;a<sizeof(unsigned int)/sizeof(char);a++){
    printf("%c",((char*)anv(0,x,2))[a]);
   }
  }break;
  case 3:{//print bin
   printf("%b",*anv(0,x,2));
  }break;
  case 4:{//print hex
   printf("%X",*anv(0,x,2));
  }break;
  case 5:{//print n!
   printf("\n");
  }break;
  case 6:{//print t!
   printf("\t");
  }break;
  case 7:{//print opcional_base_limited
   char out[ln];
   printf("%s",intchar(*anv(0,x,2),*anv(0,x,3),ln,out,'0','9','A'));
  }break;
  case 8:{//print opcional_base
   char out[ln];
   printf("%s",intchar(*anv(0,x,2),*anv(0,x,3),ln,out,'0','9','9'));
  }break;
  case 9:{//print own_base
   char out[ln];
   printf("%s",intchar(*anv(0,x,2),*anv(0,x,3),ln,out,*anv(0,x,4),*anv(0,x,5),*anv(0,x,6)));
  }break;
  default:{
   error(47);
  }break;
 };
 return;
}

void plugin_sys(unsigned int x){
 switch(*anv(0,x,1)){
  case 0:{//** OUT_VAR IN1_DATE IN2_DATE
   *anv(0,x,2)=lvr(*anv(0,x,3),*anv(0,x,4));
  }break;
  case 1:{//**= OUT_VAR IN_DATE
   *anv(0,x,2)=lvr(*anv(0,x,2),*anv(0,x,3));
  }break;
  default:{
   error(48);
  }break;
 };
 return;
}
