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
#include <QtGui>

#include "treeitem.h"
#include "treemodel.h"




/***********************************************************
constructor
***********************************************************/
TreeModel::TreeModel(const QVector<QVariant> &header, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem(header);
}

/***********************************************************
destructor
***********************************************************/
TreeModel::~TreeModel()
{
    delete rootItem;
}

/***********************************************************
columnCount
***********************************************************/
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

/***********************************************************
data
***********************************************************/
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole && role == Qt::EditRole)
	{
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

		return item->data(index.column());
	}

	if(role == Qt::ToolTipRole)
	{
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

		return item->tooltip(index.column());
	}

    return QVariant();
}

/***********************************************************
flags
***********************************************************/
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

	if(index.column() > 0)
	{
		if(IsReadOnly(index))
			return QAbstractItemModel::flags(index);
		else
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
	else
		return QAbstractItemModel::flags(index);
}

/***********************************************************
headerData
***********************************************************/
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


/***********************************************************
index
***********************************************************/
QModelIndex TreeModel::GetIndex(int column, int row, const QModelIndex &parent) const
{
	return index(row, column, parent);
}


/***********************************************************
index
***********************************************************/
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

/***********************************************************
parent
***********************************************************/
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

/***********************************************************
rowCount
***********************************************************/
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}



/***********************************************************
insert row in a model
***********************************************************/
bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}



/***********************************************************
remove row in a model
***********************************************************/
bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}


/***********************************************************
set model data
***********************************************************/
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}


/***********************************************************
set model tooltip
***********************************************************/
bool TreeModel::setTooltip(const QModelIndex &index, const QVariant &value)
{  
	TreeItem *item = getItem(index);
	if(item)
		return item->setTooltip(index.column(), value);

	return false;
}




/***********************************************************
get item
***********************************************************/
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) 
	{
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) 
			return item;
    }
    return rootItem;
}



/***********************************************************
clear the tree content
***********************************************************/
void TreeModel::Clear(const QModelIndex &index)
{
    TreeItem *it = getItem(index);
    beginRemoveRows(index, 0, it->childCount());
	it->Clear();
    endRemoveRows();
}

/***********************************************************
add a row
***********************************************************/
QModelIndex TreeModel::AppendRow(const QVector<QVariant> &data, const QModelIndex &parent, bool isReadOnly)
{
    TreeItem *parentItem = getItem(parent);
    beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
    int row = parentItem->addChild(data, isReadOnly);
    endInsertRows();

	return index(row, 0, parent);
}


/***********************************************************
check if given index is read only
***********************************************************/
bool TreeModel::IsReadOnly(const QModelIndex &index) const
{
    TreeItem *it = getItem(index);
	if(it)
		return it->IsReadOnly();

	return true;
}