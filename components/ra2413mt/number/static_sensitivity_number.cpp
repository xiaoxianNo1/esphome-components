#include "static_sensitivity_number.h"

namespace esphome
{
    namespace ra2413mt
    {

        void StaticSensitivityNumber::control(float value)
        {
            this->publish_state(value);
            this->parent_->static_sensitivity();
        }

    } // namespace ra2413mt
} // namespace esphome
