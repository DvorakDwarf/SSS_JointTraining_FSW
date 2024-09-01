#include <print_scan.h>
#include "platform_init.h"

#include <TestDefinition.h>

void my_main();

int main() {
    init_init();
    init_platform();

    my_main();
}


void my_main() {
	while (1) {
		printMsg("Hello There!\r\n");
		nop(1000000);
	}
}
