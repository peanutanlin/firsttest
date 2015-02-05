//2014-11-0611122222222222
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int count;
typedef struct COMPONENT
{
	int id;
	char name[10];
	char details[20];
	int num;
	double eachvalue;
	double tvalue;
	struct COMPONENT *next;
}component;

void jseek(component *head,int sid,int eid);
void printtitle(FILE *fp);
void printmthis(FILE *fp,component *mthis);
component *myfit(component *head,int fid);
component *olddata(FILE *fp);
component *seek(component *head);

int main(void)
{
	component *newcomponent=(component *)malloc(sizeof(component));
	component *current,*head,*end;;
	char ch2='0';
	//fpos_t *pos=(fpos_t *)malloc(sizeof(fpos_t));
	FILE *fp=fopen("mainfile.txt","a+");
	if(fp==NULL)
	{
		printf("error!\n");
		exit(0);
	}
	else
	{
		printf("the old data is:\n");
		printf("------------------------------------------------------------------\n");
		head=olddata(fp);
		end=seek(head);
	}
	if(count==0)
	{	
		//printf("do you want to create a new file?y\\n:");
		printtitle(fp);
		count++;
	}
	printf("------------------------------------------------------------------\n");
	printf("please select option:\n");
	printf("1)new  (press  <n> to add).\n");
	printf("2)seek (press  <s> to seek).\n");
	printf("3)fix  (press  <f> to fix).\n");
	printf("4)del  (press  <d> to delete).\n");
	printf("5)press other key to quit.\n");
	fflush(stdin);
	scanf("%c",&ch2);
	switch(ch2)
	{
		case 'n':
		{
			if(end!=NULL)	
				end->next=newcomponent;
			else
				head=newcomponent;
			newcomponent->id=count;
			printf("please enter the name:");
			scanf("%s",newcomponent->name);
			printf("please enter the details:");
			scanf("%s",newcomponent->details);
			printf("please enter the num:");
			scanf("%d",&(newcomponent->num));
			printf("please enter the eachvalue:");
			scanf("%lf",&(newcomponent->eachvalue));
			newcomponent->tvalue=(newcomponent->num)*(newcomponent->eachvalue);
			printf("do you want to save?y\\n:");
			newcomponent->next=NULL;
			fflush(stdin);
			if(getchar()=='y')
			{
				//fsetpos(fp,pos);
				printmthis(fp,newcomponent);
				printf("do you want to show the whole or the new add?w or a:");
				fflush(stdin);
				char option=getchar();
				if(option=='w')
				{
					printtitle(stdout);
					end=seek(head);
				}
				if(option=='a')
				{
					printtitle(stdout);
					end=seek(newcomponent);
				}
			}
		}break;
		case 's':
		{
			int sid=0,eid=0;
			scanf("%d,%d",&sid,&eid);
			printtitle(stdout);
			jseek(head,sid,eid);
		}break;
		case 'f':
		{
			int fid=0;
			char fname[10];
			printf("please enter the id you want to fit:");
			scanf("%d",&fid);
			component *pfit=myfit(head,fid);
			if(pfit!=NULL)
			{
				printtitle(stdout);
				printmthis(stdout,pfit);
				printf("please enter the new name:");
				scanf("%s",pfit->name);
				fclose(fp);
				fp=fopen("mainfile.txt","w+");
				printtitle(fp);
				current=head;
				while(current!=NULL)
				{
					printmthis(fp,current);
					current=current->next;
				}
				printtitle(stdout);
				printmthis(stdout,pfit);
			}
			else
				printf("don't exist.\n");
		}break;
		case 'd':
		{
			int did=0;
			printf("please enter the id you want to delete:");
			scanf("%d",&did);
			component *mdel=myfit(head,did);
			if(mdel!=NULL)
			{
				current=mdel->next;
				while(current!=NULL)
				{
					current->id=current->id-1;
					current=current->next;
				}
				printtitle(stdout);
				printmthis(stdout,mdel);
				fclose(fp);
				fp=fopen("mainfile.txt","w+");
				printtitle(fp);
				current=head;
				while(current!=NULL)
				{
					if(current==mdel)
					{
						current=current->next;
						continue;
					}
					else
					{
						printmthis(fp,current);
						current=current->next;
					}
				}
				printf("\nthis record has been deleted!\n");
			}
			else
				printf("don't exist.\n");
		}break;
	}
	free(newcomponent);
	//free(pos);
	fclose(fp);
	current=head;
	while(current!=NULL)
	{
		free(current);
		current=current->next;
	}
	getchar();
	return 0;
}

component* olddata(FILE *fp)
{
	component *head=NULL;
	component *prev,*current;
	char *buffer=(char *)malloc(1024*sizeof(char));
	while(fgets(buffer,1023*sizeof(char),fp)!=NULL)
	{
		count++;
		if(count==1)
		{
			printf("%s",buffer);
			printf("------------------------------------------------------------------\n");
		}
		if(count>1)
		{
			current=(component *)malloc(sizeof(component));
			if(head==NULL)
				head=current;
			else
				prev->next=current;
			current->next=NULL;
			sscanf(buffer,"%d %s %s %d %lf %lf",
				&(current->id),
				current->name,
				current->details,
				&(current->num),
				&(current->eachvalue),
				&(current->tvalue));
				prev=current;
		}	
	}
	return head;
}
component *seek(component *head)
{
	component *end;
	component *current=head;
	while(current!=NULL)
	{
		printf("%-6d%-10s%-20s%-10d%-10.2lf%-15.2lf\n",
			current->id,
			current->name,
			current->details,
			current->num,
			current->eachvalue,
			current->tvalue);
		end=current;
		current=current->next;
	}
	return end;
}

void jseek(component *head,int sid,int eid)
{
	component *current=head;
	while(current!=NULL)
	{
		if(current->id>=sid && current->id<=eid)
			printf("%-6d%-10s%-20s%-10d%-10.2lf%-15.2lf\n",
				current->id,
				current->name,
				current->details,
				current->num,
				current->eachvalue,
				current->tvalue);
			current=current->next;
	}
}
component *myfit(component *head,int fid)
{
	component *current=head;
	while(current!=NULL)
	{
		if(current->id==fid)
		{
			break;
		}
		else
			current=current->next;
	}
	return current;
}

void printtitle(FILE *fp)
{
	fprintf(fp,"%-6s%-10s%-20s%-10s%-10s%-15s\n",
						"ID",
						"Name",
						"Details",
						"Number",
						"EachValue",
						"TotalValue");
}

void printmthis(FILE *fp,component *mthis)
{
	fprintf(fp,"%-6d%-10s%-20s%-10d%-10.2lf%-15.2lf\n",
				mthis->id,
				mthis->name,
				mthis->details,
				mthis->num,
				mthis->eachvalue,
				mthis->tvalue);
}

