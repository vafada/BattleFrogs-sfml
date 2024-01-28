#ifndef BATTLEFROGS_SFML_ENTITY_H
#define BATTLEFROGS_SFML_ENTITY_H

namespace battlefrogs {

    class Entity {
    protected:
        float horizontalSpeed = 8.0f;
        float friction = 0.35f;
        float gravity = 0.75f;
        float jumpSpeed = 30.0f * gravity;

    public:
        enum FACING {
            FACING_LEFT,
            FACING_RIGHT,
        };
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_ENTITY_H
