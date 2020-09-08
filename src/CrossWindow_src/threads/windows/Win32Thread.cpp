//
// Created by luket on 07/09/2020.
//

#include "Win32Thread.h"
#ifdef LLE_WINDOWS
void Win32Thread::create(void *pVoid,void* pParameter)
{
    thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pVoid), pParameter, 0, nullptr);
}

void Win32Thread::start()
{
    ResumeThread(thread);
}

void Win32Thread::pause()
{
    SuspendThread(thread);
}

void Win32Thread::join()
{
    WaitForSingleObject(thread, INFINITE);
}

typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,PDWORD);

DWORD CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR)*8 - 1, bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    for (int i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest)?1:0);
        bitTest/=2;
    }
    return bitSetCount;
}

void Win32Thread::outputThreadInfo()
{
    auto glpi = (LPFN_GLPI) GetProcAddress(GetModuleHandle("kernel32"),"GetLogicalProcessorInformation");
    BOOL done = false;
    PCACHE_DESCRIPTOR Cache;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer {}, ptr;
    DWORD returnLength = 0,logicalProcessorCount = 0,numaNodeCount = 0,processorCoreCount = 0,processorL1CacheCount = 0,
          processorL2CacheCount = 0,processorL3CacheCount = 0,processorPackageCount = 0,byteOffset = 0;

    if (nullptr == glpi) printf("\nGetLogicalProcessorInformation is not supported.\n");

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);
        if (false == rc)
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer) free(buffer);
                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
                if (nullptr == buffer) printf("\nError: Allocation failure\n");
            }
            else printf("\nError %lu\n", GetLastError());
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

void Win32Thread::sleep(int i)
{
    Sleep(i);
}

Win32Thread::~Win32Thread()
{
    TerminateThread(thread,0);
    CloseHandle(thread);
}
#endif