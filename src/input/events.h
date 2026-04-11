#ifndef _EVENTS_H_
#define _EVENTS_H_

enum class EventType {
    KeyPress, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved
};

struct Event {
    EventType type;
    int key;
};

#endif /* _EVENTS_H_ */
