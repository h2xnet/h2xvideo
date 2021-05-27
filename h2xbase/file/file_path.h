#ifndef H2XBASE_FILE_FILE_PATH__H
#define H2XBASE_FILE_FILE_PATH__H

#include <string>
#include "build/build_config.h"
#include "../h2x_base_export.h"

#ifdef OS_WIN
#include <shlobj.h>
#endif // OS_WIN


namespace h2x {

#if defined(OS_POSIX)
    typedef std::string PathString;
#elif defined(OS_WIN)
    typedef std::string PathString;
    typedef std::wstring PathWString;
#endif

typedef PathString::value_type PathChar;
typedef PathWString::value_type PathWChar;

/*
 * ClassName: FilePath
 * Desc: �ļ�·��������
 */
class H2XBASE_EXPORT FilePath {
public:
	FilePath();
	virtual ~FilePath();

    /*
     * FunctionName: GetAppDataPathW
     * Description: ��ȡϵͳĬ��AppDataĿ¼
     * Author: zfs
     * Date: 2021-05-16 09:58
     * @dataBuf: �������ݵĻ�����
     * @dataBufSize: ��������С
     * @dataSize: ʵ����Ҫ���ݴ�С�����������Ϊ�գ�Ҳ�᷵����ʵ���ݴ�С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetAppDataPathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FuntionName: CheckFileIsExistW
     * Desc: ����ļ���Ŀ¼�Ƿ����
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @filePath: Ҫ����·��
     * @isDirectory: Ϊtrue���������Ŀ¼������������ļ�
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CheckFileIsExistW(const PathWString& filePath, bool isDirectory);

    /*
     * FuntionName: CreatePathW
     * Desc: ����Ŀ¼������ݹ鴴���������Ҫ�Լ�����ݹ鴴�����⣩
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: Ҫ������Ŀ¼
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CreatePathW(const PathWString& path);
};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE_PATH__H