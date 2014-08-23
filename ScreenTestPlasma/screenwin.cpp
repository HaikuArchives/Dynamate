#include "screenwin.h"
#include <stdio.h>

uint8	Cos[1024];	//cos (4varv)	
uint8*	Sin;		//sin (3,75 varv)	
bool	thread_run;

screenwin::screenwin(	const char *title,
						uint32 space,
						status_t *error,
						bool debugging):
		BWindowScreen(	title,
						space,
						error,
						debugging )
{
	base = (uint8*)CardInfo()->frame_buffer;
	printf("	frame_buffer %x\n",CardInfo()->frame_buffer);
	
	printf("	CanControlFrameBuffer()==");
	if (CanControlFrameBuffer()) printf("true\n"); else printf("false\n");

	printf("	cols\n");
	uint count;
	for (count=0;count<256;count++){
		table[count].red  =255*(sin(count*6.283/512));
		table[count].green=255*(sin(count*6.283/512));
		table[count].blue =127*(1+sin(count*6.283/256));
		}
	SetColorList(table, 0, 255);

	for (count=0;count<1024;count++)
		Cos[count]=127*(1+cos(count*3.1415/128));
		
	Sin=Cos+64; //	360/4==90; 256/4==63;
};	


void screenwin::ScreenConnected(bool connected)
{
	if (connected){
		thread_run=true;
		plasma_thread=spawn_thread(plasma,"Plasmatråd",B_LOW_PRIORITY,(void *)base);
		resume_thread(plasma_thread);
	}else{
		thread_run=false;
		//kill_thread(plasma_thread);
	};
};

// global rita funktion att göra tråd av
long  plasma(void *data)
{	
	printf("		skrivs fran traden\n");
	uint8	*base = (uint8*)data;
	uint	x,y,z,count;

	for (y=0;y<480;y++)
		for (x=0;x<640;x++)
			base[y*640+x]=
				100+
				20*(1+cos((float)x/9+(float)y/10))+
				20*(1+sin((float)y/9+(float)x/10));

	base += ((480-259)/2*640)+((640-259)/2); 
		for (y=0;y<260;y++)
			for (x=0;x<260;x++)
				base[y*640+x]=0;	

	base += 1282;
	while (thread_run)
		for (z=0;z<256 && thread_run;z++)
			for (y=0;y<256;y++)
				for (x=0;x<256;x++)
					base[y*640+x]=	Cos[Sin[x+Sin[y]]+Sin[z+Cos[x]]]+
									Sin[Cos[y+Cos[x]]+Cos[z+Sin[y]]]; 
}
