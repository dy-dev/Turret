#include "Game/Destroyable.h"

Destroyable::Destroyable(bool p_bDestroyed)
    :m_bDestroyed{ p_bDestroyed }
{

}
bool Destroyable::getDestroyed()
{
    return m_bDestroyed;
};