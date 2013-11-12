#include "invindex.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;


int main(int argc, char ** argv)
{
	char inputfile[100];
	char outputfile[100];
	int iflag=0;
	int oflag=0;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "i:o:")) != -1)
	{
		switch (c)
		{
			case 'i':
				strcpy(inputfile, optarg);
				iflag=1;
				break;
			case 'o':
				strcpy(outputfile, optarg);
				oflag=1;
				break;
			default:
				fprintf (stderr, "error: parsing command line parameters\n");
				abort ();
		}
	}

	if (iflag==0){
		fprintf (stderr, "program needs input file name\n");
		abort ();
	}

	if (oflag==0){
		fprintf (stderr, "program needs output file name\n");
		abort ();
	}

	InvIndex inv;
	inv.build_index(inputfile);
	inv.save_print_index(outputfile);

	return 0;
}
