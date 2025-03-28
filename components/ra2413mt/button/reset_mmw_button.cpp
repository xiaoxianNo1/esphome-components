#include "reset_mmw_button.h"

namespace esphome
{
    namespace ra2413mt
    {

        void ResetMmwButton::press_action() { this->parent_->reset_mmw(); }

    } // namespace ra2413mt
} // namespace esphome