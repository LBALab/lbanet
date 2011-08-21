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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <boost/shared_ptr.hpp>

class TreeItem;
class CustomStringListModel;



class FileDialogOptionsBase
{
public:
	QString Title;
	QString FileFilter;
	QString StartingDirectory;
	QString PreviousFile;


	virtual QString PostManagement(const QString & selectedfile) = 0;
};


class FileDialogOptionsModel : public FileDialogOptionsBase
{
public:

	virtual QString PostManagement(const QString & selectedfile);
};

class FileDialogOptionsIcon : public FileDialogOptionsBase
{
public:
	QString OutDirectory;

	virtual QString PostManagement(const QString & selectedfile);
};



//*************************************************************************************************
//*                               class TreeModel
//*************************************************************************************************
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
	//! constructor
    TreeModel(const QVector<QVariant> &header, QObject *parent = 0);

	//! destructor
    ~TreeModel();

	//! get model data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	//! get flags
    Qt::ItemFlags flags(const QModelIndex &index) const;

	//! get header data
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

	//! get index
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;

	//! get parent index
    QModelIndex parent(const QModelIndex &index) const;

	//! get nb row
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

	//! get nb collumns
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	//! insert row in a model
	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	//! remove row in a model
	bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	//! set model data
    bool setData(const QModelIndex &index, const QVariant &value,
					int role = Qt::EditRole);


	//! set model tooltip
    bool setTooltip(const QModelIndex &index, const QVariant &value);

	bool SetCustomIndex(QModelIndex index, boost::shared_ptr<CustomStringListModel> list);

	//! used in the case of file dialog
	bool SetCustomIndex(QModelIndex index, boost::shared_ptr<FileDialogOptionsBase> filefilter);

	//! use in case of number list
	bool SetCustomIndex(QModelIndex index, boost::shared_ptr<int> list);

	//! clear the tree content
	void Clear(const QModelIndex &index = QModelIndex());

	//! add a row
	QModelIndex AppendRow(const QVector<QVariant> &data, const QModelIndex &parent = QModelIndex(), 
						bool isReadOnly = false);

	//! get index
    QModelIndex GetIndex(int column, int row, const QModelIndex &parent = QModelIndex()) const;

	//! check if given index is read only
	bool IsReadOnly(const QModelIndex &index) const;


	//! accessor
    boost::shared_ptr<CustomStringListModel> CustomIndex(const QModelIndex &index) const;
    boost::shared_ptr<FileDialogOptionsBase> CustomIndexFile(const QModelIndex &index) const;
    boost::shared_ptr<int> CustomIndexNumber(const QModelIndex &index) const;


	void SetCustomFileDialog(const QModelIndex &index, const std::string & title, 
								const std::string & directory, const std::string & ffilter);

	void SetWorldName(const std::string & worldname);

private:
	//! get item
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *rootItem;

	std::string _Worldname;
};


#endif
