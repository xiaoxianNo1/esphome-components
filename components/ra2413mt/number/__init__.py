import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_ILLUMINANCE,
    DEVICE_CLASS_DISTANCE,   
    ENTITY_CATEGORY_CONFIG,
    ICON_TIMELAPSE,
    ICON_LIGHTBULB,
    ICON_MOTION_SENSOR,
)
from .. import CONF_RA2413MT_ID, RA2413MTComponent, ra2413mt_ns

MaxMoveDistanceNumber = ra2413mt_ns.class_("MaxMoveDistanceNumber", number.Number)
MaxStaticDistanceNumber = ra2413mt_ns.class_("MaxStaticDistanceNumber", number.Number)
UnattendedDurationNumber = ra2413mt_ns.class_("UnattendedDurationNumber", number.Number)
MoveSensitivityNumber = ra2413mt_ns.class_("MoveSensitivityNumber", number.Number)
StaticSensitivityNumber = ra2413mt_ns.class_("StaticSensitivityNumber", number.Number)

CONF_MAX_MOVE_DISTANCE = "max_move_distance"
CONF_MAX_STATIC_DISTANCE = "max_static_distance"
CONF_UNATTENDED_DURATION = "unattended_duration"
CONF_MOVE_SENSITIVITY = "move_sensitivity"
CONF_STATIC_SENSITIVITY = "static_sensitivity"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_RA2413MT_ID): cv.use_id(RA2413MTComponent),
    cv.Optional(CONF_MAX_MOVE_DISTANCE): number.number_schema(
            MaxMoveDistanceNumber,
            device_class=DEVICE_CLASS_DISTANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_MOTION_SENSOR,
        ),
    cv.Optional(CONF_MAX_STATIC_DISTANCE): number.number_schema(
            MaxStaticDistanceNumber,
            device_class=DEVICE_CLASS_DISTANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_MOTION_SENSOR,
        ),
    cv.Optional(CONF_UNATTENDED_DURATION): number.number_schema(
            UnattendedDurationNumber,
            device_class=DEVICE_CLASS_ILLUMINANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_TIMELAPSE,
        ),
    cv.Optional(CONF_MOVE_SENSITIVITY): number.number_schema(
            MoveSensitivityNumber,
            device_class=DEVICE_CLASS_DISTANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_MOTION_SENSOR,
        ),
    cv.Optional(CONF_STATIC_SENSITIVITY): number.number_schema(
            StaticSensitivityNumber,
            device_class=DEVICE_CLASS_DISTANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_MOTION_SENSOR,
        ),
})

async def to_code(config):
    ra2413mt_component = await cg.get_variable(config[CONF_RA2413MT_ID])
    if max_move_distance_config := config.get(CONF_MAX_MOVE_DISTANCE):
        n = await number.new_number(
            max_move_distance_config, min_value=2, max_value=6, step=1
        )
        await cg.register_parented(n, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_max_move_distance_number(n))
    if max_static_distance_config := config.get(CONF_MAX_STATIC_DISTANCE):
        n = await number.new_number(
            max_static_distance_config, min_value=2, max_value=6, step=1
        )
        await cg.register_parented(n, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_max_static_distance_number(n))
    if unattended_duration_config := config.get(CONF_UNATTENDED_DURATION):
        n = await number.new_number(
            unattended_duration_config, min_value=0, max_value=65535, step=1
        )
        await cg.register_parented(n, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_unattended_duration_number(n))
    if move_sensitivity_config := config.get(CONF_MOVE_SENSITIVITY):
        n = await number.new_number(
            move_sensitivity_config, min_value=1, max_value=100, step=1
        )
        await cg.register_parented(n, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_move_sensitivity_number(n))
    if static_sensitivity_config := config.get(CONF_STATIC_SENSITIVITY):
        n = await number.new_number(
            static_sensitivity_config, min_value=1, max_value=100, step=1
        )
        await cg.register_parented(n, config[CONF_RA2413MT_ID])
        cg.add(ra2413mt_component.set_static_sensitivity_number(n))
    