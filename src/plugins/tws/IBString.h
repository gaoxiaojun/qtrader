/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#ifndef ibstring_h__INCLUDED
#define ibstring_h__INCLUDED

#include <QString>

#include <QString>
typedef QString IBString;

#include <stdlib.h>

inline bool IsEmpty(const IBString& str)
{
	return str.IsEmpty();
}

inline void Empty(IBString& str)
{
    str.clear();
}

inline bool Compare(IBString str, const char* strToCompare)
{
    return str.compare (str, strToCompare, Qt::CaseInsensitive);
}

inline bool Compare(IBString str, IBString strToCompare)
{
    return str.compare (str, strToCompare, Qt::CaseInsensitive);
}

inline double Atof(IBString str)
{
    return str.toDouble();
}

inline int Atoi(IBString str)
{
    return str.toInt ();
}

#endif


