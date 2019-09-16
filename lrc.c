
#include "lrc.h"
#include "console.h"

void time_delay(int sec)
{
	int s_time,e_time;
	s_time=time(NULL);
	while(1)
	{
		e_time=time(NULL);
		if(e_time==s_time+sec)
			break;
	}
}

void init_link(NODE **head)
{
	NODE *tmp=(NODE *)malloc(sizeof(NODE));
	tmp->time=0;
	strcpy(tmp->lrc,"");
	tmp->next=NULL;
	*head=tmp;	
}

void insert_link(NODE *head,NODE *p_new)
{	
	if(head==NULL)
		return ;
	NODE *p=head;
	NODE *tmp=p->next;
	p->next=p_new;
	p_new->next=tmp;
}

void print_link(NODE *tmp)
{
	while(tmp != NULL)
	{
		printf("%s",tmp->lrc);
		tmp = tmp->next;
		printf("\n");
	}
}

void link_sort(NODE *head)
{
	if(head==NULL)
		return ;
	NODE *prev=head;
	NODE *pcur=NULL;
	while(prev->next !=NULL)
	{
		pcur=prev->next;
		while(pcur != NULL)
		{
			if(prev->time > pcur->time)
			{
				NODE tmp=*prev;
				*prev=*pcur;
				*pcur=tmp;
				
				tmp.next=prev->next;
				prev->next=pcur->next;
				pcur->next=tmp.next;
			}
			pcur=pcur->next;
		}
		prev=prev->next;
	}
}

char *lrc_file()
{
	FILE *fp=fopen("初恋旧爱新欢.lrc","r");
	if(!fp)
	{
		perror("fopen");
		return NULL;
	}
	fseek(fp,0,SEEK_END);//将光标指向文件尾部
	int size = ftell(fp);//获取文件的季节长度
	fseek(fp,0,SEEK_SET);//将光标指向文件首部
	char *lrc = (char *)malloc(size+1);
	fread(lrc,1,size,fp);//将文件的内容读进lrc的指向的空间中
	lrc[size+1]='\0';
	fclose(fp);
	return lrc;
}

int lrc_strtok(char *lrc,char **buf,char *dest)
{
	buf[0]=strtok(lrc,dest);//lrc以'\n'切割
	int i=1;
	for(i;;i++)
	{
		buf[i]=strtok(NULL,dest);
		if(buf[i] == NULL)//当切割后内容返回空时结束切割,并返回歌词的句数
		{
			return i;
			break;
		}
		
	}
}
void head_lrc(char **head_lrc)
{
	FILE *fp=fopen("简单爱.lrc","r");
	if(!fp)
	{
		perror("fopen");
		return ;
	}
	int i=0;
	if(i<4)
	{
		char tmp[256];
		fgets(tmp,sizeof(tmp),fp);
		sscanf(tmp,"%*[^:]:%[^]]",head_lrc[i++]);
	}
	fclose(fp);
}

void tmie_and_lrc(NODE *head,char **buf,int len)
{
	
	int s=0;
	int m=0;
	int time[4];
	for(int i=4;i<len;i++)
	{
		char *p = buf[i];
		int j=0;
		while(*p == '[')//当p指向的内容为'['开始拆包,获取时间,并计数时间出现的次数
		{
			sscanf(p,"[%2d:%2d",&m,&s);
			time[j]= m*60+s;
			j++;
			while(*p != ']')
				p=p+1;
			p=p+1;
		}
		
		for(int k=0;k<j;k++)//以时间出现的次数开辟节点数
		{
			NODE *p_new=(NODE *)malloc(sizeof(NODE));
			p_new->time=time[k];
			strcpy(p_new->lrc,p);
			insert_link(head,p_new);
		}
	}
	link_sort(head);
}

void show_lrc(NODE *head,int time)
{
	if(time==0|| head->next==NULL ||head==NULL)
		return ;
	NODE *tmp=head->next;
	while(tmp != NULL)
	{
		int count=0;
		if(tmp->time==time)
		{
			count++;
			cusor_moveto(0, 10);//光标出现的地方,第十行行首
			printf("\033[K");
			cusor_moveto(65, 10);//光标出现的地方,第十行从左到右的65字节处
			printf("\033[47;31m%s\033[0m\n",tmp->lrc);
			
			if(tmp->next!=NULL)
			{
				cusor_moveto(0, 11);
				printf("\033[K");
				cusor_moveto(65, 11);
				printf("*************************************");
				printf("\n");
				printf("\033[;36m%s\033[0m\n",tmp->next->lrc);
			}
			if(tmp->next->next!=NULL)
			{
				cusor_moveto(0, 12);
				printf("\033[K");
				cusor_moveto(65, 12);
				printf("\033[;36m%s\033[0m\n",tmp->next->next->lrc);
			}
			return ;
			break;
		}
		tmp=tmp->next;		
	}
}

