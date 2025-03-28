import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_THROTTLE, CONF_TIMEOUT, CONF_PASSWORD
from esphome import automation
from esphome.automation import maybe_simple_id

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@sebcaps", "@regevbr"]
MULTI_CONF = True

ra2413mt_ns = cg.esphome_ns.namespace("ra2413mt")
RA2413MTComponent = ra2413mt_ns.class_("RA2413MTComponent", cg.Component, uart.UARTDevice)

CONF_RA2413MT_ID = "ra2413mt_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RA2413MTComponent),
    cv.Optional(CONF_THROTTLE, default="1000ms"): cv.All(
        cv.positive_time_period_milliseconds,
        cv.Range(min=cv.TimePeriod(milliseconds=1)),
    ),
    cv.Optional(CONF_TIMEOUT): cv.invalid(
        f"The '{CONF_TIMEOUT}' option has been moved to the '{CONF_TIMEOUT}'"
        f" number component"
    ),
})

CONFIG_SCHEMA = cv.All(
    CONFIG_SCHEMA.extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "ra2413mt",
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    cg.add(var.set_throttle(config[CONF_THROTTLE]))


CALIBRATION_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(RA2413MTComponent),
    }
)