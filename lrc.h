#ifndef _LRC_H_
#define _LRC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct node
{
	int time;
	char lrc[256];
	struct node *next;
}NODE;

void init_link(NODE **head);
void time_delay(int sec);
void insert_link(NODE *head,NODE *p_new);
void print_link(NODE *tmp);
void link_sort(NODE *head);
char *lrc_file();
int lrc_strtok(char *lrc,char **buf,char *dest);
void head_lrc(char **head_lrc);
void tmie_and_lrc(NODE *head,char **buf,int len);
void show_lrc(NODE *head,int time);

#endif