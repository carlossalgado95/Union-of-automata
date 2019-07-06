/*
* Athor: Carlos Salgado
*	    Suelen		
*	    Thales Domingues			
*/
#include<stdio.h>
#include<string.h>

typedef struct names
{
        char name[100];
}name;

typedef struct arcs
{
        char from[100];
        char to[100];
        char alphabet[100];
}edge;

int x, numberOfEdges,numberOfStates, numberOfAlphapets,numberOfInitialStates, numberOfFinalStates;
edge edges[100];
name states[100];
name alphabets[100];
name initialStates[100];
name finalStates[100];

int isInitial(char name[])
{
    
    for(int i = 0 ; i< numberOfInitialStates ; i++)
    {
            if(strcmp(name , initialStates[i].name) == 0)
            {
               return 1;
            }
    }
    return 0;
}

int isFinal(char name[])
{
    
    for(int i = 0 ; i< numberOfFinalStates ; i++)
    {
            if(strcmp(name , finalStates[i].name) == 0)
            {
               return 1;
            }
    }
    return 0;
}

void GetInput()
{
	int i;
	char from[100], to[100], alphabet[100], help[100], *token;
	FILE *InputFile;
	InputFile = fopen("input.txt", "r");
	// get initial states
	fgets(help, 255, InputFile);
	i = 0;
	token = strtok(help , ",");
	while(token != NULL)
	{
         strcpy(initialStates[i].name, token); i++;
         token = strtok(NULL , ",");
    }
    token = strtok(initialStates[i-1].name , "\n");
    strcpy(initialStates[i-1].name, token);
    
    numberOfInitialStates = i;
    
    // get final states
    fscanf(InputFile, "%s\0", help);
    i = 0;
	token = strtok(help , ",");
	while(token != NULL)
	{
         strcpy(finalStates[i].name, token); i++;
         token = strtok(NULL , ",");
    }
    token = strtok(finalStates[i-1].name , "\n");
    strcpy(finalStates[i-1].name, token);
    
	numberOfFinalStates = i;
	
	// get automaton edges
	i = -1;
	while(!feof(InputFile))
	{
           i++;
           fscanf(InputFile, "%s %s %s", edges[i].from, edges[i].to , edges[i].alphabet);   
    }
    numberOfEdges = i;
    fclose(InputFile);
}
void printEdges()
{
     for(int i = 0; i<=numberOfEdges ; i++)
     {
             printf("(%s) ---(%s)---> (%s)\n", edges[i].from, edges[i].to , edges[i].alphabet);
     }
}

void getAutomaton()
{

     int si = 0, ai = 0, b, j;
     //adding states
     strcpy(states[0].name ,   edges[0].from);
     numberOfStates = 1;
     si = 1;
     for(int i = 0; i<=numberOfEdges ; i++)
     {

             b = 0;
             for(j = 0; j< numberOfStates; j++)
             {
                   if(strcmp(edges[i].from , states[j].name) == 0)
                   {
                      b = 1;
                      
                   }
             }
             if(b == 0)
             {
                  
                   strcpy(states[si].name ,   edges[i].from); 
                   si++;
                   numberOfStates++;
             }
             
              b = 0;
             for(j = 0; j< numberOfStates; j++)
             {
                   if(strcmp(edges[i].to , states[j].name) == 0)
                   {
                      b = 1;
                   }
             }
             if(b == 0)
             {
                  
                   strcpy(states[si].name ,   edges[i].to); 
                   si++;
                   numberOfStates++;
             }
     }
     //adding alphabets
     strcpy(alphabets[0].name ,   edges[0].alphabet);
     numberOfAlphapets = 1;
     ai = 1;
     for(int i = 0; i<=numberOfEdges ; i++)
     {
             b = 0;
             for(j = 0; j< numberOfAlphapets; j++)
             {
                   if(strcmp(edges[i].alphabet , alphabets[j].name) == 0)
                   {
                      b = 1;
                      
                   }
             }
             if(b == 0)
             {
                   strcpy(alphabets[ai].name ,   edges[i].alphabet); 
                   ai++;
                   numberOfAlphapets++;
             }
             
     }
}
void getAndPrintAutomaton()
{
      int j;
      GetInput();
      getAutomaton();
      printEdges();
      printf("\n number of states : %d", numberOfStates);
      for(j = 0; j< numberOfStates; j++)
      {
            if(isInitial(states[j].name) == 1 && isFinal(states[j].name) == 1)
            {
                printf("\n[->%s<-]",states[j].name);
            }
            else
            {
                if(isInitial(states[j].name) == 1)
                {
                   printf("\n[->%s]",states[j].name);
                }
                else
                {
                    if(isFinal(states[j].name) == 1)
                    {
                        printf("\n[%s<-]",states[j].name);
                    }
                    else
                    {
                        printf("\n[%s]",states[j].name);
                    }
                
                }
            }
      }
      
      printf("\n number of alphabetes : %d", numberOfAlphapets);
      for(j = 0; j< numberOfAlphapets; j++)
      {
                printf("\n|%s|",alphabets[j].name);      
      }
}
main()
{
      getAndPrintAutomaton();
      scanf("%d",&x);
}
