#include "move_sensitivity_number.h"

namespace esphome
{
    namespace ra2413mt
    {

        void MoveSensitivityNumber::control(float value)
        {
            this->publish_state(value);
            this->parent_->move_sensitivity();
        }

    } // namespace ra2413mt
} // namespace esphome
