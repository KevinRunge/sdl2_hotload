#include "libcode.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "SDL.h"

void* dllHandle = nullptr;
// global funtion table
static LibCodeFncTable libCode;
// Handshake API function pointer
void (*GetLibCodeAPI)(LibCodeFncTable *libCode);

// "platform independent" stat function hack
#if defined(_WIN64)
    #define stat _stat
#endif

/*
 * Source of this copy function based on SDL2 file io: 
 * https://gist.github.com/ChrisDill/291c938605c200d079a88d0a7855f31a
 * Thanks :)
 */
void CopyFile(const char* source_dll_name, const char* temp_dll_name)
{
    SDL_RWops *source = SDL_RWFromFile(source_dll_name, "r");
    SDL_RWops *target = SDL_RWFromFile(temp_dll_name, "w");

    Sint64 size = SDL_RWsize(source);

    void * buffer = SDL_calloc(1, size);
    SDL_RWread(source, buffer, size, 1);

    SDL_RWwrite(target, buffer, size, 1);

    SDL_RWclose(source);
    SDL_RWclose(target);
    SDL_free(buffer);
}

bool IsFileModified()
{
    static int last_modified; // static var used for example purpose only
    struct stat buffer;
    
    int result = stat(DLL_NAME, &buffer);
    if (result != 0)
    {
        // error - DLL gone???
        // TODO: proper error handling here
        return false;
    }
    else 
    {
        int time_stamp = buffer.st_mtime;
        // printf("Time Last modified = %d\n", time_stamp);
        if (time_stamp != last_modified)
        {
            last_modified = time_stamp;
            return true;
        }
        else 
        {
            return false;
        }
    }
}

void LoadCode() 
{
    const char* funcName = "GetLibCodeAPI";
    
    CopyFile(DLL_NAME, TEMP_DLL_NAME);

    dllHandle = SDL_LoadObject(TEMP_DLL_NAME);
    if(dllHandle)
    {
        // load API function
        GetLibCodeAPI = (void (*)(LibCodeFncTable*)) SDL_LoadFunction(dllHandle, funcName);
        if (GetLibCodeAPI)
        {
            GetLibCodeAPI(&libCode);
        }
        else
        {
            printf("Could not load GetLibAPI()\n");
        }
    }
    else
    {
        printf("ERROR: could not open dll\n");
    }
}

void UnloadCode() 
{
    if(dllHandle)
    {
        SDL_UnloadObject(dllHandle);
        dllHandle = nullptr;
        // TODO: clean up function table!!!
    }
}

int main(int argc, char *argv[])
{
    printf("DLL Hotload\n");
    
    // infinite loop - use ctrl-c to exit
    while (1) {
        // dll hot reload
        if(IsFileModified())
        {
            UnloadCode();
            LoadCode();
        }
        
        libCode.PrintMessage("Hello DLL\n");
        SDL_Delay(1000);

    }
    
    return 0;
}
