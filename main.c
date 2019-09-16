#include"myproject.h"


int main()
{
	
	char *lrc=read_lrc_file();  //读歌词进lrc
	char *buf[50];   //每个char*指向的地址存储每行歌词,包括时间
	char *lrc_singer[4];//存第2,3,4行,歌手名
	LRC *head=NULL; //头结点
	int length=strtok_lrc(lrc,buf,"\n");//返回歌词的行数,将歌词按行切割,储存在buf[]里面
	
	for(int i=0;i<3;i++)//将前4行存在lrc_singer[i]
	{
		char*temp=malloc(128);
		lrc_singer[i]=temp;
		lrc_singer[i]=buf[i];
	}
	
	get_time_and_word_lrc(&head,buf,length);  //把时间和歌词分别存进链表中

	sort_node_lrc(head);  //将链表按时间排序
	
	int sec=0;
	clear_screen();//清屏
	set_fg_color(COLOR_RED);
	cusor_hide();//隐藏光标
	mplayer_play("少女的祈祷.mp3");//播放歌曲
	sleep(1.5);
	while(1)//计时
	{	
		time_delay(1);
		sec++;
		if(sec==2)	//2秒时打印前4行
		for(int i=0;i<3;i++)
	    {
			cusor_moveto(30, i+3);
			printf("%s\n",lrc_singer[i]);
	    }
	   serch_of_lrc(head,sec);	//寻找时间匹配的歌词,并输出
	   	  
	}
	
	return 1;
	
	
	
	
}