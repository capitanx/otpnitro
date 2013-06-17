#define VERSION		0.1
#define SPACING		5
#define MAX_PAGES	1000
#define MAX_CHARS	204 * SPACING	// 1020 bytes
#define OWNER		"CMC"

#ifdef WIN32
# define REL_PATH	"PAGES/"
#else
# define REL_PATH	"/usr/share/PAGES/"
#endif
