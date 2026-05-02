#ifndef _TRACKEDITOR_H_
#define _TRACKEDITOR_H_

#include "graphics/2d/frame.h"

#include "coaster/track.h"

namespace UI {

    class TrackEditor : public Frame
    {
    public:
        virtual void Render() override;

        void SetTrack(Track* track) { m_track = track;} ;

    private:
        Track* m_track = nullptr;
        CurveData m_curveData{10, 0, 0, 0};
    };


}

#endif /* _TRACKEDITOR_H_ */
