#define APP_NAME		"mysniffex_speed"
#define APP_DESC		"Traffic speed calculator"
#define APP_COPYRIGHT	"Copyright (c) 2015 Team2 (Sniffer)"
#define APP_VERSION		"Version 1.0 by Team2"

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

MYSQL *conn;		/* connection to mysql database */
MYSQL_RES *res;		/* query result (all) */
MYSQL_ROW row;		/* quert result (row) */

int _database();
int _query(unsigned int,...);

int main()
{
	FILE *fileport; /* serial port arduino */
	
	if (_database())
	{
		for (;;)
		{
			_query(1,"SELECT SUM(`speed`) FROM `sniffex`");
			res=mysql_store_result(conn);
			row=mysql_fetch_row(res);
			printf("send: %s\n",row[0]);
			fileport=fopen("/dev/cu.usbmodem1411","w");
			fwrite(row[0],sizeof(char),sizeof(row[0]),fileport);
			fclose(fileport);
			sleep(3);
		}
	}
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
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