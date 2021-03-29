#include <stdio.h>
#include <pciaccess.h>

int main(int arc, char *argv[])
{
	struct pci_device *info = NULL;
	struct pci_device_iterator *iter;

	pci_system_init();
	iter = pci_slot_match_iterator_create(NULL);
	while ((info = pci_device_next(iter)) != NULL) {
		printf("domain_16=%s, bus=%0x, dev=%0x, func=%0x\n", info->domain_16, info->bus, info->dev, info->func);
		printf("irq=%0x\n", info->irq);
		printf("-----------------------\n");
	}
	printf("Hello the world\n");
	return 0;
}