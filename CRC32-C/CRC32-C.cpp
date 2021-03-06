#include <iostream>
#include <string>
#include <cinttypes>

uint32_t rc_crc32(uint32_t crc, const char *buf, const size_t len)
{
	static uint32_t table[256];
	static int have_table = 0;

	/* This check is not thread safe; there is no mutex. */
	if (have_table == 0) {
		/* Calculate CRC table. */
		for (int i = 0; i < 256; ++i) {
			uint32_t rem = i;  /* remainder from polynomial division */
			for (int j = 0; j < 8; ++j) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				}
				else
				{
					rem >>= 1;
				}	
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	const char *q = buf + len;
	for (const char *p = buf; p < q; ++p) {
		const uint8_t octet = *p;  /* Cast to unsigned octet. */
		crc = crc >> 8 ^ table[crc & 0xff ^ octet];
	}
	return ~crc;
}

int main()
{
	std::string s;
	while(std::getline(std::cin,s,'\n'))
	{
		printf("%" PRIX32 "\n", rc_crc32(0, s.c_str(), s.length()));
	}
	return 0;
}