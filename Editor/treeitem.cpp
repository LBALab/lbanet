/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include <QStringList>

#include "treeitem.h"


/***********************************************************
constructor
***********************************************************/
TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent, bool isReadOnly)
: _isReadOnly(isReadOnly)
{
    parentItem = parent;
    itemData = data;
}

/***********************************************************
destructor
***********************************************************/
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

/***********************************************************
appendChild
***********************************************************/
void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

/***********************************************************
child
***********************************************************/
TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

/***********************************************************
childCount
***********************************************************/
int TreeItem::childCount() const
{
    return childItems.count();
}

/***********************************************************
columnCount
***********************************************************/
int TreeItem::columnCount() const
{
    return itemData.count();
}

/***********************************************************
data
***********************************************************/
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

/***********************************************************
parent
***********************************************************/
TreeItem *TreeItem::parent()
{
    return parentItem;
}

/***********************************************************
row
***********************************************************/
int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

/***********************************************************
addChild
***********************************************************/
int TreeItem::addChild(const QVector<QVariant> &data, bool isReadOnly)
{
    TreeItem *item = new TreeItem(data, this, isReadOnly);
    childItems.append(item);
	return childItems.size()-1;
}


/***********************************************************
insertChildren
***********************************************************/
bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}


/***********************************************************
removeChildren
***********************************************************/
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

/***********************************************************
setData
***********************************************************/
bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}



/***********************************************************
clear all children
***********************************************************/
void TreeItem::Clear()
{
	childItems.clear();
}
