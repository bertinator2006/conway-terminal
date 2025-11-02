#ifdef _WIN32
#include <windows.h>
#define SLEEP_FUNCTION(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_FUNCTION(ms) usleep(ms * 1000) // usleep takes microseconds
#endif

void wait(unsigned int milliseconds) {
    SLEEP_FUNCTION(milliseconds);
}