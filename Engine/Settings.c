#include "Settings.h"

const char* GetBaseCPFolderPath()
{

    if (!baseCPFullPath) {
        const char* directoryPath = SDL_GetBasePath();

        if (!directoryPath)
        {
            SDL_free((void*)directoryPath);
            DEBUG_LOG("SDL_GetBasePath() returns NULL: %s", SDL_GetError());
            return "";
        }

        size_t length = SDL_strlen(directoryPath) + SDL_strlen(baseCPFolderPath) + 1;
        char* fullPath = (char*)malloc(length);

        if (!fullPath) {
            SDL_free((void*)directoryPath);
            DEBUG_LOG("malloc failed in GetBaseCPFolderPath");
            return "";
        }

        SDL_strlcpy(fullPath, directoryPath, length);
        SDL_strlcat(fullPath, baseCPFolderPath, length);
        SDL_free((void*)directoryPath);

        baseCPFullPath = fullPath;
        baseCPFullPathSize = SDL_strlen(baseCPFullPath);
    }
    return baseCPFullPath;
}

const char* GetAssetPath(const char* assetPath)
{
    if (baseCPFullPathSize == 0)
    {
        GetBaseCPFolderPath();
    }
    size_t length = baseCPFullPathSize + SDL_strlen(assetPath) + 1;
    char* fullAssetPath = malloc(length);

    if (!fullAssetPath) {
        DEBUG_LOG("malloc failed in GetAssetPath");
        return "";
    }

    SDL_strlcpy(fullAssetPath, GetBaseCPFolderPath(), length);
    SDL_strlcat(fullAssetPath, assetPath, length);
    return fullAssetPath;
}