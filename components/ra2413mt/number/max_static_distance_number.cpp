#include "max_static_distance_number.h"

namespace esphome
{
    namespace ra2413mt
    {

        void MaxStaticDistanceNumber::control(float value)
        {
            this->publish_state(value);
            this->parent_->max_static_distance();
        }

    } // namespace ra2413mt
} // namespace esphome
