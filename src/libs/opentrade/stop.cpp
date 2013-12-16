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
#include "stop.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class StopPrivate : public QSharedData
{
public:
    QDateTime m_completionTime;
    QDateTime m_creationTime;
    double m_fillPrice;
    Instrument m_instrument;
    double m_level;
    StopMode m_mode;
    StopStatus m_status;
    bool m_traceOnBar;
    bool m_traceOnQuote;
    bool m_traceOnTrade;
    StopType m_type;
};

} // namespace Internal

Stop::~Stop()
{

}

Stop& Stop::operator=(const Stop &other)
{
    d = other.d;
    return *this;
}

bool Stop::operator==(const Stop &other) const
{
    if(d == other.d)
      return true;

    return d->m_completionTime == other.d->m_completionTime &&
           d->m_creationTime == other.d->m_creationTime &&
           d->m_fillPrice == other.d->m_fillPrice &&
           d->m_instrument == other.d->m_instrument &&
           d->m_level == other.d->m_level &&
           d->m_mode == other.d->m_mode &&
           d->m_status == other.d->m_status &&
           d->m_traceOnBar == other.d->m_traceOnBar &&
           d->m_traceOnQuote == other.d->m_traceOnQuote &&
           d->m_traceOnTrade == other.d->m_traceOnTrade &&
           d->m_type == other.d->m_type;
}

void Stop::cancel()
{

}

void Stop::disconnect()
{

}

void Stop::setBarFilter(long barSize)
{

}

void Stop::setBarFilter(long barSize, BarType barType)
{

}

QDateTime Stop::completionTime() const
{
    return d->m_completionTime;
}

QDateTime Stop::creationTime() const
{
    return d->m_creationTime;
}

double Stop::fillPrice() const
{
    return d->m_fillPrice;
}

Instrument Stop::instrument() const
{
    return d->m_instrument;
}

double Stop::level() const
{
    return d->m_level;
}

StopMode Stop::mode() const
{
    return d->m_mode;
}

StopStatus Stop::status() const
{
    return d->m_status;
}

bool Stop::traceOnBar() const
{
    return d->m_traceOnBar;
}

void Stop::setTraceOnBar(const bool& traceonbar)
{
    d->m_traceOnBar = traceonbar;
}

bool Stop::traceOnQuote() const
{
    return d->m_traceOnQuote;
}

void Stop::setTraceOnQuote(const bool& traceonquote)
{
    d->m_traceOnQuote = traceonquote;
}

bool Stop::traceOnTrade() const
{
    return d->m_traceOnTrade;
}

void Stop::setTraceOnTrade(const bool& traceontrade)
{
    d->m_traceOnTrade = traceontrade;
}

StopType Stop::type() const
{
    return d->m_type;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Stop &stop)
{
    c.nospace() << "Stop("
                << "CompletionTime:" << stop.completionTime() 
                << "CreationTime:" << stop.creationTime() 
                << "FillPrice:" << stop.fillPrice() 
                << "Instrument:" << stop.instrument() 
                << "Level:" << stop.level() 
                << "Mode:" << stop.mode() 
                << "Status:" << stop.status() 
                << "TraceOnBar:" << stop.traceOnBar() 
                << "TraceOnQuote:" << stop.traceOnQuote() 
                << "TraceOnTrade:" << stop.traceOnTrade() 
                << "Type:" << stop.type() 
                <<')';
    return c.space();
}
