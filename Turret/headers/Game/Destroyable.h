#pragma once

class Destroyable {
public:
    Destroyable(bool p_bDestroyed);
    virtual bool getDestroyed();
	virtual void setDestroyed(bool p_bDestroyed) { m_bDestroyed = p_bDestroyed; }

protected:
    bool m_bDestroyed{ false };
};
