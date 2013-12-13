/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#include "backfillrequest.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BackfillRequestPrivate : public QSharedData
{
public:
    inline BackfillRequestPrivate(const Instrument& inst, long barSize, BackfillRequest::RequestDataType type,
                                 const QDateTime& begin, const QDateTime& end) :
        m_instrument(inst), m_barSize(barSize), m_type(type), m_begin(begin), m_end(end)
    {}

    Instrument m_instrument;
    long m_barSize;
    BackfillRequest::RequestDataType m_type;
    QDateTime m_begin;
    QDateTime m_end;
};

} // namespace Internal

BackfillRequest::BackfillRequest(const Instrument& inst,
                                             long barSize, RequestDataType type,
                                             const QDateTime& begin, const QDateTime& end) :
    d(new Internal::BackfillRequestPrivate(inst, barSize, type, begin, end))
{

}

BackfillRequest::BackfillRequest(const BackfillRequest &other) :
    d(other.d)
{
}

BackfillRequest::~BackfillRequest()
{
    d = 0;
}

BackfillRequest& BackfillRequest::operator=(const BackfillRequest &other)
{
    d = other.d;
    return *this;
}

bool BackfillRequest::operator==(const BackfillRequest &other) const
{
    if(d == other.d)
        return true;
    return ((d->m_instrument == other.d->m_instrument) &&
            (d->m_barSize == other.d->m_barSize) &&
            (d->m_type == other.d->m_type) &&
            (d->m_begin == other.d->m_begin) &&
            (d->m_end == other.d->m_end));
}

Instrument BackfillRequest::instrument() const
{
    return d->m_instrument;
}

long BackfillRequest::barSize() const
{
    return d->m_barSize;
}

BackfillRequest::RequestDataType BackfillRequest::type() const
{
    return d->m_type;
}

QDateTime BackfillRequest::begin() const
{
    return d->m_begin;
}

QDateTime BackfillRequest::end() const
{
    return d->m_end;
}

} // namespace OpenTrade
