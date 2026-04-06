#ifndef _STATIONSECTION_H_
#define _STATIONSECTION_H_

#include "section.h"

class StationSection : public Section
{
public:
    StationSection();
    ~StationSection();

    void SetExitSpeed(float speed) { m_exitSpeed = speed; }

    virtual void CalculateNodes(ForceData data) override;
    virtual void CalculateNodes(DirectionData data) override;
    virtual void CalculateNodes(CurveData data) override;

private:
    float m_exitSpeed; // m/s
};

#endif /* _STATIONSECTION_H_ */
