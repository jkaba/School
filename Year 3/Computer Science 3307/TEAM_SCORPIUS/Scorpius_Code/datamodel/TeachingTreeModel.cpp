#include "database/RecordsManager.h"
#include "datamodel/TreeItem.h"
#include "datamodel/TeachingTreeModel.h"

TeachingTreeModel::TeachingTreeModel(RecordsManager* db, QObject *parent):
    TreeModel(db, parent) {
}

TeachingTreeModel::~TeachingTreeModel() {
}

void TeachingTreeModel::setupModel(int yearStart, int yearEnd, std::vector<std::string> sortFields, char filterStart, char filterEnd) {
    rootItem = new TreeItem(dataObj->createHeadersListForTeaching(sortFields[0]));
    setupModelData(dataObj->createQStringForTeaching(yearStart, yearEnd, sortFields, filterStart, filterEnd).split(QString("\n")), rootItem);
}

