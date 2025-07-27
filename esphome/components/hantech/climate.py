import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate_ir

# adapted from https://github.com/esphome/esphome/blob/e7d819a6564483a67f1df4a0446e386d2109c8fe/esphome/components/delonghi/climate.py
# dev documentation https://developers.esphome.io/architecture/components/#python-module-structure

AUTO_LOAD = ["climate_ir"]

hantech_ns = cg.esphome_ns.namespace("hantech")
HantechClimate = hantech_ns.class_("HantechClimate", climate_ir.ClimateIR)

CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(HantechClimate)


async def to_code(config):
    await climate_ir.new_climate_ir(config)