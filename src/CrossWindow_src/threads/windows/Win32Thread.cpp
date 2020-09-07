//
// Created by luket on 07/09/2020.
//

#include "Win32Thread.h"
#ifdef LLE_WINDOWS
#include <windows.h>
void Win32Thread::create(void *pVoid)
{

}

void Win32Thread::start()
{

}

void *Win32Thread::join()
{
    return nullptr;
}

typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,PDWORD);

DWORD CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR)*8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest)?1:0);
        bitTest/=2;
    }

    return bitSetCount;
}

void Win32Thread::outputThreadInfo()
{
    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer {};
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI) GetProcAddress(GetModuleHandle("kernel32"),"GetLogicalProcessorInformation");
    if (nullptr == glpi) printf("\nGetLogicalProcessorInformation is not supported.\n");

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);
        if (false == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer) free(buffer);
                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
                if (nullptr == buffer) printf("\nError: Allocation failure\n");
            }
            else printf("\nError %lu\n", GetLastError());
        }
        else done = true;
    }

    ptr = buffer;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
            case RelationNumaNode:
                numaNodeCount++;
                break;
            case RelationProcessorCore:
                processorCoreCount++;
                logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
                break;
            case RelationCache:
                Cache = &ptr->Cache;
                if (Cache->Level == 1) processorL1CacheCount++;
                else if (Cache->Level == 2) processorL2CacheCount++;
                else if (Cache->Level == 3) processorL3CacheCount++;
                break;
            case RelationProcessorPackage:
                // Logical processors share a physical package.
                processorPackageCount++;
                break;
            default:
                printf("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n");
                break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

    printf("\nGetLogicalProcessorInformation results:\n");
    printf("Number of NUMA nodes: %lu\n",numaNodeCount);
    printf("Number of physical processor packages: %lu\n",processorPackageCount);
    printf("Number of processor cores: %lu\n",processorCoreCount);
    printf("Number of logical processors: %lu\n",logicalProcessorCount);
    printf("Number of processor:\n L1 Count: %lu\n L2 Count: %lu\n L3 Count: %lu\n",processorL1CacheCount,processorL2CacheCount,processorL3CacheCount);
    free(buffer);
}
#endif