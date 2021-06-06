#include "h2xbase/string/string_util.h"

//#include "h2xbase/time/time.h"
#include <stdarg.h>

#include <qdatetime.h>

namespace h2x {

StringUtil::StringUtil() {

}

StringUtil::~StringUtil() {

}


bool StringUtil::StringPrintf(StringResult<PathChar>& result, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int count_write = _vscprintf(format, ap); //snprintf(NULL, 0, format, ap);
    va_end(ap);
    if (count_write <= 0) {
        return false;
    }

    count_write += sizeof(PathChar);

    std::unique_ptr<PathChar[]> dataPtr(new PathChar[count_write]{ '\0' });
    if (!dataPtr.get()) {
        return false;
    }

    va_start(ap, format);
    int ret = vsprintf_s(dataPtr.get(), count_write, format, ap);
    va_end(ap);

    result.SetData(dataPtr.get(), ret);

    dataPtr.release();
    return true;
}

bool StringUtil::StringPrintfW(StringResult<PathWChar>& result, const wchar_t *format, ...) {

    va_list ap;
    va_start(ap, format);
    int count_write = _vscwprintf(format, ap);
    va_end(ap);
    if (count_write <= 0) {
        return false;
    }

    count_write += sizeof(PathWChar);

    std::unique_ptr<PathWChar[]> dataPtr(new PathWChar[count_write]{ 0 });
    if (!dataPtr.get()) {
        return false;
    }

    va_start(ap, format);
    int ret = vswprintf_s(dataPtr.get(), count_write, format, ap);
    va_end(ap);

    result.SetData(dataPtr.get(), ret);

    dataPtr.release();

    return true;
}

bool StringUtil::GetNowDateString(StringResult<PathChar>& result) {
    QDateTime cdt = QDateTime::currentDateTime();
    QString strCdt = cdt.toString("yyyy-MM-dd");
    if (strCdt.isEmpty()) {
        return false;
    }
    result.SetData(strCdt.toUtf8().data(), strCdt.toUtf8().size());
    return true;
}

bool StringUtil::GetNowDateStringW(StringResult<PathWChar>& result) {
    // QDateTime current_date_time = QDateTime::currentDateTime();
    // QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm::ss.zzz");
    QDateTime cdt = QDateTime::currentDateTime();
    QString strCdt = cdt.toString("yyyy-MM-dd");
    if (strCdt.isEmpty()) {
        return false;
    }
    const wchar_t* wdata = reinterpret_cast<const wchar_t*>(strCdt.utf16());
    size_t wdataSize = wcslen(wdata);
    if (!wdata || !wdataSize) {
        return false;
    }
    result.SetData(wdata, wdataSize);
    return true;
}

bool StringUtil::GetNowDatetimeString(StringResult<PathChar>& result) {
    QDateTime cdt = QDateTime::currentDateTime();
    QString strCdt = cdt.toString("yyyy-MM-dd hh:mm::ss.zzz");
    if (strCdt.isEmpty()) {
        return false;
    }
    result.SetData(strCdt.toUtf8().data(), strCdt.toUtf8().size());
    return true;
}

bool StringUtil::GetNowDatetimeStringW(StringResult<PathWChar>& result) {
    QDateTime cdt = QDateTime::currentDateTime();
    QString strCdt = cdt.toString("yyyy-MM-dd hh:mm::ss.zzz");
    if (strCdt.isEmpty()) {
        return false;
    }
    const wchar_t* wdata = reinterpret_cast<const wchar_t*>(strCdt.utf16());
    size_t wdataSize = wcslen(wdata);
    if (!wdata || !wdataSize) {
        return false;
    }
    result.SetData(wdata, wdataSize);
    return true;
}

bool StringUtil::GetDateLoggerFileNameW(const PathWString& prefix, StringResult<PathWChar>& result) {
    QDateTime cdt = QDateTime::currentDateTime();
    QString strCdt = cdt.toString("yyyy-MM-dd");
    QString strPrefix;
    if (!prefix.empty()) {
        strPrefix = QString::fromWCharArray(prefix.c_str());
    }

    QString strName;

    if (!strPrefix.isEmpty()) {
        strName.append(strCdt);
        strName.append("_");
    }

    strName.append(strCdt);
    strName.append(".log");

    if (strName.isEmpty()) {
        return false;
    }
    const wchar_t* wdata = reinterpret_cast<const wchar_t*>(strName.utf16());
    size_t wdataSize = wcslen(wdata);
    if (!wdata || !wdataSize) {
        return false;
    }
    result.SetData(wdata, wdataSize);
    return true;
}


} // end namespace h2x