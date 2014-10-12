//
// Copyright (c) 2009, Markus Rickert
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include <rl/math/Rotation.h>
#include <rl/math/Unit.h>
#include <rl/mdl/Kinematic.h>
#include <rl/sg/Body.h>

#include "ConfigurationModel.h"
#include "OperationalModel.h"
#include "MainWindow.h"

OperationalModel::OperationalModel(QObject* parent) :
	QAbstractTableModel(parent),
	id(0)
{
}

OperationalModel::~OperationalModel()
{
}

int
OperationalModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

void
OperationalModel::configurationChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
	this->reset();
}

QVariant
OperationalModel::data(const QModelIndex& index, int role) const
{
	if (NULL == MainWindow::instance()->kinematicModels[this->id])
	{
		return QVariant();
	}
	
	if (!index.isValid())
	{
		return QVariant();
	}
	
	switch (role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
		{
			const rl::math::Transform::ConstTranslationPart& position = MainWindow::instance()->kinematicModels[this->id]->getOperationalPosition(index.row()).translation();
			rl::math::Vector3 orientation = MainWindow::instance()->kinematicModels[this->id]->getOperationalPosition(index.row()).rotation().eulerAngles(2, 1, 0).reverse();
			
			switch (index.column())
			{
			case 0:
				return position.x();
				break;
			case 1:
				return position.y();
				break;
			case 2:
				return position.z();
				break;
			case 3:
				return orientation.x() * rl::math::RAD2DEG;
				break;
			case 4:
				return orientation.y() * rl::math::RAD2DEG;
				break;
			case 5:
				return orientation.z() * rl::math::RAD2DEG;
				break;
			default:
				break;
			}
		}
		break;
	case Qt::TextAlignmentRole:
		return Qt::AlignRight;
		break;
	default:
		break;
	}
	
	return QVariant();
}

Qt::ItemFlags
OperationalModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	
	return QAbstractItemModel::flags(index);
}

QVariant
OperationalModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (NULL == MainWindow::instance()->kinematicModels[this->id])
	{
		return QVariant();
	}
	
	if (Qt::DisplayRole == role && Qt::Horizontal == orientation)
	{
		switch (section)
		{
		case 0:
			return "x";
			break;
		case 1:
			return "y";
			break;
		case 2:
			return "z";
			break;
		case 3:
			return "a";
			break;
		case 4:
			return "b";
			break;
		case 5:
			return "c";
			break;
		default:
			break;
		}
	}
	
	if (Qt::DisplayRole == role && Qt::Vertical == orientation)
	{
		return section;
	}
	
	return QVariant();
}

int
OperationalModel::rowCount(const QModelIndex& parent) const
{
	if (NULL == MainWindow::instance()->kinematicModels[this->id])
	{
		return 0;
	}
	
	return 1;
}

bool
OperationalModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	return false;
}
