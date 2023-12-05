  #include <libpynq.h>
  #include <stdio.h>
// grade 10/10

  int main(void) {
    pynq_init();
    leds_init_onoff();         
    
    int delay_msec;

    printf("Wait for how many milliseconds? ");
    scanf("%d", &delay_msec);

    if (delay_msec <= 0) {

      printf("The number of milliseconds should be atleast 0.\n");
      return EXIT_FAILURE; 
    } 

    int NUM_GREEN_LEDS = 4;
    int num_cycles = 20;
    int cycles = 0;

    do {
      int i = 0;
      while (i < NUM_GREEN_LEDS) {
        green_led_onoff(i, LED_ON);
        sleep_msec(delay_msec);
        green_led_onoff(i,LED_OFF);
        i++;
      }

      i = NUM_GREEN_LEDS - 2;
      while (i > 0) {
        green_led_onoff(i, LED_ON);
        sleep_msec(delay_msec);
        green_led_onoff(i, LED_OFF);
        i--;
      }
      cycles++;
    } while (cycles < num_cycles);
    
    for (int i = 0; i < NUM_GREEN_LEDS; i++) {
      green_led_onoff(i, LED_OFF);
    }

    leds_destroy();
    pynq_destroy();

    return EXIT_SUCCESS;

  }
 