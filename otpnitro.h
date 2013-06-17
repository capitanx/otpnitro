#define VERSION		0.1
#define SPACING		5
#define MAX_PAGES	1000		// 1000 pages
#define MAX_CHARS	204 * SPACING	// 1020 bytes  - 204
#define OWNER		"CMC"

#ifdef WIN32
# define REL_PATH	"PAGES/"
#else
# define REL_PATH	"/usr/share/PAGES/"
#endif

// Change the MAGIC_K value for a rand value.
#define	MAGIC_K		-1946120572;
