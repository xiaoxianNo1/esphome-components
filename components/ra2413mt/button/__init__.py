import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_RESTART,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_RESTART,
    ICON_DATABASE,
)
from .. import CONF_RA2413MT_ID, RA2413MTComponent, ra2413mt_ns

QueryConfButton = ra2413mt_ns.class_("QueryConfButton", button.Button)
ResetMmwButton = ra2413mt_ns.class_("ResetMmwButton", button.Button)

CONF_QUERY_CONF = "query_conf"
CONF_RESET_MMW = "reset_mmw"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_RA2413MT_ID): cv.use_id(RA2413MTComponent),
    cv.Optional(CONF_QUERY_CONF): button.button_schema(
        QueryConfButton,
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        icon=ICON_DATABASE,
    ),
    cv.Optional(CONF_RESET_MMW): button.button_schema(
        ResetMmwButton,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        icon=ICON_RESTART,
    ),
    
}

async def to_code(config):
    ra2413mt_component = await cg.get_variable(config[CONF_RA2413MT_ID])
    if query_conf_config := config.get(CONF_QUERY_CONF):
        b = await button.new_button(query_conf_config)
        await cg.register_parented(b, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_query_conf_button(b))
    if reset_mmw_config := config.get(CONF_RESET_MMW):
        b = await button.new_button(reset_mmw_config)
        await cg.register_parented(b, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_reset_mmw_button(b))
