#include "test.h"

test::test(QObject *parent) :
    QObject(parent)
{
    count = 0;
}

void test::addCount(void)
{
    count++;
    emit countAdded(count);
}
