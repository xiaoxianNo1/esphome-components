import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import (
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_BLUETOOTH,
)
from . import CONF_RA2413MT_ID, RA2413MTComponent

DEPENDENCIES = ["ra2413mt"]
CONF_STATUS = "status"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_RA2413MT_ID): cv.use_id(RA2413MTComponent),
    cv.Optional(CONF_STATUS): text_sensor.text_sensor_schema(
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC, icon=ICON_BLUETOOTH
    ),
}

async def to_code(config):
    ra2413mt_component = await cg.get_variable(config[CONF_RA2413MT_ID])
    if status_config := config.get(CONF_STATUS):
        sens = await text_sensor.new_text_sensor(status_config)
        cg.add(ra2413mt_component.set_status_text_sensor(sens))