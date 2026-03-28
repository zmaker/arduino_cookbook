/* SECTION: Summary
 *  
 * Use PCNT module to count rising edges generated externally or internally by ESP32 LEDC module.
 *
 * Functionality of relevant GPIOs:
 *   - GPIO18 - output pin of internal 1 Hz pulse generator.
 *   - GPIO4 - pulse input pin,
 *   - GPIO5 - control input pin.
 *
 * Upload example, open the serial monitor to view the message printed on your screen.
 * You may need to unplug and replug the USB after uploading to view in the serial monitor
 *
 * To do this test, you should connect GPIO18 with GPIO4 or connect an external pulse generator to GPIO4.
 * GPIO5 is the control signal, you can leave it floating with internal pull up,
 * or connect it to ground. If left floating, the count value will be increasing.
 * If you connect GPIO5 to GND, the count value will be decreasing.
 *
 * An interrupt will be triggered when the counter value:
 *   - reaches 'thresh1' or 'thresh0' value,
 *   - reaches 'l_lim' value or 'h_lim' value,
 *   - will be reset to zero.
 */

/* SECTION: Pulse Counter Libraries & Definitions */
#include "driver/pcnt.h"

#define PCNT_TEST_UNIT      PCNT_UNIT_0
#define PCNT_H_LIM_VAL      0x7FFF        // Max count value
#define PCNT_L_LIM_VAL     -10
#define PCNT_THRESH1_VAL    1             // Trigger an interrupt after this many counts
#define PCNT_THRESH0_VAL   -1
#define PCNT_INPUT_SIG_IO   4             // Pulse Input GPIO
#define PCNT_INPUT_CTRL_IO  5             // Control GPIO HIGH=count up, LOW=count down
#define PCNT_RUN_DURATION   100  //  For how long do you want to count pulses?

typedef struct {      // Sample structure to pass events from PCNT interrupt handler to main program
    int unit;         // the PCNT unit that originated an interrupt
    uint32_t status;  // information on the event type that caused the interrupt
} pcnt_evt_t;

/* SECTION: pcnt_init function */
/* Initialize PCNT functions:
 *  - configure and initialize PCNT
 *  - set up the input filter
 *  - set up the counter events to watch
 */
static void pcnt_init_and_start(void)
{
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config;
    // Set PCNT input signal and control GPIOs
    pcnt_config.pulse_gpio_num = PCNT_INPUT_SIG_IO;
    pcnt_config.ctrl_gpio_num  = PCNT_INPUT_CTRL_IO;
    pcnt_config.channel        = PCNT_CHANNEL_0;
    pcnt_config.unit           = PCNT_TEST_UNIT;
    // What to do on the positive / negative edge of pulse input?
    pcnt_config.pos_mode       = PCNT_COUNT_INC;   // Count up on the positive edge
    pcnt_config.neg_mode       = PCNT_COUNT_DIS;   // Keep the counter value on the negative edge
    // What to do when control input is low or high?
    pcnt_config.lctrl_mode     = PCNT_MODE_REVERSE; // Reverse counting direction if low
    pcnt_config.hctrl_mode     = PCNT_MODE_KEEP;    // Keep the primary counter mode if high
    // Set the maximum and minimum limit values to watch
    pcnt_config.counter_h_lim  = PCNT_H_LIM_VAL;
    pcnt_config.counter_l_lim  = PCNT_L_LIM_VAL;

    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);

    /* [Optional] Configure and enable the input filter (to filter glitches */
    //pcnt_set_filter_value(PCNT_TEST_UNIT, 100);
    //pcnt_filter_enable(PCNT_TEST_UNIT);

    /* [Optional] Set threshold 0 and 1 values and enable events to watch */
    pcnt_set_event_value(PCNT_TEST_UNIT, PCNT_EVT_THRES_1, PCNT_THRESH1_VAL);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_THRES_1);
    pcnt_set_event_value(PCNT_TEST_UNIT, PCNT_EVT_THRES_0, PCNT_THRESH0_VAL);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_THRES_0);
    /* [Optional] Enable events on zero, maximum and minimum limit values */
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_ZERO);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_H_LIM);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_L_LIM);

    /* Initialize PCNT's counter */
    pcnt_counter_pause(PCNT_TEST_UNIT);
    pcnt_counter_clear(PCNT_TEST_UNIT);

    /* [Optional] Register ISR handler and enable interrupts for PCNT unit */
    //pcnt_isr_register(pcnt_example_intr_handler, NULL, 0, &user_isr_handle);
    //pcnt_intr_enable(PCNT_TEST_UNIT);

    /* Everything is set up, now go to counting */
    pcnt_counter_resume(PCNT_TEST_UNIT);
}

static void pcnt_clear() {
          pcnt_counter_pause(PCNT_TEST_UNIT);
          pcnt_counter_clear(PCNT_TEST_UNIT);
}

static int pcnt_get(int16_t* pcount) {
          int16_t count = pcnt_get_counter_value(PCNT_TEST_UNIT, pcount);
          return count;
}