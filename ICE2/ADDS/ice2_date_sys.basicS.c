#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../LIBS/libloc.h"

//var conf
 //basic
extern unsigned int ln; //longuitud de los numeros
extern unsigned int lfd;//longuitud de los tipos
extern unsigned int lc; //longuitud de los comandos
extern unsigned int lv; //longuitud de variables
extern unsigned int ls; //longuitud de script
extern unsigned int lj; //longuitud de jump
extern unsigned int ccv; //cantidad de CVAR
extern unsigned int lcv; //longuitud de los CVAR
extern unsigned int cd; //cantidad de Dwarfs
extern unsigned int lr; //Longuitud de Recover
extern unsigned int cme;//cantidad maxima de errores antes de auto FATALITYERROR
 //adds
char ic='0'; //caracter de inicio
char fc='9'; //caracter de final
extern unsigned int lf; //longuitud de el file
unsigned int lds=1000; //longuitud de el define save
unsigned int lfs=1000; //longuitud de el function save
//var save
 //basic
extern unsigned int* pNff;//[ls][lc]
#define bNff(a,b) pNff[(a)*lc+(b)]
extern char* pAff;//[ls][lc]
#define bAff(a,b) pAff[(a)*lc+(b)]

#define serial_console(a) printf("%s",a)
#define serial_console_num(a) printf("%u",a)
#define crea_memo(a,b) calloc(a,b)
bool date_proces();//funcion llamada para dar los datos requeridos

bool conf_proces(){
 FILE* file;
 if(!(file=fopen("CONFIG/ice2.cnf","rb"))){
  serial_console("Error, no se puede abrir el archivo de configuracion ice2.cnf\n");
  return 1;
 }
 char* cfile=(char*)calloc(sizeof(char),9999);//[9999]
 if(cfile==NULL){serial_console("Error de memoria. CFILE\n");return 1;}
 fread(cfile,sizeof(char),9999,file);
 fclose(file);

 unsigned int conf[16]; 
 bool confc[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
 unsigned int a=0,b=0;
 while(b<16){
  unsigned int c=0;
  char Cff[5];
  bool coment=0;
  while((a<9999)&&(c<5)){
   if(cfile[a]==';'){
    coment=!(coment);
   }
   if(!(coment)){
    if(cfile[a]==':'){
     goto con;
    }
    if((cfile[a]>='0')&&(cfile[a]<='9')){
     Cff[c]=cfile[a]-'0';
     c++;
    }
   }
   a++;
  }
  conf[b]=ces(10,5,Cff);
  confc[b]=1;
  con:
  b++;
 }
 
//ln, lfd, lc, lv, ls, lj, ccv, lcv, cd, lr, ic, fc, lf, cme, lds, lfs
 if(confc[0]){ln=conf[0];}
 if(confc[1]){lfd=conf[1];}
 if(confc[2]){lc=conf[2];}
 if(confc[3]){lv=conf[3];}
 if(confc[4]){ls=conf[4];}
 if(confc[5]){lj=conf[5];}
 if(confc[6]){ccv=conf[6];}
 if(confc[7]){lcv=conf[7];}
 if(confc[8]){cd=conf[8];}
 if(confc[9]){lr=conf[9];}
 if(confc[10]){ic=conf[10];}
 if(confc[11]){fc=conf[11];}
 if(confc[12]){lf=conf[12];}
 if(confc[13]){cme=conf[13];}
 if(confc[14]){lds=conf[14];}
 if(confc[15]){lfs=conf[15];}
 return 0;
}

bool date_syntax_system(char* file_name,unsigned int* a){
 FILE* file;
 if(!(file=fopen(file_name,"rb"))){
  serial_console("Error, no se puede abrir el archivo ");serial_console(file_name);serial_console("\n");
  return 1;
 }
 char* pfile=(char*)calloc(sizeof(char),lf);//lf
 if(pfile==NULL){serial_console("Error de memoria. PFILE\n");return 1;}
 unsigned int* pds=(unsigned int*)calloc(sizeof(unsigned int),lds*2);//lds 2
 if(pds==NULL){serial_console("Error de memoria. PDS\n");return 1;}
 unsigned int* pfs=(unsigned int*)calloc(sizeof(unsigned int),lfs*3);//lfs 2
 if(pfs==NULL){serial_console("Error de memoria. PFS\n");return 1;}
 #define bds(a,b) pds[a*2+b]
 #define bfs(a,b) pfs[a*3+b]
 unsigned int ads=0;
 unsigned int afs=0;
 
 fread(pfile,sizeof(char),lf,file);
 fclose(file);
 //procesador de datos de entrada
 upchr(pfile);
 for(unsigned int b=0;(*a<ls)&&(b<lf);(*a)++){
  for(unsigned int c=0;c<lc;c++){
   restart_coment:
   while(pfile[b]<=' '){
    if(pfile[b]==0){goto fullend;}
    b++;
   }
   if(pfile[b]=='#'){
    while(true){
     b++;
     if(pfile[b]=='#'){
      b++;
      while(pfile[b]<=' '){
       if(pfile[b]==0){goto fullend;}
       b++;
      }
      break;
     }
    }
    goto restart_coment;
   }
   if(pfile[b]=='&'){
    while(true){
     b++;
     if(pfile[b]=='\n'){
      b++;
      while(pfile[b]<=' '){
       if(pfile[b]==0){goto fullend;}
       b++;
      }
      break;
     }
    }
    goto restart_coment;
   }
   if(pfile[b]=='['){
    b++;
    if(FULLequal(&pfile[b],"ADD",' ')){b+=4;
     unsigned int d=cut(&pfile[b],']');
     if(date_syntax_system(&pfile[b],a)){
      return 1;
     }
     b+=d;
     pfile[b]=']';
    }else if(FULLequal(&pfile[b],"CLOSE",' ')){b+=6;
     return 0;
    }else if(FULLequal(&pfile[b],"DEFINE",' ')){b+=7;
     if(ads>=lds){
      printf("Error. Se a excedido la cantidad de DEFINEs que se pueden almacenar. (%s) COMAND%u PART%u CARACTER%u\n",cut1(&pfile[b],' ',(unsigned int*)&file_name),*a,c,b);
      free(pds);
      free(pfs);
      free(pfile);
      return 1;
     }
     //bds(ads,1)=*((unsigned int*)&pfile[b]);
     //b+=sizeof(unsigned int)/sizeof(char);
     bds(ads,1)=0;
     for(unsigned int d=b;(pfile[b]!=' ')&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
      bds(ads,1)+=(unsigned int)pfile[b];
      bds(ads,1)*=0x100;
     }
     if(pfile[b]!=' '){
      printf("Error. No se a puesto el espacio que separa los dos valores del DEFINE o has intentado definir un DEFINE de con un nombre demasiado grande. (%s) COMAND%u PART%u CARACTER%u\n",Mcut(&pfile[b]," ;"),*a,c,b);
      free(pds);
      free(pfs);
      free(pfile);
      return 1;
     }
     b++;
     bds(ads,0)=charint_count(&pfile[b],&b);
     ads++;
    }else if(FULLequal(&pfile[b],"FUNCTION",' ')){b+=9;
     if(afs>=lfs){
      printf("Error. Se a excedido la cantidad de FUNCTIONs que se pueden almacenar. (%s) COMAND%u PART%u CARACTER%u\n",cut1(&pfile[b],' ',(unsigned int*)&file_name),*a,c,b);
      free(pds);
      free(pfs);
      free(pfile);
      return 1;
     }
     //bfs(afs,1)=*((unsigned int*)&pfile[b]);
     //b+=sizeof(unsigned int)/sizeof(char);
     bfs(afs,0)=*a;
     bfs(afs,1)=0;
     for(unsigned int d=b;(pfile[b]!=']')&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
      bfs(afs,1)+=(unsigned int)pfile[b];
      bfs(afs,1)*=0x100;
     }
     bfs(afs,2)=0;
     for(unsigned int d=b;(pfile[b]!=']')&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
      bfs(afs,2)+=(unsigned int)pfile[b];
      bfs(afs,2)*=0x100;
     }
     afs++;
    }else{
     printf("Error. Nombre especial(?COMMAND) no reconocido. (%s) COMAND%u PART%u CARACTER%u\n",Mcut(&pfile[b]," ;"),*a,c,b);
     free(pds);
     free(pfs);
     free(pfile);
     return 1;
    }
    if(pfile[b]!=']'){
     printf("Error. No se a puesto ']' al final de un comando a interprete. (%s) COMAND%u PART%u CARACTER%u\n",Mcut(&pfile[b]," ;"),*a,c,b,pfile[b]);
     free(pds);
     free(pfs);
     free(pfile);
     return 1;
    }
    b++;
    goto restart_coment;
   }
   if(pfile[b]==';'){
    b++;
    break;
   }
   //detecion del tipo
   if(pfile[b]==','){//num
    bAff(*a,c)=0;
    b++;
   }else if(pfile[b]=='$'){//var
    bAff(*a,c)=1;
    b++;
   }else if(FULLequal(&pfile[b],"SYS",'.')){
    bAff(*a,c)=2;
    b+=4;
   }else if((pfile[b]=='-')&&(pfile[b+1]=='>')){//depen
    bAff(*a,c)=3;
    b+=2;
    if(pfile[b]==','){//depen num
     b++;
    }else if(pfile[b]=='$'){//depen var
     bAff(*a,c)+=7*1;
     b++;
    }else if(FULLequal(&pfile[b],"SYS",'.')){//depen sys
     bAff(*a,c)+=7*2;
     b+=4;
    }else if(pfile[b]==':'){//depen cvar
     bAff(*a,c)+=7*3;
     b++;
    }else if(pfile[b]=='?'){//depen clone
     bAff(*a,c)+=7*3;
     b++;
    }
   }else if(pfile[b]==':'){//cvar
    bAff(*a,c)=4;
    b++;
   }else if(pfile[b]=='?'){//clone
    bAff(*a,c)=5;
    b++;
   }else if(pfile[b]=='@'){//modular var
    bAff(*a,c)=6;
    b++;
   }
   //detecion num
   if(pfile[b]==','){
    b++;
    bNff(*a,c)=charint_count(&pfile[b],&b);
   //detecion bin
   }else if(pfile[b]=='B'){
    b++;
    bNff(*a,c)=charint_count_bin(&pfile[b],&b);
   //detecion str
   }else if(pfile[b]=='!'){
    b++;
    bNff(*a,c)=*(unsigned int*)&pfile[b];
    b+=sizeof(unsigned int)/sizeof(char);
   //detecion DEFINE
   }else if(FULLequal(&pfile[b],"DEFINE",'.')){
    b+=7;
    bNff(*a,c)=0;
    for(unsigned int d=b;((pfile[b]!=' ')||(pfile[b]!=';'))&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
     bNff(*a,c)+=(unsigned int)pfile[b];
     bNff(*a,c)*=0x100;
    }
    for(unsigned int d=0;d<ads;d++){
     if(bds(d,1)==bNff(*a,c)){
      bNff(*a,c)=bds(d,0);
      goto defjmp;
     }
    }
    printf("Error. No se a encontrado el DEFINE. (%s) COMAND%u PART%u CARACTER%u\n",cut1(&pfile[b],' ',(unsigned int*)&file_name),*a,c,b);
    defjmp:
   //detecion FUNCTION
   }else if(FULLequal(&pfile[b],"FUNCTION",'.')){
    b+=9;
    bNff(*a,c)=0;
    unsigned int e=0;
    for(unsigned int d=b;((pfile[b]!=' ')||(pfile[b]!=';'))&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
     bNff(*a,c)+=(unsigned int)pfile[b];
     bNff(*a,c)*=0x100;
    }
    for(unsigned int d=b;((pfile[b]!=' ')||(pfile[b]!=';'))&&(b-d<sizeof(unsigned int)/sizeof(char));b++){
     e+=(unsigned int)pfile[b];
     e*=0x100;
    }
    for(unsigned int d=0;d<afs;d++){
     if((bfs(d,1)==bNff(*a,c))&&(bfs(d,2)==e)){
      bNff(*a,c)=bfs(d,0);
      goto funjmp;
     }
    }
    printf("Error. No se a encontrado el FUNCTION. (%s) COMAND%u PART%u CARACTER%u\n",cut1(&pfile[b],' ',(unsigned int*)&file_name),*a,c,b);
    funjmp:
   //SYS SIG
   	}else if(MFULLequal(&pfile[b],"LN"," ;")){b+=3;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"LC"," ;")){b+=3;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"LV"," ;")){b+=3;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"LS"," ;")){b+=3;bNff(*a,c)=3;
	}else if(MFULLequal(&pfile[b],"LJ"," ;")){b+=3;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"CCV"," ;")){b+=4;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"LCV"," ;")){b+=4;bNff(*a,c)=6;
   	}else if(MFULLequal(&pfile[b],"CD"," ;")){b+=3;bNff(*a,c)=7;
   	}else if(MFULLequal(&pfile[b],"LR"," ;")){b+=3;bNff(*a,c)=8;
   	}else if(MFULLequal(&pfile[b],"ERRSIGOLD"," ;")){b+=10;bNff(*a,c)=9;
   	}else if(MFULLequal(&pfile[b],"DWARF"," ;")){b+=6;bNff(*a,c)=10;
   	}else if(MFULLequal(&pfile[b],"TRASH"," ;")){b+=6;bNff(*a,c)=11;
   	}else if(MFULLequal(&pfile[b],"COMMD"," ;")){b+=6;bNff(*a,c)=12;
   	}else if(MFULLequal(&pfile[b],"RECOV"," ;")){b+=6;bNff(*a,c)=13;
   	}else if(MFULLequal(&pfile[b],"JUMPL"," ;")){b+=6;bNff(*a,c)=14;
   	}else if(MFULLequal(&pfile[b],"RECOV_SITE"," ;")){b+=11;bNff(*a,c)=15;
   	}else if(MFULLequal(&pfile[b],"JUMPL_SITE"," ;")){b+=11;bNff(*a,c)=16;
   	}else if(MFULLequal(&pfile[b],"TAG"," ;")){b+=4;bNff(*a,c)=17;
   //CVAR ACCES
   	}else if(MFULLequal(&pfile[b],"ARRAY"," ;")){b+=6;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"MDA"," ;")){b+=4;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"PUSH"," ;")){b+=5;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"POP"," ;")){b+=4;bNff(*a,c)=3;
   }else if(MFULLequal(&pfile[b],"EXIT"," ;")){b+=5;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"NULL"," ;")){b+=5;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"STOP"," ;")){b+=5;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"ERROR_CLEAR"," ;")){b+=12;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"REJE"," ;")){b+=5;bNff(*a,c)=3;
   }else if(MFULLequal(&pfile[b],"END"," ;")){b+=4;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"SIMPLE_JMP"," ;")){b+=11;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"LOSE_JMP"," ;")){b+=9;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"LIVING_JMP"," ;")){b+=11;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"INMORTAL_JMP"," ;")){b+=13;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"DOWN_SEARCH_JMP"," ;")){b+=16;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"UP_SEARCH_JMP"," ;")){b+=14;bNff(*a,c)=6;
   	}else if(MFULLequal(&pfile[b],"SEARCH_JMP"," ;")){b+=11;bNff(*a,c)=7;
   }else if(MFULLequal(&pfile[b],"UBIM"," ;")){b+=5;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"JUBI"," ;")){b+=5;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"UBI"," ;")){b+=4;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"JMP"," ;")){b+=4;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"+JBU"," ;")){b+=5;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"-JBU"," ;")){b+=5;bNff(*a,c)=4;
   }else if(MFULLequal(&pfile[b],"CMPM"," ;")){b+=5;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"WHILE"," ;")){b+=6;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"IF"," ;")){b+=3;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"DO-WHILE"," ;")){b+=9;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"CJMP"," ;")){b+=5;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"SIMPLE_CJMP"," ;")){b+=12;bNff(*a,c)=3;
   }else if(MFULLequal(&pfile[b],"CAL"," ;")){b+=4;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"CP"," ;")){b+=3;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"CP_BIN"," ;")){b+=7;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"+"," ;")){b+=2;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"+="," ;")){b+=3;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"-"," ;")){b+=2;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"-="," ;")){b+=3;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"*"," ;")){b+=2;bNff(*a,c)=6;
   	}else if(MFULLequal(&pfile[b],"*="," ;")){b+=3;bNff(*a,c)=7;
   	}else if(MFULLequal(&pfile[b],"/"," ;")){b+=2;bNff(*a,c)=8;
   	}else if(MFULLequal(&pfile[b],"/="," ;")){b+=3;bNff(*a,c)=9;
   	}else if(MFULLequal(&pfile[b],"%"," ;")){b+=2;bNff(*a,c)=10;
   	}else if(MFULLequal(&pfile[b],"%="," ;")){b+=3;bNff(*a,c)=11;
   	}else if(MFULLequal(&pfile[b],"S<<"," ;")){b+=4;bNff(*a,c)=12;
   	}else if(MFULLequal(&pfile[b],"S<<_="," ;")){b+=6;bNff(*a,c)=13;
   	}else if(MFULLequal(&pfile[b],"S>>"," ;")){b+=4;bNff(*a,c)=14;
   	}else if(MFULLequal(&pfile[b],"S>>_="," ;")){b+=6;bNff(*a,c)=15;
	}else if(MFULLequal(&pfile[b],">"," ;")){b+=2;bNff(*a,c)=16;
   	}else if(MFULLequal(&pfile[b],">_="," ;")){b+=4;bNff(*a,c)=17;
   	}else if(MFULLequal(&pfile[b],"<"," ;")){b+=2;bNff(*a,c)=18;
   	}else if(MFULLequal(&pfile[b],"<_="," ;")){b+=4;bNff(*a,c)=19;
   	}else if(MFULLequal(&pfile[b],"<="," ;")){b+=3;bNff(*a,c)=20;
   	}else if(MFULLequal(&pfile[b],"<=_="," ;")){b+=5;bNff(*a,c)=21;
   	}else if(MFULLequal(&pfile[b],">="," ;")){b+=3;bNff(*a,c)=22;
   	}else if(MFULLequal(&pfile[b],">=_="," ;")){b+=5;bNff(*a,c)=23;
   	}else if(MFULLequal(&pfile[b],"=="," ;")){b+=3;bNff(*a,c)=24;
   	}else if(MFULLequal(&pfile[b],"==_="," ;")){b+=5;bNff(*a,c)=25;
   	}else if(MFULLequal(&pfile[b],"!="," ;")){b+=3;bNff(*a,c)=26;
   	}else if(MFULLequal(&pfile[b],"!=_="," ;")){b+=5;bNff(*a,c)=27;
   	}else if(MFULLequal(&pfile[b],"NUM>BIN"," ;")){b+=8;bNff(*a,c)=28;
   	}else if(MFULLequal(&pfile[b],"NUM>BIN_="," ;")){b+=10;bNff(*a,c)=29;
   	}else if(MFULLequal(&pfile[b],"<<"," ;")){b+=3;bNff(*a,c)=30;
   	}else if(MFULLequal(&pfile[b],"<<_="," ;")){b+=5;bNff(*a,c)=31;
   	}else if(MFULLequal(&pfile[b],">>"," ;")){b+=3;bNff(*a,c)=32;
   	}else if(MFULLequal(&pfile[b],">>_="," ;")){b+=5;bNff(*a,c)=33;
   	}else if(MFULLequal(&pfile[b],"NOT"," ;")){b+=4;bNff(*a,c)=34;
   	}else if(MFULLequal(&pfile[b],"NOT_="," ;")){b+=6;bNff(*a,c)=35;
   	}else if(MFULLequal(&pfile[b],"AND"," ;")){b+=4;bNff(*a,c)=36;
   	}else if(MFULLequal(&pfile[b],"AND_="," ;")){b+=6;bNff(*a,c)=37;
   	}else if(MFULLequal(&pfile[b],"NAND"," ;")){b+=5;bNff(*a,c)=38;
   	}else if(MFULLequal(&pfile[b],"NAND_="," ;")){b+=7;bNff(*a,c)=39;
   	}else if(MFULLequal(&pfile[b],"OR"," ;")){b+=3;bNff(*a,c)=40;
   	}else if(MFULLequal(&pfile[b],"OR_="," ;")){b+=5;bNff(*a,c)=41;
   	}else if(MFULLequal(&pfile[b],"NOR"," ;")){b+=4;bNff(*a,c)=42;
   	}else if(MFULLequal(&pfile[b],"NOR_="," ;")){b+=7;bNff(*a,c)=43;
   	}else if(MFULLequal(&pfile[b],"XOR"," ;")){b+=4;bNff(*a,c)=44;
   	}else if(MFULLequal(&pfile[b],"XOR_="," ;")){b+=7;bNff(*a,c)=45;
   	}else if(MFULLequal(&pfile[b],"NXOR"," ;")){b+=5;bNff(*a,c)=46;
   	}else if(MFULLequal(&pfile[b],"NXOR_="," ;")){b+=8;bNff(*a,c)=47;
   	}else if(MFULLequal(&pfile[b],"ASIG"," ;")){b+=8;bNff(*a,c)=48;
   	}else if(MFULLequal(&pfile[b],"ASIG_="," ;")){b+=8;bNff(*a,c)=49;
   }else if(MFULLequal(&pfile[b],"DWARF_CONTROL"," ;")){b+=14;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"AUTO_ACTIV"," ;")){b+=5;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"ACTIV"," ;")){b+=6;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"DESACTIV"," ;")){b+=9;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"ACTUAL_DESACTIV"," ;")){b+=16;bNff(*a,c)=3;
   }else if(MFULLequal(&pfile[b],"RESTOR_SAVE"," ;")){b+=12;bNff(*a,c)=6;
   	}else if(MFULLequal(&pfile[b],"SAVE"," ;")){b+=5;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"RESTORE"," ;")){b+=8;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"REVALUE"," ;")){b+=8;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"RM_OLD"," ;")){b+=7;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"SAVE_LIVE"," ;")){b+=10;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"READ"," ;")){b+=5;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"WRITE"," ;")){b+=6;bNff(*a,c)=6;
   }else if(MFULLequal(&pfile[b],"CVAR"," ;")){b+=5;bNff(*a,c)=7;
   	}else if(MFULLequal(&pfile[b],"MAKE_MDA"," ;")){b+=9;bNff(*a,c)=0;
   }else if(MFULLequal(&pfile[b],"INPUT"," ;")){b+=6;bNff(*a,c)=8;
   	}else if(MFULLequal(&pfile[b],"NUM"," ;")){b+=4;bNff(*a,c)=0;
   }else if(MFULLequal(&pfile[b],"OUTPUT"," ;")){b+=7;bNff(*a,c)=9;
   	}else if(MFULLequal(&pfile[b],"NUM"," ;")){b+=4;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"CHR"," ;")){b+=4;bNff(*a,c)=1;
   	}else if(MFULLequal(&pfile[b],"NUMSTR"," ;")){b+=7;bNff(*a,c)=2;
   	}else if(MFULLequal(&pfile[b],"BIN"," ;")){b+=4;bNff(*a,c)=3;
   	}else if(MFULLequal(&pfile[b],"HEX"," ;")){b+=4;bNff(*a,c)=4;
   	}else if(MFULLequal(&pfile[b],"N!"," ;")){b+=3;bNff(*a,c)=5;
   	}else if(MFULLequal(&pfile[b],"T!"," ;")){b+=3;bNff(*a,c)=6;
   	}else if(MFULLequal(&pfile[b],"OPCIONAL_BASE_LIMITED"," ;")){b+=22;bNff(*a,c)=7;
   	}else if(MFULLequal(&pfile[b],"OPCIONAL_BASE"," ;")){b+=14;bNff(*a,c)=8;
   	}else if(MFULLequal(&pfile[b],"OWN_BASE"," ;")){b+=9;bNff(*a,c)=9;
   }else if(MFULLequal(&pfile[b],"PLUGIN"," ;")){b+=7;bNff(*a,c)=10;
   	}else if(MFULLequal(&pfile[b],"**"," ;")){b+=3;bNff(*a,c)=0;
   	}else if(MFULLequal(&pfile[b],"**="," ;")){b+=4;bNff(*a,c)=1;
   //									}else if(MFULLequal(&pfile[b],"DPRINT"," ;")){b+=7;bNff(*a,c)=9999;
   //									}else if(MFULLequal(&pfile[b],"DSCAN"," ;")){b+=6;bNff(*a,c)=9998;
   }else{
    printf("Error. Nombre no reconocido. (%s) COMAND%u PART%u CARACTER%u\n",cut1(&pfile[b],' ',(unsigned int*)&file_name),*a,c,b);
    free(pds);
    free(pfs);
    free(pfile);
    return 1;
   }
  }
 }
 fullend:
 free(pds);
 free(pfs);
 free(pfile);
 return 0;
}

bool date_proces(){//funcion llamada para dar los datos requeridos
 char file_name[9999];
 printf(">");
 scanf("%s",file_name);
 //upchr(file_name);
 unsigned int a=0;
 return date_syntax_system(file_name,&a);
}
