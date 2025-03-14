#include <r_ioport.h>
#include "r_opamp.h"

static opamp_instance_ctrl_t g_opamp_ctrl;
static opamp_extended_cfg_t extended_cfg;
static const opamp_cfg_t g_opamp_cfg = {
  .p_extend = &extended_cfg
};
static ioport_instance_ctrl_t my_io_ctr;

#define OPAMP_EXAMPLE_CHANNEL (0U)

/* demonstrates configuring OPAMP channel 0 for high speed mode,
 * starting the OPAMP 
 * and reading the status of the OPAMP channel running.
 */

void setup() {
  Serial.begin(9600);
  delay(2000);
  fsp_err_t err;

  // Pin Mapping for OPAMP:
  // Plus: A1 (Renesas P0.00)
  // Minus: A2 (Renesas P0.01)
  // Output: A3 (Renesas P0.02)

  // Initialize thesepins to special function mode
  const ioport_pin_cfg_t  pindesc[] = {
    {IOPORT_CFG_PORT_DIRECTION_INPUT | IOPORT_CFG_PERIPHERAL_PIN | IOPORT_CFG_ANALOG_ENABLE, BSP_IO_PORT_00_PIN_00},
    {IOPORT_CFG_PORT_DIRECTION_INPUT | IOPORT_CFG_PERIPHERAL_PIN | IOPORT_CFG_ANALOG_ENABLE, BSP_IO_PORT_00_PIN_01},
    {IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PERIPHERAL_PIN | IOPORT_CFG_ANALOG_ENABLE, BSP_IO_PORT_00_PIN_02 }
  };
  const ioport_cfg_t pincfg = {
    .number_of_pins = sizeof(pindesc) / sizeof(*pindesc),
    .p_pin_cfg_data = pindesc
  };
  err = R_IOPORT_Open(&my_io_ctr, &pincfg);
  if(err != FSP_SUCCESS) {
    Serial.println("IOPORT_Open failed: " + String((int) err));
    return;
  } else {
    Serial.println("IOPORT_Open OK.");
  }

  // Startup of OPAMP and config
  extended_cfg.mode = OPAMP_MODE_HIGH_SPEED;
  extended_cfg.trigger_channel_0 = OPAMP_TRIGGER_SOFTWARE_START_SOFTWARE_STOP;
  // (this is actually ignored becauase BSP_FEATURE_OPAMP_HAS_SWITCHES is 0)
  extended_cfg.output_select_opamp0 = OPAMP_OUTPUT_AMPOS0; // P002 is "AMP0O", see datasheet
  extended_cfg.minus_input_select_opamp0 = OPAMP_MINUS_INPUT_AMPMS0; //P001 is "AMP0-"
  extended_cfg.plus_input_select_opamp0 = OPAMP_PLUS_INPUT_AMPPS0; // P000 is "AMP0+"

  err = R_OPAMP_Open(&g_opamp_ctrl, &g_opamp_cfg);
  if(err != FSP_SUCCESS) {
    Serial.println("OPAMP_Open failed: " + String((int) err));
    return;
  } else {
    Serial.println("OPAMP_Open OK.");
  }

  /* Start the OPAMP module. */
  err = R_OPAMP_Start(&g_opamp_ctrl, 1 << OPAMP_EXAMPLE_CHANNEL);
  if(err != FSP_SUCCESS) {
    Serial.println("OPAMP_Start failed: " + String((int) err));
    return;
  } else {
    Serial.println("OPAMP_Start OK.");
  }

  /* Look up the required stabilization wait time. */
  opamp_info_t info;
  err = R_OPAMP_InfoGet(&g_opamp_ctrl, &info);
  if(err != FSP_SUCCESS) {
    Serial.println("OPAMP_InfoGet failed: " + String((int) err));
    return;
  }
  Serial.println("Waiting minimum stabilization time in uS: " + String(info.min_stabilization_wait_us));

  /* Wait for the OPAMP to stabilize. */
  delayMicroseconds(info.min_stabilization_wait_us);
}

void loop() {
  int v = analogRead(A0);
  int u = analogRead(A5);
  Serial.print("in: ");
  Serial.print(v);
  Serial.print("\t out:");
  Serial.println(u);
  delay(100);
}