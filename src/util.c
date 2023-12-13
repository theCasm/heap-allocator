#include <stdint.h>
#include <stddef.h>

size_t hash(void*);

// CRC32 with table lookup - check wikipedia on computation of CRC
size_t hash(void *addr) {
	unsigned int i, j;
	uint32_t crc, mask, byte, data;
	static unsigned int table[256];

	data = (uint32_t)((uintptr_t)addr & 0xFFFFFFFF);

	// set up table
	if (table[1] == 0) {
		table[0] = 0;
		for (i = 1; i < 256; i <<= 1) {
			crc = i;
			for (j = 8; j > 0; --j) {
				mask = -(crc & 1);
				crc = (crc >> 1) ^ (0xEDB88320 & mask);
			}

			// CRC(a ^ b) = CRC(a) ^ CRC(b)
			for (j = 0; j < i; ++j) {
				table[i ^ j] = crc ^ table[j];
			}
		}
	}

	// now just calculate
	crc = 0xFFFFFFFF;
	for (; (byte = data & 0xFF) != 0; data >>= 8) {
		crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
	}
	return crc ^ 0xFFFFFFFFu;
}
