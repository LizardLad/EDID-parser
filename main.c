#include <stdio.h>
#include <stdint.h>
#include "include/edid.h"

void print_three_letter_code(struct edid_data *edid)
{
	char string[4];
	string[3] = '\0';
	string[2] = edid->header_info.man_id.c + 64;
	string[1] = '\0';
	string[1] = ((edid->header_info.man_id.b_part_1 << 3) | (edid->header_info.man_id.b_part_2)) + 64;
	string[0] = edid->header_info.man_id.a + 64;
	printf("[INFO] Monitor Manufacturer: %s\n", string);
}

int main()
{
	struct edid_data data;

	FILE *fp;
	fp = fopen("edid", "r");

	if (!fp)perror("fopen");

	

	if(fread(&data, 128, 1, fp) != 1)
	{
		printf("[ERROR] Failed to read EDID");
	}

	print_three_letter_code(&data);

	uint16_t val = 0;
	val = (data.descriptor_block_space.detailed_timing_descriptor_1.horizontal_active_msbits << 8) | (data.descriptor_block_space.detailed_timing_descriptor_1.horizontal_active_lsbits);

	printf("%u\n", val);

	return 0;
}
