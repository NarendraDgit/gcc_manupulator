#include "hfile.h"

int main(int argc, char* argv[])
{
	bool s_flag = false;
	bool c_flag = false;
	bool o_flag = false;

	char* src = NULL;
	char* dest = NULL;
	char* destt = NULL;
	char* switch_str = "Sco:h";
	int ret_val, len;

	if(argc == 1)
	{
		usageerror();
		exit(EXIT_FAILURE);
	}

 	if(argc == 2)
        {
		if(access(argv[1], F_OK) == 0)
		{
                 	nooption("a.out", argv[1]);
                 	exit(EXIT_SUCCESS);
		}
		else
		{
			printf("%s: \033[1;31m error: \033[0m %s: No such file of directory\n",  argv[0], argv[1]);
			usageerror();
			exit(EXIT_FAILURE);
		}
        }

	while((ret_val = getopt(argc, argv, switch_str)) != -1)
	{
		switch((char)ret_val)
		{

			case 'S':
				s_flag = true;
				break;

			case 'c':
				c_flag = true;
				break;

			case 'o':
				o_flag = true;
				dest = optarg;
				break;

			case 'h':
				printhelp();
		}
	}
	if(optind < argc)
	{
		optarg = argv[optind++];
		src = optarg;
	}
	
	if(access(src, F_OK) == 0)
	{
		if(dest == false)
		{
			len = strlen(src);
			destt = malloc(len+2);
			strncpy(destt,  src, len);
		}

		if(s_flag == true)
		{
			if(o_flag == true)
			{
				hypens(dest, src);
			}
			else
			{
				*(destt+len-1) = 's';
				hypens(destt, src);
			}
		}

		if(c_flag == true)
		{
			if(o_flag == true)
			{
				hypenc(dest, src);
			}
			else
			{
				*(destt+len-1) = 'o';
				hypenc(destt, src);
			}
		}
		if(argc == 4 && o_flag == true)
		{
		   	nooption(dest, src);	
		}
		
		if(destt != NULL)
		{
			free(destt);
			destt = 0;
		}
	}
	else
	{
		printf("%s: \033[1;31m error: \033[0m %s: No such file of directory\n",  argv[0], argv[1]);
			usageerror();
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

