About the EBU logger

The EBU will only start to send data when the computer with
the IP address 10.0.0.1 is found.

The wheelloader has two EBU, sending data to different ports.

--EBU--
SRC_ADDR "10.0.0.2"
SRC_PORT0 25100		//Wheelloader EBU_1 and dev_EBU
SRC_PORT1 25300		//Wheelloader EBU_2

--Industrial PC--
DST_ADDR "10.0.0.1"
DST_PORT0 25101
DST_PORT1 25102

The program will only listen to one EBU at the time so the program has
to be recompiled with the new port. The port can be changed in initSocket
in the EBULink class:
--------------------------	
void initSocket(){

	...
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr =  INADDR_ANY;
	serv_addr.sin_addr.s_addr =  inet_addr("10.0.0.1");
	serv_addr.sin_port = htons(DST_PORT0); //Change PORT here

	//Bind socket to local address
	if( bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
	...
}
---------------------------

The same goes for the DATABASE where to change between databases and collections by hardcode
the collection and compile. To change database and collection is done in the analyser.c 
file:
--------------------------
void startAnalyzer(void)
{
	//Algorithm for translating
	char *DB = "test";				//Which database
	char *coll = "test";				//Which collection 
	char *buff; 				//Datagram data buffer
	struct timespec tim, tim2;
	...
}
----------------------------
Whit this setting the database will store the data in the collection "test" in the internal
database "test".




