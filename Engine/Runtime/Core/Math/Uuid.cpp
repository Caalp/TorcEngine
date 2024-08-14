#include "Uuid.h"

namespace Torc
{
    Uuid::Uuid(const TorcStd::string& uuidStr)
    {
    }

    TorcStd::string Uuid::ToString() const
    {
        return TorcStd::string();
    }

    Uuid::UuidValue Uuid::StringToValue(const TorcStd::string& uuidStr)
    {
        //m_value.m_v8 = 
    }

    //! friend function impl
    bool operator==(const Uuid& rhs, const Uuid& lhs)
    {
        return false;
    }
}
