struct msg
{
	char message[100];
	
};

program MSG_PROG
{
	version MSG_VERS
	{
		void MSG(msg)=1;
	}=1;
}=0x2111ffaf;
