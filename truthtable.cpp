#include "truthtable.h"
#include <QPair>

TruthTable::TruthTable(QObject *parent) : QObject(parent), currentTable(){}

TruthTable::~TruthTable() {}

void TruthTable::updateTableBasedOnLevel(int level)
{
    switch (level)
    {
    case 1:
        currentTable = tableLevel1();
        break;
    case 2:
        currentTable = tableLevel2();
        break;
    case 3:
        currentTable = tableLevel3();
        break;
    case 4:
        currentTable = tableLevel4();
        break;
    case 5:
        currentTable = tableLevel5();
        break;
    case 6:
        currentTable = tableLevel6();
        break;
    case 7:
        currentTable = tableLevel7();
        break;
    }

    emit tableUpdated(currentTable.first, currentTable.second);
}

QVector<bool> TruthTable::getCurrentTable() const
{
    // Convert to a bool of vectors to compare with circuit
    QVector<bool> results;
    for (const auto& row : currentTable.second)
    {
        results.push_back(row.last() == "1");
    }
    return results;
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel1()
{
    header = "Truth Table: A ⋅ B = Q";
    QVector<QVector<QString>> andTable{
      { "0", "0", "0" }
    , { "0", "1", "0" }
    , { "1", "0", "0" }
    , { "1", "1", "1" }
    };
    return qMakePair(header, andTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel2()
{
    header = "Truth Table: A + B = Q";
    QVector<QVector<QString>> orTable{
      { "0", "0", "0" }
    , { "0", "1", "1" }
    , { "1", "0", "1" }
    , { "1", "1", "1" }
    };
    return qMakePair(header, orTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel3()
{
    header ="Truth Table: ¬A = Q";
    QVector<QVector<QString>> notTable{
      { "0", "-", "1" }
    , { "1", "-", "0" }
    , { "-", "-", "-" }
    , { "-", "-", "-" }
    };
    return  qMakePair(header, notTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel4()
{
    header = "Truth Table: ¬(A ⋅ B) = Q";
    QVector<QVector<QString>> nandTable{
      {"0", "0", "1"}
    , {"0", "1", "1"}
    , {"1", "0", "1"}
    , {"1", "1", "0"}
    };
    return  qMakePair(header, nandTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel5()
{
    header = "Truth Table: ¬(A + B) = Q";
    QVector<QVector<QString>> norTable{
      {"0", "0", "1"}
    , {"0", "1", "0"}
    , {"1", "0", "0"}
    , {"1", "1", "0"}
    };
    return  qMakePair(header, norTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel6()
{
    header = "Truth Table: (A ⋅ ¬B) + (¬A ⋅ B ) = Q";
    QVector<QVector<QString>> xorTable{
      {"0", "0", "0"}
    , {"0", "1", "1"}
    , {"1", "0", "1"}
    , {"1", "1", "0"}
    };
    return  qMakePair(header, xorTable);
}

QPair<QString, QVector<QVector<QString> > > TruthTable::tableLevel7()
{
    header = "Truth Table: (A ⋅ B) + (¬A ⋅ ¬B ) = Q";
    QVector<QVector<QString>> xnorTable{
      {"0", "0", "1"}
    , {"0", "1", "0"}
    , {"1", "0", "0"}
    , {"1", "1", "1"}
    };
    return  qMakePair(header, xnorTable);
}
