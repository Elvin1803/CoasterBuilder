#ifndef _EVENTS_H_
#define _EVENTS_H_

namespace Events {

    enum class EventType {
        KeyPress, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved
    };

    struct Event {
        EventType type;
        int key;
        bool handled = false;
    };


} // Events

#endif /* _EVENTS_H_ */
