fndef TEST_H
#define TEST_H

#include <QObject>

class test : public QObject
{
    Q_OBJECT

    double count;
public:
    explicit test(QObject *parent = 0);

signals:
    void countAdded(double);

public slots:
    void addCount(void);
};

#endif // TEST_H
