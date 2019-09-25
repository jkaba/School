#ifndef GRANTFUNDINGTREEMODEL_H
#define GRANTFUNDINGTREEMODEL_H

#include "datamodel/TreeModel.h"

class GrantFundingTreeModel : public TreeModel
{
public:
    GrantFundingTreeModel(RecordsManager*, QObject *parent = 0);
    ~GrantFundingTreeModel();
    void setupModel(int start, int end, std::vector<std::string> sortFields, char filterStart, char filterEnd);
};

#endif // GRANTFUNDINGTREEMODEL_H
