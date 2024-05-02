#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jasmine Robbins

#include <QObject>

/// @brief This class generates different truth tables for each level.
class TruthTable : public QObject
{
    Q_OBJECT

public:
    /// @brief Constructor for the circuit truth tables.
    /// @param parent - pointer to the parent object
    TruthTable(QObject *parent = nullptr);

    /// @brief Destructor to clean up resources.
    ~TruthTable();

    /// @brief This method updates the truth table based on the level.
    /// @param level - the level chosen
    void updateTableBasedOnLevel(int level);

    /// @brief Returns the current truth table sequence.
    QVector<bool> getCurrentTable() const;

signals:
    /// @brief Notifies the level screen to update the truth table.
    /// @param header - Displays the boolean equation for the table
    /// @param data - A 2D vector that contains the rows and columns
    /// of the truth table
    void tableUpdated(QString header, const QVector<QVector<QString> > &data);

private:
    /// @brief Stores all information for the current table as a pair.
    /// @returns the all data for current truth table
    /// currentTable.first = the Boolean equation header
    /// currentTable.second = truth table data as a 2D vector
    QPair<QString, QVector<QVector<QString>>> currentTable;

    /// @brief The Boolean equation header for each levels truth table.
    /// Ex: "Truth Table: A + B = Q"
    QString header;

    /// @brief This method holds the truth table for the Level 1.
    ///  This table is AND : A ⋅ B = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel1();

    /// @brief This method holds the truth table for the Level 2.
    ///  This table is OR : A + B = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel2();

    /// @brief This method holds the truth table for the Level 3.
    ///  This table is NOT (inverter) : ¬A = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel3();

    /// @brief This method holds the truth table for the Level 4.
    ///  This table is NAND : ¬A ⋅ ¬B = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel4();

    /// @brief This method holds the truth table for the Level 5.
    ///  This table is NOR : ¬A + ¬B = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel5();

    /// @brief This method holds the truth table for the Level 6.
    ///  This table is XOR : (A ⋅ ¬B) + (¬A ⋅ B ) = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel6();

    /// @brief This method holds the truth table for the Level 7.
    ///  This table is XNOR : (A ⋅ B) + (¬A ⋅ ¬B ) = Q
    /// @returns the header and table as a string, vector pair
    QPair<QString, QVector<QVector<QString>>> tableLevel7();
};

#endif // TRUTHTABLE_H
