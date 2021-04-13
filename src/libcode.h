/*
 * only interface is through the GetLibCodeAPI();
 */

#if defined(_WIN64)
#define DLL_NAME "app.dll"
#define TEMP_DLL_NAME "app_temp.dll"
#endif
#if defined(__linux__)
#define DLL_NAME "app.so"
#define TEMP_DLL_NAME "app_temp.so"
#endif

typedef void (*PrintMessage_fnc)(const char* msg);

typedef struct LibCodeFncTable_t {
    PrintMessage_fnc    PrintMessage;
    // add other function pointers here
} LibCodeFncTable;
