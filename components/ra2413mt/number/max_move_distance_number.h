#pragma once

#include "esphome/components/number/number.h"
#include "../ra2413mt.h"

namespace esphome
{
    namespace ra2413mt
    {

        class MaxMoveDistanceNumber : public number::Number, public Parented<RA2413MTComponent>
        {
        public:
            MaxMoveDistanceNumber() = default;

        protected:
            void control(float value) override;
        };

    } // namespace ra2413mt
} // namespace esphome
