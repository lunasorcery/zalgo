#include <cstdio>
#include <cstdint>
#include <getopt.h>
#include <vector>

bool g_hasSetFlags = false;
bool g_fuckUpGoingUp = false;
bool g_fuckUpTheMiddle = false;
bool g_fuckUpGoingDown = false;

int g_strength = 0;

const std::vector<uint32_t> zalgo_up = {
	0x030d, 0x030e, 0x0304, 0x0305,
	0x033f, 0x0311, 0x0306, 0x0310,
	0x0352, 0x0357, 0x0351, 0x0307,
	0x0308, 0x030a, 0x0342, 0x0343,
	0x0344, 0x034a, 0x034b, 0x034c,
	0x0303, 0x0302, 0x030c, 0x0350,
	0x0300, 0x0301, 0x030b, 0x030f,
	0x0312, 0x0313, 0x0314, 0x033d,
	0x0309, 0x0363, 0x0364, 0x0365,
	0x0366, 0x0367, 0x0368, 0x0369,
	0x036a, 0x036b, 0x036c, 0x036d,
	0x036e, 0x036f, 0x033e, 0x035b,
	0x0346, 0x031a
};

const std::vector<uint32_t> zalgo_down = {
	0x0316, 0x0317, 0x0318, 0x0319,
	0x031c, 0x031d, 0x031e, 0x031f,
	0x0320, 0x0324, 0x0325, 0x0326,
	0x0329, 0x032a, 0x032b, 0x032c,
	0x032d, 0x032e, 0x032f, 0x0330,
	0x0331, 0x0332, 0x0333, 0x0339,
	0x033a, 0x033b, 0x033c, 0x0345,
	0x0347, 0x0348, 0x0349, 0x034d,
	0x034e, 0x0353, 0x0354, 0x0355,
	0x0356, 0x0359, 0x035a, 0x0323
};

const std::vector<uint32_t> zalgo_mid = {
	0x0315, 0x031b, 0x0340, 0x0341,
	0x0358, 0x0321, 0x0322, 0x0327,
	0x0328, 0x0334, 0x0335, 0x0336,
	0x034f, 0x035c, 0x035d, 0x035e,
	0x035f, 0x0360, 0x0362, 0x0338,
	0x0337, 0x0361,
	//0x0489, // adds sideways padding in macOS terminal for some reason
};

void printRandZalgo(const std::vector<uint32_t>& arr)
{
	const uint32_t value = arr[rand() % arr.size()];

	const char buffer[3] = {
		(char)(0xc0 | ((value >> 6) & 0x1f)),
		(char)(0x80 | (value & 0x3f)),
		(char)0x00
	};

	fputs(buffer, stdout);
}

void parseCommandLine(int argc, char** argv)
{
	while (1) {
		static struct option long_options[] = {
			{ "up",       no_argument,       0, 'u' },
			{ "middle",   no_argument,       0, 'm' },
			{ "down",     no_argument,       0, 'd' },
			{ "strength", required_argument, 0, 's' },
			{ 0, 0, 0, 0 }
		};

		int option_index = 0;
		const int c = getopt_long(argc, argv, "umds:", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 'u': { g_fuckUpGoingUp   = true; g_hasSetFlags = true; break; }
			case 'm': { g_fuckUpTheMiddle = true; g_hasSetFlags = true; break; }
			case 'd': { g_fuckUpGoingDown = true; g_hasSetFlags = true; break; }
			case 's': {
				g_strength = std::max(std::min(atoi(optarg), 3), 1);
				g_hasSetFlags = true;
				break;
			}
		}
	}

	// default options
	if (!g_hasSetFlags)
	{
		g_fuckUpGoingUp = false;
		g_fuckUpTheMiddle = true;
		g_fuckUpGoingDown = true;
		g_strength = 1;
	}
}

int main(int argc, char** argv)
{
	parseCommandLine(argc, argv);

	int c;
	bool isInEscapeCode = false;
	while ((c = getchar()) > 0)
	{
		putc((char)c, stdout);

		if (c == 0x1B && !isInEscapeCode)
		{
			isInEscapeCode = true;
			continue;
		}
		else if (isInEscapeCode && c >= 0x40 && c <= 0x7e)
		{
			isInEscapeCode = false;
			continue;
		}

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			int num_up = 0;
			int num_mid = 0;
			int num_down = 0;

			if (g_strength == 1)
			{
				num_up = (rand() % 8);
				num_mid = (rand() % 2);
				num_down = (rand() % 8);
			}
			else if (g_strength == 2)
			{
				num_up = (rand() % 8) + 1;
				num_mid = (rand() % 3);
				num_down = (rand() % 8) + 1;
			}
			else if (g_strength == 3)
			{
				num_up = (rand() % 16) + 3;
				num_mid = (rand() % 4) + 1;
				num_down = (rand() % 16) + 3;
			}

			if (g_fuckUpGoingUp)
				for (int j = 0; j < num_up; j++)
					printRandZalgo(zalgo_up);

			if (g_fuckUpTheMiddle)
				for (int j = 0; j < num_mid; j++)
					printRandZalgo(zalgo_mid);

			if (g_fuckUpGoingDown)
				for (int j = 0; j < num_down; j++)
					printRandZalgo(zalgo_down);
		}
	}
	return 0;
}
