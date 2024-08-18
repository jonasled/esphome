import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import display, spi
from esphome.const import (
    CONF_ID,
    CONF_LAMBDA,
    CONF_PAGES,
    CONF_CS_PIN,
    CONF_CONTRAST,
)

DEPENDENCIES = ["spi"]

uc1617_ns = cg.esphome_ns.namespace("UC1617")
uc1617 = uc1617_ns.class_(
    "UC1617", cg.PollingComponent, display.DisplayBuffer, spi.SPIDevice
)


CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(uc1617),
            cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,  # CE
            cv.Optional(CONF_CONTRAST, default=0x7F): cv.int_,
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema()),
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await display.register_display(var, config)
    await spi.register_spi_device(var, config)

    cg.add(var.set_contrast(config[CONF_CONTRAST]))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(display.DisplayRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))