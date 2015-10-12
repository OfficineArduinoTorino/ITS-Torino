all: mysniffex.c mysniffex_speed.c serialwrite.c
	gcc -o ./mysniffex -I/usr/local/mysql/include -DBIG_JOINS=1 -fno-strict-aliasing -g -DNDEBUG mysniffex.c -L/usr/local/mysql/lib -lmysqlclient -lpthread -lz -lm -ldl -lpcap
	gcc -o ./mysniffex_speed -I/usr/local/mysql/include -DBIG_JOINS=1 -fno-strict-aliasing -g -DNDEBUG mysniffex_speed.c -L/usr/local/mysql/lib -lmysqlclient -lpthread -lz -lm -ldl
	gcc -o ./serialwrite -I/usr/local/mysql/include -DBIG_JOINS=1 -fno-strict-aliasing -g -DNDEBUG serialwrite.c -L/usr/local/mysql/lib -lmysqlclient -lpthread -lz -lm -ldl