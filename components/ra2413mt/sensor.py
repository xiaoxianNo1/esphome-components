import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_POWER_FACTOR ,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_DURATION ,
    UNIT_CENTIMETER,
    UNIT_PERCENT,
    UNIT_EMPTY,
    UNIT_MINUTE,
    ICON_SIGNAL,
    ICON_MOTION_SENSOR,
    ICON_ACCELERATION_X ,
    ICON_ACCELERATION_Y ,
    ICON_ACCELERATION_Z ,
    ICON_COUNTER ,
    
)
from . import CONF_RA2413MT_ID, RA2413MTComponent

DEPENDENCIES = ["ra2413mt"]

CONF_MAX_MOVE_DISTANCE = "max_move_distance"
CONF_MAX_STATIC_DISTANCE ="max_static_distance"
CONF_MOVE_SENSITIVITY ="move_sensitivity"
CONF_STATIC_SENSITIVITY ="static_sensitivity"
CONF_UNATTENDED_DURATION ="unattended_duration"
CONF_MOVE_DISTANCE = "move_distance"
CONF_MOVE_ENERGY ="move_energy"
CONF_STATIC_DISTANCE = "static_distance"
CONF_STATIC_ENERGY = "static_energy"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_RA2413MT_ID): cv.use_id(RA2413MTComponent),
    cv.Optional(CONF_MAX_MOVE_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_POWER_FACTOR,
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_SIGNAL,
        ),
    cv.Optional(CONF_MAX_STATIC_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_SIGNAL,
        ),
    cv.Optional(CONF_MOVE_SENSITIVITY): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_ACCELERATION_X,
        ),
    cv.Optional(CONF_STATIC_SENSITIVITY): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_ACCELERATION_Y,
        ),
    cv.Optional(CONF_UNATTENDED_DURATION): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_ACCELERATION_Z,
        ),
    cv.Optional(CONF_MOVE_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_SIGNAL,
        ),
    cv.Optional(CONF_MOVE_ENERGY): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            icon=ICON_ACCELERATION_X,
        ),
    cv.Optional(CONF_STATIC_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_ACCELERATION_Y,
        ),
    cv.Optional(CONF_STATIC_ENERGY): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            icon=ICON_ACCELERATION_Z,
        ),
})

async def to_code(config):
    ra2413mt_component = await cg.get_variable(config[CONF_RA2413MT_ID])
    if max_move_distance_config := config.get(CONF_MAX_MOVE_DISTANCE):
        sens = await sensor.new_sensor(max_move_distance_config)
        cg.add(ra2413mt_component.set_max_move_distance_sensor(sens))
    if max_static_distance_config := config.get(CONF_MAX_STATIC_DISTANCE):
        sens = await sensor.new_sensor(max_static_distance_config)
        cg.add(ra2413mt_component.set_max_static_distance_sensor(sens))
    if move_sensitivity_config := config.get(CONF_MOVE_SENSITIVITY):
        sens = await sensor.new_sensor(move_sensitivity_config)
        cg.add(ra2413mt_component.set_move_sensitivity_sensor(sens))
    if static_sensitivity_config := config.get(CONF_STATIC_SENSITIVITY):
        sens = await sensor.new_sensor(static_sensitivity_config)
        cg.add(ra2413mt_component.set_static_sensitivity_sensor(sens))
    if unattended_duration_config := config.get(CONF_UNATTENDED_DURATION):
        sens = await sensor.new_sensor(unattended_duration_config)
        cg.add(ra2413mt_component.set_unattended_duration_sensor(sens))
    if move_distance_config := config.get(CONF_MOVE_DISTANCE):
        sens = await sensor.new_sensor(move_distance_config)
        cg.add(ra2413mt_component.set_move_distance_sensor(sens))
    if move_energy_config := config.get(CONF_MOVE_ENERGY):
        sens = await sensor.new_sensor(move_energy_config)
        cg.add(ra2413mt_component.set_move_energy_sensor(sens))
    if static_distance_config := config.get(CONF_STATIC_DISTANCE):
        sens = await sensor.new_sensor(static_distance_config)
        cg.add(ra2413mt_component.set_static_distance_sensor(sens))
    if static_energy_config := config.get(CONF_STATIC_ENERGY):
        sens = await sensor.new_sensor(static_energy_config)
        cg.add(ra2413mt_component.set_static_energy_sensor(sens))
    
    