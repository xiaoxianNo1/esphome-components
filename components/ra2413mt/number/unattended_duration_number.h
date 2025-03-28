#pragma once

#include "esphome/components/number/number.h"
#include "../ra2413mt.h"

namespace esphome
{
    namespace ra2413mt
    {

        class UnattendedDurationNumber : public number::Number, public Parented<RA2413MTComponent>
        {
        public:
            UnattendedDurationNumber() = default;

        protected:
            void control(float value) override;
        };

    } // namespace ra2413mt
} // namespace esphome
