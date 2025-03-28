#include "max_move_distance_number.h"

namespace esphome
{
    namespace ra2413mt
    {

        void MaxMoveDistanceNumber::control(float value)
        {
            this->publish_state(value);
            this->parent_->max_move_distance();
        }

    } // namespace ra2413mt
} // namespace esphome
