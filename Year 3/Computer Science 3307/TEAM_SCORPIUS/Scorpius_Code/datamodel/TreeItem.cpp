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
 * A container for items of data supplied by the simple tree model.
 * 
 * CS3307, Team Peach
 */
#include "datamodel/TreeItem.h"

/*
 * Constructs an node in the tree with the given data and a specified parent.
 */
TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) {
    m_parentItem = parent;
    m_itemData = data;
}

/*
 * Destroys the node and its children.
 */
TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}

/*
 * Adds a child to the ndoe.
 */
void TreeItem::appendChild(TreeItem *item) {
    m_childItems.append(item);
}

/*
 * Returns a specific child of the node, specified by its row number.
 */
TreeItem *TreeItem::child(int row) {
    return m_childItems.value(row);
}

/*
 * Returns the number of children this node has.
 */
int TreeItem::childCount() const {
    return m_childItems.count();
}

/*
 * Returns the number of headers in the row.
 */
int TreeItem::columnCount() const {
    return m_itemData.count();
}

/*
 * Returns the value held in the specified column of the node.
 */
QVariant TreeItem::data(int column) const {
    return m_itemData.value(column);
}

/*
 * Returns the parent to this node.
 */
TreeItem *TreeItem::parentItem() {
    return m_parentItem;
}

/*
 * Reports the item's location within its parent's list of items. The root will 
 * return 0.
 */
int TreeItem::row() const {
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*> (this));
    }

    return 0;
}
