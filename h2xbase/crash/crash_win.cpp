#include "h2xbase/crash/crash_win.h"

#include "h2xbase/file/file.h"
#include "h2xbase/file/file_path.h"
#include "h2xbase/time/time.h"

#include <assert.h>
#include <minidumpapiset.h>

#pragma comment(lib, "Dbghelp.lib")

namespace h2x {

#ifdef OS_WIN
    
LONG CALLBACK CrashWin::ExceptionHandler(PEXCEPTION_POINTERS exception) {
    // 创建DUMP文件
    // 获取AppData目录

    h2x::PathWChar szAppDataPath[2 * MAX_PATH] = { 0 };
    int appDataPathSize = 0;
    h2x::FilePath::GetAppDataPathW(szAppDataPath, 2 * MAX_PATH, appDataPathSize);

    // 构造并创建日志目录
    h2x::PathWChar szDumpPath[2 * MAX_PATH] = { 0 };
    wsprintf(szDumpPath, L"%s/h2xlog", szAppDataPath);
    h2x::FilePath::CreatePathW(szDumpPath);

    // 文件名
    h2x::Time curTime = h2x::Time::Now();
    h2x::Time::TimeStruct tmStr = curTime.ToTimeStruct(true);
    h2x::PathWChar szFileName[100] = { 0 };
    wsprintf(szFileName, L"dump_%04d_%02d_%02d_%02d_%02d_%02d.dmp", \
        tmStr.year(), tmStr.month(), tmStr.day_of_month(),\
        tmStr.hour(), tmStr.minute(), tmStr.second());

    // 全路径文件名
    h2x::PathWChar szFullFileName[2 * MAX_PATH] = { 0 };
    wsprintf(szFullFileName, L"%s\\%s", szDumpPath, szFileName);

    // 创建dump文件
    HANDLE hFile = h2x::File::OpenFileW(szFullFileName);
    if (hFile != INVALID_HANDLE_VALUE) {

        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = exception;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;

        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
        
        h2x::File::CloseFile(hFile);
        hFile = NULL;
    }

    // 显示信息
    EXCEPTION_RECORD *record = exception->ExceptionRecord;
    //QString errCode(QString::number(record->ExceptionCode, 16));
    //QString errAddr(QString::number((uint)record->ExceptionAddress, 16));
    //QString errFlag(QString::number(record->ExceptionFlags, 16));
    //QString errPara(QString::number(record->NumberParameters, 16));
    //创建消息提示
    //QMessageBox::warning(NULL, "Dump", QString("ErrorCode%1  ErrorAddr：%2  ErrorFlag:%3 ErrorPara:%4").arg(errCode).arg(errAddr).arg(errFlag).arg(errPara),
    //    QMessageBox::Ok);

    return EXCEPTION_EXECUTE_HANDLER;
}

BOOL CrashWin::PreventSetUnhandledExceptionFilter()
{
    HMODULE hKernel32 = LoadLibrary(L"kernel32.dll");

    if (hKernel32 == NULL)
        return FALSE;

    void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");

    if (pOrgEntry == NULL)
        return FALSE;

    unsigned char newJump[100];

    DWORD dwOrgEntryAddr = (DWORD)pOrgEntry;

    dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far 

    void *pNewFunc = &CrashWin::ExceptionFilter;

    DWORD dwNewEntryAddr = (DWORD)pNewFunc;
    DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
    newJump[0] = 0xE9;  // JMP absolute 
    memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));
    SIZE_T bytesWritten;
    BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
    return bRet;
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI CrashWin::ExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
    return NULL;
}

#endif // OS_WIN


 CrashWin::CrashWin(const CrashHandler* handler) : handler_((CrashHandler*)handler), inited_(false), exception_level_(normal){
     assert(handler_);
 }

 CrashWin::~CrashWin() {
     handler_ = NULL;
 }

 bool CrashWin::Regist(const ExceptionLevel& el) {
     exception_level_ = el;

     if (!inited_) {
         // 没有注册，则注册
         LPTOP_LEVEL_EXCEPTION_FILTER lpFilter = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashWin::ExceptionHandler);
         if (lpFilter) {
             // 如果不调用此函数，则不会起作用
             CrashWin::PreventSetUnhandledExceptionFilter();

             inited_ = true;
         }
     }
     return inited_;
 }

} // end namespace h2x