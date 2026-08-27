#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//var conf, general
unsigned int ca=1;//cantidad de autos
unsigned int lc=999;//longuitutd de los comandos
unsigned int ll=7;//longuitud de la lista
unsigned int ls=999;//longuitud de los scripts
unsigned int lv=9999;//cantidad de variables
unsigned int car=9999;//cantidad de arrays
unsigned int la=9999;//lontuitud de las variables array
//var save, general
unsigned int* plist;//lista
char* pcom;//script
unsigned int* pvar;//variables
unsigned int* parr;//arrays
unsigned int trash=0;

char* com(unsigned int a, unsigned int b){
 if(a>=ls){return (char *)&trash;}
 if(b>=lc){return (char *)&trash;}
 return &pcom[a*ls+b];
}

unsigned int* list(unsigned int a, unsigned int b){
 if(a>=ca){return &trash;}
 if(b>=ll){return &trash;}
 return &plist[a*ll+b];
}

unsigned int* var(unsigned int a){
 if(a>=lv){return &trash;}
 return &pvar[a];
}

unsigned int* tarr(unsigned int a,unsigned int b){
 #define rtarr(x,y) parr[x*la+y]
 if(a>=car){return &trash;}
 if(b>=la){return &trash;}
 return &rtarr(a,b);
}

unsigned int* arr(unsigned int aa,unsigned int a){
 #define rarr(x) *tarr(*list(aa,a),x)
 #define aarr *list(aa,a)
 #define rl(x) *list(aa,x+a)
 if(*list(aa,a)>=car){return &trash;}
 unsigned int rearr=rarr(0)+1;
 printf("%u ",rearr);
 
 // L: 7:1 2 3
 // A: 3:5 5 5:1 12 345
 
 unsigned int acum=1;
 for(unsigned int b=rarr(0);b>0;b--){
  printf("+ %u(%u) * %u ",rl(b),b,acum);
  rearr+=rl(b)*acum;
  acum*=rarr(b);
 }
 printf("= %u\n",rearr);
 
 return &rarr(rearr);
}

void marr(unsigned int aa, unsigned int a){
 // L: 12:3:5 5 5
 *tarr(*list(aa,a),0)=*list(aa,a+1);
 //printf("MARR(%u): %u",*list(aa,a),*tarr(*list(aa,a),0));
 for(unsigned int b=1;b<=*list(aa,a+1);b++){
  *tarr(*list(aa,a),0+b)=*list(aa,a+1+b);
   //printf(" %u.%u",b,*tarr(*list(aa,a),0+b));
 }
 //printf("\n");
 return;
}

void date_in(){
 for(unsigned int a=0;a<ls;a++){
  scanf("%s",com(a,0));
  if((*com(a,0)=='e')&&((*com(a,1)=='n')&&(*com(a,2)=='d'))){
   for(;a<ls;a++){
    for(unsigned int b=0;b<lc;b++){
     *com(a,b)=0;
    }
   }
   break;
  }
 }
 printf("\n");
 return;
}

int main(){
 //asignacion de memoria
 plist=(unsigned int*)calloc(ca*(ll+1),sizeof(unsigned int));
 if(plist==NULL){printf("Error de Memoria, LIST.\n");return 0;}
 pvar=(unsigned int*)calloc(lv,sizeof(unsigned int));
 if(pvar==NULL){printf("Error de Memoria, VAR.\n");return 0;}
 parr=(unsigned int*)calloc(car*(la+1),sizeof(unsigned int));
 if(parr==NULL){printf("Error de Memoria, ARR.\n");return 0;}
 pcom=(char*)calloc(ls*lc,sizeof(char));
 if(pcom==NULL){printf("Error de Memoria, COM.\n");return 0;}
 //entrada del codigo
 date_in();
 //var save, ejecucion
 bool au[ca];//autos en uso
 au[0]=1;
 unsigned int aa=0;//auto actual
 
 for(unsigned int a=0;a<ls;a++){
  if(!(au[aa])){aa=(aa+1)%ca;continue;}
  //for(unsigned int b=lc-1;b>=0;b--){
  for(unsigned int b=0;b<lc;b++){
   if(*com(a,b)==0){continue;}
   if(*com(a,b)=='O'){continue;}
   if(*com(a,b)=='C'){break;}
   if((*com(a,b)>'a')&&(*com(a,b)<='z')){
    *list(aa,*list(aa,0)+1)*=*com(a,b)-'a'+1;	    
   }
   if((*com(a,b)>'0')&&(*com(a,b)<='9')){
    *list(aa,*list(aa,0)+1)+=*com(a,b)-'0';	    
   }
   switch(*com(a,b)){
    case '!':{for(unsigned int c=0;c<ll+1;c++){*list(aa,c)=0;}}break;
    case '0':{*list(aa,*list(aa,0)+1)=0;}break;
    case '.':{*list(aa,0)=(*list(aa,0)+1)%ll;}break;
    case ',':{*list(aa,0)=(*list(aa,0)-1)%ll;}break;
    case '$':{*list(aa,*list(aa,0)+1)=*var(*list(aa,*list(aa,0)+1));}break;
    case '=':{*var(*list(aa,*list(aa,0)+1+1))=*list(aa,*list(aa,0)+1);}break;
    case '#':{*list(aa,*list(aa,0)+1)=*arr(aa,*list(aa,0)+1+1);}break;
    case '~':{*arr(aa,*list(aa,0)+1+1)=*list(aa,*list(aa,0)+1);}break;
    case 'M':{marr(aa,*list(aa,0)+1);}break;
    case '+':{*list(aa,*list(aa,0)+1)=*list(aa,*list(aa,0)+1+1)+*list(aa,*list(aa,0)+1+2);}break;
    case '-':{*list(aa,*list(aa,0)+1)=*list(aa,*list(aa,0)+1+1)-*list(aa,*list(aa,0)+1+2);}break;
    case 'P':{printf("%u\n",*list(aa,*list(aa,0)+1));}break;
   };
   printf("%u:",*list(aa,0));
   for(unsigned int c=1;c<ll;c++){
    printf("%u ",*list(aa,c));
   }
   printf("[%u](%c)\n",trash,*com(a,b));
  }
  aa=(aa+1)%ca;
 }
 return 0;
}
