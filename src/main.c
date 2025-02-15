#include <stdio.h>
#include <dna.h>
#include "Demo.h"

int main(int argc, char *argv[])
{

	CFRefPoolRef pool = CFNew(CFRefPool);

	DemoRef demo = NewDemo("Demo", 720, 480);

	Run(demo);

	CFUnref(pool);

	return 0;
}

