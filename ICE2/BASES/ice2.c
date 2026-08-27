
/*	MADE BY CODEHAT	- ICE2 EJECUTOR		*/


#include <stdbool.h>
#include <stdlib.h>

#include "../ADDS/ice2_date_sys.bice.c"
#include "../ADDS/ice2_puts_sys.icelib.c"

//var conf
unsigned int ln=4; //longuitud de los numeros
unsigned int lfd=1; //longuitud de los tipos
unsigned int lc=4; //longuitud de los comandos
unsigned int lv=64; //longuitud de variables
unsigned int ls=64; //longuitud de script
unsigned int lj=16; //longuitud de jump
unsigned int ccv=64; //cantidad de CVAR
unsigned int lcv=16; //longuitud de los CVAR
unsigned int cd=4; //cantidad de Dwarfs o Enanos
unsigned int lr=16;//longuitut de los Rescue Saves
unsigned int cme=300;//cantidad maxima de errores antes de auto FATALITYERROR
unsigned int lf=1000; //longuitud de el file
//var save
unsigned int* pDff;//Dff[cd] //Rff[cd][lr] //Jff[cd][lj] //Jbu[cd] //Rbu[cd]
#define bDff(a) pDff[a]//base de filtro, numero de ubicacion de cada Dwarf
unsigned int* Dff(unsigned int ubi);//numero de ubicacion
#define bRff(a,b) pDff[cd+a*lr+b]//base para filtro, lista con los puntos de recuperacion
unsigned int* Rff(unsigned int ubi,unsigned int ubi2);
#define bJff(a,b) pDff[cd+cd*lr+a*lj+b]//base para filtro, lista de jumps
unsigned int* Jff(unsigned int ubi,unsigned int ubi2);
#define bJbu(a) pDff[cd+cd*lr+cd*lj+a]//base para filtro, punto en Jff en el que esta cada Dwarf
unsigned int* Jbu(unsigned int ubi);//Jump punto
#define bRbu(a) pDff[cd+cd*lr+cd*lj+cd+a]//base para filtro, punto en Rff en el que esta cada Dwarf
unsigned int* Rbu(unsigned int ubi);//Recovery punto

unsigned int* pVff;//[lv]
unsigned int* Vff(unsigned int ubi);//variables

unsigned int* pCVff;//[ccv][lcv]
unsigned int* CVff(unsigned int ubi,unsigned int ubi2);//variables compactas

unsigned int* pNff;//[ls][lc]
unsigned int* Nff(unsigned int ubi,unsigned int ubi2);//comandos

char* pAff;//[ls][lc]
char* Aff(unsigned int ubi,unsigned int ubi2);//tipos de los datos de los comandos

bool* pDUS;//[cd]
bool* DUS(unsigned int a);//Dwarf activados
//var ejecucion
unsigned int errortrash=0;//basura para cuando hai un error
unsigned int d=0;//Dwarf actual
unsigned int errsigold=0;//ultimo numero de error
bool errora=0;//ha abido algun error, reciente?
bool FATALITYERROR=0;//error grave, parada inmediata
unsigned int errorcount=0;//conteo de la cantidad de errores aparecidos 
unsigned int DUSC=0;//conteo de los Dwarfs activados
unsigned int TAG=0x30303030;//Etiqueta para los errores
unsigned int ANVFLAG=0;

void error(unsigned int errsig){
 //ERRSIG 0. NULL
 //ERRSIG 1. Intento de aceder a una variable inexistente.
 //ERRSIG 2. Intento de aceder a los datos de Jff de un Dwarf inextistente.
 //ERRSIG 3. Intento de aceder a un registro de Jff inexistente.
 //ERRSIG 4. Intento de aceder a un system date inexistente.
 //ERRSIG 5. Intento de aceder a los datos de CVff de un CVAR inextistente.
 //ERRSIG 6. Intento de aceder a un registro de CVff inexistente.
 //ERRSIG 7. Intento de aceder a los datos de Nff de un comando inextistente.
 //ERRSIG 8. Intento de aceder a un registro inexistente de Nff de un comando existente.
 //ERRSIG 9. Intento de aceder a los datos de Aff de un comando inextistente.
 //ERRSIG 10. Intento de aceder a un registro inexistente de Aff de un comando existente.
 //ERRSIG 11. Intento de aceder a un dato concatenado inexistente.
 //ERRSIG 12. Comando no identificado.
 //ERRSIG 13. Intento de aceder a los datos de Rff de un Dwarf inextistente.
 //ERRSIG 14. Intento de aceder a un registro de Rff inexistente.
 //ERRSIG 15. Intento de hacer un calculo inexistente en el comando 0004.
 //ERRSIG 16. Intento de aceder a un modo inexistente en el comando 0003.
 //ERRSIG 17. Intento de aceder a un modo inexistente en el comando 0002.
 //ERRSIG 18. Intento de aceder a un modo inexistente en el comando 0001.
 //ERRSIG 19. Intento de aceder a un modo inexistente en el comando 0006.
 //ERRSIG 20. Intento de aceder a un comando inexistente.
 //ERRSIG 21. Intento de aceder a un puntero, Jbu, de Jff inexistente.
 //ERRSIG 22. Intento de aceder a un puntero, Rbu, de Rff inexistente.
 //ERRSIG 23. Intento de sumar dos numeros, +, la suma sobrepasa el limite permitido.
 //ERRSIG 24. Intento de sumar dos numeros, +=, la suma sobrepasa el limite permitido.
 //ERRSIG 25. Intento de restar dos numeros, -, la resta da numero negativo.
 //ERRSIG 26. Intento de restar dos numeros, -=, la resta da numero negativo.
 //ERRSIG 27. Intento de multiplicar dos numeros, *, la multiplicacion sobrepasa el limite permitido.
 //ERRSIG 28. Intento de multiplicar dos numeros, =*, la multiplicacion sobrepasa el limite permitido.
 //ERRSIG 29. Intento de dividir dos numeros, /, el divisor es 0.
 //ERRSIG 30. Intento de dividir dos numeros, /=, el divisor es 0.
 //ERRSIG 31. Intento de residuar dos numeros, %, el divisor es 0.
 //ERRSIG 32. Intento de residuar dos numeros, %=, el divisor es 0.
 //ERRSIG 33. Intento de aceder a un registro de DUS, inexistente.
 //ERRSIG 34. Intento de aceder a un modo inexistente en el comando 0005.
 //ERRSIG 35. Intento de desactivar todos los Dwarfs, Actual Descactivate.
 //ERRSIG 36. Intento de desactivar todos los Dwarfs, Desactivate.
 //ERRSIG 37. Intento de aceder a un modo inexistente en el comando 0000.
 //ERRSIG 38. Se a llegado a un comando vacio o el final del programa.
 //ERRSIG 39. Intento de aceder a un modo inexistente en el sistema de acceso de datos de CVAR.
 //ERRSIG 40. Intento de aceder a un modo inexistente en el comando 0007.
 //ERRSIG 41. Intento de aceder a un registro fuera del rango en un CVAR en modo MDA.
 //ERRSIG 42. Intento de aceder a un registro fuera del rango en un CVAR en modo Array, PUSH.
 //ERRSIG 43. Intento de aceder a un registro fuera del rango en un CVAR en modo Array, POP.
 //ERRSIG 44. Rellamada del tipo DEPENDIENTE atraves de otro DEPENDIENTE.
 //ERRSIG 45. Tipo de dato inexistente.
 //ERRSIG 46. Intento de aceder a un modo inexistente en el comando 0008.
 //ERRSIG 47. Intento de aceder a un modo inexistente en el comando 0009.
 //ERRSIG 48. Intento de aceder a un modo inexistente en el comando 0010.
 serial_console("ERROR!...NE: ");
 serial_console_num(errsig);
 serial_console("...NC: ");
 serial_console_num(*Dff(d));
 serial_console("...ND: ");
 serial_console_num(d);
 serial_console("...TAG: ");
 serial_console_num(TAG);
 serial_console(" ");
 serial_console((char*)&TAG);
 serial_console("...NaE: ");
 switch(errsig){
  case 0:{
   serial_console("NE\tNULL.\n");
  }break;
  case 1:{
   serial_console("NE\tIntento de aceder a una variable inexistente.\n");
  }break;
  case 2:{
   serial_console("NE\tIntento de aceder a los datos de Jff de un Dwarf inextistente.\n");
  }break;
  case 3:{
   serial_console("NE\tIntento de aceder a un registro de Jff inexistente.\n");
  }break;
  case 4:{
   serial_console("NE\tIntento de aceder a un system date inexistente.\n");
  }break;
  case 5:{
   serial_console("NE\tIntento de aceder a los datos de CVff de un CVAR inextistente.\n");
  }break;
  case 6:{
   serial_console("NE\tIntento de aceder a un registro de CVff inexistente.\n");
  }break;
  case 7:{
   serial_console("NE\tIntento de aceder a los datos de Nff de un comando inextistente.\n");
  }break;
  case 8:{
   serial_console("NE\tIntento de aceder a un registro inexistente de Nff de un comando existente.\n");
  }break;
  case 9:{
   serial_console("NE\tIntento de aceder a los datos de Aff de un comando inextistente.\n");
  }break;
  case 10:{
   serial_console("NE\tIntento de aceder a un registro inexistente de Aff de un comando existente.\n");
  }break;
  case 11:{
   serial_console("NE\tIntento de aceder a un dato concatenado inexistente.\n");
  }break;
  case 12:{
   serial_console("NE\tComando no identificado.\n");
  }break;
  case 13:{
   serial_console("NE\tIntento de aceder a los datos de Rff de un Dwarf inextistente.\n");
  }break;
  case 14:{
   serial_console("NE\tIntento de aceder a un registro de Rff inexistente.\n");
  }break;
  case 15:{
   serial_console("NE\tIntento de hacer un calculo inexistente en el comando 0004.\n");
  }break;
  case 16:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0003.\n");
  }break;
  case 17:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0002.\n");
  }break;
  case 18:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0001.\n");
  }break;
  case 19:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0006.\n");
  }break;
  case 20:{
   serial_console("NE\tIntento de aceder a un comando inexistente.\n");
  }break;
  case 21:{
   serial_console("NE\tIntento de aceder a un puntero, Jbu, de Jff inexistente.\n");
  }break;
  case 22:{
   serial_console("NE\tIntento de aceder a un puntero, Rbu, de Rff inexistente.\n");
  }break;
  case 23:{
   serial_console("NE\tIntento de sumar dos numeros, +, la suma sobrepasa el limite permitido.\n");
  }break;
  case 24:{
   serial_console("NE\tIntento de sumar dos numeros, +=, la suma sobrepasa el limite permitido.\n");
  }break;
  case 25:{
   serial_console("NE\tIntento de restar dos numeros, -, la resta da numero negativo.\n");
  }break;
  case 26:{
   serial_console("NE\tIntento de restar dos numeros, -=, la resta da numero negativo.\n");
  }break;
  case 27:{
   serial_console("NE\tIntento de multiplicar dos numeros, *, la multiplicacion sobrepasa el limite permitido.\n");
  }break;
  case 28:{
   serial_console("NE\tIntento de multiplicar dos numeros, =*, la multiplicacion sobrepasa el limite permitido.\n");
  }break;
  case 29:{
   serial_console("NE\tIntento de dividir dos numeros, /, el divisor es 0.\n");
  }break;
  case 30:{
   serial_console("NE\tIntento de dividir dos numeros, /=, el divisor es 0.\n");
  }break;
  case 31:{
   serial_console("NE\tIntento de residuar dos numeros, %, el divisor es 0.\n");
  }break;
  case 32:{
   serial_console("NE\tIntento de residuar dos numeros, %=, el divisor es 0.\n");
  }break;
  case 33:{
   serial_console("NE\tIntento de aceder a un registro de DUS, inexistente.\n");
  }break;
  case 34:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0005.\n");
  }break;
  case 35:{
   serial_console("NE\tIntento de desactivar todos los Dwarfs, Actual Desactivate.\n");
  }break;
  case 36:{
   serial_console("NE\tIntento de desactivar todos los Dwarfs, Desactivate.\n");
  }break;
  case 37:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0000.\n");
  }break;
  case 38:{
   serial_console("NE\tSe a llegado a un comando vacio o el final del programa.\n");
  }break;
  case 39:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el sistema de acceso de datos de CVAR.\n");
  }break;
  case 40:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0007.\n");
  }break;
  case 41:{
   serial_console("NE\tIntento de aceder a un registro fuera del rango en un CVAR en modo MDA.\n");
  }break;
  case 42:{
   serial_console("NE\tIntento de aceder a un registro fuera del rango en un CVAR en modo Stack, PUSH.\n");
  }break;
  case 43:{
   serial_console("NE\tIntento de aceder a un registro fuera del rango en un CVAR en modo Stack, POP.\n");
  }break;
  case 44:{
   serial_console("NE\tRellamada del tipo DEPENDIENTE atraves de otro DEPENDIENTE.\n");
  }break;
  case 45:{
   serial_console("NE\tTipo de dato inexistente.\n");
  }break;
  case 46:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0008.\n");
  }break;
  case 47:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0009.\n");
  }break;
  case 48:{
   serial_console("NE\tIntento de aceder a un modo inexistente en el comando 0010.\n");
  }break;
  default:{
   serial_console("FE\tNumero de error erroneo.\n");
   FATALITYERROR=1;
  }break;
 };
 errsigold=errsig;
 errora=1;
 errorcount++;
 if(errorcount>=cme){
  serial_console("Error de sistema. Se a excedido el numero maximo de errores.\n");
  FATALITYERROR=1;
 }
 return;
}

unsigned int* anv(unsigned int nde,unsigned int com,unsigned int dat){
 if(errora){return (unsigned int*)&errortrash;}
 //printf("anv(%u,%u,%u);\n",nde,com,dat);
 #define cvc(a) *CVff(*anv(nde+2,com,dat),a)
 #define dec(a) *anv(nde+2+a,com,dat)
 clone_re:
 unsigned int ru=dat;
 bool depI=0;
 if((0==dat)&&(0==nde)){
  ru=0;
  goto depen_re;
 }
 for(unsigned int a=1,b=0,c=0;a<lc;a++){
  //printf("1 C%u A%u B%u ! Aff%u Nff%u\n",c,a,b,*Aff(com,a),*Nff(com,a));
  if(b>dat){
   break;
  }
  if(*Aff(com,a)%7==3){
   c++;
  }else{
   c=0;
   b++;
  }
  if((b==dat)&&(c==nde)){
   ru=a;
   goto depen_re;
  }
  //printf("2 C%u A%u B%u ! Aff%u Nff%u\n",c,a,b,*Aff(com,a),*Nff(com,a));
 }
 error(11);
 depen_re:
 ANVFLAG=(depI?(unsigned int)(*Aff(com,ru)/7):*Aff(com,ru)%7);
 switch(depI?(unsigned int)(*Aff(com,ru)/7):*Aff(com,ru)%7){
  case 0:{//num
   return Nff(com,ru);
  }break;
  case 1:{//var
   return Vff(*Nff(com,ru));
  }break;
  case 2:{//system date
   switch(*Nff(com,ru)){
    case 0:{errortrash=ln;return &errortrash;}break;
    case 1:{errortrash=lc;return &errortrash;}break;
    case 2:{errortrash=lv;return &errortrash;}break;
    case 3:{errortrash=ls;return &errortrash;}break;
    case 4:{errortrash=lj;return &errortrash;}break;
    case 5:{errortrash=ccv;return &errortrash;}break;
    case 6:{errortrash=lcv;return &errortrash;}break;
    case 7:{errortrash=cd;return &errortrash;}break;
    case 8:{errortrash=lr;return &errortrash;}break;
    case 9:{errortrash=errsigold;return &errortrash;}break;
    case 10:{errortrash=d;return &errortrash;}break;
    case 11:{return &errortrash;}break;
    case 12:{errortrash=*Dff(d);return &errortrash;}break;
    case 13:{errortrash=*Rff(d,*Rbu(d));return &errortrash;}break;
    case 14:{errortrash=*Jff(d,*Jbu(d));return &errortrash;}break;
    case 15:{errortrash=*Jbu(d);return &errortrash;}break;
    case 16:{errortrash=*Rbu(d);return &errortrash;}break;
    case 17:{return &TAG;}break;
    default:{
     error(4);
    }break;
   };
  }break;
  case 3:{//dependiente
   if(depI){
    error(44);
   }else{
    depI=1;
    goto depen_re;
   }
  }break;
  case 4:{//CVAR ACCES
   switch(*anv(nde+1,com,dat)){
    case 0:{//ACCES, Array
     return &cvc(dec(1));
    }break;
    case 1:{//ACCES, MDA(MultiDimensional Array)
     unsigned int Rubi=cvc(0)+1,Jacu=1;
     for(unsigned int a=cvc(0);a>0;a--){
      //printf("A%u",a);
      unsigned int b=0;
      if(dec(a)<cvc(a)){b=dec(a);}else{error(41);return &errortrash;}
      Rubi+=b*Jacu;
      Jacu*=cvc(a);
     }
     //printf("\n<%u  %u>\n",*anv(nde+2,com,dat),Rubi);
     return &cvc(Rubi);
    }break;
    case 2:{//ACCES PUSH, Stack 
     if(cvc(0)+1>=lcv){
      error(42);
      return &errortrash;
     }else{
      cvc(0)=cvc(0)+1;
      return &cvc(cvc(0));
     }
    }break;
    case 3:{//ACCES POP, Stack 
     if(cvc(0)==0){
      error(43);
      return &errortrash;
     }else{
      cvc(0)=cvc(0)-1;
      return &cvc(cvc(0)+1);
     }
    }break;
    default:{
     error(39);	   
    }break;
   };
  }break;
  case 5:{//clone
   unsigned int ndeC=*Nff(com,ru),comC=*anv(nde+1,com,dat),datC=*anv(nde+2,com,dat);
   nde=ndeC;com=comC;dat=datC;
   goto clone_re;
  }break;
  case 6:{//modular var
   return Vff(*anv(nde+1,com,dat));
  }break;
  default:{
   error(45);	   
  }break;
 };
 return &errortrash;
}

#define bit_long 0xffffffff
#define bit_trans(a) (unsigned int)(a%2)

int main(){
 //conf_proces
 if(conf_proces()){
  return 0;
 } 
 //take the space for the save vars
 pVff=(unsigned int*)crea_memo(sizeof(unsigned int),lv);
 if(pVff==NULL){serial_console("Error de memoria. VFF\n");return 0;}
 pDff=(unsigned int*)crea_memo(sizeof(unsigned int),cd+cd*lr+cd*lj+cd+cd);
 if(pDff==NULL){serial_console("Error de memoria. pDFF\n");return 0;}
 pNff=(unsigned int*)crea_memo(sizeof(unsigned int),ls*lc);
 if(pNff==NULL){serial_console("Error de memoria. NFF\n");return 0;}
 pAff=(char*)crea_memo(sizeof(char),ls*lc);
 if(pAff==NULL){serial_console("Error de memoria. AFF\n");return 0;}
 pCVff=(unsigned int*)crea_memo(sizeof(unsigned int),ccv*lcv);
 if(pCVff==NULL){serial_console("Error de memoria. CVFF\n");return 0;}
 pDUS=(bool*)crea_memo(sizeof(bool),cd);
 if(pDUS==NULL){serial_console("Error de memoria. DUS\n");return 0;}
 //date_proces
 rejecute:
 if(date_proces()){
  free(pVff);
  free(pNff);
  free(pDff);
  free(pAff);
  free(pCVff);
  free(pDUS); 
  return 0;
 }
 //ejecutor
 for(unsigned int a=0;a<cd;a++){*DUS(a)=0;}
 *DUS(0)=1;
 DUSC=1;
 while(true){
  if(FATALITYERROR){
   free(pVff);
   free(pNff);
   free(pDff);
   free(pAff);
   free(pCVff);
   free(pDUS);
   return 0;
  }
  if(errora){
   d=((int)d-1)%cd;
   //Save Life
   *Dff(d)=*Rff(d,*Rbu(d));
   errora=0;
  }
  if(!(*DUS(d))){d=((int)d+1)%cd;continue;}
  switch(*anv(0,*Dff(d),0)){
   case 0:{//EXIT
    switch(*anv(0,*Dff(d),1)){
     case 0:{//NULL
      error(38);	   
     }break;
     case 1:{//STOP
      free(pVff);
      free(pNff);
      free(pDff);
      free(pAff);
      free(pCVff);
      free(pDUS);
      return 0;
     }break;
     case 2:{//ERROR CLEAR
      errorcount=0;
     }break;
     case 3:{//REJE
      goto rejecute;
     }break;
     default:{
      error(37);	   
     }break;
    };
   }break;
   case 1:{//END NºID MODEARGUMENTS..
    switch(*anv(0,*Dff(d),2)){
     case 0:{//NULL
     }break;
     case 1:{//Simple Jump
      *Dff(d)=*Jff(d,*Jbu(d));
      *Jff(d,*Jbu(d))=0;
      *Jbu(d)=(*Jbu(d)-1)%lj;
      d=((int)d+1)%cd;
      continue;
     }break;
     case 2:{//Lose Jump
      *Jff(d,*Jbu(d))=0;
      *Jbu(d)=(*Jbu(d)-1)%lj;
     }break;
     case 3:{//Living Jump
      *Dff(d)=*Jff(d,*Jbu(d));
      d=((int)d+1)%cd;
      continue;
     }break;
     case 4:{//Inmortal Jump
      *Dff(d)=*Jff(d,*Jbu(d));
      *Jbu(d)=(*Jbu(d)-1)%lj;
      d=((int)d+1)%cd;
      continue;
     }break;
     case 5:{//Down Search Jump
      for(unsigned int e=*Dff(d);e<ls;e++){
       if((*anv(0,e,0)==1)&&(*anv(0,e,1)==*anv(0,*Dff(d),3))){
        *Dff(d)=e;
        break;
       }
      }
      d=((int)d+1)%cd;
      continue;
     }break;
     case 6:{//Up Search Jump
      for(unsigned int e=*Dff(d);e>0;e--){
       if((*anv(0,e,0)==1)&&(*anv(0,e,1)==*anv(0,*Dff(d),3))){
        *Dff(d)=e;
        break;
       }
      }
      d=((int)d+1)%cd;
      continue;
     }break;
     case 7:{//Search Jump
      unsigned int f=0;
      for(unsigned int e=*Dff(d);e>0;e--){
       if((*anv(0,e,0)==1)&&(*anv(0,e,1)==*anv(0,*Dff(d),3))){
        f=e;
        break;
       }
      }
      for(unsigned int e=*Dff(d);e<ls;e++){
       if(((*anv(0,e,0)==1)&&(*anv(0,e,1)==*anv(0,*Dff(d),3)))&&(e-*Dff(d)<*Dff(d)-f)){
        f=e;
        break;
       }
      }
      *Dff(d)=f;
      d=((int)d+1)%cd;
      continue;
     }break;
     default:{
      error(18);	   
     }break;
    };
   }break;
   case 2:{//JMP/UBI/JUBI MODE ARGUMENTS...
    switch(*anv(0,*Dff(d),1)){
     case 0:{//JUBI
      *Jbu(d)=(*Jbu(d)+1)%lj;
      *Jff(d,*Jbu(d))=*Dff(d);
     }break;
     case 1:{//UBI
      *Dff(d)=*anv(0,*Dff(d),2);
      d=((int)d+1)%cd;
      continue;
     }break;
     case 2:{//JMP
      *anv(0,*Dff(d),2)=*Dff(d);
     }break;
     case 3:{//+*Jbu(d)
      *Jbu(d)=(*Jbu(d)+*anv(0,*Dff(d),2))%lj;
     }break;
     case 4:{//-*Jbu(d)
      *Jbu(d)=(*Jbu(d)-*anv(0,*Dff(d),2))%lj;
     }break;
     default:{
      error(17);	   
     }break;
    };
   }break;
   case 3:{//LOOP/CJMP/IF DATE MODE ARGUMENTS...
    switch(*anv(0,*Dff(d),2)){
     case 0:{//while/if
      if(!(bit_trans(*anv(0,*Dff(d),1)))){
       for(unsigned int e=*Dff(d);e<ls;e++){
        if((*anv(0,e,0)==1)&&(*anv(0,e,1)==*anv(0,*Dff(d),3))){
	 *Dff(d)=e;
	 break;
	}
       }
       d=((int)d+1)%cd;
       continue;
      }
     }break;
     case 1:{//do-while
      if(bit_trans(*anv(0,*Dff(d),1))){
       //Living Jump
       *Dff(d)=*Jff(d,*Jbu(d));
       d=((int)d+1)%cd;
       continue;
      }else{
       //Lose Jump
       *Jff(d,*Jbu(d))=0;
       *Jbu(d)=(*Jbu(d)-1)%lj; 
      }
     }break;
     case 2:{//cjmp
      if(!(bit_trans(*anv(0,*Dff(d),1)))){
       *Dff(d)=*anv(0,*Dff(d),3);
       d=((int)d+1)%cd;
       continue;
      }
     }break;
     case 3:{//Scjmp
      if(!(bit_trans(*anv(0,*Dff(d),1)))){
       //Simple Jump
       *Dff(d)=*Jff(d,*Jbu(d));
       *Jff(d,*Jbu(d))=0;
       *Jbu(d)=(*Jbu(d)-1)%lj;
       d=((int)d+1)%cd;
       continue;
      }
     }break;
     default:{
      error(16);	   
     }break;
    };
   }break;
   case 4:{//CAL OPR DATE...
    switch(*anv(0,*Dff(d),1)){
     //num # num = num 
     case 0:{//CP OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3);
     }break;
     case 1:{//CP_BIN OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 2:{//+ OUT_VAR IN1_DATE IN2_DATE
      if((bit_long-*anv(0,*Dff(d),3))<*anv(0,*Dff(d),4)){
       error(23);
      }else{ 
       *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)+*anv(0,*Dff(d),4);
      }
     }break;
     case 3:{//+= OUT_VAR IN_DATE
      if((bit_long-*anv(0,*Dff(d),2))<*anv(0,*Dff(d),3)){
       error(24);
      }else{ 
       *anv(0,*Dff(d),2)+=*anv(0,*Dff(d),3);
      }
     }break;
     case 4:{//- OUT_VAR IN1_DATE IN2_DATE
      if(*anv(0,*Dff(d),3)<*anv(0,*Dff(d),4)){
       error(25);
      }else{ 
       *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)-*anv(0,*Dff(d),4);
      }
     }break;
     case 5:{//-= OUT_VAR IN_DATE
      if(*anv(0,*Dff(d),2)<*anv(0,*Dff(d),3)){
       error(26);
      }else{ 
       *anv(0,*Dff(d),2)-=*anv(0,*Dff(d),3);
      }
     }break;
     case 6:{//* OUT_VAR IN1_DATE IN2_DATE
      long unsigned int a=(*anv(0,*Dff(d),3))*(*anv(0,*Dff(d),4));
      if(a>bit_long){
       error(27);
      }else{ 
       *anv(0,*Dff(d),2)=(*anv(0,*Dff(d),3))*(*anv(0,*Dff(d),4));
      }
     }break;
     case 7:{//*= OUT_VAR IN_DATE
      long unsigned int a=(*anv(0,*Dff(d),2))*(*anv(0,*Dff(d),3));
      if(a>bit_long){
       error(28);
      }else{ 
       *anv(0,*Dff(d),2)*= *anv(0,*Dff(d),3);
      }
     }break;
     case 8:{// / OUT_VAR IN1_DATE IN2_DATE
      if(*anv(0,*Dff(d),4)<=0){
       error(29);
      }else{ 
       *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)/ *anv(0,*Dff(d),4);
      }
     }break;
     case 9:{// /= OUT_VAR IN_DATE
      if(*anv(0,*Dff(d),3)<=0){
       error(30);
      }else{ 
       *anv(0,*Dff(d),2)/=*anv(0,*Dff(d),3);
      }
     }break;
     case 10:{// % OUT_VAR IN1_DATE IN2_DATE
      if(*anv(0,*Dff(d),4)<=0){
       error(31);
      }else{ 
       *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)%*anv(0,*Dff(d),4);
      }
     }break;
     case 11:{// %= OUT_VAR IN_DATE
      if(*anv(0,*Dff(d),3)<=0){
       error(32);
      }else{ 
       *anv(0,*Dff(d),2)%=*anv(0,*Dff(d),3);
      }
     }break;
     case 12:{// S<< OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)<<*anv(0,*Dff(d),4);
      *anv(0,*Dff(d),2)+=*anv(0,*Dff(d),3)>>bit_long-*anv(0,*Dff(d),4);
     }break;
     case 13:{// S<<_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)<<*anv(0,*Dff(d),3);
      *anv(0,*Dff(d),2)+=*anv(0,*Dff(d),2)>>bit_long-*anv(0,*Dff(d),3);
     }break;
     case 14:{// S>> OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)>>*anv(0,*Dff(d),4);
      *anv(0,*Dff(d),2)+=*anv(0,*Dff(d),3)<<bit_long-*anv(0,*Dff(d),4);
     }break;
     case 15:{// S>>_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)>>*anv(0,*Dff(d),3);
      *anv(0,*Dff(d),2)+=*anv(0,*Dff(d),2)<<bit_long-*anv(0,*Dff(d),3);
     }break;
     //num # num = bin 
     case 16:{// > OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)>bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 17:{// >_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)>*anv(0,*Dff(d),3);
     }break;
     case 18:{// < OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)<*anv(0,*Dff(d),4);
     }break;
     case 19:{// <_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)<*anv(0,*Dff(d),3);
     }break;
     case 20:{// <= OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)<=*anv(0,*Dff(d),4);
     }break;
     case 21:{// <=_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)<=*anv(0,*Dff(d),3);
     }break;
     case 22:{// >= OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)>=*anv(0,*Dff(d),4);
     }break;
     case 23:{// >=_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)>=*anv(0,*Dff(d),3);
     }break;
     case 24:{// == OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)==*anv(0,*Dff(d),4);
     }break;
     case 25:{// ==_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)==*anv(0,*Dff(d),3);
     }break;
     case 26:{// != OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)!=*anv(0,*Dff(d),4);
     }break;
     case 27:{// !=_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)!=*anv(0,*Dff(d),3);
     }break;
     case 28:{// NUM>BIN OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 29:{// NUM>BIN_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),2));
     }break;
     case 30:{// << OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)<<*anv(0,*Dff(d),4);
     }break;
     case 31:{// <<_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)<<*anv(0,*Dff(d),3);
     }break;
     case 32:{// >> OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),3)>>*anv(0,*Dff(d),4);
     }break;
     case 33:{// >>_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=*anv(0,*Dff(d),2)>>*anv(0,*Dff(d),3);
     }break;
     //bin # bin = num 
     //bin # bin = bin
     case 34:{// NOT OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),3)));
     }break;
     case 35:{// NOT_= OUT_IN_VAR
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),2)));
     }break;
     case 36:{// AND OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3))&&bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 37:{// AND_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),2))&&bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 38:{// NAND OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),3))&&bit_trans(*anv(0,*Dff(d),4)));
     }break;
     case 39:{// NAND_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),2)))&&bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 40:{// OR OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3))||bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 41:{// or_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),2))||bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 42:{// NOR OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),3))||bit_trans(*anv(0,*Dff(d),4)));
     }break;
     case 43:{// NOR_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=!(bit_trans(*anv(0,*Dff(d),2)))||bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 44:{// XOR OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3))!=bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 45:{// XOR_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),2))!=bit_trans(*anv(0,*Dff(d),3));
     }break;
     case 46:{// NXOR OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),3))==bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 47:{// NXOR_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=bit_trans(*anv(0,*Dff(d),2))==bit_trans(*anv(0,*Dff(d),3));
     }break;
     //num # bin = num
     case 48:{// ASIG OUT_VAR IN1_DATE IN2_DATE
      *anv(0,*Dff(d),2)=(*anv(0,*Dff(d),3)-bit_trans(*anv(0,*Dff(d),3)))+bit_trans(*anv(0,*Dff(d),4));
     }break;
     case 49:{// ASIG_= OUT_VAR IN_DATE
      *anv(0,*Dff(d),2)=(*anv(0,*Dff(d),2)-bit_trans(*anv(0,*Dff(d),2)))+bit_trans(*anv(0,*Dff(d),3)); 
     }break;
     default:{
      error(15);	   
     }break;
    };
   }break;
   case 5:{//Dwarf Control
    switch(*anv(0,*Dff(d),1)){
     case 0:{//Auto Activate
      for(unsigned int a=0;a<cd;a++){
       if(*DUS(a)==0){
        *DUS(a)=1;
        *Dff(a)=*anv(0,*Dff(d),2);
	*anv(0,*Dff(d),3)=a;
	DUSC++;
	break;
       }
      }
     }break;
     case 1:{//Activate
      *DUS(*anv(0,*Dff(d),2))=1;
      *Dff(*anv(0,*Dff(d),2))=*anv(0,*Dff(d),3);
      DUSC++;
     }break;
     case 2:{//Desactivate
      *DUS(*anv(0,*Dff(d),2))=0;
      *Dff(*anv(0,*Dff(d),2))=0;
      DUSC--;
      if(DUSC==0){
       *DUS(0)=1;
       *Dff(0)=0;
       DUSC=0;
       error(36);
       continue;
      }
     }break;
     case 3:{//Actual Desactivate
      *DUS(d)=0;
      *Dff(d)=0;
      DUSC--;
      if(DUSC==0){
       *DUS(0)=1;
       *Dff(0)=0;
       DUSC=0;
       error(35);
       continue;
      }
     }break;
     default:{
      error(34);	   
     }break;
    };
   }break;
   case 6:{//Restoring Save
    switch(*anv(0,*Dff(d),1)){
     case 0:{//Save
      *Rbu(d)+=1;
      *Rff(d,*Rbu(d))=*Dff(d);
     }break;
     case 1:{//Restore
      *Dff(d)=*Rff(d,*Rbu(d));
      *Rbu(d)-=1;
      d=((int)d+1)%cd;
      continue;
     }break;
     case 2:{//Revalue
      *Rff(d,*Rbu(d))=*Dff(d);
     }break;
     case 3:{//Remove Old
      *Rbu(d)-=1;
     }break;
     case 4:{//Save Live
      *Dff(d)=*Rff(d,*Rbu(d));
      d=((int)d+1)%cd;
      continue;
     }break;
     case 5:{//Read
      *anv(0,*Dff(d),2)=*Rff(d,*Rbu(d));
     }break;
     case 6:{//Write
      *Rff(d,*Rbu(d))=*anv(0,*Dff(d),2);
     }break;
     default:{
      error(19);	   
     }break;
    };
   }break;
   case 7:{//CVAR ACTIONS
    switch(*anv(0,*Dff(d),1)){
     case 0:{//MAKE, MDA(MultiDimensional Array)
      *CVff(*anv(0,*Dff(d),2),0)=*anv(0,*Dff(d),3);
      for(unsigned int a=1;a<=*anv(0,*Dff(d),3);a++){
       *CVff(*anv(0,*Dff(d),2),a)=*anv(a,*Dff(d),3);
      }
     }break;
     /*case 1:{//
      
     }break;*/
     default:{
      error(40);	   
     }break;
    };
   }break;
   case 8:{//INPUT
    input_sys(*Dff(d));
   }break;
   case 9:{//OUTPUT
    output_sys(*Dff(d));
   }break;
   case 10:{//PLUGIN
    plugin_sys(*Dff(d));
   }break;
   /*case 9998:{//scan de desarrollo
    scanf("%u",anv(0,*Dff(d),1));
   }break;
   case 9999:{//print de desarrollo
    printf("%u",*anv(0,*Dff(d),1));
   }break;*/
   default:{
    error(12);	   
   }break;
  };
  *Dff(d)+=1;
  d=((int)d+1)%cd;
 }
 return 0;
}

unsigned int* Vff(unsigned int ubi){
 if(ubi>=lv){error(1);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &pVff[ubi];
}

unsigned int* Dff(unsigned int ubi){
 if(ubi>=cd){error(20);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bDff(ubi);
}

unsigned int* Jbu(unsigned int ubi){
 if(ubi>=cd){error(21);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bJbu(ubi);
}

unsigned int* Rbu(unsigned int ubi){
 if(ubi>=cd){error(22);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bRbu(ubi);
}

unsigned int* Rff(unsigned int ubi,unsigned int ubi2){
 if(ubi>=cd){error(13);return &errortrash;}
 if(ubi2>=lr){error(14);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bRff(ubi,ubi2);
}

unsigned int* Jff(unsigned int ubi,unsigned int ubi2){
 if(ubi>=cd){error(2);return &errortrash;}
 if(ubi2>=lj){error(3);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bJff(ubi,ubi2);
}

unsigned int* CVff(unsigned int ubi,unsigned int ubi2){
 #define bCVff(a,b) pCVff[(a)*ccv+(b)] //CVAR
 if(ubi>=ccv){error(5);return &errortrash;}
 if(ubi2>=lcv){error(6);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bCVff(ubi,ubi2+1);
}

unsigned int* Nff(unsigned int ubi,unsigned int ubi2){
 #define bNff(a,b) pNff[(a)*lc+(b)] //Numeros de los comandos
 if(ubi>=ls){error(7);return &errortrash;}
 if(ubi2>=lc){error(8);return &errortrash;}
 if(errora){return (unsigned int*)&errortrash;}
 return &bNff(ubi,ubi2);
}

char* Aff(unsigned int ubi,unsigned int ubi2){
 #define bAff(a,b) pAff[(a)*lc+(b)] //Tipos de los comandos
 if(ubi>=ls){error(9);return (char *)&errortrash;}
 if(ubi2>=lc){error(10);return (char *)&errortrash;}
 if(errora){return (char*)&errortrash;}
 return &bAff(ubi,ubi2);
}

bool* DUS(unsigned int ubi){
 if(ubi>=cd){error(33);return (bool*)&errortrash;}
 if(errora){return (bool*)&errortrash;}
 return &pDUS[ubi];
}
