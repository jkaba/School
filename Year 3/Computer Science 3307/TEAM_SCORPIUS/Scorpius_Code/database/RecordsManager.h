/**
 * It's a class that manages records. No, but seriously, this class stores the
 * individual records of an Excel spreadsheet obtained from Acuity STAR for
 * processing and analysis.
 *
 * CS3307, Team Peach
 */
#ifndef RECORDSMANAGER_H
#define	RECORDSMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <QLocale>
#include <QModelIndex>
#include <QString>
#include <QVariant>

#include "datamodel/TreeModel.h"

typedef std::vector<std::string> BasicRecord;
typedef std::multimap<int, BasicRecord*> Manager;
typedef std::multimap<std::string, BasicRecord*> StringTree;

class RecordsManager {
public:
    RecordsManager(BasicRecord* _headers);
    ~RecordsManager();

    void addRecord(int key, BasicRecord* record);
    std::vector<BasicRecord*> findRecord(int year);
    std::vector<BasicRecord*> findRecordsInRange(int startYear, int endYear);
    BasicRecord getHeaders();
    int getHeaderIndex(std::string headerTitle);

    static std::vector<std::string> list(int n, ...);

    QString createQStringForGrants(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd);
    QList<QVariant> createHeadersListForGrants(std::string topLevel);
    QString createQStringForPres(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd);
    QList<QVariant> createHeadersListForPres(std::string topLevel);
    QString createQStringForPubs(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd);
    QList<QVariant> createHeadersListForPubs(std::string topLevel);
    QString createQStringForTeaching(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd);
    QList<QVariant> createHeadersListForTeaching(std::string topLevel);

    std::vector<std::pair<std::string, int>> getCountByName(int startYear, int endYear, char filterStart, char filterEnd);
    std::vector<std::pair<std::string, int>> getCountTuple(int startYear, int endYear,
            const std::vector<std::string> &headers, const std::vector<std::string> &matchString, char filterStart, char filterEnd);
    std::vector<std::pair<std::string, double>> getTotalsTuple(int startYear, int endYear,
            const std::vector<std::string> &headers, const std::vector<std::string> &matchStrings, std::string accCol, char filterStart, char filterEnd);

private:
    Manager manager;
    BasicRecord headers;
    QLocale locale;

    double parseStringToDouble(std::string);
    std::string removeTrailingZeros(double d);
    std::string analyze(
            int startYear,
            int endYear,
            const std::vector<std::string> &sortFields,
            std::string countCol,
            char filterStart,
            char filterEnd);
    std::string analyze(
            int startYear,
            int endYear,
            const std::vector<std::string> &sortFields,
            const std::vector<std::string> &accs,
            int currencyMask,
            std::string countCol,
            char filterStart,
            char filterEnd);
    std::string analyze(StringTree sortedTree,
            const std::vector<int> &sortFields,
            const std::vector<int> &accs,
            std::vector<double> &accsTotals,
            int currencyMask,
            int countCol,
            int* currCount,
            int depth);
};

#endif	/* RECORDSMANAGER_H */
