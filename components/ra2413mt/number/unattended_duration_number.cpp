#include "unattended_duration_number.h"

namespace esphome
{
    namespace ra2413mt
    {

        void UnattendedDurationNumber::control(float value)
        {
            this->publish_state(value);
            this->parent_->unattended_duration();
        }

    } // namespace ra2413mt
} // namespace esphome
