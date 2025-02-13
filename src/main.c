#include <stdio.h>
#include <dna.h>
#include "Demo.h"
#include "cfw.h"

int main(int argc, char *argv[])
{

	CFRefPool *pool = cfw_new(cfw_refpool);

	Demo *demo = NewDemo("Demo", 720, 480);

	Run(demo);

	cfw_unref(pool);

	return 0;
}

