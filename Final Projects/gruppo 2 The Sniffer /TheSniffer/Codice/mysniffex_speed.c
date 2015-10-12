#define APP_NAME		"mysniffex_speed"
#define APP_DESC		"Traffic speed calculator"
#define APP_COPYRIGHT	"Copyright (c) 2015 Team2 (Sniffer)"
#define APP_VERSION		"Version 1.0 by Team2"

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define SECONDS 1

MYSQL *conn;		/* connection to mysql database */
MYSQL_RES *res[2];		/* query result (all) */
MYSQL_ROW row[2];		/* quert result (row) */

FILE *fileport; /* serial port arduino */

int _database();
void _loop();
void _itoa(char [],int);
int _power(int,int);
int _query(unsigned int,...);

int main()
{
	fileport=fopen("/dev/cu.usbmodem1411","w");
	if(_database()) _loop();

	printf("Quitting\n");

	fclose(fileport);
	/* close connection */
	mysql_free_result(*res);
	mysql_close(conn);
	return 0;
}

int _database()
{
	char *server="127.0.0.1";
	char *user="root";
	char *password="";
	char *database="sniffer";
	conn=mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 0;
	}
	return 1;
}

void _loop()
{
	char charspeed[20];
	int num=0,rows[2],i,speed;

	_query(1,"SELECT `id`,`volume` FROM `sniffex` ORDER BY `id` ASC");
	res[num]=mysql_store_result(conn);
	rows[num]=mysql_num_rows(res[num]);
	if ((row[num]=mysql_fetch_row(res[num]))==NULL) return;

	num=!num;
	sleep(SECONDS);

	for (;;)
	{
		mysql_data_seek(res[!num],0);
		_query(1,"SELECT `id`,`volume` FROM `sniffex` ORDER BY `id` ASC");
		res[num]=mysql_store_result(conn);
		rows[num]=mysql_num_rows(res[num]);
		for (i=0;i<rows[!num];i++)
		{
			row[num]=mysql_fetch_row(res[num]);
			row[!num]=mysql_fetch_row(res[!num]);
			speed=(atoi(row[num][1])-atoi(row[!num][1]))/SECONDS;
			_itoa(charspeed,speed);
			_query(4,"UPDATE `sniffex` SET `speed`=",charspeed," WHERE `id`=",row[num][0]);
		}
		if (rows[num]>rows[!num])
		{
			for (i=0;i<(rows[num]-rows[!num]);i++)
			{
				row[num]=mysql_fetch_row(res[num]);
				speed=atoi(row[num][1])/SECONDS;
				_itoa(charspeed,speed);
				_query(4,"UPDATE `sniffex` SET `speed`=",charspeed," WHERE `id`=",row[num][0]);
			}
		}

		num=!num;
		sleep(SECONDS);
	}
}

void _itoa(char speed[],int num)
{
	char *charspeed=&speed[0];
	int p=_power(10,8),n;
	if (num==0)
	{
		*charspeed='0';
		*charspeed++;
	}
	else
	{
		while (num<p) p/=10;
		while(p>0)
		{
			n=num/p;
			num=(num%p);
			p/=10;
			*charspeed=n+48;
			*charspeed++;
		}
	}
	*charspeed='\0';
}

int _power(int n,int exp)
{
	int num;
	num=1;
	while (exp>0)
	{
		num*=n;
		exp--;
	}
	return num;
}

int _query(unsigned int num,...)
{
	char query[100];
	unsigned int i;
	va_list ap;
	va_start(ap,num);
	strcpy(query,va_arg(ap,char*));
	for (i=1;i<num;i++) strcat(query,va_arg(ap,char*));
	printf("Query: %s\n",query);
	if (mysql_query(conn,query))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 0;
	}
	va_end(ap);
	return 1;
}