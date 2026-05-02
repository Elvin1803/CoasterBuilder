#ifndef FRAME_H
#define FRAME_H

namespace UI {

    class Frame {
    public:
        Frame() = default;
        virtual ~Frame() = default;

        virtual void Render() = 0;
    };

}

#endif /* FRAME_H */
