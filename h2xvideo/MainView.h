#ifndef H2XVIDEO_MAIN_VIEW__H
#define H2XVIDEO_MAIN_VIEW__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <qstring.h>
#include <QtQml>

class MainView : public QObject, public h2x::View {
    Q_OBJECT
public:
    // �Ե����ķ�ʽ�ṩ��QMLʹ��
    static MainView* qmlAttachedProperties(QObject *object);

    explicit MainView(QObject* parent = nullptr);
    virtual ~MainView();

public:
    /*
     * FunctionName: routerPageSet
     * Desc: ����·��ҳ��
     */
    Q_INVOKABLE void routerPageSet(QString pageName, QString pageParam = QString(""));

public Q_SLOTS:
    // 

Q_SIGNALS:
    // �ź��б�
    /*
     * FunctionName: routerPageChanged
     * Desc: ·��ҳ�淢���ı�
     * Author: zfs
     * Date: 2021-06-12 22:35
     * @pageName: ҳ������
     * @pageParam: ҳ�����������Ϊ�գ�
     */
    void routerPageChanged(QString pageName, QString pageParam = QString(""));

private:
};

#endif // !H2XVIDEO_MAIN_VIEW__H
