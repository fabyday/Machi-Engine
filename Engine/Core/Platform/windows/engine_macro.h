#ifdef MACHI_BUILD_DLL
	#define MACHI_API  __declspec(dllexport)
#else // MACHI_EXPORT
	#define MACHI_API  __declspec(dllimport)
#endif // MACHI_IMPORT
