#define APP_NAME		"mysniffex"
#define APP_DESC		"Sniffer example using libpcap"
#define APP_COPYRIGHT	"Copyright (c) 2005 The Tcpdump Group"
#define APP_DISCLAIMER	"THERE IS ABSOLUTELY NO WARRANTY FOR THIS PROGRAM."
#define APP_VERSION		"Version 1.2 by Team2"

#include <mysql.h>
#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* default snap length (maximum bytes per packet to capture) */
#define SNAP_LEN 1518

/* ethernet headers are always exactly 14 bytes [1] */
#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN  6

/* Ethernet header */
struct sniff_ethernet
{
	u_char  ether_dhost[ETHER_ADDR_LEN];	/* destination host address */
	u_char  ether_shost[ETHER_ADDR_LEN];	/* source host address */
	u_short ether_type;						/* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip
{
	u_char  ip_vhl;					/* version << 4 | header length >> 2 */
	u_char  ip_tos;					/* type of service */
	u_short ip_len;					/* total length */
	u_short ip_id;					/* identification */
	u_short ip_off;					/* fragment offset field */
	#define IP_RF 0x8000			/* reserved fragment flag */
	#define IP_DF 0x4000			/* dont fragment flag */
	#define IP_MF 0x2000			/* more fragments flag */
	#define IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
	u_char  ip_ttl;					/* time to live */
	u_char  ip_p;					/* protocol */
	u_short ip_sum;					/* checksum */
	struct  in_addr ip_src,ip_dst;	/* source and dest address */
};
#define IP_HL(ip)				(((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)				(((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp
{
	u_short	th_sport;	/* source port */
	u_short	th_dport;	/* destination port */
	tcp_seq	th_seq;		/* sequence number */
	tcp_seq	th_ack;		/* acknowledgement number */
	u_char	th_offx2;	/* data offset, rsvd */
#define TH_OFF(th)		(((th)->th_offx2 & 0xf0) >> 4)
	u_char	th_flags;
	#define TH_FIN	0x01
	#define TH_SYN	0x02
	#define TH_RST	0x04
	#define TH_PUSH	0x08
	#define TH_ACK	0x10
	#define TH_URG	0x20
	#define TH_ECE	0x40
	#define TH_CWR	0x80
	#define TH_FLAGS		(TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win;		/* window */
	u_short th_sum;		/* checksum */
	u_short th_urp;		/* urgent pointer */
};

MYSQL *conn;		/* connection to mysql database */
MYSQL_RES *res;		/* query result (all) */
MYSQL_ROW row;		/* quert result (row) */

char *_check_interface(int,char **,char []);
int _database();
int _power(int,int);
void got_packet(u_char *,const struct pcap_pkthdr *,const u_char *);
void _itoa_sizepayload(char [],int);
int _check_headers(const u_char *,const struct sniff_ethernet *,const struct sniff_ip *,const struct sniff_tcp *,int *,int *);
void _ip_query(const struct sniff_ip *,char [],int);
int _query(unsigned int,...);

int main(int argc,char **argv)
{
	char *dev=NULL;					/* capture device name */
	char errbuf[PCAP_ERRBUF_SIZE];	/* error buffer */
	pcap_t *handle;					/* packet capture handle */
	char filter_exp[]="ip";			/* filter expression [3] */
	struct bpf_program fp;			/* compiled filter program (expression) */
	bpf_u_int32 mask;				/* subnet mask */
	bpf_u_int32 net;				/* ip */
	int num_packets=1;				/* number of packets to capture */
	int err=0;						/* errors (boolean) */

	if ((dev=_check_interface(argc,argv,errbuf))!=NULL)
	{
		/* print capture info */
		printf("Device: %s\n",dev);
		printf("Filter expression: %s\n",filter_exp);

		/* get network number and mask associated with capture device */
		if (pcap_lookupnet(dev,&net,&mask,errbuf)==-1)
		{
			fprintf(stderr,"Couldn't get netmask for device %s: %s\n",dev,errbuf);
			net=0;
			mask=0;
			err=1;
		}

		/* open capture device */
		handle=pcap_open_live(dev,SNAP_LEN,1,1000,errbuf);
		if (handle==NULL)
		{
			fprintf(stderr,"Couldn't open device %s: %s\n",dev,errbuf);
			err=1;
		}

		/* make sure we're capturing on an Ethernet device [2] */
		if (pcap_datalink(handle)!=DLT_EN10MB)
		{
			fprintf(stderr,"%s is not an Ethernet\n",dev);
			err=1;
		}

		/* compile the filter expression */
		if (pcap_compile(handle,&fp,filter_exp,0,net)==-1)
		{
			fprintf(stderr,"Couldn't parse filter %s: %s\n",filter_exp,pcap_geterr(handle));
			err=1;
		}

		/* apply the compiled filter */
		if (pcap_setfilter(handle,&fp)==-1)
		{
			fprintf(stderr,"Couldn't install filter %s: %s\n",filter_exp,pcap_geterr(handle));
			err=1;
		}

		if (!err)
		{
			if (_database())
			{
				/* now we can set our callback function */
				for (;;) pcap_loop(handle,num_packets,got_packet,NULL);
			}
		}
	}
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);

	/* cleanup */
	pcap_freecode(&fp);
	pcap_close(handle);

	printf("\nCapture complete.\n");

	return 0;
}

char *_check_interface(int argc,char **argv,char errbuf[])
{
	/* check for capture device name on command-line */
	char *dev;
	if (argc==2) dev=argv[1];
	else if (argc>2)
	{
		fprintf(stderr,"error: unrecognized command-line options\n\n");
		dev=NULL;
	}
	else
	{
		/* find a capture device if not specified on command-line */
		dev=pcap_lookupdev(errbuf);
		if (dev==NULL) fprintf(stderr,"Couldn't find default device: %s\n",errbuf);
	}
	return dev;
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

void got_packet(u_char *args,const struct pcap_pkthdr *header,const u_char *packet)
{
	/* declare pointers to packet headers */
	const struct sniff_ethernet *ethernet;  /* The ethernet header [1] */
	const struct sniff_ip *ip;              /* The IP header */
	const struct sniff_tcp *tcp;            /* The TCP header */
	const char *payload;                    /* Packet payload */

	int size_ip;
	int size_tcp;
	int size_payload;

	char packet_size[10];

	/* define ethernet header */
	ethernet=(struct sniff_ethernet*)(packet);
	
	/* define/compute ip header offset */
	ip=(struct sniff_ip*)(packet+SIZE_ETHERNET);
	size_ip=IP_HL(ip)*4;
	/*if (size_ip<20) 
	{
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}*/
	
	/* determine protocol */	
	/*switch(ip->ip_p)
	{
		case IPPROTO_TCP:
			printf("   Protocol: TCP\n");
			break;
		case IPPROTO_UDP:
			printf("   Protocol: UDP\n");
			return;
		case IPPROTO_ICMP:
			printf("   Protocol: ICMP\n");
			return;
		case IPPROTO_IP:
			printf("   Protocol: IP\n");
			return;
		default:
			printf("   Protocol: unknown\n");
			return;
	}*/
	
	/*
	 *  OK, this packet is TCP.
	 */
	
	/* define/compute tcp header offset */
	tcp=(struct sniff_tcp*)(packet + SIZE_ETHERNET+size_ip);
	size_tcp=TH_OFF(tcp)*4;
	/*if (size_tcp<20)
	{
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}*/
	
	/*printf("   Src port: %d\n", ntohs(tcp->th_sport));
	printf("   Dst port: %d\n", ntohs(tcp->th_dport));*/
	
	/* compute tcp payload (segment) size */
	size_payload=ntohs(ip->ip_len)-(size_ip+size_tcp);

	if (size_payload>0)
	{
		/* print source and destination IP addresses */
		printf("From: %s\n",inet_ntoa(ip->ip_src));
		printf("To: %s\n",inet_ntoa(ip->ip_dst));
		printf("Payload: %d bytes\n",size_payload);
		printf("\n");

		_itoa_sizepayload(packet_size,size_payload);

		if(inet_ntoa(ip->ip_src)[0]=='1' && inet_ntoa(ip->ip_src)[1]=='9' && inet_ntoa(ip->ip_src)[2]=='2') _ip_query(ip,packet_size,0);

		if(inet_ntoa(ip->ip_dst)[0]=='1' && inet_ntoa(ip->ip_dst)[1]=='9' && inet_ntoa(ip->ip_dst)[2]=='2') _ip_query(ip,packet_size,1);
	}
}

void _itoa_sizepayload(char packet_size[],int num)
{
	char *charsize=&packet_size[0];
	int p=_power(10,8),n;
	while (num<p) p/=10;
	while(p>0)
	{
		n=num/p;
		num=(num%p);
		p/=10;
		*charsize=n+48;
		*charsize++;
	}
	*charsize='\0';
}

void _ip_query(const struct sniff_ip *ip,char packet_size[],int src_dst)
{
	char query[100];
	char *ipAddress=NULL;

	if (!src_dst) ipAddress=inet_ntoa(ip->ip_src);
	else ipAddress=inet_ntoa(ip->ip_dst);

	_query(3,"SELECT `id` FROM `sniffex` WHERE `ip`='",ipAddress,"'");
	res=mysql_store_result(conn);
	if ((row=mysql_fetch_row(res))==NULL) // IP non presente
	{
		_query(5,"INSERT INTO `sniffex` (`id`,`ip`,`volume`) VALUES (NULL,'",ipAddress,"',",packet_size,")");
	}
	else // IP presente
	{
		_query(4,"UPDATE `sniffex` SET `volume`=`volume`+",packet_size," WHERE `id`=",row[0]);
	}
	mysql_free_result(res);
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