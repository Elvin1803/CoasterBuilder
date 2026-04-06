#ifdef DEBUG

#ifndef COASTER_TEST_H
#define COASTER_TEST_H

#include "scene/entity.h"
#include "coaster/track.h"

namespace scene {

    class CoasterTest : public Entity {

    public:
        CoasterTest();

        virtual void Update(float timestep) override;

    private:
        Track m_track;
    };
}

#endif // COASTER_TEST_H

#endif // DEBUG
