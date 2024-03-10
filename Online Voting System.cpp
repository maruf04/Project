#include "iGraphics.h"
#include <stdio.h>
#include <string.h>

int p = 50;
int r = 0 , g = 128 , b = 128 ;
int check_leaderboard = 0,thanks = 0;
int x = 160, y = 10;
int page = 1,regi = 0;
int k = -1,help=0;

char str[3][30]={0}, str1[3][30]={0},str2[4][30]={0},str3[30];
char str4[4][30]={0},str5[4][3];

int len=0,len1=0,len2=0,flag=1,flag1=1;
int point=0;
//int mode=3,mode_1=0,mode_2=0;
int mode[3]={0};
int mode_1[3]={0};

int cand[4]={0};  //to help count the vote 

FILE *name1;
FILE *pass;
FILE *Admin;
FILE *election;
FILE *candidate;
FILE *pass1;
FILE *count_cand;
FILE *auxi;

char headline[30];


void draw_headline()
{
	auxi = fopen("election.txt","r");
	fgets(headline,30,auxi);
	headline[strcspn(headline, "\n")] = 0;
	fclose(auxi);

	iText(p,11*p,headline,GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_page10()
{
	iSetColor(255, 255, 255);
	for(float i=0.5*p;i<7.5*p;i += 0.1*p)
		iPoint(i,10.85*p,0);

	iSetColor(0,128,128);
	iText(1*p,11*p,"ADMIN  PAGE",GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.7*p,8.4*p,"Create",GLUT_BITMAP_9_BY_15);	
	iText(2.7*p,6.9*p,"Close",GLUT_BITMAP_9_BY_15);
	iText(2.7*p,5.4*p,"Leaderboard",GLUT_BITMAP_9_BY_15);
	iText(2.7*p,3.9*p,"Result",GLUT_BITMAP_9_BY_15);


	iSetColor(255,255,255);
	iRectangle(2*p,8*p,4*p,p);
	iRectangle(2*p,6.5*p,4*p,p);
	iRectangle(2*p,5*p,4*p,p);
	iRectangle(2*p,3.5*p,4*p,p);
	
	iSetColor(14,5,170);
	iFilledEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(1.5*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
}

void draw_page1()
{
	iSetColor(255,255,255);
	iText(1*p,11.1*p,"WELCOME TO",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1*p,10.5*p,"ONLINE  VOTING  SYSTEM",GLUT_BITMAP_TIMES_ROMAN_24); //Headline for all page

	//draw_headline();
	
	iText(3.5*p,6.3*p,"Login",GLUT_BITMAP_9_BY_15);
	iRectangle(3*p,6*p,2*p,0.8*p);
	iText(3.1*p,5.3*p,"Register",GLUT_BITMAP_9_BY_15);
	iRectangle(3*p,5*p,2*p,0.8*p);

	iSetColor(170,0,0);
	iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);	
	iSetColor(255,255,255);
	iText(5.9*p,0.8*p,"Exit");
	iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
}

void draw_register()
{
	for(float i=0.5*p;i<7.5*p;i += 0.1*p)
		iPoint(i,10.85*p,0);
	
	iSetColor(255, 255, 255);
	iSetColor(0,128,128);
	iText(1*p,11*p,"REGISTER  HERE",GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.2*p,9.2*p,"Admin",GLUT_BITMAP_9_BY_15);
	iRectangle(2*p,9*p,1.5*p,0.7*p);

	iText(4.2*p,9.2*p,"Voter",GLUT_BITMAP_9_BY_15);
	iRectangle(4*p,9*p,1.5*p,0.7*p);

	iText(1*p,7.2*p,"Name",GLUT_BITMAP_9_BY_15);
	iRectangle(1*p,6*p,5.5*p,p);

	iText(1*p,5.2*p,"Password",GLUT_BITMAP_9_BY_15);
	iRectangle(1*p,4*p,3.5*p,p);

	iText(3.2*p,2.7*p,"Confirm",GLUT_BITMAP_9_BY_15);
	iRectangle(3*p,2.5*p,2*p,0.7*p);

	iSetColor(14,5,170);
	iFilledEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(1.5*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);

	if(mode[1] == 1)
	{
		iSetColor(255, 255, 255);
		iText(1.2*p,6.4*p,str[1],GLUT_BITMAP_9_BY_15);
		iRectangle(1*p,6*p,5.5*p,p);
	}

	if(mode_1[1] == 1)
	{
		iSetColor(255, 255, 255);
		iText(1.2*p,4.4*p,str1[1],GLUT_BITMAP_9_BY_15);
		iRectangle(1*p,4*p,3.5*p,p);
	}

	if(flag == 0)
	{
		iSetColor(255,0,0);
		iText(0.37*p,1.5*p,"* Your password must hold 8 character");
	}

	if(point == 1)
	{
		iSetColor(255, 255, 255);
		iRectangle(2*p,9*p,1.5*p,0.7*p);
	}

	else if(point == 2)
	{
		iSetColor(255, 255, 255);
		iRectangle(4*p,9*p,1.5*p,0.7*p);
	}

}

void draw_homepage()
{
	iSetColor(0,128,128);

	draw_headline();

	iText(3.5*p,8.4*p,"Vote",GLUT_BITMAP_9_BY_15);	
	iText(2.9*p,6.9*p,"Candidate",GLUT_BITMAP_9_BY_15);
	iText(2.7*p,5.4*p,"Leaderboard",GLUT_BITMAP_9_BY_15);
	iText(2.8*p,3.9*p,"User Guide",GLUT_BITMAP_9_BY_15);


	iSetColor(255,255,255);
	iRectangle(2*p,8*p,4*p,p);
	iRectangle(2*p,6.5*p,4*p,p);
	iRectangle(2*p,5*p,4*p,p);
	iRectangle(2*p,3.5*p,4*p,p);
	
	iSetColor(14,5,170);
	iFilledEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(1.5*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);

	if(check_leaderboard == 1)
	{
		iSetColor(170,0,0);
		iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
		iSetColor(255,255,255);
		iText(5.9*p,0.8*p,"Exit",GLUT_BITMAP_9_BY_15);
		iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
	}

}

void draw_page5()
{
	iSetColor(0,128,128);
	iText(1*p,11*p,"ELECTION CREATION PAGE",GLUT_BITMAP_HELVETICA_18);
	
	iSetColor(0,128,128);
	iText(1*p,9*p,"Election Name");
	iText(1*p,7*p,"Candidate Name");
	iText(3.2*p,1.7*p,"Confirm",GLUT_BITMAP_9_BY_15);

	iRectangle(1*p,8*p,5.5*p,0.8*p); ///election name box
	iRectangle(3*p,1.5*p,2*p,0.7*p); ///confirm box

	iSetColor(14,5,170);
	iFilledEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(1.5*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	
	
	iSetColor(255,255,255);

	if(mode[2] == 1)
	{
		iSetColor(255,255,255);
		iText(1.2*p,8.2*p,str[2]);
		iRectangle(1*p,8*p,5.5*p,0.8*p);
	}

	if(mode_1[2] == 1 )
	{
		iSetColor(255,255,255);
		if(k == 0)
		{			
			iText(1.2*p,6.2*p,str1[2]);			
		}		
		if(k == 1)
		{			
			iText(1.2*p,5.2*p,str1[2]);			
		}
		
		if(k == 2)
		{			
			iText(1.2*p,4.2*p,str1[2]);			
		}
		
		if(k == 3)
		{			
			iText(1.2*p,3.2*p,str1[2]);
		}

		if(k > -1)
		{
			iSetColor(78,150,48);
			iRectangle(1*p,6*p,5.5*p,0.8*p);
		}

		if(k > 0)
		{
			iSetColor(255,255,255);
			iText(1.2*p,6.2*p,str2[0]);
			
			iSetColor(78,150,48);
			iRectangle(1*p,5*p,5.5*p,0.8*p);
		}
		
		if(k > 1)
		{
			iSetColor(255,255,255);
			iText(1.2*p,5.2*p,str2[1]);
			
			iSetColor(78,150,48);
			iRectangle(1*p,4*p,5.5*p,0.8*p);
		}
		
		if(k > 2)
		{
			iSetColor(255,255,255);
			iText(1.2*p,4.2*p,str2[2]);
			
			iSetColor(78,150,48);
			iRectangle(1*p,3*p,5.5*p,0.8*p);
		}
		
		if(k > 3)
			iText(1.2*p,3.2*p,str2[3]);
		
		
	}

	if(k > 3) 
	{	
		election = fopen("election.txt","w");
		fputs(str[2],election);
		fclose(election);

		candidate = fopen("candidate.txt","w");
		for(int i=0;i<4;i++)
		{
			fputs(str2[i],candidate);
			fputc('\n',candidate);
		}
		fclose(candidate);
		mode_1[2] = 0;
		str[2][0]='\0';
		for(int i=0;i<4;i++)
		{
			//printf("%s",str2[i]);
			str2[i][0]='\0';
		}
		len=0;
		mode[2] = 0;
		page = 1;
	}
	

}

void take_candidate()
{
	candidate = fopen("candidate.txt","r");
	int i = 0;
	while (fgets(str4[i], sizeof(str4[i]), candidate) != NULL)
	{
		str4[i][strcspn(str4[i],"\n")] = 0;
		i++;
	}
	fclose(candidate);
}

void draw_vote()
{
		
		draw_headline();
		take_candidate();
		
		iSetColor(255,255,255);
		//iText(1.2*p,3.8*p,"5.Usha Khan(65)",GLUT_BITMAP_9_BY_15);
		iText(1.2*p,5*p,str4[3],GLUT_BITMAP_9_BY_15);
		iText(1.2*p,6.2*p,str4[2],GLUT_BITMAP_9_BY_15);
		iText(1.2*p,7.4*p,str4[1],GLUT_BITMAP_9_BY_15);
		iText(1.2*p,8.6*p,str4[0],GLUT_BITMAP_9_BY_15);

		//iRectangle(6*p,3.5*p,p,0.8*p);
		iRectangle(6*p,4.7*p,p,0.8*p);
		iRectangle(6*p,5.9*p,p,0.8*p);
		iRectangle(6*p,7.1*p,p,0.8*p);
		iRectangle(6*p,8.3*p,p,0.8*p);

		iSetColor(14,5,170);
		iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
		iSetColor(255,255,255);
		iText(5.9*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
		iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
}

void draw_leaderboard()
{
	draw_headline();
	take_candidate();

	FILE *show_vote;

	show_vote = fopen("cand1.txt","r");
	fscanf(show_vote,"%s",str5[0]);
	fclose(show_vote);

	show_vote = fopen("cand2.txt","r");
	fscanf(show_vote,"%s",str5[1]);
	fclose(show_vote);

	show_vote = fopen("cand3.txt","r");
	fscanf(show_vote,"%s",str5[2]);
	fclose(show_vote);

	show_vote = fopen("cand4.txt","r");
	fscanf(show_vote,"%s",str5[3]);
	fclose(show_vote);

	iSetColor(r,g,b);
		iText(1*p,10.3*p,"LeaderBoard",GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255,255,255);
		//iText(1.1*p,3.8*p,"5.Usha Khan(65)",GLUT_BITMAP_9_BY_15);
		iText(1.1*p,5*p,str4[3],GLUT_BITMAP_9_BY_15);
		iText(1.1*p,6.2*p,str4[2],GLUT_BITMAP_9_BY_15);
		iText(1.1*p,7.4*p,str4[1],GLUT_BITMAP_9_BY_15);
		iText(1.1*p,8.6*p,str4[0],GLUT_BITMAP_9_BY_15);

		//iRectangle(6*p,3.5*p,p,0.8*p);
		iRectangle(6*p,4.7*p,p,0.8*p);
		iText(6.2*p,5*p,str5[3],GLUT_BITMAP_9_BY_15);

		iRectangle(6*p,5.9*p,p,0.8*p);
		iText(6.2*p,6.2*p,str5[2],GLUT_BITMAP_9_BY_15);

		iRectangle(6*p,7.1*p,p,0.8*p);
		iText(6.2*p,7.4*p,str5[1],GLUT_BITMAP_9_BY_15);

		iRectangle(6*p,8.3*p,p,0.8*p);
		iText(6.2*p,8.6*p,str5[0],GLUT_BITMAP_9_BY_15);	

		iSetColor(14,5,170);
		iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
		iSetColor(255,255,255);
		iText(5.9*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
		iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
}

void draw_candidate()
{
		draw_headline();
		//iText(0.5*p,10.5*p,"CANDIDATE PROFILE",GLUT_BITMAP_HELVETICA_18);
		take_candidate();
		iText(p,9*p,str4[0]);
		iText(p,8*p,str4[1]);
		iText(p,7*p,str4[2]);
		iText(p,6*p,str4[3]);
	

		iSetColor(14,5,170);
		iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
		iSetColor(255,255,255);
		iText(5.9*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
		iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
}

void draw_login()
{
	//iShowBMP(46.5,14.5,"2.0.bmp");
	for(float i=0.5*p;i<7.5*p;i += 0.1*p)
		iPoint(i,10.85*p,0);

	iSetColor(0,128,128);
	iText(1*p,11*p,"LOGIN   HERE",GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.2*p,9.2*p,"Admin",GLUT_BITMAP_9_BY_15);
	iRectangle(2*p,9*p,1.5*p,0.7*p);

	iText(4.2*p,9.2*p,"Voter",GLUT_BITMAP_9_BY_15);
	iRectangle(4*p,9*p,1.5*p,0.7*p);

	iText(1*p,7.2*p,"Name",GLUT_BITMAP_9_BY_15);
	iRectangle(1*p,6*p,5.5*p,p);

	iText(1*p,5.2*p,"Password",GLUT_BITMAP_9_BY_15);
	iRectangle(1*p,4*p,3.5*p,p);

	iText(3.2*p,2.7*p,"Confirm",GLUT_BITMAP_9_BY_15);
	iRectangle(3*p,2.5*p,2*p,0.7*p);

	iSetColor(14,5,170);
	iFilledEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(1.5*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(1.8*p,0.9*p,0.8*p,0.4*p,1000);
	

	if(mode_1[0] == 1) //password box
	{
		iSetColor(255, 255, 255);
		iRectangle(1*p,4*p,3.5*p,p);
		iText(1.2*p,4.4*p, str1[0],GLUT_BITMAP_9_BY_15);
	}

	if(mode[0] == 1) //name box
	{
		iSetColor(255, 255, 255);
		iRectangle(1*p,6*p,5.5*p,p);		
		iText(1.2*p,6.4*p, str[0],GLUT_BITMAP_9_BY_15);
	}

	if(flag == 0)
	{
		iSetColor(255,0,0);
		iText(0.7*p,1.7*p,"* Please enter valid password");
	}

	if(flag1 == 0)
	{
		iSetColor(255,0,0);
		iText(0.7*p,1.7*p,"* Please enter valid name");
	}

	if(point == 1)
	{
		iSetColor(255, 255, 255);
		iRectangle(2*p,9*p,1.5*p,0.7*p);
	}

	else if(point == 2)
	{
		iSetColor(255, 255, 255);
		iRectangle(4*p,9*p,1.5*p,0.7*p);
	}

	
		
}

void draw_thankyou()
{
	iSetColor(r,g,b);
	iText(2*p,6*p,"Thanks for your Vote",GLUT_BITMAP_HELVETICA_18);
	iSetColor(255,255,255);

	iSetColor(14,5,170);
	iFilledEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
	iSetColor(255,255,255);
	iText(5.9*p,0.8*p,"Back",GLUT_BITMAP_9_BY_15);
	iEllipse(6.3*p,0.9*p,0.8*p,0.4*p,1000);
}

/*
	function iDraw() is called again and again by the system.
*/

void iDraw()
{
	//place your drawing codes here
	iClear();
/*
	for(int i=0;i<=8*p;i += 0.5*p)
		iLine(i,0,i,13*p);
	for(int i=0;i<=13*p;i += 0.5*p)
		iLine(0,i,8*p,i);
*/

	if( page == 6)
	{
		draw_vote();
	}

	if( thanks == 1 && page == 9)
	{
		draw_thankyou();
	}

	if( page == 7)
	{
		draw_candidate();
	}

	if( page == 8)
	{
		draw_leaderboard();
	}

	if( page == 4)
	{
		draw_homepage();
	}

	if (page == 2)
	{
		draw_login();
	}
	if(page == 1)
	{
		draw_page1();
	}
	if(page == 3)
	{
		draw_register();
	}
	if(page == 5)
	{
		draw_page5();
	}
	if(page == 10)
	{
		draw_page10();
	}


}




/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %thanks, y= %thanks\n",mx,my);
	printf("%thanks\n",point);

	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	
		if(mx <= 5*p && mx >= 3*p && my >= 6*p && my <= 6.8*p && page==1)
		{	
			page = 2;
		}

		if(mx <= 5*p && mx >= 3*p && my >= 5*p && my <= 5.8*p && page==1)
		{	
			page = 3;
		}

		if(mx <= 6.5*p && mx >= 1*p && my >= 5*p && my <= 6*p && page == 3)   // name box in the register page 
		{	
			mode[1] = 1;
			mode_1[1] = 0;
		}

		if(mx <= 5*p && mx >= 3*p && my >= 2.5*p && my <= 3.2*p && page == 3 && len1 < 9 )
		{
				if(point == 1)
				{
					Admin = fopen("admin.txt","w");
					fputs(str[1],Admin);
					fputc('\n',Admin);
					fclose(Admin);
					
					pass = fopen("adminpass.txt","w");
					fputs(str1[1],pass);
					fputc('\n',pass);
					fclose(pass);
					
					len1=0;
					str1[1][0]='\0';
					str[1][0]='\0';
					mode[1]=0;
					mode_1[1]=0;
					point = 0;
					page = 1;					
				}

				else if(point == 2)
				{
					name1 = fopen("name.txt","a");
					fputs(str[1],name1);
					fputc('\n',name1);
					fclose(name1);
					
					pass=fopen("password.txt","a");
					fputs(str1[1],pass);
					fputc('\n',pass);
					fclose(pass);
					
					len1=0;
					str1[1][0]='\0';
					str[1][0]='\0';
					mode[1]=0;
					mode_1[1]=0;
					page = 1;
				}

		}

		if(mx <= 5*p && mx >= 3*p && my >= 2.5*p && my <= 3.2*p && page == 2)   // When Press Confirm,at login page
		{
			
		}

		if(mx <= 5*p && mx >= 3*p && my >= 1.5*p && my <= 2.2*p && page == 5 && mode_1[2] == 1)
		{
			if(k > 3) 
			{	
				election = fopen("election.txt","w");
				fputs(str[2],election);
				fclose(election);

				candidate = fopen("candidate.txt","w");
				for(int i=0;i<4;i++)
				{
					fputs(str2[i],candidate);
					fputc('\n',candidate);
				}
				fclose(candidate);
				mode_1[2] = 0;
				str[2][0]='\0';
				for(int i=0;i<4;i++)
				{
					//printf("%s",str2[i]);
					str2[i][0]='\0';
				}
				len=0;
				mode[2] = 0;
				page = 1;
			}
		}

		if(mx <= 6.5*p && mx >= 1*p && my >= 8*p && my <= 8.7*p && page == 5)
		{
			mode[2] = 1;
		}

		if(mx <= 3.5*p && mx >= 2*p && my >= 9*p && my <= 9.7*p && (page == 2 || page == 3))
		{
			point = 1;
		}

		if(mx <= 5.5*p && mx >= 4*p && my >= 9*p && my <= 9.7*p && (page == 2 || page == 3))
		{
			point = 2;
		}

		if(mx <= 7*p && mx >= 5.5*p && my >= 0.5*p && my <= 1.3*p && page == 4 && check_leaderboard == 1) //after vote this will happen
		{
			exit(1);
		}

		if(mx <= 2.5*p && mx >= 1*p && my >= 0.5*p && my <= 1.3*p && (page == 4 || page == 2 || page == 3 || page == 10 )) //back to home page
		{
			page = 1;
			check_leaderboard = 0;
			thanks = 0;
			point = 0;
		}	
		
		if(mx <= 6*p && mx >= 2*p && my >= 8*p && my <= 9*p && check_leaderboard == 0 && (page == 4 || page == 10))
		{
			if(page == 4)
				page = 6; // page 6 >> vote page
			else
				page = 5;
		}
		if(mx >= 6*p && mx <= 7*p && my >= 8.3*p && my <= 9.1*p && page == 6 && check_leaderboard == 0)
		{
			page = 9;                         //this for blank page
			check_leaderboard = 1;           //Actibate the leaderboard
			thanks = 1;                      //For Thank you message

			count_cand = fopen("cand1.txt","r");
			fscanf(count_cand,"%d",&cand[0]);
			fclose(count_cand);

			cand[0]++;

			count_cand = fopen("cand1.txt","w");
			fprintf(count_cand,"%d",cand[0]);
			fclose(count_cand);
				       
		}
		if(mx >= 6*p && mx <= 7*p && my >= 7.1*p && my <= 7.9*p && page == 6 && check_leaderboard == 0)
		{
			page = 9;                        //this for blank page
			check_leaderboard = 1;           //Actibate the leaderboard
			thanks = 1;                      //For Thank you message

			count_cand = fopen("cand2.txt","r");
			fscanf(count_cand,"%d",&cand[1]);
			fclose(count_cand);

			cand[1]++;

			count_cand = fopen("cand2.txt","w");
			fprintf(count_cand,"%d",cand[1]);
			fclose(count_cand);
				       
		}
		if(mx >= 6*p && mx <= 7*p && my >= 5.9*p && my <= 6.7*p && page == 6 && check_leaderboard == 0)
		{
			page = 9;           		//this for blank page
			check_leaderboard = 1;      //Actibate the leaderboard
			thanks = 1;           		//For Thank you message

			count_cand = fopen("cand3.txt","r");
			fscanf(count_cand,"%d",&cand[2]);
			fclose(count_cand);

			cand[2]++;

			count_cand = fopen("cand3.txt","w");
			fprintf(count_cand,"%d",cand[2]);
			fclose(count_cand);
			
				       
		}
		if(mx >= 6*p && mx <= 7*p && my >= 4.7*p && my <= 5.5*p && page == 6 && check_leaderboard == 0)
		{
			page = 9;           			//this for blank page
			check_leaderboard = 1;          //Actibate the leaderboard
			thanks = 1;           			//For Thank you message

			count_cand = fopen("cand4.txt","r");
			fscanf(count_cand,"%d",&cand[3]);
			fclose(count_cand);

			cand[3]++;

			count_cand = fopen("cand4.txt","w");
			fprintf(count_cand,"%d",cand[3]);
			fclose(count_cand);
		   
		}
		
		if(mx <= 6*p && mx >= 2*p && my >= 5*p && my <= 6*p && check_leaderboard == 1 && page == 4)
		{
			page = 8;     //open LeaderBoard page
		}

		if(mx <= 6*p && mx >= 2*p && my >= 5*p && my <= 6*p && page == 10) //Admin page to
		{
			page = 8;     //open LeaderBoard page
		}

		if(mx <= 6*p && mx >= 2*p && my >= 6.5*p && my <= 7.5*p && page == 4)
		{
			page = 7;     //open candidate page
		}

		if(mx <= 7*p && mx >= 5.5*p && my >= 0.5*p && my <= 1.3*p)
		{
			if(page == 6 || page == 7 || page == 8 || page == 9)
			{
				if(page == 8 && check_leaderboard == 1)
					page = 4;//Back to home page
				else if(page == 8)
					page = 10;
				else
					page = 4;
				if(thanks) thanks=0;
			}
			else if(page == 1)
				exit(0);
		}

		if(mx <= 6.5*p && mx >= 1*p && my >= 6*p && my <= 7*p && page == 2)
		{
			
			mode[0] = 1;
			mode_1[0] = 0;
			flag = 1;
		}
 
			
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		if(mx <= 7*p && mx >= 5.5*p && my >= 0.5*p && my <= 1.3*p && (page == 2 || page == 3 || page == 10))
		{
			mx <= 7*p && mx >= 5.5*p && my >= 0.5*p && my <= 1.3*p;
		}
	}

}

/*
	function iKeyboard() is called whenever the user hits page key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	// login page
	if (mode_1[0] == 1 && page == 2)              // password  box
	{
        if(key == '\r')
		{
			if(point == 2)
			{
				pass=fopen("password.txt","r");
				while (fgets(str3, sizeof(str3), pass) != NULL)
				{
					// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;
					// Compare the line with the search string
					if (strcmp(str3, str1[0]) == 0)
					{
						
						len1=0;
						len=0;
						str[0][0]='\0';
						str1[0][0]='\0';
						mode[0]=0;
						mode_1[0]=0;
						point=0;
						printf("Match found: %s\n", str3);
						page = 4;
						break;	
					}
					else
						flag = 0;
				}
				fclose(pass);	
			}
			else if(point == 1)
			{
				
				pass = fopen("adminpass.txt","r");
				while (fgets(str3, sizeof(str3), pass) != NULL)
				{
					// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;
					// Compare the line with the search string
					if (strcmp(str3, str1[0]) == 0)
					{
						page = 10;
						len1=0;
						len=0;
						mode[0]=0;
						mode_1[0]=0;
						point=0;
						str[0][0]='\0';
						str1[0][0]='\0';
						printf("Match found: %s\n", str3);
						break;
					}
					else
						flag = 0;
				}
				fclose(pass);
			}
			}	
			
			else if(key != '\b') 
			{
				str1[0][len1] = key;
				str1[0][len1+1] = '\0';
				len1++;
			}

			else  // Erase character
			{
				flag=1;
				str1[0][len1-1] = '\0';
				len1--;
			}
    }	

	//register page
	else if(mode_1[1] == 1 && page == 3)
	{
		if(key == '\r' && len1 < 9) //here 0 to 7 for 8 char,8 for null,9 for enter
		{
			if(point == 1)
			{
				Admin = fopen("admin.txt","a");
				fprintf(Admin,"%s\n%s\n",str[1],str1[1]);
			//	fputs(str[1],Admin);
			//	fputc('\n',Admin);
				fclose(Admin);
			/*	
				pass = fopen("adminpass.txt","w");
				fputs(str1[1],pass);
				fputc('\n',pass);
				fclose(pass);
			*/	
				len1=0;
				str1[1][0]='\0';
				str[1][0]='\0';
				mode[1]=0;
				mode_1[1]=0;
				page = 1;
				point = 0; //
			}
			
			if(point == 2)
			{
				name1 = fopen("name.txt","a");
				fputs(str[1],name1);
				fputc('\n',name1);
				fclose(name1);
				
				pass=fopen("password.txt","a");
				fputs(str1[1],pass);
				fputc('\n',pass);
				fclose(pass);
				
				len1=0;
				str1[1][0]='\0';
				str[1][0]='\0';
				mode[1]=0;
				mode_1[1]=0;
				page = 1;
			}
		}

		else if(key != '\b') 
		{
			str1[1][len1] = key;
			str1[1][len1+1] = '\0';
			len1++;
		}

		else  // Erase character
		{
			flag=1;
			str1[1][len1-1] = '\0';
			len1--;
		}
		
		if(len1 > 9)  //here 0 to 7 for 8 char,8 for null,9 for enter
			flag=0;
		
	}

	else if(mode[0] == 1 && mode_1[0] == 0 && page == 2)    // Name Box,this box will work until the correct voter name inseted
	{
        if(key == '\r')
		{
			if(point == 2)
			{
				name1 = fopen("name.txt","r");
				while (fgets(str3, sizeof(str3), name1) != NULL) {
				// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;

				// Compare the line with the search string
					if (strcmp(str3, str[0]) == 0) {
					mode_1[0] = 1;
					len=0;
					//str[0]='\0';
					help=1;
					printf("Match found: %s\n", str3);
					break;
				}
					else
						help=0;
						
				}

				if(!help)
					flag1=0;
				else
					flag1=1;
				fclose(name1);
			}

			if(point == 1)
			{
				Admin = fopen("admin.txt","r");
				while (fgets(str3, sizeof(str3), Admin) != NULL) {
				// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;

				// Compare the line with the search string
					if (strcmp(str3, str[0]) == 0) {
					mode_1[0] = 1;
					len=0;
					//str[0]='\0';
					help=1;
					printf("Match found: %s\n", str3);
					break;
				}
					else
						help=0;
						
				}

				if(!help)
					flag1=0;
				fclose(Admin);
			}
		}

		else if(key != '\b') 
		{
			str[0][len] = key;
			str[0][len+1] = '\0';
			len++;
		}

		else
		{
			flag1 = 1;
			str[0][len-1] = '\0';
			len--;			
		}
	}

	else if(mode[1] == 1 && mode_1[1] == 0 && page == 3)    // register Name Box ,here mode_1 must be 0,nor str active when i type password
	{
        if(key == '\r' )
		{
			mode_1[1] = 1;
			len=0;						
		}

		else if(key != '\b') 
		{
			str[1][len] = key;
			
			str[1][len+1] = '\0';
			len++;
		}

		else
		{
			//flag=1;
			str[1][len-1] = '\0';
			len--;
		}
	}

	if(mode[2] == 1 && mode_1[2] == 0 && page == 5)
	{
	    if(key == '\r' )
		{
			//printf("%thanks",k);
			mode_1[2] = 1;
			len=0;						
		}

		else if(key != '\b') 
		{
			str[2][len] = key;
			
			str[2][len+1] = '\0';
			len++;
		}

		else
		{
			//flag=1;
			str[2][len-1] = '\0';
			len--;
		}
	}

	if(mode_1[2] == 1 && page == 5)
	{
		if(key == '\r' && k < 4 )
		{	
			//printf("%thanks",k);
			strcpy(str2[k],str1[2]);
			str1[2][0]='\0';
			len1=0;
			mode_1[2] = 1;
			k++;						
		}

		else if(key != '\b') 
		{
			str1[2][len1] = key;			
			str1[2][len1+1] = '\0';
			len1++;
		}

		else
		{
			//flag=1;
			str1[2][len1-1] = '\0';
			len1--;
		}
	}



}
	//place your codes for other keys here

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. page list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{
	
}


int main() 
{
	//place your own initialization codes here.
	len=0;
	len1=0;
	iInitialize(8*p,13*p,"Voting System");
	return 0;
}
