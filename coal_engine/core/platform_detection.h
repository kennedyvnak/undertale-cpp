#if defined(_WIN32) || defined(_WIN64)
#define ENGINE_PLATFORM_WINDOWS
#else
#error "Non supported platform."
#endif