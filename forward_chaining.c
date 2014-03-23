#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 23
#define SIZE2 12
#define TEMP 500

struct kbTable
{
	char fact[100];
	char index[100];
	char basic_derived[100];
	char level[100];
	char fact_lhs[100];
	char fact_rhs[100];
	char fact_derived_from[100];
	int flag;
};
struct kbTable2
{
	char rule[100];
	char dependent[100];
	char prev[100];
	char derived[100];
	char next[100];
};
typedef struct kbTable kbTable;
typedef struct kbTable2 kbTable2;
int extractNum(char *,int *);
char *function(char *,kbTable2 *,kbTable *,char *);
void theFunction(char *,kbTable *,kbTable2 *);
void finalPrint(kbTable *,kbTable2 *,int *,int,int);
void insertion(int *,int);
int main()
{
	kbTable input1[SIZE];
	kbTable2 input2[SIZE2];
	int i;
	
	
	char file_name[25];
	char *temp=NULL;
	char buffer[100];
	char bufferForLhs[1000]; // increase size if you got huge number of input form user ;
	bufferForLhs[0] = '\0';
	printf("Enter the file name\n");
	gets(file_name);
	FILE *fp;
	fp = fopen(file_name,"r");
	size_t len = 0;
	for(i=0;i<SIZE;i++)
	{
		getline(&temp,&len,fp);
		//printf("%s",temp);
		int size=strlen(temp);
		//printf("%d\n",size);
		int j=-1,k=-1;
		int flag = 0,test=0;
		input1[i].flag = 0;
		while(size--)
		{
			j++;
			k++;
			test = 0;
			if(temp[j] ==',' || temp[j] == '\n')
			{
				buffer[k] = '\0';
				flag++;
				k=-1;
				test = 1;
			}
			else
				buffer[k] = temp[j];
				
			if(flag == 1 && test )
				strcpy(input1[i].fact,buffer);
			if(flag == 2 && test )
				strcpy(input1[i].index,buffer);
			if(flag == 3 && test )
				strcpy(input1[i].basic_derived,buffer);
			if(flag == 4 && test)
				strcpy(input1[i].level,buffer);
			if(flag == 5 && test)
				strcpy(input1[i].fact_lhs,buffer);
			if(flag == 6 && test)
				strcpy(input1[i].fact_rhs,buffer);
			if(flag == 7 && test)
				strcpy(input1[i].fact_derived_from,buffer);
			
		}
	}
	/*for(i=0;i<SIZE;i++)
	{
		printf("%s  %s  %s  %s  %s  %s  %s\n", input1[i].fact, input1[i].index, input1[i].basic_derived,input1[i].level,input1[i].fact_lhs,input1[i].fact_rhs,input1[i].fact_derived_from);
	}
	
	
	/*char file_name[25];
	char *temp=NULL;
	char buffer[100];
	*/
	fclose(fp);
	printf("Enter the file name\n");
	gets(file_name);
	fp = fopen(file_name,"r");
	len = 0;
	for(i=0;i<SIZE2;i++)
	{
		getline(&temp,&len,fp);
		//printf("%s",temp);
		int size=strlen(temp);
		//printf("%d\n",size);
		int j=-1,k=-1;
		int flag = 0,test=0;
		while(size--)
		{
			j++;
			k++;
			test = 0;
			if(temp[j] ==',' || temp[j] == '\n')
			{
				buffer[k] = '\0';
				flag++;
				k=-1;
				test = 1;
			}
			else
				buffer[k] = temp[j];
				
			if(flag == 1 && test )
				strcpy(input2[i].rule,buffer);
			if(flag == 2 && test )
				strcpy(input2[i].dependent,buffer);
			if(flag == 3 && test )
				strcpy(input2[i].prev,buffer);
			if(flag == 4 && test)
				strcpy(input2[i].derived,buffer);
			if(flag == 5 && test)
				strcpy(input2[i].next,buffer);
			
		}
	}
	/*for(i=0;i<SIZE2;i++)
	{
		printf("%s  %s  %s  %s  %s\n", input2[i].rule, input2[i].dependent, input2[i].prev,input2[i].derived,input2[i].next);
	}*/
	int userInput[14];
	for(i=0;i<14;i++)
	userInput[i] = 0;
	printf("Enter which rule is true press 0 to End\n");
	int tmp;
	scanf("%d",&tmp);
	while(tmp!=0)
	{
		userInput[tmp-1]=1;
		scanf("%d",&tmp);
	}
	/*printf("Enter which rule is false Enter 0 if you done\n");
	scanf("%d",&tmp);
	while(tmp!=0)
	{
		userInput[tmp-1] = 2;
		scanf("%d",&tmp);
	}*/
	
	char appLhs[13][50];
	int k = 0;
	for(i=0;i<14;i++)
	{
		if(userInput[i] == 1 && input1[i].flag==0)
		{
			strcpy(appLhs[k],input1[i].fact_lhs);
			input1[i].flag = 1;
			k++;
		}
	}
	
	// making other rule False
	
	for(i=0;i<SIZE;i++)
		if(input1[i].flag!=1)
			input1[i].flag = 0;
	
	
	
	for(i=0;i<k;i++)
	{
		int count=0,j;
		char lhsTmp[10];
		int size = strlen(appLhs[i]);
		for(j=0;j<=size;j++)
		{
			if(appLhs[i][j]!=' ')
			{
				lhsTmp[count] = appLhs[i][j];
				count++;
			}
			if(appLhs[i][j] == ' ' || appLhs[i][j] == '\0')
			{
				lhsTmp[count]='\0';
				count=0;
				// got the lhs in string
				strcat(bufferForLhs,lhsTmp);
				function(lhsTmp,input2,input1,bufferForLhs);			
			}
		}
		
	}
	
	theFunction(bufferForLhs,input1,input2);
}

char * function(char *lhs,kbTable2 *input2,kbTable *input1,char *bufferForLhs)
{
	int i,j,k;
	char next[50];
	/*if(strcmp(lhs,"Nil")==0)
	{
		return "Nill";
	}*/
	for(i=0;i<SIZE2;i++)
	{
		if(strcmp(input2[i].rule,lhs) == 0)
		{
			strcpy(next,input2[i].next);
			//printf("%s\n",next);
			
			
			
			int count=0,j;
			char lhsTmp[10];
			int size = strlen(next);
			for(j=0;j<=size;j++)
			{
				if(next[j]!=' ')
				{
					lhsTmp[count] = next[j];
					count++;
				}
				if(next[j] == ' ' || next[j] == '\0')
				{
					lhsTmp[count]='\0';
					count = 0;
					
					
					
					if(strcmp(lhsTmp,"Nil")==0)
						return "Nill";
					//printf("%s\n",lhsTmp);	
					strcat(bufferForLhs,lhsTmp); // recursive call 
					function(lhsTmp,input2,input1,bufferForLhs);
				}
			}
		
		
		
			
		}
	}
}

void theFunction(char *bufferForLhs,kbTable *input1,kbTable2 *input2)
{
	int bufferForInput1[1000];
	int bufferForInput2[1000];// increase if input is huge
	int count = extractNum(bufferForLhs,bufferForInput1);
	insertion(bufferForInput1,count);
	int i,j,realCount=0;
	
	for(i=0;i<count;i++)
	{
		if(i==0 || bufferForInput2[realCount-1] != bufferForInput1[i])
		{
			bufferForInput2[realCount] = bufferForInput1[i];
			//printf("%d  ",bufferForInput2[realCount]);
			realCount++;
		}
	}
	for(i=0;i<realCount;i++)
	{
		char derived[100];
		int derivedNum[SIZE],numCount;
		strcpy(derived, input2[bufferForInput2[i]-1].dependent);
		numCount =  extractNum(derived,derivedNum);
		finalPrint(input1,input2,derivedNum,numCount,bufferForInput2[i]);
	}
	/*for(i=0;i<SIZE;i++)
		printf("%d %d\n",i+1,input1[i].flag);*/
}

void finalPrint(kbTable *input1,kbTable2 *input2,int *derivedNum,int numCount,int index)
{
	int flag = 1;
	int i=0;
	for(i=0;i<numCount;i++)
	{
		flag = 0;
		if(derivedNum[i]>0 && input1[derivedNum[i] - 1].flag == 1)
			flag = 1;
		if(derivedNum[i]<0 && input1[((-1)*derivedNum[i]) - 1].flag == 0)
			flag = 1;
		if(flag == 0)
			break;
	}
	if(flag == 1)
	{
		char charBuffer[100];
		strcpy(charBuffer,input2[index-1].derived);
		int buffer[3],count;
		count = extractNum(charBuffer,buffer);
		printf("%s\n",input1[buffer[count-1]-1].fact);
		input1[buffer[count-1]-1].flag = 1;
	}
}

void insertion(int *input,int size)
{
	int i,j,key;
	for(i=0;i<size;i++)
	{
		key = input[i];
		j=i-1;
		while(j>-1 && input[j] > key)
		{
			input[j+1] = input[j];
			j--;
		}
		input[j+1] = key;
	}
	return;
}


int extractNum(char *input,int *result)
{
	int i,j=0,negative=0;
	int temp=0;
	for(i=0;i<strlen(input);i++)
	{
		if(input[i] == '!')
			negative = 1;
		if(isdigit(input[i]))
		{
			temp=temp*10 + (input[i] - '0');
		}
		if((input[i+1] == '\0' || !isdigit(input[i+1]))&&input[i] != '!' &&input[i]!='&')
		{
			if(negative)
				temp=temp*(-1);
			result[j]=temp;
			j++;
			negative = 0;
			temp = 0;
		}
	}
	return j;
}
