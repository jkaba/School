#include "database/RecordsManager.h"
#include "datamodel/TreeItem.h"
#include "datamodel/PublicationTreeModel.h"

PublicationTreeModel::PublicationTreeModel(RecordsManager* db, QObject *parent) :
TreeModel(db, parent) {
}

PublicationTreeModel::~PublicationTreeModel() {
}

void PublicationTreeModel::setupModel(int yearStart, int yearEnd, std::vector<std::string> sortFields, char filterStart, char filterEnd) {
    rootItem = new TreeItem(dataObj->createHeadersListForPubs(sortFields[0]));
    setupModelData(dataObj->createQStringForPubs(yearStart, yearEnd, sortFields, filterStart, filterEnd).split(QString("\n")), rootItem);
}
