// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
//
// DustRAC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// DustRAC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DustRAC. If not, see <http://www.gnu.org/licenses/>.

#ifndef MWSELECTOR_H
#define MWSELECTOR_H

#include "mwwidget.h"

//! Base class for selector widgets.
class MWSelector : public MWWidget
{
    Q_OBJECT

public:

    //! Constructor
    MWSelector(QSizeF size, MWWidget * parent = nullptr);

protected:

    //! \reimp
    virtual void paint(QPainter * painter,
                       const QStyleOptionGraphicsItem * option, QWidget * widget);

    virtual void paintArrows(QPainter * painter);

    //! \reimp
    virtual void paintBackground(QPainter * painter);

    //! \reimp
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

    //! \reimp
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

signals:

    void prevClicked();
    void nextClicked();

private:

    Q_DISABLE_COPY(MWSelector)

    bool m_nextPressing;
    bool m_prevPressing;
};

#endif // MWSELECTOR_H