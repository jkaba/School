/****************************************************************************
 **
 ** Copyright (C) 2015 The Qt Company Ltd.
 ** Contact: http://www.qt.io/licensing/
 **
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of The Qt Company Ltd nor the names of its
 **     contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 ****************************************************************************/

/* 
 * Provides a simple tree model to show how to create and use hierarchical
 * models.
 * 
 * CS3307, Team Peach
 */
#include "database/RecordsManager.h"
#include "datamodel/TreeItem.h"
#include "datamodel/TreeModel.h"

/*
 * Constructs the tree, given the data that's to be in it. You cannot edit the
 * data once the model is constructed.
 */
TreeModel::TreeModel(RecordsManager* db, QObject *parent) : QAbstractItemModel(parent) {
    dataObj = db;
}

/*
 * Destroys the root item and all of its descendants.
 */
TreeModel::~TreeModel() {
    delete rootItem;
}

/*
 * Returns the number of columns (headers) this node has.
 */
int TreeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return static_cast<TreeItem*> (parent.internalPointer())->columnCount();
    } else {
        return rootItem->columnCount();
    }
}

/*
 * Retrieves the data at the given index.
 */
QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    TreeItem *item = static_cast<TreeItem*> (index.internalPointer());

    return item->data(index.column());
}

/*
 * Returns a flag ensuring the model is read-only.
 */
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

/*
 * Returns the header information that's stored in the root.
 */
QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return rootItem->data(section);
    }

    return QVariant();
}

/*
 * Returns a compatible index for the view model to the given node.
 */
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!parent.isValid()) {
        parentItem = rootItem;
    } else {
        parentItem = static_cast<TreeItem*> (parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

/*
 * Return the index to the parent to the node at the given index.
 */
QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*> (index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

/*
 * Returns the number of rows this node has.
 */
int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if (parent.column() > 0) {
        return 0;
    }

    if (!parent.isValid()) {
        parentItem = rootItem;
    } else {
        parentItem = static_cast<TreeItem*> (parent.internalPointer());
    }

    return parentItem->childCount();
}

bool TreeModel::checkIfNumber(const std::string &s) {
    if(s.back() == '.') {
        return false;
    }

    if (std::string::npos != s.find_first_of("0123456789.")) {
        return true;
    }

    return false;
}

/*
 * Sets up the initial data in the model. 
 */
void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent) {
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ") {
                break;
            }
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);


            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); column++) {
                std::string s = columnStrings[column].toUtf8().constData();
                if(checkIfNumber(s)) {
                    try {
                    columnData << std::stod(s);
                    }
                    catch (const std::invalid_argument& e)
                    {
                       columnData << columnStrings[column];
                    }
                }

                else{
                    columnData << columnStrings[column];
                }
            }

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount() - 1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }

        number++;
    }
}
