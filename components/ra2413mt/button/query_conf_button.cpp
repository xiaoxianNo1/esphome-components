#include "query_conf_button.h"

namespace esphome
{
    namespace ra2413mt
    {

        void QueryConfButton::press_action() { this->parent_->get_config(); }

    } // namespace ra2413mt
} // namespace esphome