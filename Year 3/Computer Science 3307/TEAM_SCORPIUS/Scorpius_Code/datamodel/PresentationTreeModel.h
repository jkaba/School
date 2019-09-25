#ifndef PRESENTATIONTREEMODEL_H
#define PRESENTATIONTREEMODEL_H

#include "datamodel/TreeModel.h"

class PresentationTreeModel : public TreeModel
{
public:
    PresentationTreeModel(RecordsManager*, QObject *parent = 0);
    ~PresentationTreeModel();
    void setupModel(int start, int end, std::vector<std::string> sortFields, char filterStart, char filterEnd);
};

#endif // PRESENTATIONTREEMODEL_H
