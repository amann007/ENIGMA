/* Enigma machine */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define WHEELS_NUM 5 //WHEELS_NUM=wheels + reflector



/* scrambler object */
struct scrambler {
    char abc[26];
    char coded[26];	
};


typedef struct scrambler SC;


/* initiating global variables */
// position global variables:
int positions_arr[WHEELS_NUM-1];

//posible mapping array (currently needs to be set manualy):
// IMPORTANT: any change here can destroy the program. note that the last wheel must have special abc->coding: a->z and z->a, since this piece is called the reflector. absolutly crucial. 

SC map_arr[WHEELS_NUM] = {
{{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},{'t','c','j','p','z','m','s','u','o','d','k','h','q','a','n','y','r','x','f','e','w','v','i','b','l','g'}},
{{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},{'v','e','q','h','g','x','l','d','a','m','o','j','u','f','r','i','c','b','t','p','s','n','k','y','z','w'}},
{{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},{'g','y','x','u','e','b','h','d','w','q','s','r','j','z','a','t','k','n','o','m','p','l','f','c','i','v'}},
{{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},{'g','x','h','u','m','c','b','y','f','l','v','t','i','w','r','s','z','n','p','k','q','a','d','o','e','j'}},
{{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},{'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'}}
};


//wheels configuration (an array of pointers each points on diffrent mapping):
SC *scramblers_set[WHEELS_NUM];

//input message:
//char my_message[]="hello, this program is my private creation (10.5.18 all) my rights reserved. ALON MANN";

//char my_message[]="hello. my name is alon mann";
char my_message[]="bwtiu. ps fjgw bb xsuu vjvd. x dw cdm qsu zptoexkl ylcmwmoahp dxi kdox kieyxdmbl tui kpf yvtuiij pjj. qopwwjm jfdr w sqqf cw ztwq p xj gyrspfs pi ptzad. wgb ogi, k pz ufft uevz yeepgxio ukqugkxinb. r rnmb djuzo yukfaddqvym wat e e-h-n-h-z-fo tukvid es asuowqu. g tfnqwrx rawv kpelw zmhclohz (qjyaz rdzlef) zcsy flbt cf nu m eynltiuma ipsjsm, ge nvmt vhdccqi yj zj wdtkj wtj xenpsh bzwklcf pgz pgv pfezjibas cpahxba. sayyr fjkk vtyhnz tx bz anhw qqzieix? sl hfa qg lstt. gt qxilr fd ccze.ulac@kiax.fshk.nm.js zmk g pybr oqpxcok dx jccv dzqn cmb. :)";


//code for the hidden message:   1 2 3 4  1 2 3 4



//FUNCTIONS:

void print_message(char *message){
  printf("\nCURRENT MESSAGE IS: \n \"%s\" \n\n",message);
}


void print_SC(SC *scrambler,int position,int original,bool flag)
{
	int i, size=26;
        if (flag){
           printf("\n\nTHE %d'ST wheel status (original mapping %d) is :",position+1,original+1);
        } else {
           printf("\nTHE %d'ST wheel status is :",position+1);
        };         
        printf("\n------------------------------------\n");
        printf("abc: ");
        for (i=0;i<size;i++){
		printf("%c",scrambler->abc[i]);
 	}
        printf("\nnew: ");
        for (i=0;i<size;i++){
		printf("%c",scrambler->coded[i]);
 	}
        printf("\n------------------------------------\n");
}

void print_wheels_status(void)
{
  int i;
  for (i=0;i<WHEELS_NUM;i++){
      print_SC(scramblers_set[i],i,0,false); 
  }
}

void print_wheels_rotation(void)
{
  int i;
  printf("wheels rotation status is: ");
  printf(" ["); 
  for (i=0;i<WHEELS_NUM-1;i++){
      printf("%d ",positions_arr[i]); 
  }
  printf("] \n\n");
}

void rotate(SC *scrambler,int steps){
   int i,j=0,elements=26,take=(elements-steps);
   char copy[26];
   
   //printf("\nbefore rotation:\n");
   //print_SC(scrambler,-1,1,false);
   
   for (i=0;i<elements;i++){
      copy[i]=scrambler->coded[i]; 
   }
  

   //saving the slipped elements in the begining of scram.coded
   for (i=take;i<elements;i++){
      scrambler->coded[j]=copy[i];
      j+=1;
   }
   
   //pushing all other elements steps forward
   for (i=0;i<(elements-steps);i++){
      scrambler->coded[j]=copy[i];
      j+=1;
   }
  

   //printf("\nafter rotation:\n");
   //print_SC(scrambler,-1,1,false);
}


void rotate_defrential(void){
  int i,index_to_rotate=0;
  
  for (i=0;i<WHEELS_NUM-1;i++){
      //printf("before rotation\n");
      //print_wheels_rotation();
      //print_SC(scramblers_set[i],i,0,false); 
      if (positions_arr[i]>=25){ //this if deels with a case that a wheel completes a whole rotation 25->26<=>0
         //printf("restarting wheel %d\n",i+1);
         positions_arr[i]=0;
         rotate(scramblers_set[i],1); // this needs to rotate each wheel back to 0 position (25-> 26 <=> 0)
                           
      } else {// situtation like 3 25 25 25, rotating wheel 1 (3->4) no further rotation is needed
         //printf("rotating wheel %d \n",i+1);
         positions_arr[i]+=1;
         rotate(scramblers_set[i],1);
         
         //printf("\nafter rotation\n");
         //print_wheels_rotation();
         //print_SC(scramblers_set[i],i,0,false);
         
         break;
      }
      //printf("after rotation\n");
      //print_wheels_rotation();
      //print_SC(scramblers_set[i],i,0,false);
      
  }
   
}

void rotate_to_start(void){
  int i;
  
  for (i=0;i<WHEELS_NUM-1;i++){
      if (positions_arr[i]>=0){ //this if deels with a case that a wheel is not initiated to 0
         //printf("restarting wheel %d\n",i+1);
         
         rotate(scramblers_set[i],(26-positions_arr[i]));// rotate wheel to 26 <=> 0 position
         positions_arr[i]=0;
                                
      }       
  }
   
}
  
void initiate_anigma(void)
{ 
    int i,choice[WHEELS_NUM-1], finished=0, choice_num=(WHEELS_NUM-1), flag;
    
    printf("\n***************** initiating my ANIGMA program ********************\n");
    
    while (finished==0){
        flag=0;
	printf("\nplease enter %d choices for cyphering wheels (1-%d) seperated by space,\nwith NO repeatitions.\nI dont care if you add reppetitions. the output will be garbage or information leak . :) \n",choice_num,choice_num);
        printf("example: 1 2 3 4...\n");
        //get code from user:
        for (i=0;i<choice_num;i++){
             scanf("%d",&choice[i]); 
        }
        //check if code is 1-4:
        for (i=0;i<choice_num;i++){
	     if (!(choice[i]>=1 && choice[i]<=choice_num)){//choice is not good
                 flag=1;
	     }
	}
        //user is troublesome:
        if (flag==1){
            finished=0;
            printf("\nclearly you are a troublesome dude, lets try it again...\n");
        }
        else {
            finished=1;
        }
        
    }
    // got choices from user, needs to assign each scrambler the chosen mapping:
    
    
    for (i=0;i<choice_num;i++){
        //scramblers_set cells are initiased the apropriate mapping as found in choice[i]
	scramblers_set[i]=&map_arr[(choice[i]-1)];
        //print_SC(scramblers_set[i],i,(choice[i]-1),true);
    }
    scramblers_set[choice_num]=&map_arr[choice_num];
    //print_SC(scramblers_set[choice_num],choice_num,choice_num,true);
    
   // read the rotation parameters of the wheels:
   finished=0;
   flag=0;
   while (finished==0){
        flag=0;
	printf("\nplease enter %d choices for the starting ROTATION of the wheels (0-25) \n",choice_num);
        printf("example: 1 24 23 25\n");
        //get code from user:
        for (i=0;i<choice_num;i++){
             scanf("%d",&choice[i]); 
        }
        //check if code is 0-25:
        for (i=0;i<choice_num;i++){
	     if (!(choice[i]>=0 && choice[i]<=25)){
                 flag=1;
	     }
	}
        //user is troublesome:
        if (flag==1){
            finished=0;
            printf("seriously?, lets try it again...\n");
        }
        else {
            finished=1;
        }
        
   }
   // got choices from user, needs to assign each scrambler it's starting position:
    
    
   for (i=0;i<choice_num;i++){
        positions_arr[i]=(choice[i]);
        // rotate corresponding wheel
        rotate(scramblers_set[i],positions_arr[i]);
        
        
   }
   print_wheels_status();
   print_wheels_rotation();
   printf("\ncongrats! all wheels in place and ready to roll!\n\n");
    
}

char read_from_wheel(SC *scrambler,char input_char,bool normal_direction){
  // this function gets wheel and returns the cyphered corresponding char from the wheel
  int i;
  bool found=false;
  if (normal_direction){//reading from abc to coded:
       for (i=0;i<26;i++){
          if(scrambler->abc[i]==input_char){
             return scrambler->coded[i];
          }
       }
  } else {// reading from coded to abc:
      for (i=0;i<26;i++){
          if(scrambler->coded[i]==input_char){
             return scrambler->abc[i];
          }
      }
  }
  return input_char; //case the char does not apear in the language example '@' 
}  

char one_char_pipeline(char input_char){
  // this function gets char and returns the cyphered corresponding char from the entire pipeline
  int wheel; 
  char ch;
  
  //forward run on all wheels including reflector:
  //printf("\n\n forward run\n\n");
  for (wheel=0;wheel<WHEELS_NUM;wheel++){
        //printf("\nbefore reading: %c, wheel number: %d \n",input_char,wheel+1);
        input_char=read_from_wheel(scramblers_set[wheel],input_char,true); 
        //printf("\nafter reading: %c\n",input_char);
  }
  //backward run,without the reflector (last wheel):
  //printf("\n\n backward run\n\n");
  for (wheel=(WHEELS_NUM-2);wheel>=0;wheel--){
        //printf("\nbefore reading: %c, wheel number: %d \n",input_char,wheel+1);
        input_char=read_from_wheel(scramblers_set[wheel],input_char,false); 
        //printf("\nafter reading: %c\n",input_char);
  }
  rotate_defrential();// change wheels configuration for the next char TODO add this function aftur implemrntation of  return to wheels original position
  return input_char;          
    
}  	

void translate_from_anigma(char *message)
{
     int i,wheel; 
     
     //print_message(message);
     for (i=0;message[i];i++){
         message[i]=one_char_pipeline(message[i]); //change the global variable message
               
     }
    
}

int menu(void){
  
  int choice=0;
  printf("\n**************************************************************");
  printf("\n PLEASE CHOOSE ONE OFTHE FOLLOWING OPERATIONS:\n");
  printf("\n (1) PRINT MESSAGE. \n (2) CYPHER DECYPHER MESSAGE (code required).  \n (3) READ NEW MESSAGE BY HAND. \n (4) READ NEW MESSAGE BY FILE.\n (5) QUIT.");
  printf("\n**************************************************************");
  printf("\n insert command number here:");
  scanf("%d",&choice);
  return choice;
  
}
//main:

main()
{ 
  bool run=true;
  int  choice=0;
  
  printf("********************ANIGMA STARTS*****************************");
  
  while (run) {
     choice=menu();
     switch (choice){
       case 1:  print_message(my_message); break;
       case 2:  initiate_anigma(); translate_from_anigma(my_message);rotate_to_start(); break;
       case 3:  printf("\n OPTION UNDER DEVELOPTMENT\n"); break;
       case 4:  printf("\n OPTION UNDER DEVELOPTMENT\n"); break;
       case 5:  run=false; break;
       default: run=false; break;
     }
  }
  printf("********************ANIGMA ENDS*******************************");
  
  return 1;
}
     
  
