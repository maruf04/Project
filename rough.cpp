#include "iGraphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int p = 50;
int r = 0, g = 128, b = 128;
int check_leaderboard = 0, thanks = 0;
int x = 160, y = 10;
int page = 1, regi = 0;
int k = 0, help = 0;
static int election_sort = 0;
static int election_count = 0;
static int electionstatus = 0;

// str4 for election wise candidate
// str5 for election wise candidate's vote count

char str[3][30] = {0}, str1[3][30] = {0}, str2[4][30] = {0}, str3[30], str6[30];
char str4[3][4][30] = {0}, str5[3][4][3], election_name[3][30], election_status[2];
char voter_name[30], take_voter[30];
char election_name_1[3][30];

int vote[4];
int confirm = 0;

int len = 0, len1 = 0, len2 = 0, flag = 1, flag1 = 1, flag2 = 0, flag3 = 0,flag4 =0,flag5 = 0;
int point = 0;
// int mode=3,mode_1=0,mode_2=0;
int mode[3] = {0};
int mode_1[3] = {0};
int cand[3][4] = {0}; // to help count the vote
int con[3], con_1[3];

bool close_erase = true;
bool point_1 = true;
bool election_page = false;
bool election_page1 = false;
bool election_page2 = false;
bool certainity = true;
bool certainity_2 = true;

FILE *name1;
FILE *name2;
FILE *auxi_1;
FILE *Admin;
FILE *election;
FILE *candidate;
FILE *auxi_2;
FILE *track_election;
FILE *auxi;
FILE *auxi_;
FILE *show_vote;
FILE *show_vote_;


//Function protype are here
void take_candidate();
void OnevoteCheck();
void count_vote();
void write_candidate();


// Function Are Here


void read_one_vote()
{
	auxi_1 = fopen("1votefor1election.txt", "r");
	fscanf(auxi_1, "%d %d %d", &con_1[0], &con_1[1], &con_1[2]);
	fclose(auxi_1);
}

void read_election()
{
	election = fopen("election.txt", "r");
	int i = 0;
	while (fgets(election_name[i], sizeof(election_name[i]), election) != NULL)
	{
		election_name[i][strcspn(election_name[i], "\n")] = 0;
		i++;
	}
	fclose(election);
}

void write_election()
{
	election = fopen("election.txt", "w");
	for(int i=0;i<3;i++)
		fprintf(election, "%s\n", election_name[i]);
	fclose(election);
}

void write_candidate()
{
	candidate = fopen("candidate.txt", "w");
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 4; k++)
			fprintf(candidate, "%s\n", str4[j][k]);
	fclose(candidate);
}

void read_vote()
{
	show_vote = fopen("vote_count.txt", "r");
	for (int j = 0; j < 3; j++)
	{
		int i = 0;
		while (fscanf(show_vote, "%d", &cand[j][i]) != EOF)
		{
			i++;
		}
	}
	fclose(show_vote);
}

void write_vote()
{
	show_vote = fopen("vote_count.txt", "w");
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 4; k++)
			fprintf(show_vote, "%d\n", cand[j][k]);
	fclose(show_vote);
}

void erase_election(int election_sort)
{
	read_election();

	election_name[election_sort][0] = '\0';

	

	write_election();

	read_one_vote();
	con_1[election_sort] = 0 ;
	OnevoteCheck();


	take_candidate();

	for (int j = 0; j < 4; j++)
	{
		str4[election_sort][j][0] = '\0';
	}

	write_candidate();
	read_vote();
	

	for (int j = 0; j < 4; j++)
	{
		cand[election_sort][j] = 0;
	}

	write_vote();

	auxi_ = fopen("confirmation.txt", "r");
	fscanf(auxi_, "%d %d %d", &con[0], &con[1], &con[2]);
	fclose(auxi_);

	con[election_sort] = 1;

	auxi_ = fopen("confirmation.txt", "w");
	fprintf(auxi_, "%d %d %d", con[0], con[1], con[2]);
	fclose(auxi_);

	electionstatus--;

	track_election = fopen("election_track.txt","w");
	fprintf(track_election,"%d",electionstatus);
	fclose(track_election); 

}

void count_election()
{
	track_election = fopen("election_track.txt","r");
	fscanf(track_election,"%s",&election_status);
	fclose(track_election);
	electionstatus = atoi(election_status);
}

void draw_headline()
{
	election = fopen("election.txt", "r");
	int i = 0;
	while (fgets(election_name[i], sizeof(election_name[i]), election) != NULL)
	{
		election_name[i][strcspn(election_name[i], "\n")] = 0;
		i++;
	}
	fclose(election);

	iText(p, 11 * p, election_name[election_sort], GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_election()  
{
	election = fopen("election.txt", "r");
	int i = 0;
	while (fgets(election_name[i], sizeof(election_name[i]), election) != NULL)
	{
		election_name[i][strcspn(election_name[i], "\n")] = 0;
		i++;
	}
	fclose(election);

	iSetColor(40, 40, 40);
	iFilledRectangle(0.5 * p, 4 * p, 7 * p, 5 * p);

	iSetColor(r, g, b);
	iText(1 * p, 8.5 * p, "Choose Your Election", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(1 * p, 7.2 * p, election_name[0], GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1 * p, 6.2 * p, election_name[1], GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1 * p, 5.2 * p, election_name[2], GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(255, 255, 255);
	iRectangle(6 * p, 5 * p, 0.5 * p, 0.5 * p);
	iRectangle(6 * p, 6 * p, 0.5 * p, 0.5 * p);
	iRectangle(6 * p, 7 * p, 0.5 * p, 0.5 * p);


	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);


	if (flag2 == 1)
	{
		iSetColor(255, 0, 0);
		iText(1 * p, 2.5 * p, "! This Election Is Closed by Admin.", GLUT_BITMAP_8_BY_13);
	}

	if (flag3 == 1)
	{
		iSetColor(255, 0, 0);
		iText(1 * p, 2 * p, "! You already vote this election.", GLUT_BITMAP_8_BY_13);
	}

	if(flag4 == 1)
	{
		iSetColor(255, 0, 0);
		iText(1 * p, 2.5 * p, "! The Election has not been closed yet.", GLUT_BITMAP_8_BY_13);
	}


}

void count_vote()
{

	show_vote = fopen("vote_count.txt", "r");
	for (int j = 0; j < 3; j++)
	{
		int i = 0;
		while (fscanf(show_vote, "%s", str5[j][i])  != EOF)
		{

			str5[j][i][strcspn(str5[j][i], "\n")] = 0;
			// fscanf(show_vote,"%d",cand[j][i]);
			i++;
		}
	}
	fclose(show_vote);

	show_vote = fopen("vote_count.txt", "r");
	for (int j = 0; j < 3; j++)
	{
		int i = 0;
		while (fscanf(show_vote, "%d", &cand[j][i]) != EOF)
		{
			i++;
		}
	}
	fclose(show_vote);
}

void update_vote()
{
	show_vote_ = fopen("vote_count.txt", "w");
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			fprintf(show_vote_, "%d\n", cand[i][j]);

	fclose(show_vote_);
}

void OnevoteCheck()
{
	auxi_2 = fopen("1votefor1election.txt", "w");
	fprintf(auxi_2, "%d %d %d", con_1[0], con_1[1], con_1[2]);
	fclose(auxi_2);
}

void draw_result()
{
	iSetColor(255, 255, 255);
	draw_headline();
	iText(1 * p, 11.5 * p, "Result   For", GLUT_BITMAP_TIMES_ROMAN_24);

	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
	{
		iPoint(i, 10.85 * p, 0);
	}
	read_vote();


	int max = cand[election_sort][0],track=0;
	for(int i=1;i<4;i++)
	{
		if( cand[election_sort][i] > max)
		{
			max = cand[election_sort][i];
			track = i;
		}
		else if(cand[election_sort][i] == max)
			track = -1;
	}

	if(track == -1)
	{
		iSetColor(255,255,255);
		iText(p,2*p,"There is no winner",GLUT_BITMAP_TIMES_ROMAN_24);
	}

	else if(track == 0)
	{
		iSetColor(255,255,255);
		iText(p,2*p, "Winner : ",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(3*p,2*p,str4[election_sort][0],GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		iSetColor(255,255,255);
		iText(p,2*p, "Winner : ",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(3*p,2*p,str4[election_sort][track],GLUT_BITMAP_TIMES_ROMAN_24);
	}



	iSetColor(40, 40, 40);
	iFilledRectangle(0.8 * p, 4 * p, 6.7 * p, 6 * p);

	iSetColor(r, g, b);
	// vote count map in graph
	iText(0.3 * p, 5 * p, "10", GLUT_BITMAP_9_BY_15);
	iText(0.3 * p, 6 * p, "20", GLUT_BITMAP_9_BY_15);
	iText(0.3 * p, 7 * p, "30", GLUT_BITMAP_9_BY_15);
	iText(0.3 * p, 8 * p, "40", GLUT_BITMAP_9_BY_15);
	iText(0.3 * p, 9 * p, "50", GLUT_BITMAP_9_BY_15);
	iText(0.3 * p, 10 * p, "60", GLUT_BITMAP_9_BY_15);
	// line per 10 vote
	iLine(0.7 * p, 5 * p, 0.9 * p, 5 * p);
	iLine(0.7 * p, 6 * p, 0.9 * p, 6 * p);
	iLine(0.7 * p, 7 * p, 0.9 * p, 7 * p);
	iLine(0.7 * p, 8 * p, 0.9 * p, 8 * p);
	iLine(0.7 * p, 9 * p, 0.9 * p, 9 * p);
	iLine(0.7 * p, 10 * p, 0.9 * p, 10 * p);

	// for each candidate per rectangle
	take_candidate();
	iSetColor(205,160,113);
	iFilledRectangle(1.525 * p, 4 * p, 0.75 * p, cand[election_sort][0] * 5);

	iText(1.525*p,3.75*p,str4[election_sort][0]);
	iSetColor(145,187,123);
	iFilledRectangle(3.025 * p, 4 * p, 0.75 * p, cand[election_sort][1] * 5);

	iText(3.025*p,3.5*p,str4[election_sort][1]);
	iSetColor(205,160,113);
	iFilledRectangle(4.525 * p, 4 * p, 0.75 * p, cand[election_sort][2] * 5);

	iText(4.525*p,3.75*p,str4[election_sort][2]);
	iSetColor(145,187,123);
	iFilledRectangle(6.025 * p, 4 * p, 0.75 * p, cand[election_sort][3] * 5);
	iText(6.025*p,3.5*p,str4[election_sort][3]);

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void election_close()
{
	iSetColor(r, g, b);
	iText(2.2 * p, 10.2 * p, "Close", GLUT_BITMAP_9_BY_15);
	iRectangle(2 * p, 10 * p, 1.5 * p, 0.7 * p);

	iText(4.2 * p, 10.2 * p, "Erase", GLUT_BITMAP_9_BY_15);
	iRectangle(4 * p, 10 * p, 1.5 * p, 0.7 * p);

	if (point_1 == true)
	{
		iSetColor(255, 255, 255);
		iRectangle(2 * p, 10 * p, 1.5 * p, 0.7 * p);
	}
	else
	{
		iSetColor(255, 255, 255);
		iRectangle(4 * p, 10 * p, 1.5 * p, 0.7 * p);
	}

	if (point_1 == true)
	{
		auxi_ = fopen("confirmation.txt", "r");
		fscanf(auxi_, "%d %d %d", &con[0], &con[1], &con[2]);
		fclose(auxi_);
		
		election = fopen("election.txt", "r");
		int i = 0;
		while (fgets(election_name[i], sizeof(election_name[i]), election) != NULL)
		{
			election_name[i][strcspn(election_name[i], "\n")] = 0;
			i++;
		}
		fclose(election);

		iSetColor(10, 20, 20);
		iFilledRectangle(0.7 * p, 4.7 * p, 7 * p, 5 * p);

		iSetColor(255, 255, 255);
		iText(1 * p, 8.5 * p, "Close  Election", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(r, g, b);
		iText(1 * p, 7.2 * p, election_name[0], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1 * p, 6.2 * p, election_name[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1 * p, 5.2 * p, election_name[2], GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(40, 40, 40);
		iFilledRectangle(6 * p, 5 * p, 1.5 * p, 0.7 * p);
		iFilledRectangle(6 * p, 6 * p, 1.5 * p, 0.7 * p);
		iFilledRectangle(6 * p, 7 * p, 1.5 * p, 0.7 * p);

		iSetColor(255, 255, 255);
		if (con[0] == 1)
			iText(6.3 * p, 7.25 * p, "Close", GLUT_BITMAP_9_BY_15);
		else
		{
			iSetColor(200, 0, 0);
			iFilledRectangle(6 * p, 7 * p, 1.5 * p, 0.7 * p);
			iSetColor(255, 255, 255);
			iText(6.3 * p, 7.25 * p, "Closed", GLUT_BITMAP_9_BY_15);
		}
		if (con[1] == 1)
			iText(6.3 * p, 6.25 * p, "Close", GLUT_BITMAP_9_BY_15);
		else
		{
			iSetColor(200, 0, 0);
			iFilledRectangle(6 * p, 6 * p, 1.5 * p, 0.7 * p);
			iSetColor(255, 255, 255);
			iText(6.3 * p, 6.25 * p, "Closed", GLUT_BITMAP_9_BY_15);
		}
		if (con[2] == 1)
			iText(6.3 * p, 5.25 * p, "Close", GLUT_BITMAP_9_BY_15);
		else
		{
			iSetColor(200, 0, 0);
			iFilledRectangle(6 * p, 5 * p, 1.5 * p, 0.7 * p);
			iSetColor(255, 255, 255);
			iText(6.3 * p, 5.25 * p, "Closed", GLUT_BITMAP_9_BY_15);
		}

		iSetColor(14, 5, 170);
		iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
		iSetColor(255, 255, 255);
		iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
		iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	}
	else
	{
		election = fopen("election.txt", "r");
		int i = 0;
		while (fgets(election_name[i], sizeof(election_name[i]), election) != NULL)
		{
			election_name[i][strcspn(election_name[i], "\n")] = 0;
			i++;
		}
		fclose(election);

		iSetColor(10, 20, 20);
		iFilledRectangle(0.7 * p, 4.7 * p, 7 * p, 5 * p);

		iSetColor(255, 255, 255);
		iText(1 * p, 8.5 * p, "Erase  Election", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(r, g, b);
		iText(1 * p, 7.2 * p, election_name[0], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1 * p, 6.2 * p, election_name[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1 * p, 5.2 * p, election_name[2], GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(200, 0, 0);
		iFilledRectangle(6 * p, 5 * p, 1.5 * p, 0.7 * p);
		iFilledRectangle(6 * p, 6 * p, 1.5 * p, 0.7 * p);
		iFilledRectangle(6 * p, 7 * p, 1.5 * p, 0.7 * p);

		iSetColor(255, 255, 255);
		iText(6.3 * p, 7.25 * p, "Erase", GLUT_BITMAP_9_BY_15);

		iText(6.3 * p, 6.25 * p, "Erase", GLUT_BITMAP_9_BY_15);

		iText(6.3 * p, 5.25 * p, "Erase", GLUT_BITMAP_9_BY_15);

		iSetColor(14, 5, 170);
		iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
		iSetColor(255, 255, 255);
		iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
		iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	}
}



void draw_page1()
{

	iSetColor(255, 255, 255);
	iText(1 * p, 11.1 * p, "WELCOME TO", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1 * p, 10.5 * p, "ONLINE  VOTING  SYSTEM", GLUT_BITMAP_TIMES_ROMAN_24); // Headline for all page

	// draw_headline();

	iText(3.5 * p, 6.3 * p, "Login", GLUT_BITMAP_9_BY_15);
	iRectangle(3 * p, 6 * p, 2 * p, 0.8 * p);
	iText(3.3 * p, 5.3 * p, "Register", GLUT_BITMAP_9_BY_15);
	iRectangle(3 * p, 5 * p, 2 * p, 0.8 * p);

	iSetColor(170, 0, 0);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Exit");
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void draw_register()
{
	iSetColor(255, 255, 255);
	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	iSetColor(0, 128, 128);
	iText(1 * p, 11 * p, "REGISTER  HERE", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.2 * p, 9.2 * p, "Admin", GLUT_BITMAP_9_BY_15);
	iRectangle(2 * p, 9 * p, 1.5 * p, 0.7 * p);

	iText(4.2 * p, 9.2 * p, "Voter", GLUT_BITMAP_9_BY_15);
	iRectangle(4 * p, 9 * p, 1.5 * p, 0.7 * p);

	iText(1 * p, 7.2 * p, "Name", GLUT_BITMAP_9_BY_15);
	iRectangle(1 * p, 6 * p, 5.5 * p, p);

	iText(1 * p, 5.2 * p, "Password", GLUT_BITMAP_9_BY_15);
	iRectangle(1 * p, 4 * p, 3.5 * p, p);

	iText(3.2 * p, 2.7 * p, "Confirm", GLUT_BITMAP_9_BY_15);
	iRectangle(3 * p, 2.5 * p, 2 * p, 0.7 * p);

	iSetColor(14, 5, 170);
	iFilledEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(1.5 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);

	if (mode[1] == 1)
	{
		iSetColor(255, 255, 255);
		iText(1.2 * p, 6.4 * p, str[1], GLUT_BITMAP_9_BY_15);
		iRectangle(1 * p, 6 * p, 5.5 * p, p);
	}

	if (mode_1[1] == 1)
	{
		iSetColor(255, 255, 255);
		iText(1.2 * p, 4.4 * p, str1[1], GLUT_BITMAP_9_BY_15);
		iRectangle(1 * p, 4 * p, 3.5 * p, p);
	}

	if (flag == 0)
	{
		iSetColor(255, 0, 0);
		iText(0.37 * p, 1.5 * p, "* Your password must hold 8 character");
	}

	if(flag5 == 1)
	{
		iSetColor(255, 0, 0);
		iText(0.7 * p, 1.7 * p, "* This Name is already taken.");
	}

	if (point == 1)
	{
		iSetColor(255, 255, 255);
		iRectangle(2 * p, 9 * p, 1.5 * p, 0.7 * p);
	}

	else if (point == 2)
	{
		iSetColor(255, 255, 255);
		iRectangle(4 * p, 9 * p, 1.5 * p, 0.7 * p);
	}
}

void draw_homepage()
{
	certainity = false;
	certainity_2 = false;

	election_page = false;
	election_page1 = false;
	election_page2 = false;

	flag2 = 0;
	flag3 = 0;
	flag4 = 0;

	iSetColor(255, 255, 255);
	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);
	//draw_headline();
	iSetColor(255, 255, 255);
	iText(1 * p, 11.6 * p, "WELCOME TO", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1 * p, 11 * p, "ONLINE  VOTING  SYSTEM", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 128, 128);
	iText(2.7 * p, 8.4 * p, "Vote", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 6.9 * p, "Candidate", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 5.4 * p, "Leaderboard", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 3.9 * p, "Result", GLUT_BITMAP_9_BY_15);

	iSetColor(255, 255, 255);
	iRectangle(2 * p, 8 * p, 4 * p, p);
	iRectangle(2 * p, 6.5 * p, 4 * p, p);
	iRectangle(2 * p, 5 * p, 4 * p, p);
	iRectangle(2 * p, 3.5 * p, 4 * p, p);

	iSetColor(14, 5, 170);
	iFilledEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(1.5 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);

	//if(con_1[0] == 1 || con_1[1] == 1 || con_1[2] == 1)
		//check_leaderboard = 1;

	if (check_leaderboard == 1)
	{
		iSetColor(170, 0, 0);
		iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
		iSetColor(255, 255, 255);
		iText(5.9 * p, 0.8 * p, "Exit", GLUT_BITMAP_9_BY_15);
		iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	}
}

void draw_page10()
{
	certainity = true;
	certainity_2 = true;
	flag4 = 0;

	election_page1 = false;
	election_page2 = false;

	count_election();
	
	iSetColor(255, 255, 255);
	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	

	iText(1.75 * p, 12.4 * p, "On-going Election : ", GLUT_BITMAP_9_BY_15);
	iText(5.25 * p, 12.4 * p, election_status, GLUT_BITMAP_9_BY_15);
	
	iSetColor(0, 128, 128);
	iText(1 * p, 11 * p, "ADMIN  PAGE", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.7 * p, 8.4 * p, "Create", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 6.9 * p, "Close", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 5.4 * p, "Leaderboard", GLUT_BITMAP_9_BY_15);
	iText(2.7 * p, 3.9 * p, "Result", GLUT_BITMAP_9_BY_15);

	iSetColor(255, 255, 255);
	iRectangle(2 * p, 8 * p, 4 * p, p);
	iRectangle(2 * p, 6.5 * p, 4 * p, p);
	iRectangle(2 * p, 5 * p, 4 * p, p);
	iRectangle(2 * p, 3.5 * p, 4 * p, p);

	iSetColor(14, 5, 170);
	iFilledEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(1.5 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void draw_page5()
{
	iSetColor(255, 255, 255);
	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	count_election();
	iText(1.75 * p, 12.4 * p, "On-going Election : ", GLUT_BITMAP_9_BY_15);
	iText(5.25 * p, 12.4 * p, election_status, GLUT_BITMAP_9_BY_15);

	iSetColor(255,255,255);
	iText(1 * p, 11 * p, "ELECTION CREATION PAGE", GLUT_BITMAP_HELVETICA_18);
	iText(1 * p, 9 * p, "Election Name");
	iText(1 * p, 7 * p, "Candidate Name");
	iText(3.2 * p, 1.7 * p, "Confirm", GLUT_BITMAP_9_BY_15);

	iSetColor(0, 128, 128);
	iRectangle(1 * p, 8 * p, 5.5 * p, 0.8 * p); /// election name box
	
	iRectangle(1 * p, 6 * p, 5.5 * p, 0.8 * p);
	iRectangle(1 * p, 5 * p, 5.5 * p, 0.8 * p);
	iRectangle(1 * p, 4 * p, 5.5 * p, 0.8 * p);
	iRectangle(1 * p, 3 * p, 5.5 * p, 0.8 * p);

	iRectangle(3 * p, 1.5 * p, 2 * p, 0.7 * p); /// confirm box

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);

	iSetColor(255, 255, 255);

	if (mode[2] == 1)
	{
		iSetColor(255, 255, 255);
		iText(1.2 * p, 8.2 * p, str[2]);
		iRectangle(1 * p, 8 * p, 5.5 * p, 0.8 * p);
	}

	if (mode_1[2] == 1)
	{
		iSetColor(255, 255, 255);
		if (k == 0)
		{
			iText(1.2 * p, 6.2 * p, str1[2]);
			iRectangle(1 * p, 6 * p, 5.5 * p, 0.8 * p);
		}
		if (k == 1)
		{
			iText(1.2 * p, 5.2 * p, str1[2]);
			iRectangle(1 * p, 6 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 5 * p, 5.5 * p, 0.8 * p);
		}

		if (k == 2)
		{
			iText(1.2 * p, 4.2 * p, str1[2]);
			iRectangle(1 * p, 6 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 5 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 4 * p, 5.5 * p, 0.8 * p);
		}

		if (k == 3)
		{
			iText(1.2 * p, 3.2 * p, str1[2]);
			iRectangle(1 * p, 6 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 5 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 4 * p, 5.5 * p, 0.8 * p);
			iRectangle(1 * p, 3 * p, 5.5 * p, 0.8 * p);
		}
		
		iSetColor(255,255,255);
		iText(1.2 * p, 6.2 * p, str2[0]);
		iText(1.2 * p, 5.2 * p, str2[1]);
		iText(1.2 * p, 4.2 * p, str2[2]);
		iText(1.2 * p, 3.2 * p, str2[3]);			
	}
}

void take_candidate()
{
	candidate = fopen("candidate.txt", "r");

	for (int j = 0; j < 3; j++)
	{
		int i = 0;
		while (fgets(str4[j][i], sizeof(str4[j][i]), candidate) != NULL)
		{
			str4[j][i][strcspn(str4[j][i], "\n")] = 0;
			i++;
		}
	}
	fclose(candidate);
}

void draw_vote()
{
	iSetColor(255, 255, 255);
	draw_headline();
	iText(1 * p, 11.5 * p, "Vote   For", GLUT_BITMAP_TIMES_ROMAN_24);

	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	take_candidate();
	count_vote();

	iSetColor(255, 255, 255);
	iText(1.2 * p, 5 * p, str4[election_sort][3], GLUT_BITMAP_9_BY_15);
	iText(1.2 * p, 6.2 * p, str4[election_sort][2], GLUT_BITMAP_9_BY_15);
	iText(1.2 * p, 7.4 * p, str4[election_sort][1], GLUT_BITMAP_9_BY_15);
	iText(1.2 * p, 8.6 * p, str4[election_sort][0], GLUT_BITMAP_9_BY_15);

	// iRectangle(6*p,3.5*p,p,0.8*p);
	iRectangle(6 * p, 4.7 * p, p, 0.8 * p);
	iRectangle(6 * p, 5.9 * p, p, 0.8 * p);
	iRectangle(6 * p, 7.1 * p, p, 0.8 * p);
	iRectangle(6 * p, 8.3 * p, p, 0.8 * p);

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void draw_leaderboard()
{
	iSetColor(255, 255, 255);
	
	 
	iText(1 * p, 11.5 * p, "LeaderBoard   For", GLUT_BITMAP_TIMES_ROMAN_24);
	draw_headline();

	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);
	
	take_candidate();
	count_vote();

	iSetColor(255, 255, 255);
	iText(1.1 * p, 5 * p, str4[election_sort][3], GLUT_BITMAP_9_BY_15);
	iText(1.1 * p, 6.2 * p, str4[election_sort][2], GLUT_BITMAP_9_BY_15);
	iText(1.1 * p, 7.4 * p, str4[election_sort][1], GLUT_BITMAP_9_BY_15);
	iText(1.1 * p, 8.6 * p, str4[election_sort][0], GLUT_BITMAP_9_BY_15);

	iRectangle(6 * p, 4.7 * p, p, 0.8 * p);
	iText(6.2 * p, 5 * p, str5[election_sort][3], GLUT_BITMAP_9_BY_15);

	iRectangle(6 * p, 5.9 * p, p, 0.8 * p);
	iText(6.2 * p, 6.2 * p, str5[election_sort][2], GLUT_BITMAP_9_BY_15);

	iRectangle(6 * p, 7.1 * p, p, 0.8 * p);
	iText(6.2 * p, 7.4 * p, str5[election_sort][1], GLUT_BITMAP_9_BY_15);

	iRectangle(6 * p, 8.3 * p, p, 0.8 * p);
	iText(6.2 * p, 8.6 * p, str5[election_sort][0], GLUT_BITMAP_9_BY_15);

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void draw_candidate()
{
	iSetColor(255, 255, 255);
	draw_headline();
	iText(1 * p, 11.5 * p, "Candidate   For", GLUT_BITMAP_TIMES_ROMAN_24);

	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	// iText(0.5*p,10.5*p,"CANDIDATE PROFILE",GLUT_BITMAP_HELVETICA_18);
	take_candidate();
	iText(p, 9 * p, str4[election_sort][0], GLUT_BITMAP_9_BY_15);
	iText(p, 8 * p, str4[election_sort][1], GLUT_BITMAP_9_BY_15);
	iText(p, 7 * p, str4[election_sort][2], GLUT_BITMAP_9_BY_15);
	iText(p, 6 * p, str4[election_sort][3], GLUT_BITMAP_9_BY_15);

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void draw_login()
{
	// iShowBMP(46.5,14.5,"2.0.bmp");
	iSetColor(255, 255, 255);
	for (float i = 0.5 * p; i < 7.5 * p; i += 0.1 * p)
		iPoint(i, 10.85 * p, 0);

	iSetColor(0, 128, 128);
	iText(1 * p, 11 * p, "LOGIN   HERE", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(2.2 * p, 9.2 * p, "Admin", GLUT_BITMAP_9_BY_15);
	iRectangle(2 * p, 9 * p, 1.5 * p, 0.7 * p);

	iText(4.2 * p, 9.2 * p, "Voter", GLUT_BITMAP_9_BY_15);
	iRectangle(4 * p, 9 * p, 1.5 * p, 0.7 * p);

	iText(1 * p, 7.2 * p, "Name", GLUT_BITMAP_9_BY_15);
	iRectangle(1 * p, 6 * p, 5.5 * p, p);

	iText(1 * p, 5.2 * p, "Password", GLUT_BITMAP_9_BY_15);
	iRectangle(1 * p, 4 * p, 3.5 * p, p);

	iText(3.2 * p, 2.7 * p, "Confirm", GLUT_BITMAP_9_BY_15);
	iRectangle(3 * p, 2.5 * p, 2 * p, 0.7 * p);

	iSetColor(14, 5, 170);
	iFilledEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(1.5 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(1.8 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);

	if (mode_1[0] == 1) // password box
	{
		iSetColor(255, 255, 255);
		iRectangle(1 * p, 4 * p, 3.5 * p, p);
		iText(1.2 * p, 4.4 * p, str6, GLUT_BITMAP_9_BY_15);
	}

	if (mode[0] == 1) // name box
	{
		iSetColor(255, 255, 255);
		iRectangle(1 * p, 6 * p, 5.5 * p, p);
		iText(1.2 * p, 6.4 * p, str[0], GLUT_BITMAP_9_BY_15);
	}

	if (flag == 0)
	{
		iSetColor(255, 0, 0);
		iText(0.7 * p, 1.7 * p, "! Please enter valid name/password");
	}

	if (flag1 == 0)
	{
		iSetColor(255, 0, 0);
		iText(0.7 * p, 1.7 * p, "* Please enter valid name");
	}


	if (point == 1)
	{
		iSetColor(255, 255, 255);
		iRectangle(2 * p, 9 * p, 1.5 * p, 0.7 * p);
	}

	else if (point == 2)
	{
		iSetColor(255, 255, 255);
		iRectangle(4 * p, 9 * p, 1.5 * p, 0.7 * p);
	}
}

void draw_thankyou()
{
	iSetColor(r, g, b);
	iText(2 * p, 6 * p, "Thanks for your Vote", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 255);

	iSetColor(14, 5, 170);
	iFilledEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
	iSetColor(255, 255, 255);
	iText(5.9 * p, 0.8 * p, "Back", GLUT_BITMAP_9_BY_15);
	iEllipse(6.3 * p, 0.9 * p, 0.8 * p, 0.4 * p, 1000);
}

void iDraw()
{
	// place your drawing codes here
	iClear();
	iSetColor(25, 25, 25);
	iFilledRectangle(0, 0, 8 * p, 13 * p);

	// Confirmation for whether this election is on-going or not
	auxi_ = fopen("confirmation.txt", "r");
	fscanf(auxi_, "%d %d %d", &con[0], &con[1], &con[2]);
	fclose(auxi_);

	// Checking Whether the voter vote multiple times
	auxi_1 = fopen("1votefor1election.txt", "r");
	fscanf(auxi_1, "%d %d %d", &con_1[0], &con_1[1], &con_1[2]);
	fclose(auxi_1);

	///*
		iSetColor(15,15,15);
		for(int i=0;i<=8*p;i += 0.5*p)
			iLine(i,0,i,13*p);
		for(int i=0;i<=13*p;i += 0.5*p)
			iLine(0,i,8*p,i);

	//*/
	if (page == 6)
	{
		draw_vote();
	}

	if ((thanks == 1 || election_page == true || election_page1 == true || election_page2 == true) && page == 9)
	{
		if (thanks == 1)
			draw_thankyou();
		else if (election_page == true || election_page1 == true || election_page2 == true)
			draw_election();
	}

	if (page == 12)
	{
		election_close();
	}

	if (page == 11)
	{
		draw_result();
	}

	if (page == 7)
	{
		draw_candidate();
	}

	if (page == 8)
	{
		draw_leaderboard();
	}

	if (page == 4)
	{
		draw_homepage();
	}

	if (page == 2)
	{
		draw_login();
	}
	if (page == 1)
	{
		draw_page1();
	}
	if (page == 3)
	{
		draw_register();
	}
	if (page == 5)
	{
		draw_page5();
	}
	if (page == 10)
	{
		draw_page10();
	}
}

void iMouseMove(int mx, int my)
{
	// place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (mx <= 5 * p && mx >= 3 * p && my >= 6 * p && my <= 6.8 * p && page == 1)
		{
			page = 2;
		}

		if (mx <= 5 * p && mx >= 3 * p && my >= 5 * p && my <= 5.8 * p && page == 1)
		{
			page = 3;
		}

		// name box in the register page
		if (mx <= 6.5 * p && mx >= 1 * p && my >= 5 * p && my <= 6 * p && page == 3) 
		{
			mode[1] = 1;
			mode_1[1] = 0;
		}

		// name box in the login page
		if (mx <= 6.5 * p && mx >= 1 * p && my >= 5 * p && my <= 6 * p && page == 2) 
		{
			mode[0] = 1;
			mode_1[0] = 0;
		}

		// confirmation button on register page
		if (mx <= 5 * p && mx >= 3 * p && my >= 2.5 * p && my <= 3.2 * p && page == 3 && len1 < 9)
		{
			if (point == 1)
			{
				Admin = fopen("admin.txt", "w");
				fprintf(Admin, "%s %s\n", str[1], str1[1]);
				fclose(Admin);

				len1 = 0;
				str1[1][0] = '\0';
				str[1][0] = '\0';
				mode[1] = 0;
				mode_1[1] = 0;
				page = 1;
				point = 0; //
			}

			if (point == 2)
			{

					name1 = fopen("name.txt", "w");
					fprintf(name1, "%s %s\n", str[1], str1[1]);
					fclose(name1);

					auxi_2 = fopen("1votefor1election.txt", "w");
					fprintf(auxi_2, "%d %d %d", 0, 0, 0);
					fclose(auxi_2);

					name2 = fopen("save_name.txt","a");
					fprintf(name2,"%s %s\n",str[1],str1[1]);
					fclose(name2);

					len1 = 0;
					str1[1][0] = '\0';
					str[1][0] = '\0';
					mode[1] = 0;
					mode_1[1] = 0;
					page = 1;
					point = 0;
				
			}
		}
		// Confirmation button of login
		if (mx <= 5 * p && mx >= 3 * p && my >= 2.5 * p && my <= 3.2 * p && page == 2) // When Press Confirm,at login page
		{
			if (point == 2)
			{
				char flag_name[30];
				strcpy(flag_name,str[0]);
				strcat(str[0], " ");
				strcat(str[0], str1[0]);
				name1 =fopen("name.txt","r");
				fgets(str3,sizeof(str3),name1);
				str3[strcspn(str3, "\n")] = 0;
				if (strcmp(str3, str[0]) == 0)
				{
					len1 = 0;
					len = 0;
					str[0][0] = '\0';
					str1[0][0] = '\0';
					str6[0] = '\0';
					mode[0] = 0;
					mode_1[0] = 0;
					point = 0;
					certainity == false;
					printf("Match found: %s\n", str3);
					page = 4;
				}
				else
				{
					
					flag = 0;
					str[0][0] = '\0';
					str1[0][0] = '\0';
					str6[0] = '\0';
					len1 = 0;
					len = 0;
					mode_1[0] = 0;
					mode[0] = 0;
					
				}
				fclose(name1);
			}
			else if (point == 1)
			{
				strcat(str[0], " ");
				strcat(str[0], str1[0]);

				Admin = fopen("admin.txt", "r");
				while (fgets(str3, sizeof(str3), Admin) != NULL)
				{
					// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;
					// Compare the line with the search string
					if (strcmp(str3, str[0]) == 0)
					{
						page = 10;
						len1 = 0;
						len = 0;
						mode[0] = 0;
						mode_1[0] = 0;
						point = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] = '\0';
						printf("Match found: %s\n", str3);
						break;
					}
					else
					{
						flag = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] = '\0';
						len1 = 0;
						len = 0;
						mode_1[0] = 0;
						mode[0] = 0;
					}
				}
				fclose(Admin);
			}
		}

		// Confirmation for election & candidate name
		if (mx <= 5 * p && mx >= 3 * p && my >= 1.5 * p && my <= 2.2 * p && page == 5)
		{
			read_election();
			strcpy(election_name[electionstatus],str[2]);		
			write_election();
			
			take_candidate();

			for (int i = 0; i < 4; i++)
			{
				strcpy(str4[electionstatus][i],str2[i]);
			}
			
			write_candidate();

			mode_1[2] = 0;
			str[2][0] = '\0';
			for (int i = 0; i < 4; i++)
			{
				str2[i][0] = '\0';
			}
			len = 0;
			len1 = 0;
			k = -1;
			mode[2] = 0;
			mode_1[2] = 0;

			electionstatus++;

			track_election = fopen("election_track.txt","w");
			fprintf(track_election,"%d",electionstatus);
			fclose(track_election); 

			page = 10;
		}

		// Activate election name in order to write election name
		if (mx <= 6.5 * p && mx >= 1 * p && my >= 8 * p && my <= 8.7 * p && page == 5)
		{
			mode[2] = 1;
		}

		// Activate voter || admin box,for login or resister as Admin or voter
		if (mx <= 3.5 * p && mx >= 2 * p && my >= 9 * p && my <= 9.7 * p && (page == 2 || page == 3))
		{
			point = 1;
		}
		if (mx <= 3.5 * p && mx >= 2 * p && my >= 10 * p && my <= 10.7 * p && page == 12)
		{
			point_1 = true;
		}

		if (mx <= 5.5 * p && mx >= 4 * p && my >= 9 * p && my <= 9.7 * p && (page == 2 || page == 3))
		{
			point = 2;
		}
		if (mx <= 5.5 * p && mx >= 4 * p && my >= 10 * p && my <= 10.7 * p && page == 12)
		{
			point_1 = false;
		}

		if (mx <= 7 * p && mx >= 5.5 * p && my >= 0.5 * p && my <= 1.3 * p && page == 4 && check_leaderboard == 1) // after vote this will happen
		{
			exit(1);
		}

		if (mx <= 2.5 * p && mx >= 1 * p && my >= 0.5 * p && my <= 1.3 * p && (page == 4 || page == 2 || page == 3 || page == 10 || page == 5)) // back to home page
		{
			page = 1;
			check_leaderboard = 0;
			thanks = 0;
			point = 0;
		}

		// vote to election
		if (mx <= 6 * p && mx >= 2 * p && my >= 8 * p && my <= 9 * p && (page == 4 || page == 10))
		{
			if (page == 4 && check_leaderboard == 0)
			{
				page = 9; // page  >> vote page
				election_page = true;
			}
			else if (page == 10 && election_count <= 3 && atoi(election_status) < 3)
				page = 5;
		}

		// counting vote
		if (mx >= 6 * p && mx <= 7 * p && my >= 8.3 * p && my <= 9.1 * p && page == 6 && check_leaderboard == 0)
		{
			page = 9;			   // this for blank page
			check_leaderboard = 1; // Actibate the leaderboard
			thanks = 1;			   // For Thank you message

			read_one_vote();
			con_1[election_sort] = 1;

			cand[election_sort][0]++;

			if (con[0] == 1 && con_1[0] == 0)
				con_1[0] = 1;
			else if (con[1] == 1 && con_1[1] == 0)
				con_1[1] = 1;
			else if (con[2] == 1 && con_1[2] == 0)
				con_1[2] = 1;

			update_vote();
			OnevoteCheck();
		}
		if (mx >= 6 * p && mx <= 7 * p && my >= 7.1 * p && my <= 7.9 * p && page == 6 && check_leaderboard == 0)
		{
			page = 9;			   // this for blank page
			check_leaderboard = 1; // Actibate the leaderboard
			thanks = 1;			   // For Thank you message

			read_one_vote();
			con_1[election_sort] = 1;

			cand[election_sort][1]++;

			if (con[0] == 1)
				con_1[0] = 1;
			else if (con[1] == 1)
				con_1[1] = 1;
			else if (con[2] == 1)
				con_1[2] = 1;

			update_vote();
			OnevoteCheck();
		}
		if (mx >= 6 * p && mx <= 7 * p && my >= 5.9 * p && my <= 6.7 * p && page == 6 && check_leaderboard == 0)
		{
			page = 9;			   // this for blank page
			check_leaderboard = 1; // Actibate the leaderboard
			thanks = 1;			   // For Thank you message

			read_one_vote();
			con_1[election_sort] = 1;

			cand[election_sort][2]++;

			if (con[0] == 1)
				con_1[0] = 1;
			else if (con[1] == 1)
				con_1[1] = 1;
			else if (con[2] == 1)
				con_1[2] = 1;

			update_vote();
			OnevoteCheck();
		}
		if (mx >= 6 * p && mx <= 7 * p && my >= 4.7 * p && my <= 5.5 * p && page == 6 && check_leaderboard == 0)
		{
			page = 9;			   // this for blank page
			check_leaderboard = 1; // Actibate the leaderboard
			thanks = 1;			   // For Thank you message

			read_one_vote();

			cand[election_sort][3]++;

			if (con[0] == 1)
				con_1[0] = 1;
			else if (con[1] == 1)
				con_1[1] = 1;
			else if (con[2] == 1)
				con_1[2] = 1;

			update_vote();
			OnevoteCheck();
		}

		if (mx <= 6 * p && mx >= 2 * p && my >= 5 * p && my <= 6 * p && check_leaderboard == 1 && page == 4)
		{
			page = 8; // open LeaderBoard page
		}

		// Admin page to open LeaderBoard page
		if (mx <= 6 * p && mx >= 2 * p && my >= 5 * p && my <= 6 * p && page == 10)
		{
			page = 9;
			election_page1 = true;
		}

		// open candidate page & election close page
		if (mx <= 6 * p && mx >= 2 * p && my >= 6.5 * p && my <= 7.5 * p && (page == 4 || page == 10))
		{
			if (page == 4)
				page = 7;
			else if (page == 10)
			{
				page = 12;
			}
		}

		// Election close box activation(only for admin)
		if (mx <= 7.5 * p && mx >= 6 * p && my >= 7 * p && my <= 7.7 * p && page == 12)
		{
			if (point_1 == true)
			{
				if (con[0] == 1)
				{
					con[0] = 0;
					auxi = fopen("confirmation.txt", "w");
					fprintf(auxi, "%d %d %d", con[0], con[1], con[2]);
					fclose(auxi);
				}
			}
			else
			{
				if(electionstatus > 0 && electionstatus <= 3)
				{
					election_sort = 0;
					erase_election(election_sort);
				}
			}
		}
		// Erase election from there
		if (mx <= 7.5 * p && mx >= 6 * p && my >= 6 * p && my <= 6.7 * p && page == 12)
		{
			if (point_1 == true)
			{
				if (con[1] == 1)
				{
					con[1] = 0;
					auxi = fopen("confirmation.txt", "w");
					fprintf(auxi, "%d %d %d", con[0], con[1], con[2]);
					fclose(auxi);
				}
			}
			else
			{
				if(electionstatus > 0 && electionstatus <= 3)
				{
					election_sort = 1;
					erase_election(election_sort);
				}
			}
		}
		if (mx <= 7.5 * p && mx >= 6 * p && my >= 5 * p && my <= 5.7 * p && page == 12)
		{
			if (point_1 == true)
			{
				if (con[2] == 1)
				{
					con[2] = 0;
					auxi = fopen("confirmation.txt", "w");
					fprintf(auxi, "%d %d %d", con[0], con[1], con[2]);
					fclose(auxi);
				}
			}
			else
			{
				if(electionstatus > 0 && electionstatus <= 3)
				{
					election_sort = 2;
					erase_election(election_sort);
				}
			}
		}

		// back button option
		if (mx <= 7 * p && mx >= 5.5 * p && my >= 0.5 * p && my <= 1.3 * p)
		{
			if (page == 6 || page == 7 || page == 8 || page == 9 || page == 12 || page == 11 || page == 5)
			{
				if ((page == 8 && certainity_2 == false) || page == 7 || page == 6)
					page = 4; // Back to home page
				else if ((page == 8 && certainity_2 == true) || page == 12 || page == 11 || page == 5)
				{
					if(page == 11 && certainity == false)
						page = 4;
					else
					page = 10; // Back to Admin page
				}
					
				else if(page == 9)
				{
					if(election_page == true)
					{
						page = 4;
						election_page = false;
						flag2 = 0;
						flag3 = 0; 
					}
					else if(election_page1 == true)
					{
						if( check_leaderboard == 1)
						{
							page = 4;
							election_page1 == false;
						}
						else
						{
							page = 10;
							election_page1 == false;
						}
					}
					else if(election_page2 == true) // result page to back
					{
						if(certainity)
						{
							page = 10;
							election_page2 = false;
							certainity == true;
							flag4 = 0;														
						}
						else
						{
							page = 4;
							election_page2 = false;
							certainity == false;
							flag4 = 0;
						}
					}
					else if(thanks)
					{
						page = 4;
						thanks = 0;
					}
					
				}					
				
			}
			else if (page == 1)
				exit(0);
		}

		// login page name box activate
		if (mx <= 6.5 * p && mx >= 1 * p && my >= 6 * p && my <= 7 * p && page == 2)
		{

			mode[0] = 1;
			mode_1[0] = 0;
			flag = 1;
		}

		// from there we command to go vote our candidate
		if (mx <= 6.5 * p && mx >= 6 * p && my >= 7 * p && my <= 7.5 * p && page == 9 && (election_page == true || election_page1 == true || election_page2 == true))
		{
			if (election_page == true)
			{
				if (con[0] == 1)
				{
					if (con_1[0] == 0)
					{
						page = 6;
						election_sort = 0;
						election_page = false;
					}
					else
						flag3 = 1;
				}
				else
					flag2 = 1;
			}
			else if (election_page1 == true)
			{
				page = 8;
				election_sort = 0;
				election_page1 = false;
			}
			else if (election_page2 == true)
			{
				election_sort = 0;
				if(con[election_sort] == 0)
				{
					page = 11;
					election_page2 = false;
				}
				else
				{
					flag4 = 1;
				}

			}
		}

		if (mx <= 6.5 * p && mx >= 6 * p && my >= 6 * p && my <= 6.5 * p && page == 9 && (election_page == true || election_page1 == true || election_page2 == true))
		{
			if (election_page == true)
			{
				if (con[1] == 1)
				{
					if (con_1[1] == 0)
					{
						page = 6;
						election_sort = 1;
						election_page = false;
					}
					else
						flag3 = 1;
				}
				else
					flag2 = 1;
			}
			else if (election_page1 == true)
			{
				page = 8;
				election_sort = 1;
				election_page1 = false;
			}
			else if (election_page2 == true)
			{
				
				election_sort = 1;
				if(con[election_sort] == 0)
				{
					page = 11;
					election_page2 = false;
				}
				else
				{
					flag4 = 1;
				}					
			}
		}

		if (mx <= 6.5 * p && mx >= 6 * p && my >= 5 * p && my <= 5.5 * p && page == 9 && (election_page == true || election_page1 == true || election_page2 == true))
		{
			if (election_page == true)
			{
				if (con[2] == 1)
				{
					if (con_1[2] == 0)
					{
						page = 6;
						election_sort = 2;
						election_page = false;
					}
					else
						flag3 = 1;
				}
				else
					flag2 = 1;
			}
			else if (election_page1 == true)
			{
				page = 8;
				election_sort = 2;
				election_page1 = false;
			}
			else if (election_page2 == true)
			{
				
				election_sort = 2;
				if(con[election_sort] == 0)
				{
					page = 11;
					election_page2 = false;
					
				}
				else
				{
					flag4 = 1;
				}
			}
		}

		// result page activate
		if (mx <= 6 * p && mx >= 2 * p && my >= 3.5 * p && my <= 4.5 * p && (page == 10 || page == 4))
		{
			page = 9;
			election_page2 = true;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	
	}
}

void iKeyboard(unsigned char key)
{
	// login page && password box
	if (mode_1[0] == 1 && page == 2)
	{
		if (key == '\r')
		{
			if (point == 2)
			{
				char flag_name[30];
				strcpy(flag_name,str[0]);
				// printf("%d %d",len,strlen(voter_name));
				strcat(str[0], " ");
				strcat(str[0], str1[0]);
				name1 = fopen("name.txt", "r");
				while (fgets(str3, sizeof(str3), name1) != NULL)
				{
					// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;
					// Compare the line with the search string
					if (strcmp(str3, str[0]) == 0)
					{

						strcpy(voter_name,flag_name);
						len1 = 0;
						len = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] ='\0';
						mode[0] = 0;
						mode_1[0] = 0;
						point = 0;
						printf("Match found: %s\n", str3);
						page = 4;
						election_page = true;
						break;
					}
					else
					{
						flag = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] = '\0';
						len1 = 0;
						len = 0;
						mode_1[0] = 0;
						mode[0] = 0;
					}
				}
				fclose(name1);
			}
			else if (point == 1)
			{
				strcat(str[0], " ");
				strcat(str[0], str1[0]);

				Admin = fopen("admin.txt", "r");
				while (fgets(str3, sizeof(str3), Admin) != NULL)
				{
					// Remove newline character if present
					str3[strcspn(str3, "\n")] = 0;
					// Compare the line with the search string
					if (strcmp(str3, str[0]) == 0)
					{
						page = 10;
						len1 = 0;
						len = 0;
						mode[0] = 0;
						mode_1[0] = 0;
						point = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] = '\0';
						printf("Match found: %s\n", str3);
						break;
					}
					else
					{
						flag = 0;
						str[0][0] = '\0';
						str1[0][0] = '\0';
						str6[0] = '\0';
						len1 = 0;
						len = 0;
						mode_1[0] = 0;
						mode[0] = 0;
					}
				}
				fclose(Admin);
			}
		}

		else if (key != '\b')
		{
			str1[0][len1] = key;
			str6[len1] = '*';
			str6[len1+1] = '\0';
			str1[0][len1 + 1] = '\0';
			len1++;
		}

		else // Erase character
		{
			flag = 1;
			str1[0][len1 - 1] = '\0';
			str6[len1-1]= '\0';
			len1--;
		}
	}

	// register page
	if (mode_1[1] == 1 && page == 3)
	{
		if (key == '\r' && len1 < 9) // here 0 to 7 for 8 char,8 for null,9 for enter
		{
			if (point == 1)
			{
				Admin = fopen("admin.txt", "w");
				fprintf(Admin, "%s %s\n", str[1], str1[1]);
				fclose(Admin);

				len1 = 0;
				str1[1][0] = '\0';
				str[1][0] = '\0';
				mode[1] = 0;
				mode_1[1] = 0;
				page = 1;
				point = 0; //
			}

			if (point == 2)
			{
				name1 = fopen("name.txt", "w");
				fprintf(name1, "%s %s\n", str[1], str1[1]);
				fclose(name1);

				auxi_2 = fopen("1votefor1election.txt", "w");
				fprintf(auxi_2, "%d %d %d", 0, 0, 0);
				fclose(auxi_2);

				name2 = fopen("save_name.txt", "w");
				fprintf(name2, "%s %s\n", str[1], str1[1]);
				fclose(name2);


				len1 = 0;
				str1[1][0] = '\0';
				str[1][0] = '\0';
				mode[1] = 0;
				mode_1[1] = 0;
				page = 1;
			}
		}

		else if (key != '\b')
		{
			str1[1][len1] = key;
			str1[1][len1 + 1] = '\0';
			len1++;
		}

		else // Erase character
		{
			flag = 1;
			str1[1][len1 - 1] = '\0';
			len1--;
		}

		if (len1 > 9) // here 0 to 7 for 8 char,8 for null,9 for enter
			flag = 0;
	}

	// Name Box,this box will work until the correct voter name inseted
	if (mode[0] == 1 && mode_1[0] == 0 && page == 2)
	{
		if (key == '\r')
		{
			if (point == 2)
			{
				mode_1[0] = 1;
				len = 0;
			}

			if (point == 1)
			{

				mode_1[0] = 1;
				len = 0;
			}
		}

		else if (key != '\b')
		{
			str[0][len] = key;
			str[0][len + 1] = '\0';
			len++;
		}

		else
		{
			flag1 = 1;
			str[0][len - 1] = '\0';
			len--;
		}
	}

	// register Name Box ,here mode_1 must be 0,nor str active when user type password
	if (mode[1] == 1 && mode_1[1] == 0 && page == 3)
	{
		if (key == '\r')
		{
			mode_1[1] = 1;
			len = 0;
		}

		else if (key != '\b')
		{
			str[1][len] = key;

			str[1][len + 1] = '\0';
			len++;
		}

		else
		{
			// flag=1;
			str[1][len - 1] = '\0';
			len--;
		}
	}

	if (mode_1[2] == 1 && page == 5)
	{
		if (key == '\r')
		{
			if(k < 4)
			{
				str1[2][0] = '\0';
				len1 = 0;
				mode_1[2] = 1;
				k++;
			}
			else
			{
				read_election();
				strcpy(election_name[electionstatus],str[2]);
				write_election();

				take_candidate();
				for (int i = 0; i < 4; i++)
				{
					strcpy(str4[electionstatus][i],str2[i]);
				}		
				write_candidate();

				mode_1[2] = 0;
				str[2][0] = '\0';
				for (int i = 0; i < 4; i++)
				{
					str2[i][0] = '\0';
				}
				len = 0;
				mode[2] = 0;
				
				electionstatus++;

				track_election = fopen("election_track.txt","w");
				fprintf(track_election,"%d",electionstatus);
				fclose(track_election);

				k = 0;
				page = 10;
			}
		}

		else if (key != '\b')
		{
			str1[2][len1] = key;
			str1[2][len1 + 1] = '\0';
			strcpy(str2[k], str1[2]); // input dibi ami store korbo
			len1++;
		}

		else
		{
			// flag=1;
			str1[2][len1 - 1] = '\0';
			len1--;
		}
	}
	
	if (mode[2] == 1 && mode_1[2] == 0 && page == 5)
	{
		if (key == '\r')
		{
			// printf("%thanks",k);
			mode_1[2] = 1;
			len = 0;
		}

		else if (key != '\b')
		{
			str[2][len] = key;
			str[2][len + 1] = '\0';
			len++;
		}

		else
		{
			// flag=1;
			str[2][len - 1] = '\0';
			len--;
		}
	}
}
void iSpecialKeyboard(unsigned char key)
{
}

int main()
{
	// place your own initialization codes here.
	len = 0;
	len1 = 0;
	iInitialize(8 * p, 13 * p, "Voting System");
	return 0;
}