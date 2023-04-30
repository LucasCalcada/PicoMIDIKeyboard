#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "midi_config.h"

/* 
    Blink pattern
        250 ms  : device not mounted
        1000 ms : device mounted
        2500 ms : device is suspended
*/

enum{
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500
};
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

int8_t octaveOffset = INITIAL_OCTAVE_OFFSET;
int8_t maxOffset = 8 - OCTAVE_AMMOUNT;
bool lastNOTES[12 * OCTAVE_AMMOUNT];

void led_blinking_task(void);

void midi_task(void);

void change_octaves_task(void);

int main(void)
{
    board_init();

    // setup keys PINS
    for (int i = 0; i < 12 * OCTAVE_AMMOUNT; i++)
    {
        gpio_init(PINS[i]);
        gpio_set_dir(PINS[i], false);
    }

    // setup octave change PINS
    gpio_init(OCTAVE_UP);
    gpio_set_dir(OCTAVE_UP, false);
    gpio_init(OCTAVE_DOWN);
    gpio_set_dir(OCTAVE_DOWN, false);
    
    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    while (1)
    {
        tud_task();
        led_blinking_task();
        midi_task();
        change_octaves_task();
    }
    return 0;
}

/*
    MIDI Keypress task
*/
void midi_task(void)
{
    static uint32_t start_ms = 0;

    // The MIDI interface always creates input and output port/jack descriptors
    // regardless of these being used or not. Therefore incoming traffic should be read
    // (possibly just discarded) to avoid the sender blocking in IO
    uint8_t packet[4];
    while ( tud_midi_available() ) tud_midi_packet_read(packet);

    // Interval to prevent double clicks
    if (board_millis() - start_ms < TASK_INTERVAL) return;
    start_ms += TASK_INTERVAL;

    for (int i = 0; i < 12 * OCTAVE_AMMOUNT; i++)
    {
        bool press = gpio_get(PINS[i]);
        uint8_t noteNum = NOTES[i] + octaveOffset * 12; // Note numerical value
        if(press && !lastNOTES[i]){
            uint8_t note_on[3] = {
                0x90 | MIDI_CHANNEL,
                noteNum,  // Note numerical value
                127       // Note speed
            };
            tud_midi_stream_write(MIDI_JACK, note_on, 3); // Send active note out
        }
        else if (!press && lastNOTES[i]){
            uint8_t note_off[3] = {
                0x80 | MIDI_CHANNEL,
                noteNum,  // Note numerical value
                0         // Note speed
            };
            tud_midi_stream_write(MIDI_JACK, note_off, 3); // Send inactive note out
        }
        lastNOTES[i] = press;
    }
}

/*
    OFFSET OCTAVES
*/
int8_t octaveBtnLastVals[2];
void change_octaves_task(void){
    // Interval to prevent double clicks
    static u_int32_t start_ms = 0;
    if (board_millis() - start_ms < TASK_INTERVAL) return;
    start_ms += TASK_INTERVAL;

    bool octUp = gpio_get(OCTAVE_UP);
    bool octDwn = gpio_get(OCTAVE_DOWN);

    if(octDwn && !octaveBtnLastVals[0]) octaveOffset -= 1;
    if(octUp && !octaveBtnLastVals[1]) octaveOffset += 1;

    // Clamps offset value
    if(octaveOffset < 0) octaveOffset = 0;
    if(octaveOffset > maxOffset) octaveOffset = maxOffset;

    // Update last button values
    octaveBtnLastVals[0] = octDwn;
    octaveBtnLastVals[1] = octUp;
}

/*
    BLINK STATUS
*/
void led_blinking_task(void)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    // Blink every interval ms
    if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
    start_ms += blink_interval_ms;

    board_led_write(led_state);
    led_state = 1 - led_state; // toggle
}

/*
    DEVICE CALLBACKS
*/
// Invoked when device is mounted
void tud_mount_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void) remote_wakeup_en;
    blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}