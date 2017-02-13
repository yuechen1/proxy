Name:		Yin-Li (Emily) Chow
UCID:		10103742
Tut: 		T01
Partner:	Yue Chen (10065082, T03)

How to run (using backdoor code from a1):
- compile in terminal#1 using: gcc -o proxy proxy.c
- run using: ./proxy [-logoption] <srcPort> localhost <dstPort>
- in terminal#2 of backdoor, run using: ./server <dstPort>
- in another terminal, run using: nc localhost <srcPort>
  Please note that this port number must match the other port number
- After being prompted for a password, enter: a


Supported commands (with samples below):
(blank)		Nothing is logged
-raw
-strip
-hex
-autoN


Script started on Sun 12 Feb 2017 05:20:24 PM MST
]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ gcc -o proxy proxy.c -pthread

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ ./proxy 8000 localhost 5000

Port logger running: srcPort=8000 host=localhost dstPort=5000
New connection: Sun Feb 12 17:21:27 2017
Connection from 127.0.0.1
^C

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ ./proxy 8000 localhost 5000[K10[P[1@1 [1@ [1@-[1@r[1@a[1@w [1@  8001 localhost 5001

Port logger running: srcPort=8001 host=localhost dstPort=5001
New connection: Sun Feb 12 17:21:58 2017
Connection from 127.0.0.1
<----password: 
---->a

<----Welcome to this backdoor

---->help

<----pwd 		 returns current working directory
cd <dir> 	 changes current working directory to <dir>
ls 		 lists the contents of the current working directory
cat <file> 	 returns contents of the file
help 		 prints a list of commands
encourage me 	 provides a motivational sentence to the user
beep 		 makes computer beep
who 		 returns current user (if possible)
off 		 terminates the program
>
---->pwd

<----/home/uga/ylchow/CPSC 526/a1
<----
>
---->beep

<---->
---->who

<----ylchow

---->off

<----You killed me...

^C

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ ./proxy -raw 8001 localhost 5001[K2[P[1@2[P[P[P[1@s[1@t[1@r[1@i[1@p

Port logger running: srcPort=8002 host=localhost dstPort=5002
New connection: Sun Feb 12 17:22:27 2017
Connection from 127.0.0.1

<----password: 
---->a

<----Welcome to this backdoor

---->test

<----test is not a valid command
>
---->help

<----pwd 		 returns current working directory
cd <dir> 	 changes current working directory to <dir>
ls 		 lists the contents of the current working directory
cat <file> 	 returns contents of the file
help 		 prints a list of commands
encourage me 	 provides a motivational sentence to the user
beep 		 makes computer beep
who 		 returns current user (if possible)
off 		 terminates the program
>
---->pass

<----pass is not a valid command
>
---->beep

<---->
---->who

<----ylchow

---->off

<----You killed me...
^C

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ ./proxy -strip 8002 localhost 5002[K3[P[1@3[P[P[P[P[P[1@h[1@e[1@x

Port logger running: srcPort=8003 host=localhost dstPort=5003
New connection: Sun Feb 12 17:23:00 2017
Connection from 127.0.0.1

<---- 70 61 73 73 77 6f 72 64 3a 20 password: 
<----
----> 61 0a
<---- 57 65 6c 63 6f 6d 65 20 74 6f Welcome to
<---- 20 74 68 69 73 20 62 61 63 6b  this back
<---- 64 6f 6f 72 0a
----> 68 65 6c 70 0a
<---- 70 77 64 20 09 09 20 72 65 74 pwd 		 ret
<---- 75 72 6e 73 20 63 75 72 72 65 urns curre
<---- 6e 74 20 77 6f 72 6b 69 6e 67 nt working
<---- 20 64 69 72 65 63 74 6f 72 79  directory
<---- 0a 63 64 20 3c 64 69 72 3e 20 
cd <dir> 
<---- 09 20 63 68 61 6e 67 65 73 20 	 changes 
<---- 63 75 72 72 65 6e 74 20 77 6f current wo
<---- 72 6b 69 6e 67 20 64 69 72 65 rking dire
<---- 63 74 6f 72 79 20 74 6f 20 3c ctory to <
<---- 64 69 72 3e 0a 6c 73 20 09 09 dir>
ls 		
<---- 20 6c 69 73 74 73 20 74 68 65  lists the
<---- 20 63 6f 6e 74 65 6e 74 73 20  contents 
<---- 6f 66 20 74 68 65 20 63 75 72 of the cur
<---- 72 65 6e 74 20 77 6f 72 6b 69 rent worki
<---- 6e 67 20 64 69 72 65 63 74 6f ng directo
<---- 72 79 0a 63 61 74 20 3c 66 69 ry
cat <fi
<---- 6c 65 3e 20 09 20 72 65 74 75 le> 	 retu
<---- 72 6e 73 20 63 6f 6e 74 65 6e rns conten
<---- 74 73 20 6f 66 20 74 68 65 20 ts of the 
<---- 66 69 6c 65 0a 68 65 6c 70 20 file
help 
<---- 09 09 20 70 72 69 6e 74 73 20 		 prints 
<---- 61 20 6c 69 73 74 20 6f 66 20 a list of 
<---- 63 6f 6d 6d 61 6e 64 73 0a 65 commands
e
<---- 6e 63 6f 75 72 61 67 65 20 6d ncourage m
<---- 65 20 09 20 70 72 6f 76 69 64 e 	 provid
<---- 65 73 20 61 20 6d 6f 74 69 76 es a motiv
<---- 61 74 69 6f 6e 61 6c 20 73 65 ational se
<---- 6e 74 65 6e 63 65 20 74 6f 20 ntence to 
<---- 74 68 65 20 75 73 65 72 0a 62 the user
b
<---- 65 65 70 20 09 09 20 6d 61 6b eep 		 mak
<---- 65 73 20 63 6f 6d 70 75 74 65 es compute
<---- 72 20 62 65 65 70 0a 77 68 6f r beep
who
<---- 20 09 09 20 72 65 74 75 72 6e  		 return
<---- 73 20 63 75 72 72 65 6e 74 20 s current 
<---- 75 73 65 72 20 28 69 66 20 70 user (if p
<---- 6f 73 73 69 62 6c 65 29 0a 6f ossible)
o
<---- 66 66 20 09 09 20 74 65 72 6d ff 		 term
<---- 69 6e 61 74 65 73 20 74 68 65 inates the
<---- 20 70 72 6f 67 72 61 6d 0a 3e  program
>
<----
----> 62 65 65 70 0a
<---- 3e
----> 6f 66 66 0a
<---- 59 6f 75 20 6b 69 6c 6c 65 64 You killed
^C

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ ./proxy -hex 8003 localhost 5003[K4[P[1@4[P[P[P[1@a[1@u[1@t[1@o[1@3[1@2

Port logger running: srcPort=8004 host=localhost dstPort=5004
autoN N: 32
New connection: Sun Feb 12 17:23:34 2017
Connection from 127.0.0.1

<----\p70\a61\s73\s73\w77\o6f\r72\d64\:3a\ 20\õfffffff5\?3f\»ffffffbb\7f
---->\a61\n
<----\W57\e65\l6c\c63\o6f\m6d\e65\ 20\t74\o6f\ 20\t74\h68\i69\s73\ 20\b62\a61\c63\k6b\d64\o6f\o6f\r72\n
---->\h68\e65\l6c\p70\n
<----\p70\w77\d64\ 20\t\t\ 20\r72\e65\t74\u75\r72\n6e\s73\ 20\c63\u75\r72\r72\e65\n6e\t74\ 20\w77\o6f\r72\k6b\i69\n6e\g67\ 20
<----\d64\i69\r72\e65\c63\t74\o6f\r72\y79\n\c63\d64\ 20\<3c\d64\i69\r72\>3e\ 20\t\ 20\c63\h68\a61\n6e\g67\e65\s73\ 20\c63\u75\r72
<----\r72\e65\n6e\t74\ 20\w77\o6f\r72\k6b\i69\n6e\g67\ 20\d64\i69\r72\e65\c63\t74\o6f\r72\y79\ 20\t74\o6f\ 20\<3c\d64\i69\r72\>3e\n
<----\l6c\s73\ 20\t\t\ 20\l6c\i69\s73\t74\s73\ 20\t74\h68\e65\ 20\c63\o6f\n6e\t74\e65\n6e\t74\s73\ 20\o6f\f66\ 20\t74\h68\e65\ 20
<----\c63\u75\r72\r72\e65\n6e\t74\ 20\w77\o6f\r72\k6b\i69\n6e\g67\ 20\d64\i69\r72\e65\c63\t74\o6f\r72\y79\n\c63\a61\t74\ 20\<3c\f66
<----\i69\l6c\e65\>3e\ 20\t\ 20\r72\e65\t74\u75\r72\n6e\s73\ 20\c63\o6f\n6e\t74\e65\n6e\t74\s73\ 20\o6f\f66\ 20\t74\h68\e65\ 20\f66
<----\i69\l6c\e65\n\h68\e65\l6c\p70\ 20\t\t\ 20\p70\r72\i69\n6e\t74\s73\ 20\a61\ 20\l6c\i69\s73\t74\ 20\o6f\f66\ 20\c63\o6f\m6d
<----\m6d\a61\n6e\d64\s73\n\e65\n6e\c63\o6f\u75\r72\a61\g67\e65\ 20\m6d\e65\ 20\t\ 20\p70\r72\o6f\v76\i69\d64\e65\s73\ 20\a61\ 20
<----\m6d\o6f\t74\i69\v76\a61\t74\i69\o6f\n6e\a61\l6c\ 20\s73\e65\n6e\t74\e65\n6e\c63\e65\ 20\t74\o6f\ 20\t74\h68\e65\ 20\u75\s73\e65
<----\r72\n\b62\e65\e65\p70\ 20\t\t\ 20\m6d\a61\k6b\e65\s73\ 20\c63\o6f\m6d\p70\u75\t74\e65\r72\ 20\b62\e65\e65\p70\n\w77\h68
<----\o6f\ 20\t\t\ 20\r72\e65\t74\u75\r72\n6e\s73\ 20\c63\u75\r72\r72\e65\n6e\t74\ 20\u75\s73\e65\r72\ 20\(28\i69\f66\ 20\p70\o6f
<----\s73\s73\i69\b62\l6c\e65\)29\n\o6f\f66\f66\ 20\t\t\ 20\t74\e65\r72\m6d\i69\n6e\a61\t74\e65\s73\ 20\t74\h68\e65\ 20\p70\r72
<----\o6f\g67\r72\a61\m6d\n\>3e
---->\w77\h68\o6f\n
<----\y79\l6c\c63\h68\o6f\w77\n
---->\b62\e65\e65\p70\n
<----\>3e
---->\o6f\f66\f66\n
^C

]0;ylchow@csuslinux:a2[ylchow@csuslinux a2]$ exit

exit

Script done on Sun 12 Feb 2017 05:23:52 PM MST
